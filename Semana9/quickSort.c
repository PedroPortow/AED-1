
#include <stdlib.h>
#include <stdio.h>

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

int main() {
    int array[] = {10, 7, 8, 9, 1, 5};
    int size = 6;
    
    printf("Array original: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    QuickSort(array, 0, size - 1);
    
    printf("Array ordenado: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    return 0;
} 