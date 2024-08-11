//contain the core logic for the game, including the rules and player behaviors.
#include <stdio.h>

int main(){
int arr[] = {1,2,3,4,5};
//sub_arr[]
int i,j,k = 0;
for (k < 5; k++;){
    printf("%d,%d,%d",arr[i], arr[j], arr[k]);
    for (j < 5; j++;){
        printf("%d,%d,%d",arr[i], arr[j], arr[k]);
        for (k < 5; k++;){
            printf("%d,%d,%d",arr[i], arr[j], arr[k]);
        }
    }
}
}