#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Divide na metade em 2 subarray 
    vai dividindo na metade recursivamete esses 2 subarray
    ate que n de pra dividir mais
    depois faz o caminho inverso ( volta mergeando ) ja ordenando
*/

void merge(int arr[], int inicio, int mid, int fim) {
    int *arrTemp;   // array auxiliar criado pra ir ordenando
    int p1 = inicio; // inicio do subarray da esquerda
    int p2 = mid + 1; // inicio subarray da direita 
    int tamanho = fim - inicio + 1; //length do array
    bool fim1 = false, fim2 = false; //booleano usado pra verificar se chegou no fim dos subarrs

    arrTemp = (int *) malloc(tamanho * sizeof(int));

    int i, j, k;
    if(arrTemp != NULL){    //vai percorrer todo o arr temp
        for(i = 0; i < tamanho; i++){
            if(fim1 == false && fim2 == false){ //se nao tiver chegado no fim ainda
                if(arr[p1] < arr[p2]){
                    arrTemp[i] = arr[p1++];
                } else {
                    arrTemp[i] = arr[p2++];
                }

                if(p1 > mid) fim1 = true;  //subarray da esquerda acabou?
                if(p2 > fim) fim2 = true;   //subarray da direita acabou?
            } else {
                //ve qual array que chegou no fim e copia o resto dos valores
                // do que nao chegou no fim (isso vai ta ordenado)
                if(fim1 == false){
                    arrTemp[i]  = arr[p1++];
                } else {
                    arrTemp[i] = arr[p2++];
                }
            }
        }
        for(j = 0, k=inicio; j<tamanho; j++, k++){
            arr[k] = arrTemp[j];
        }

        free(arrTemp);
    }
}

void mergeSort(int arr[], int inicio, int fim) {
    if (inicio < fim) { 

        /*
            pq que quando o inicio < fim do primeiro subarray e falso, nao para a execucao?
            por causa do callstack
        */

        int mid = inicio + (fim - inicio) / 2; //pegando a metade do array

        mergeSort(arr, inicio, mid);  // aqui ja foi passado metade inicial do array

        mergeSort(arr, mid + 1, fim); // aqui ja foi passado metade final do array


        // volta mergeando essas 2 metades e REORDENANDO
        merge(arr, inicio, mid, fim);
    }
}


int main() {
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, 0, arr_size - 1);

    printf("Array ordenado: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}