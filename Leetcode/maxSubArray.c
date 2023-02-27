#include <stdlib.h>
#include <stdio.h>

// percorrer o array, 
// posso criar uma variavel com um valor mt baixo so pro caso inicial?
// vou percorrendo e somando numa variavel e comparando com a outra variavel
// se for maior seto ela ne? 

int maxSubArray(int *nums, int numsSize){
    int sum = 0;
    int maiorSoma = NULL;


    for(int i = 0; i < numsSize; i++){

        if(sum >= 0){
            sum += nums[i];
        } else {
            sum = nums[i];
        }

        if(maiorSoma == NULL){
            maiorSoma = sum;
        }

        if(sum > maiorSoma){
            maiorSoma = sum;
        }
    }

    return maiorSoma;
}

int main(){

    int numsSize = 0;
    int *nums = NULL;
    int resposta = 0;

    printf("digite o tamanho do arr\n");
    scanf("%d", &numsSize);

    nums = (int *) malloc(sizeof(int) * numsSize);

    for(int i = 0; i < numsSize; i++){
        printf("digite num \n");
        scanf("%d", &nums[i]);
    }

    resposta = maxSubArray(nums, numsSize);

    printf("%d", resposta);

    return 0;
}