#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//#define random rand() % 6 + 1



enum speBoardCell
{
    Base = 0,
    X = 1,
    Approach = 51
};

struct player
{
    short id;
    short roll_val;

    struct peice
    {
        short curr_position; 
    } p1, p2, p3, p4;
    
    short Base;
    short X;
    short Approach;
    char color[8];
    
    //
} Yellow, Blue, Red, Green;

//begin of prototype
int baseMove(struct player, struct player, struct player, struct player);
int roll(struct player);
int checkforsix(short val);
//end of prototype


void initBoardCells()
{
    short boardCell[52];
    for (int i = 0; i < 52; i++)
    {
        boardCell[i] = i + 1;
        printf("%d,", boardCell[i]);
    }

    enum speBoardCell currCell;

    // return boardCell;
}

int random(short t){
    short value = rand() % t + 1;
    //printf("%d", value);
    return value;
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

// int roll(int* player_id)
// {
//     srand(time(0));
//     int order[4];
//     int x = *player_id;
//     switch (x)
//     {
//     case 0:
//         order[0] = Yellow.roll_val = random;
//         order[1] = Blue.roll_val = random;
//         order[2] = Red.roll_val = random;
//         order[3] = Green.roll_val = random;
//         break;
//     case 1:
//         order[0] = Blue.roll_val = random;
//         order[1] = Red.roll_val = random;
//         order[2] = Green.roll_val = random;
//         order[3] = Yellow.roll_val = random;
//         break;
//     case 2:
//         order[0] = Red.roll_val = random;
//         order[1] = Green.roll_val = random;
//         order[2] = Yellow.roll_val = random;
//         order[3] = Blue.roll_val = random;
//         break;
//     case 3:
//         order[0] = Green.roll_val = random;
//         order[1] = Yellow.roll_val = random;
//         order[2] = Blue.roll_val = random;
//         order[3] = Red.roll_val = random;
//         break;
//         // default:
//         // break;
//     }

//     int length = sizeof(order) / sizeof(order[0]);

//     print_arr(order, length);
// }

int getMax()
{
    short arr[4] = {Yellow.roll_val, Blue.roll_val, Red.roll_val, Green.roll_val};
    int length = sizeof(arr) / sizeof(arr[0]);
    short max = arr[0];
    for (int k = 1; k <= length; k++)
    {
        if (max < arr[k])
        {
            max = arr[k];
        }
    }
    return max;
}

int isMaxDup(int max){
    short arr[4] = {Yellow.roll_val, Blue.roll_val, Red.roll_val, Green.roll_val};
    short count = 0;

    for (int i = 0; i < 4; i++) {
        if (arr[i] == max) {
            count++;
        }
    }
    // Check if there are two or more maximum elements
    if (count >= 2) {
        //printf("The array contains two maximum elements.\n");
        return 1;
    } else {
        //printf("The array does not contain two maximum elements.\n");
        return -1;
    }
}

void getRoundStarter()
{
    {
        Yellow.roll_val = random(6);
        Blue.roll_val = random(6);
        Red.roll_val = random(6);
        Green.roll_val = random(6);
    }

    {
        printf("Yellow rolls %d\n", Yellow.roll_val);
        printf("Blue rolls %d\n", Blue.roll_val);
        printf("Red rolls %d\n", Red.roll_val);
        printf("Green rolls %d\n\n", Green.roll_val);
    }

    int max = getMax();

    int maxDup = isMaxDup(max);

    if(maxDup == -1){
        short id;
        if (Yellow.roll_val == max){
            printf("Yellow player has the highest roll and will begin the game.\n");
            printf("The order of a single round is Yellow, Blue, Red, Green\n");
            id = 0;
            baseMove(Yellow, Blue, Red, Green);        
            
        }
        else if (Blue.roll_val == max){
            printf("Blue player has the highest roll and will begin the game.\n");
            printf("The order of a single round is Blue, Red, Green, Yellow\n");
            id = 1;
            baseMove(Blue, Red, Green, Yellow);        
        }
        else if (Red.roll_val == max){
            printf("Red player has the highest roll and will begin the game.\n");
            printf("The order of a single round is Red, Green, Yellow, Blue\n");
            id  = 2;
            baseMove(Red, Green, Yellow, Blue);        
        }
        else if (Green.roll_val == max){
            printf("Green player has the highest roll and will begin the game.\n");
            printf("The order of a single round is Green, Yellow, Blue, Red\n");
            id = 3;
            baseMove(Green, Yellow, Blue, Red);        
        }
    } else if (maxDup == 1)
    {
        printf("Multiple max values >> Rolling again...\n\n");
        getRoundStarter();
    }
}

int baseMove(struct player x1, struct player x2, struct player x3, struct player x4){
    printf("val:%d",roll(x1));
    int val = roll(x1);
    if (val == 6 && x1.p1.curr_position == -1){
        x1.p1.curr_position = 2;
        val = roll(x1);
        if (roll(x1) == 6){
            x1.p1.curr_position = 8;
            val = roll(x1);
            if (roll(x1) == 6){
                x1.p1.curr_position = 8;
            } else{
                x1.p1.curr_position = x1.p1.curr_position + val;
            }
        } else{
            x1.p1.curr_position = x1.p1.curr_position + val;
        }
    } else{
        /* code */
    }
    

    checkforsix(roll(x1));
}

int roll(struct player x){
    x.roll_val = random(6);
    return x.roll_val;
}
// first_move get the random dice value from the roll() and do a move for a peice
int checkforsix(short val)
{

    for (int six=0; six<3;six++){
        if (1==1){
            ;
        };
    }
    return ;
    {
    // x.id =2;
    // switch (2)
    // {case 1:
        
    //     printf("fuck");
    //     break;
    
    // default:
    //     break;
    // }
    }
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
    srand(time(0));

    if (startGame(0)){
        printf("Game started...\n\n");
    }
    else {
        printf("Hum, see ya next time...\n\n");
        return 0;
    }

    {
        Yellow.roll_val, Blue.roll_val, Red.roll_val, Green.roll_val = 0;

        Yellow.p1.curr_position, Yellow.p2.curr_position, Yellow.p3.curr_position, Yellow.p4.curr_position = -1;
        Blue.p1.curr_position, Blue.p2.curr_position, Blue.p3.curr_position, Blue.p4.curr_position = -1;
        Red.p1.curr_position, Red.p2.curr_position, Red.p3.curr_position, Red.p4.curr_position = -1;
        Green.p1.curr_position, Green.p2.curr_position, Green.p3.curr_position, Green.p4.curr_position = -1;
    }

    {
        printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
        printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
        printf("The red player has four (04) pieces named R1, R2, R3, and R4\n");
        printf("The green player has four (04) pieces named G1, G2, G3, and G4\n\n");
    }

    getRoundStarter();
    printf("struct: %d",checkforsix(2));

    return 0;
}