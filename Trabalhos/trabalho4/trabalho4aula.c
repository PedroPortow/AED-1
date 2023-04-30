#include <stdlib.h>
#include <stdio.h>

// Percorrer o vetor e achar os K maiores elementos
// Ordenacao por selecao??

// Ordenar por selecao invertidamente, botando em ordem descrecente
// E dps passar os K primeiros elementos desse array pro array
// de retorno
//Perorre o array sempre

int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize){
    int i, j, maxElementIndex;
    int* arrReturn = NULL;
    arrReturn = malloc(sizeof(int) * k);
    *returnSize = (int) k;

    for(i = 0; i < numsSize - 1; i++){
        maxElementIndex = i;

        for(j = i + 1; j < numsSize; j++){
            if(nums[j] > nums[i]){  //se 1 pos na frente maior
                maxElementIndex = j; //elemrnto maior vai ta no j
            } else {
                maxElementIndex = i;
            }

            int changeAux = nums[maxElementIndex]; // changeaux = elemento maior
            nums[maxElementIndex] = nums[i];   
            nums[i] = changeAux;
        }
    }

    // for(int cont = 0; cont < numsSize; cont++){
    //     printf("ARRAY ORDENADO: %d \n", nums[cont]);
    // }

    for(int cont = 0; cont < k; cont++){
        arrReturn[cont] = nums[cont];
    }
    
    return arrReturn;
}

int main(){
    int numsSize = 4;
    int* nums = NULL;
    int* returnSize = malloc(sizeof(int));
    int* answer = NULL;
    int k = 0; 


    printf("digite o tamanho do arr\n");
    scanf("%d", &numsSize);

    printf("digite os k elementos\n");
    scanf("%d", &k);

    nums = (int *) malloc(sizeof(int) * numsSize);

    for(int i = 0; i < numsSize; i++){
        printf("digite num \n");
        scanf("%d", &nums[i]);
    }

    answer = maxSubsequence(nums, numsSize, k, returnSize);


    printf("-----------------");
    printf("K ELEMENTOS COM MAIOR SOMA \n");
    for(int cont = 0; cont < k; cont++){
        printf("%d ", answer[cont]);
    }
    printf("\n");
    printf("-----------------");
    return 0;
}