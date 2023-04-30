#include <stdlib.h>
#include <stdio.h>

/*
    Dado um conjunto de dados armazenados em ordem aleatória, reordena-los com base
    em uma regra de precedência.

    COMPLEXIDADE DE TEMPO => O(n^2) (Quadrático), sendo que o n é o length do array
    

    *------------   TESTE DE MESA   ------------*

    entrada =>  12, 11, 13, 5, 6

    Index |  i |  j |  key |  array       |  array[i] |  array[j] |
    ------|----|----|------|--------------|-----------|-----------|
    -     |    |    |      | 12 11 13 5 6 |           |           |
    1     |  1 |  0 |  11  | 12 11 13 5 6 |    11     |    12     | 
    2     |  2 |  1 |  13  | 11 12 13 5 6 |    13     |    12     | 
    3     |  3 |  2 |  5   | 11 12 13 5 6 |    5      |    13     | 
    4     |  4 |  2 |  6   | 11 12 5 13 6 |    6      |    5      | 
    5     |  4 |  3 |  6   | 5 11 12 13 6 |    6      |    13     | 

*/


void insertionSort(int arr[], int length){
   int i, key, j;

   for (i = 1; i < length; i++) {   
       key = arr[i];                // Pega elemento do array pra ser ordenado
       j = i - 1;                   // J vai ser usado pra pegar a posição anterior do array

        /* Move os elementos do vetor que são maiores que a key, uma posição a frente (para cada um) */
        /* Só vai entrar no while, se o elemento antes do key, for maior que ele (ou seja, tem que ordenar) */
        while (j >= 0 && arr[j] > key){ 
           arr[j + 1] = arr[j]; // Empurra o elemento anterior pra frente
           j = j - 1;           // j é decrementado 
        }
        arr[j + 1] = key;
        /*
            Se chegar aqui sem entrar no while => j + 1 = i (Posição certa pra inserir)
            Se chegar aqui entrando no while => j = i - 2 , portanto j + i vai ser a posição certa pra inserir a key
        */  
   }
}


int main(){
    int array[] = {12, 11, 13, 5, 6};
    int arrayLength = sizeof(array)/sizeof(array[0]);

   insertionSort(array, arrayLength);

   printf("Vetor ordenado: ");
   for (int i=0; i < arrayLength; i++)
       printf("%d ", array[i]);
    printf("\n");

    return 0;
}