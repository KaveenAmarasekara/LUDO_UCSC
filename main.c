#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define random rand() % 6 + 1

enum speBoardCell
{
    Base = 0,
    X = 1,
    Approach = 51
};

struct player
{
    int id;
    int roll_val;
    int init_position;
    int curr_position;
    int Base;
    int X;
    int Approach;
    char color[8];
    
    //
} Yellow, Blue, Red, Green;

void initBoardCells()
{
    int boardCell[52];
    for (int i = 0; i < 52; i++)
    {
        boardCell[i] = i + 1;
        printf("%d,", boardCell[i]);
    }

    enum speBoardCell currCell;

    // return boardCell;
}

// sort any array
void sort_arr(int arr[], int lenght)
{
    int i, j, temp;
    for (i = 0; i < lenght - 1; i++)
    {
        for (j = 0; j < lenght - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_arr(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int roll(int* player_id)
{
    srand(time(0));
    int order[4];
    int x = *player_id;
    switch (x)
    {
    case 0:
        order[0] = Yellow.roll_val = random;
        order[1] = Blue.roll_val = random;
        order[2] = Red.roll_val = random;
        order[3] = Green.roll_val = random;
        break;
    case 1:
        order[0] = Blue.roll_val = random;
        order[1] = Red.roll_val = random;
        order[2] = Green.roll_val = random;
        order[3] = Yellow.roll_val = random;
        break;
    case 2:
        order[0] = Red.roll_val = random;
        order[1] = Green.roll_val = random;
        order[2] = Yellow.roll_val = random;
        order[3] = Blue.roll_val = random;
        break;
    case 3:
        order[0] = Green.roll_val = random;
        order[1] = Yellow.roll_val = random;
        order[2] = Blue.roll_val = random;
        order[3] = Red.roll_val = random;
        break;
        // default:
        // break;
    }

    int length = sizeof(order) / sizeof(order[0]);

    print_arr(order, length);
}

int getMax()
{
    int arr[4] = {Yellow.roll_val, Blue.roll_val, Red.roll_val, Green.roll_val};
    int length = sizeof(arr) / sizeof(arr[0]);
    int max = arr[0];
    for (int k = 1; k <= length; k++)
    {
        if (max < arr[k])
        {
            max = arr[k];
        }
    }
    return max;
}

void getRoundStarter()
{
    roll(0);
    int max = getMax();
    {
        printf("Yellow rolls %d\n", Yellow.roll_val);
        printf("Blue rolls %d\n", Blue.roll_val);
        printf("Red rolls %d\n", Red.roll_val);
        printf("Green rolls %d\n\n", Green.roll_val);
    } 

    int id;

    if (Yellow.roll_val == max){
        printf("Yellow player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Yellow, Blue, Red, Green\n");
        id = 0;
    }
    else if (Blue.roll_val == max){
        printf("Blue player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Blue, Red, Green, Yellow\n");
        Blue.id = 1;
    }
    else if (Red.roll_val == max){
        printf("Red player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Red, Green, Yellow, Blue\n");
        Red.id  = 2;
    }
    else if (Green.roll_val == max){
        printf("Green player has the highest roll and will begin the game.\n");
        printf("The order of a single round is Green, Yellow, Blue, Red\n");
        Green.id = 3;
    }
}

// first_move get the random dice value from the roll() and do a move for a peice
int baseMove()
{
    // if( == 0){
                                  
    // }
}

int startGame(int game_state){
    if (!game_state){
        printf("Welcome to LUDO UCSC | KTA-231006\n");
        printf("\n");
    }
    char pref;
    printf("Start new game? (Y/n):");
    scanf(" %c", &pref);
    if (pref == 89 || pref == 121 || pref == 13){ //13>Enter
        game_state = 1;
        printf("\n");
    }
    if (pref == 78|| pref == 110){
        game_state = 0;
        printf("\n");
    }
    return game_state;
}

int main(void)
{
    if (startGame(0)){
        printf("Game started...\n\n");
    }
    else {
        printf("Hum, see ya next time...\n\n");
        return 0;
    }

    {
        printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
        printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
        printf("The red player has four (04) pieces named R1, R2, R3, and R4\n");
        printf("The green player has four (04) pieces named G1, G2, G3, and G4\n\n");
    }

    getRoundStarter();




    // int value = 4;
    // int arr[4];
    // arr[2] = roll(&value);
    // printf("%d", arr[2]);
    // pass orer before sort
    //getRoundStarter(order, length);

    // initBoardCells();
    // printf("%d", boardCell);

    /*struct players{
        int id;
        int p[] ;


    }Red, Yellow, Green, Blue;
    */
    // const m 2;
    //    int arr[m];
    return 0;
}