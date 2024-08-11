#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define random rand() % 6 + 1

enum speBoardCell
{
    Base = 0,
    X = 1,
    Approach = 51
};

struct player
{
    // int color[4];
    int roll_val;
    int init_position;
    int curr_position;
    int Base;
    int X;
    int Approach;
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

// int roll(int range){

//     int value;
//     int values[10];
//     srand(time(0));
//     int j = 0;
//     for ( j < range; j++;){
//         value = rand() % 6;
//         values[j] = value;
//         //printf("%d\n,", values[j]);
//     }

//         //assigning random values to the roll-round value
//         Yellow.roll_val = values[1];
//         Blue.roll_val = values[2];
//         Red.roll_val = values[3];
//         Green.roll_val = values[4];

//     return values;
// }

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
    printf("\n");
}

int roll(int player_id)
{
    srand(time(0));
    int value;
    int order[4];
    switch (player_id)
    {
    case 0:
        Yellow.roll_val = random;
        Blue.roll_val = random;
        Red.roll_val = random;
        Green.roll_val = random;
        order[] = {Yellow.roll_val, Blue.roll_val, Red.roll_val, Green.roll_val};
        break;
    case 1:
        Blue.roll_val = random;
        Red.roll_val = random;
        Green.roll_val = random;
        Yellow.roll_val = random;
        int order[4] = {Blue.roll_val, Red.roll_val, Green.roll_val, Yellow.roll_val};
        break;
    case 2:
        Red.roll_val = random;
        Green.roll_val = random;
        Yellow.roll_val = random;
        Blue.roll_val = random;
        int order[4] = {Red.roll_val, Green.roll_val, Yellow.roll_val, Blue.roll_val};
        break;
    case 3:
        Green.roll_val = random;
        Yellow.roll_val = random;
        Blue.roll_val = random;
        Red.roll_val = random;
        int order[4] = {Green.roll_val, Yellow.roll_val, Blue.roll_val, Red.roll_val};
        break;
        // default:
        // break;
    }

    int length = sizeof(order) / sizeof(order[0]);

    // print order[]
    print_arr(order, length);

    sort_arr(order, length);

    // print sorted > order[]
    print_arr(order, length);
}

// base_move get the random dice value from the roll() and do a move for a peice
int baseMove()
{
    // if( == 0){

    // }
}

int main(void)
{
    // int value = 4;
    // int arr[4];
    // arr[2] = roll(&value);
    // printf("%d", arr[2]);
    roll(0);

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