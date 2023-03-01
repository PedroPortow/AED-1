#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 [0, 5 10, 15, 17, 25]
 [0, 5, 10, 15, 17]

*/

int minCostClimbingStairs(int* cost, int costSize){
    int costIndexZero = 0;
    int costIndexOne = 0;

    int costZeroOneStep = 0;
    int costZeroTwoSteps = 0;

    int costOneOneStep = 0;
    int costOneTwoSteps = 0;
    

    for(int i = 0; i < costSize + 1; i++){ 
        if(i <= costSize){
            costZeroOneStep += cost[i];
        }

        for(int j = 0; j < costSize + 1; j += 2){
            if(i <= costSize){
                costZeroTwoSteps += cost[i];
            }
        }
    }

    if(costZeroOneStep > costZeroTwoSteps){
        costIndexZero = costZeroTwoSteps;
    } else {
        costIndexZero = costZeroOneStep;
    }

    for(int i = 1; i < costSize + 1; i++){ 
        if(i <= costSize){
            costOneOneStep += cost[i];
        }

        for(int j = 1; j < costSize + 1; j += 2){
            if(i <= costSize){
                costOneTwoSteps += cost[i];
            }
        }
    }

    if(costOneOneStep > costOneTwoSteps){
        costIndexOne = costOneTwoSteps;
    } else {
        costIndexOne = costOneOneStep;
    }

    if(costIndexZero > costIndexOne){
        return costIndexOne;
    } else{
        return costIndexZero;
    }

}

//ta errado


int main(){
    int numsSize = 0;
    int *nums = NULL;
    int resposta;

    printf("digite o tamanho do arr\n");
    scanf("%d", &numsSize);

    nums = (int *) malloc(sizeof(int) * numsSize);

    for(int i = 0; i < numsSize; i++){
        printf("digite num \n");
        scanf("%d", &nums[i]);
    }

    resposta = minCostClimbingStairs(nums, numsSize);

    printf("%d", resposta);

    return 0;
}