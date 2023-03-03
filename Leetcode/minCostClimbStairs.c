#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 [0, 5 10, 15, 17, 25]
 [0, 5, 10, 15, 17]

 solução horrorosa mas é isso por enquanto
*/

int minCostClimbingStairs(int* cost, int costSize){

   int costTwoStepsIndexZero = 0;
   int costOneStepIndexZero = 0;
   
   int costOneStepIndexOne = 0;
   int costTwoStepsIndexOne = 0;

   int minCostIndexOne = 0;
   int minCostIndexZero = 0;

   //index 0 1 - 1
   for(int i = 0; i < costSize; i++){
    costOneStepIndexZero += cost[i];
   }

   for(int i = 0; i < costSize; i += 2){
    costTwoStepsIndexZero += cost[i];
   }

   for(int i = 1; i < costSize; i++){
    costOneStepIndexOne += cost[i];
   }

   for(int i = 1; i < costSize; i += 2){
    costTwoStepsIndexOne += cost[i];
   }

   if(costTwoStepsIndexOne < costOneStepIndexOne){
    minCostIndexOne = costTwoStepsIndexOne;
   } else {
    minCostIndexOne = costOneStepIndexOne;
   }

   if(costTwoStepsIndexZero < costOneStepIndexZero){
    minCostIndexZero = costTwoStepsIndexZero;
   } else {
    minCostIndexZero = costOneStepIndexZero;
   }

   return minCostIndexOne < minCostIndexZero ? minCostIndexOne : minCostIndexZero;
}

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