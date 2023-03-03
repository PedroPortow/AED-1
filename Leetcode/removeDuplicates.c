#include <stdlib.h>
#include <stdio.h>

//removeDuplicates from sorted array
//n dava pra 
// [0,0,1,1,1,2,2,3,3,4]

int removeDuplicates(int* nums, int numsSize){
    int cont = 0;
    int *uniqueArray = NULL;

    for(int i = 0; i < numsSize - 1; i++){
        if(nums[i] != nums[i + 1]){
            if(!uniqueArray){
                uniqueArray = malloc(sizeof(int));
                uniqueArray[cont] = nums[i];
                cont++;
            } else {
               
                uniqueArray = realloc(uniqueArray, sizeof(int) * cont);
                uniqueArray[cont] = nums[i];
                cont++;
            }
        }
    }

      if(numsSize > 0){
        cont++;
        uniqueArray = realloc(uniqueArray, sizeof(int) * cont);
        uniqueArray[cont - 1] = nums[numsSize - 1];
    }

      for(int i = 0; i < cont; i++){
        printf("%d ", uniqueArray[i]);
    }


    return cont;

    

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

    resposta = removeDuplicates(nums, numsSize);


    return 0;
}