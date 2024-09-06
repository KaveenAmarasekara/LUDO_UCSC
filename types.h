#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define BOARD_SIZE 52 //0-51
#define HOME_STR_SIZE 7

typedef enum {YELLOW, BLUE, RED, GREEN} Color;
typedef enum {IN_BASE, IN_X, ON_PATH, IN_HOME, HOME_STR, ON_APPROACH } Status;
typedef enum {Clockwise, Counter_Clockwise} Direction;

typedef struct {
    int id;
    Color color;
    Status status;
    int position;
    Direction direction;
    int capture_count;
} Piece;

typedef struct {
    Color color;
    int num_pieces_on_board;
    int num_pieces_in_base;
    int num_pieces_in_home;
    int approach_postition;
    Piece pieces[NUM_PIECES];
    int win;
} Player;

typedef struct {
    int mystery_cell_position;
} Board;


// Function prototypes
const char* colorToString(Color color);
const char* directionToString(Direction direction);

void initializePlayers(Player players[NUM_PLAYERS]);
void initializeBoard(Board *board);
void printBoard(Board *board);
void printPlayerStatus(Player players[NUM_PLAYERS]);
void printMysteryCellStatus(Board *board);

int rollDice();
int coin();
void movePiece(Player *player, int pieceIndex, int diceValue, Board *board);
void handleMysteryCell(Piece *piece, Board *board);

void redPlayerBehavior(Player *player, Board *board, int diceValue);
void greenPlayerBehavior(Player *player, Board *board, int diceValue);
void yellowPlayerBehavior(Player *player, Board *board, int diceValue);
void bluePlayerBehavior(Player *player, Board *board, int diceValue);

int determineFirstPlayer(Player players[NUM_PLAYERS]);

#endif
