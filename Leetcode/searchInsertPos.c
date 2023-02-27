#include <stdlib.h>
#include <stdio.h>

// 7
// 2 4 5 6 8


int searchInsert(int *nums, int numsSize, int target){
    for(int i = 1; i < numsSize; i++){
        int lastPos = i - 1;

        if(nums[i] == target || nums[lastPos] == target){
            printf("ja tava no array");
            return i;
        } else {
            if(nums[i] > target && nums[lastPos] < target){
                return lastPos;
            }
        }

    }

    return 0;
}

int main(){

    int numsSize = 0;
    int *nums = NULL;
    int target = 0;
    int resposta;

    printf("digite o tamanho do arr\n");
    scanf("%d", &numsSize);

    nums = (int *) malloc(sizeof(int) * numsSize);

    for(int i = 0; i < numsSize; i++){
        printf("digite num \n");
        scanf("%d", &nums[i]);
    }

    printf("digite o target");
    scanf("%d", &target);

    resposta = searchInsert(nums, numsSize, target);

    printf("%d", resposta);

    return 0;
}