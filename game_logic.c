#include "types.h"

//Gets player-piece color and returns relavant string
const char* colorToString(Color color) {
    switch (color) {
        case YELLOW:
            return "Yellow";
        case BLUE:
            return "Blue";
        case RED:
            return "Red";
        case GREEN:
            return "Green";
        default:
            return "Unknown";
    }
}

//Gets player-piece color and returns relavant string
const char* directionToString(Direction direction) {
    switch (direction) {
        case Clockwise:
            return "clockwise"; //head == 0
        case Counter_Clockwise:
            return "counter_clockwise"; //tail == 1
        
        default:
            return "up-side-down";
    }
}

//the dice roll function for the entire game.
int rollDice() {
    return rand() % 6 + 1;
}

int coin(){
    return rand() % 2;
}

//inititalize player+piece struct elements. inlcuded: before game loop starts 
void initializePlayers(Player players[NUM_PLAYERS]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].color = (Color)i;
        players[i].num_pieces_on_board = 0;
        players[i].num_pieces_in_base = NUM_PIECES;
        players[i].num_pieces_in_home = 0;
        players[i].win = 0;

        if (players[i].color == YELLOW){players[i].approach_postition = 52;}
        if (players[i].color == BLUE){players[i].approach_postition = 65;}
        if (players[i].color == RED){players[i].approach_postition = 78;}
        if (players[i].color == GREEN){players[i].approach_postition = 91;}
        
        for (int j = 0; j < NUM_PIECES; j++) {
            players[i].pieces[j].id = j;
            players[i].pieces[j].status = IN_BASE;
            players[i].pieces[j].position = -1;
            players[i].pieces[j].color = players[i].color;
            players[i].pieces[j].capture_count = 0;
            players[i].pieces[j].direction = coin();
        }
    }
}

void initializeBoard(Board *board) {
    board->mystery_cell_position = rand() % BOARD_SIZE;
}

void printBoard(Board *board) {
    printf("\n=== Board Status ===\n");
    printf("Mystery Cell Position: %d\n", board->mystery_cell_position);
    printf("====================\n\n");
}

//Prints each player piece status after each round, inlcuded: in the end of the game loop
void printPlayerStatus(Player players[NUM_PLAYERS]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {

        printf("=================================\n");
        printf("Location of %s player Pieces\n", colorToString(players[i].color));
        printf("=================================\n");

        //ex: Piece 2 -> On Path at position 49 
        for (int j = 0; j < NUM_PIECES; j++) {
            printf("Piece %d -> ", players[i].pieces[j].id + 1);
            switch (players[i].pieces[j].status) {
                case IN_BASE:
                    printf("In Base\n");
                    break;
                case IN_X:
                    printf("At Starting Position X\n");
                    break;
                case ON_PATH:
                    printf("On Path at L%d\n",
                        (players[i].pieces[j].position > BOARD_SIZE ? players[i].pieces[j].position - BOARD_SIZE : players[i].pieces[j].position));
                    break;
                case ON_APPROACH:
                    printf("On Approach\n");
                    break;
                case HOME_STR:
                    printf("In Home straight at L%d\n", players[i].pieces[j].position);
                    break;
                case IN_HOME:
                    printf("In Home\n");
                    break;
            }
        }
        printf("\n");
        printf("%s player now has %d/4 pieces on the board and %d/4 pieces in the base and %d/4 pieces in the home.\n", 
                colorToString(players[i].color), players[i].num_pieces_on_board, players[i].num_pieces_in_base, players[i].num_pieces_in_home);
        printf("\n");
    }
}

void printMysteryCellStatus(Board *board) {
    printf("Mystery Cell is at position %d\n", board->mystery_cell_position);
}

//move each piece upon player behaviours. inluded: playerBehavoiurs()
void movePiece(Player *player, int pieceIndex, int diceValue, Board *board) {
    Piece *piece = &player->pieces[pieceIndex]; //creates a pointer to access each player>piece struct
    int prev_location = piece->position;

    //check if the piece in the base
    if (piece->status == IN_BASE) {
        //if roll is 6, move piece to the start point(X), else ignore
        if (diceValue == 6) {
            piece->status = ON_PATH;
                
            if (player->color == YELLOW){piece->position = 2;}//2
            else if (player->color == BLUE){piece->position = 15;}//15
            else if (player->color == RED){piece->position = 28;}//28
            else if (player->color == GREEN){piece->position = 41;}//41
            
            //change on board and on base pieces count for the player
            player->num_pieces_on_board++;
            player->num_pieces_in_base--;
            
            printf("%s player moves Piece %d to the starting position.\n", colorToString(player->color), piece->id + 1);
            printf("%s player now has %d/4 pieces on the board and %d/4 pieces in the base and %d/4 pieces in the home.\n", colorToString(player->color), player->num_pieces_on_board, player->num_pieces_in_base, player->num_pieces_in_home);
            
        } else {
            printf("%s player cannot move Piece %d out of the base without rolling a 6.\n", colorToString(player->color), piece->id + 1);
        }
    }
    else if (piece->status == ON_APPROACH){
        if(piece->capture_count > 0) {
            if (diceValue == 6){
                piece->status = IN_HOME;
                piece->position = -2;
                player->num_pieces_on_board = player->num_pieces_on_board - 1;
                player->num_pieces_in_home = player->num_pieces_in_home + 1;
                printf("%s player's Piece %d has reached home!\n", colorToString(player->color), piece->id + 1);
            }
            else {
                piece->status = HOME_STR;
                piece->position = piece->position - player->approach_postition - HOME_STR_SIZE;
                printf("%s player's Piece %d capture count is %d and enters to the Home_Straight:\n", colorToString(player->color), piece->id + 1, piece->capture_count);
                printf("\t%s player's Piece %d now is in the Home_Straight at L%d.\n", colorToString(player->color), piece->id + 1, piece->position);
            }
        }
        else {
                piece->status = ON_PATH;
                piece->position = piece->position - BOARD_SIZE;
                printf("%s player's Piece %d capture count is %d, so couldn't enter to the Home_Straight and left the approch:\n", colorToString(player->color), piece->id + 1, piece->capture_count);
                printf("\t%s player's Piece %d now is on the Path at L%d.\n", colorToString(player->color), piece->id + 1, piece->position);
        }
    }

    else if (piece->status == HOME_STR){
        int tempPost = piece->position + diceValue;

        if (tempPost == -2){
            piece->status = IN_HOME;
            piece->position = -2;
            player->num_pieces_on_board = player->num_pieces_on_board - 1;
            player->num_pieces_in_home = player->num_pieces_in_home + 1;

            printf("%s player's Piece %d has reached home!\n", colorToString(player->color), piece->id + 1);
        }
        else if (tempPost < -2){
            piece->position = piece->position + diceValue;
            piece->status = HOME_STR;
            printf("%s player moves Piece %d from location L%d to L%d.\n",
                    colorToString(player->color), piece->id + 1,
                    prev_location,
                    piece->position
            );
        }
        else if (tempPost > -2){
            piece->status = HOME_STR;
            printf("%s player's Piece %d cannot reach home.\n", colorToString(player->color), piece->id + 1);
        }
    }

    //check if the piece on the path and do move
    else if (piece->status == ON_PATH) {
        piece->position += diceValue;

        //check for the piece whether has reached 52nd/approach cell
        if (piece->position >= player->approach_postition) {
            
            if (piece->position == player->approach_postition){
                piece->status = ON_APPROACH;
                printf("%s player's Piece %d now is in approach!\n", colorToString(player->color), piece->id + 1);
                
            }
            else if (piece->position > player->approach_postition){
                if(piece->capture_count > 0) {

                    piece->status = HOME_STR;
                    piece->position = piece->position - player->approach_postition - HOME_STR_SIZE;
                    printf("%s player's Piece %d capture count is %d and enters to the Home_Straight:\n", colorToString(player->color), piece->id + 1, piece->capture_count);
                    printf("\t%s player's Piece %d now is in the Home_Straight at L%d.\n", colorToString(player->color), piece->id + 1, piece->position);

                }
                else {
                    piece->status = ON_PATH;
                    piece->position = piece->position - BOARD_SIZE;
                    printf("%s player's Piece %d capture count is %d, so couldn't enter to the Home_Straight and pass the approch:\n", colorToString(player->color), piece->id + 1, piece->capture_count);
                    printf("\t%s player's Piece %d now is on the Path at L%d.\n", colorToString(player->color), piece->id + 1, piece->position);
                }
            }

        } else {
            printf("%s player moves Piece %d from location L%d to L%d by %d units %s direction.\n",
                    colorToString(player->color), piece->id + 1,
                    (prev_location > BOARD_SIZE) ? prev_location - BOARD_SIZE : prev_location,
                    (piece->position > BOARD_SIZE) ? piece->position - BOARD_SIZE : piece->position,
                    diceValue, directionToString(0/*piece->direction*/)
            );
            
            handleMysteryCell(piece, board);
        }

        // Check for capturing an opponent's piece
        for (int i = 0; i < NUM_PLAYERS; i++) {
            Player *opponent = &player[i]; //creates new struct pointer to assign access all player structs

            if (opponent->color != player->color) { //ensure curr_player is exclusive
                for (int j = 0; j < NUM_PIECES; j++) {
                    Piece *opponentPiece = &opponent->pieces[j]; //creates new struct pointer to assign access all pieces of particular player
                    if (opponentPiece->status == ON_PATH && opponentPiece->position == piece->position) {
                        //check for capturing upon land and execute
                        opponentPiece->status = IN_BASE;
                        opponentPiece->position = -1;
                        opponent->num_pieces_on_board--;
                        opponent->num_pieces_in_base++;
                        piece->capture_count++;
                        
                        printf("\t:%s player's Piece %d lands on L%d, captures %s player's Piece %d, and returns it back to the base!\n",
                                colorToString(player->color), piece->id + 1,
                                (piece->position > BOARD_SIZE) ? piece->position - BOARD_SIZE : piece->position,
                                colorToString(opponent->color), opponentPiece->id + 1);
                        printf("\t:%s player now has %d/4 on pieces on the board and %d/4 pieces on the base and %d/4 pieces in the home.\n",
                                        colorToString(opponent->color), opponent->num_pieces_on_board, opponent->num_pieces_in_base, opponent->num_pieces_in_home);                                                
                    }
                }
            }
        }


    }

    //just in case of repeating home_pieces.
    else if (piece->status == IN_HOME) {

        printf("%s player's Piece %d is already at home.\n", colorToString(player->color), piece->id + 1);

    }
}

void handleMysteryCell(Piece *piece, Board *board) {
    if (piece->position == board->mystery_cell_position) {
        int event = rand() % 3;
        switch (event) {
            case 0:
                piece->position += 5;
                if (piece->position >= BOARD_SIZE) {
                    piece->status = IN_HOME;
                    piece->position = -1;
                    
                    if (piece->color == YELLOW) {printf("Mystery Cell Event: Yellow player's Piece %d moved directly to home!\n", piece->id);}
                    if (piece->color == BLUE) {printf("Mystery Cell Event: Blue player's Piece %d moved directly to home!\n", piece->id);}
                    if (piece->color == RED) {printf("Mystery Cell Event: Red player's Piece %d moved directly to home!\n", piece->id);}
                    if (piece->color == GREEN) {printf("Mystery Cell Event: Green player's Piece %d moved directly to home!\n", piece->id);}
                } else {
                    printf("Mystery Cell Event: %s Player's Piece %d moved forward by 5 positions to %d.\n",
                           piece->color == RED ? "Red" :
                           piece->color == GREEN ? "Green" :
                           piece->color == YELLOW ? "Yellow" : "Blue",
                           piece->id + 1,
                           piece->position);
                }
                break;
            case 1:
                piece->position -= 3;
                if (piece->position < 0) {piece->position = 0;}
                printf("Mystery Cell Event: %s Player's Piece %d moved backward by 3 positions to %d.\n",
                       piece->color == RED ? "Red" :
                       piece->color == GREEN ? "Green" :
                       piece->color == YELLOW ? "Yellow" : "Blue",
                       piece->id,
                       piece->position);
                break;
            case 2:
                printf("Mystery Cell Event: %s Player's Piece %d lost a turn.\n",
                       piece->color == RED ? "Red" :
                       piece->color == GREEN ? "Green" :
                       piece->color == YELLOW ? "Yellow" : "Blue",
                       piece->id);
                // Implement logic to skip next turn if needed
                break;
        }
    }
}

void yellowPlayerBehavior(Player *player, Board *board, int diceValue) {
    int consecutiveSixes = 0;

    while (1) {
        if (diceValue == 6) {
            consecutiveSixes++;
            if (consecutiveSixes == 3) {
                // Move the piece and then pass the turn to the next player
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        printf("Yellow player rolled a 6 three times. Passing turn to next player.\n");
                        return;
                    }
                }
            } else {
                // Move the piece and allow the player to roll again
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        diceValue = rollDice();
                        printf("\nYellow rolled %d for the %d time\n", diceValue, consecutiveSixes + 1);
                        
                        break;
                    }
                }
            }
        } else {
            // Move the piece and end the turn
            for (int i = 0; i < NUM_PIECES; i++) {
                if (player->pieces[i].status == ON_PATH || (player->pieces[i].status == IN_BASE && diceValue == 6) || player->pieces[i].status == ON_APPROACH || player->pieces[i].status == HOME_STR) {
                    movePiece(player, i, diceValue, board);
                    return;
                }
            }
            printf("Yellow player has no valid moves.\n");
            return;
        }
    }
}
void bluePlayerBehavior(Player *player, Board *board, int diceValue) {
    int consecutiveSixes = 0;

    while (1) {
        if (diceValue == 6) {
            consecutiveSixes++;
            if (consecutiveSixes == 3) {
                // Move the piece and then pass the turn to the next player
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        printf("Blue player rolled a 6 three times. Passing turn to next player.\n");
                        return;
                    }
                }
            } else {
                // Move the piece and allow the player to roll again
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        diceValue = rollDice();
                        printf("\nBlue rolled %d for the %d time\n", diceValue, consecutiveSixes+1);
                        break;
                    }
                }
            }
        } else {
            // Move the piece and end the turn
            for (int i = 0; i < NUM_PIECES; i++) {
                if (player->pieces[i].status == ON_PATH || (player->pieces[i].status == IN_BASE && diceValue == 6) || player->pieces[i].status == ON_APPROACH || player->pieces[i].status == HOME_STR) {
                    movePiece(player, i, diceValue, board);
                    return;
                }
            }
            printf("Blue player has no valid moves.\n");
            return;
        }
    }
}
void redPlayerBehavior(Player *player, Board *board, int diceValue) {
    int consecutiveSixes = 0;

    while (1) {
        if (diceValue == 6) {
            consecutiveSixes++;
            if (consecutiveSixes == 3) {
                // Move the piece and then pass the turn to the next player
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        printf("Red player rolled a 6 three times. Passing turn to next player.\n");
                        return;
                    }
                }
            } else {
                // Move the piece and allow the player to roll again
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        diceValue = rollDice();
                        printf("\nRed rolled %d for the %d time\n", diceValue, consecutiveSixes+1);
                        break;
                    }
                }
            }
        } else {
            // Move the piece and end the turn
            for (int i = 0; i < NUM_PIECES; i++) {
                if (player->pieces[i].status == ON_PATH || (player->pieces[i].status == IN_BASE && diceValue == 6) || player->pieces[i].status == ON_APPROACH || player->pieces[i].status == HOME_STR) {
                    movePiece(player, i, diceValue, board);
                    return;
                }
            }
            printf("Red player has no valid moves.\n");
            return;
        }
    }
}
void greenPlayerBehavior(Player *player, Board *board, int diceValue) {
    int consecutiveSixes = 0;

    while (1) {
        if (diceValue == 6) {
            consecutiveSixes++;
            if (consecutiveSixes == 3) {
                // Move the piece and then pass the turn to the next player
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        printf("Green player rolled a 6 three times. Passing turn to next player.\n");
                        return;
                    }
                }
            } else {
                // Move the piece and allow the player to roll again
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (player->pieces[i].status != IN_HOME) {
                        movePiece(player, i, diceValue, board);
                        diceValue = rollDice();
                        printf("\nGreen rolled %d for the %d time\n", diceValue, consecutiveSixes+1);
                        break;
                    }
                }
            }
        } else {
            // Move the piece and end the turn
            for (int i = 0; i < NUM_PIECES; i++) {
                if (player->pieces[i].status == ON_PATH || (player->pieces[i].status == IN_BASE && diceValue == 6) || player->pieces[i].status == ON_APPROACH || player->pieces[i].status == HOME_STR) {
                    movePiece(player, i, diceValue, board);
                    return;
                }
            }
            printf("Green player has no valid moves.\n");
            return;
        }
    }
}

int determineFirstPlayer(Player players[NUM_PLAYERS]) {
    int highestRoll = 0;
    int firstPlayer = 0;
    int rolls[NUM_PLAYERS];

    printf("Choosing the first player by dice roll...\n\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        rolls[i] = rollDice();

        printf("%s rolls %d\n",colorToString(players[i].color), rolls[i]);
        
        if (rolls[i] > highestRoll) {
            highestRoll = rolls[i];
            firstPlayer = i;
        }
    }
    printf("\n");

    // Check for ties
    int tieCount = 0;
    for (int j = 0; j < NUM_PLAYERS; j++) {
        if (rolls[j] == highestRoll) {
            tieCount++;
        }
        else continue;
    }

    if (tieCount > 1) {
        printf("Multiple max values >> Tied players Roll again...\n\n");
        return determineFirstPlayer(players);
    }
    else ;
    
    if (players[firstPlayer].color == YELLOW){
        printf("Yellow player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Yellow, Blue, Red, Green\n\n");
    }
    else if (players[firstPlayer].color == BLUE){
        printf("Blue player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Blue, Red, Green, Yellow\n\n");
    }
    else if (players[firstPlayer].color == RED){
        printf("Red player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Red, Green, Yellow, Blue\n\n");
    }
    else if (players[firstPlayer].color == GREEN){
        printf("Green player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Green, Yellow, Blue, Red\n\n");
    }

    return firstPlayer;
}
