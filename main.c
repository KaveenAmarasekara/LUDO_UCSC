#include "types.h"
#include "game_logic.c"

int main() {
    srand(time(NULL)); // Seed random number generator

    {
        printf("\n~ Welcome to LUDO UCSC | KTA-23000066 ~\n\n");
        
        printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
        printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
        printf("The red player has four (04) pieces named R1, R2, R3, and R4\n");
        printf("The green player has four (04) pieces named G1, G2, G3, and G4\n\n");
    }

    Player players[NUM_PLAYERS];
    Board board;
    int currentPlayer;
    int gameWon = 0;
    int roundNumber = 1;
    int finished = 0;

    initializePlayers(players);
    initializeBoard(&board);
    currentPlayer = determineFirstPlayer(players);

    while ((!gameWon) /*&& !(finished == 4)*/) {
        printf("\n--------- << Round %d >> --------------------------------------------------------------------------------------------\n", roundNumber);

        for (int k = 0; k < NUM_PLAYERS; k++) {
            int playerIndex = (currentPlayer + k) % NUM_PLAYERS;
            Player *player = &players[playerIndex];
            int diceValue = rollDice();

            printf("\n%s rolled %d\n", colorToString(players[playerIndex].color), diceValue);

            switch (players[playerIndex].color) {
                case YELLOW:
                    yellowPlayerBehavior(player, &board, diceValue);
                    break;
                case BLUE:
                    bluePlayerBehavior(player, &board, diceValue);
                    break;
                case RED:
                    redPlayerBehavior(player, &board, diceValue);
                    break;
                case GREEN:
                    greenPlayerBehavior(player, &board, diceValue);
                    break;
            }

            //Check win condition
            if (player->num_pieces_in_home == NUM_PIECES) {
                printf("\n*** %s player has won the game! ***\n", colorToString(players[playerIndex].color));
                gameWon = 1;
                break;
            }

            // if (player->num_pieces_in_home == NUM_PIECES && player->win == 0){
            //     if (gameWon = 0){
            //         printf("\n*** %s player has won the game! ***\n", colorToString(players[playerIndex].color));
            //         gameWon = 1;
            //         player->win = 1;
            //         //finished++;
            //     }
            //     else {
            //         //finished++;
            //         player->win = 1;
            //         printf("\n*** %s player is the %d winner! ***\n", colorToString(players[playerIndex].color), finished);
            //     }
            // }
        } 

        printBoard(&board);
        printPlayerStatus(players);
        roundNumber++;
    }

    return 0;
}
