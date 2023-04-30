#include <stdlib.h>
#include <stdio.h>

/*
    =>  Percorre a lista, encontra o menor valor
    =>  Troca de lugar com o primeiro elemento NÃO-ORDENADO da lista
    =>  Repete os passos até todo o length da lista
*/

void selectionSort(int array[], int size){
   int i, j, min_idx;

   for (i = 0; i < size-1; i++){
       // Encontra o elemento mínimo no subvetor não ordenado
       min_idx = i;
       for (j = i+1; j < size; j++){
           if (array[j] < array[min_idx])
               min_idx = j;
       }
       // Troca o elemento mínimo com o primeiro elemento não ordenado
       int temp = array[min_idx];
       array[min_idx] = array[i];
       array[i] = temp;
   }
}

int main(){
   int vetor[] = {12, 11, 13, 5, 6};
   int size = sizeof(vetor)/sizeof(vetor[0]);

   selectionSort(vetor, size);

   printf("Vetor ordenado: ");
   for (int i=0; i < size; i++)
       printf("%d ", vetor[i]);
   printf("\n");

   return 0;
}