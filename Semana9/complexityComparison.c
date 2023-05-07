#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


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

void QuickSort(int data[], int left, int right){
    int i, j, tmp, pivot;
    
    i = left;
    j = right;
    pivot = data[(left + right) / 2];

    do {
        while (data[i] < pivot) {  // enquanto i nao apontar pra uma elemento na pos errada
            i++;
        }
        while (data[j] > pivot) { // enquanto j nao apontar pra um elemento na pos errada
            j--;
        }   
        if (i <= j) {               
            tmp = data[i];          //faz o swap
            data[i] = data[j];
            data[j] = tmp;
            i++;                // pos swap, os dois ja andam uma casa
            j--;
        }
    } while (i <= j);

    // chegando aqui ja vai ter dividido a lista
    if (left < j) {     // da esqurda ate antes do pivo
        QuickSort(data, left, j);
    } 
    if (i < right) {    // do fim ate depois do pivo
        QuickSort(data, i, right);
    }
}

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

int main() {
    int n = rand() % 5000;
    
    int arr[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1001; 
    }

  

    insertionSort(arr, n);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1001; 
    }

    selectionSort(arr, n);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1001; 
    }
    mergeSort(arr, 0, n - 1);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1001; 
    }
    QuickSort(arr, 0, n - 1);

    printf("ultimo vetor gerado ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    

    printf("\n");
    
    return 0;
}