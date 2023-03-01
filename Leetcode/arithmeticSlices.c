#include <stdlib.h>
#include <stdio.h>

/*
n elementos = 4
[1,2,3,4]

elementos = 5
[1, 2, 3, 4, 5]

*/

int numberOfArithmeticSlices(int* nums, int numsSize){
    int slices = 0;

    for(int i = 1; i < numsSize - 1; i++){
        int previousPos = i - 1;
        int razao = nums[i] - nums[previousPos];

        for(int j = i + 1; j <  numsSize; j++){
            if(nums[i] + razao == nums[j]){
                slices += 1;
            } 
        }
    }

    if(numsSize - slices == 2){
        slices++;
    }

    return slices;
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

    resposta = numberOfArithmeticSlices(nums, numsSize);

    printf("%d", resposta);

    return 0;
}