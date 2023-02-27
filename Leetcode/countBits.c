#include <stdlib.h>
#include <stdio.h>

int* countBits(int n, int* returnSize){
    returnSize = malloc(sizeof(int) * (n + 1));

    int arrReturn = malloc(sizeof(returnSize));

    if(n == 0){
        //continuar
    }

}

int main(){
    int* returnSize = NULL;
    int n;
    int *resposta;

    printf("digita o numero ");
    scanf("%d", &n);


    resposta = countBits(n, returnSize);


    return 0;
}