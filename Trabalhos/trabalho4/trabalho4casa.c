#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// O(n^2)

void selectionSortDec( int nums[], int numsSize ) {
    for( int i = 0; i < numsSize - 1; i++ ) {
        int maxElementIndex = i;

        for( int j = i + 1; j < numsSize; j++ ) {
            if( nums[j] > nums[i] ){  
                maxElementIndex = j; 
            } else {
                maxElementIndex = i;
            }

            int changeAux = nums[maxElementIndex]; 
            nums[maxElementIndex] = nums[i];   
            nums[i] = changeAux;
        }
    }
}

void selectionSortAsc( int nums[], int size ){
    for( int i = 0; i < size - 1; i++ ) {
        int minElementIndex = i;

        for( int j = i + 1; j < size; j++ ) {
            if( nums[j] < nums[i] ){   
                minElementIndex = j; 
            } else {
                minElementIndex = i;
            }

            int changeAux = nums[minElementIndex]; 
            nums[minElementIndex] = nums[i];   
            nums[i] = changeAux;
        }
    }
}

int* maxSubsequence( int* nums, int numsSize, int k, int* returnSize ) {
    // criar cópia do array original para manter a ordem dos elementos
    int* arrNotSorted = malloc( sizeof(int) * numsSize );
    memcpy( arrNotSorted, nums, numsSize * sizeof(int) );

    selectionSortDec( nums, numsSize );

    // selecionar os k primeiros elementos do array ordenado
    *returnSize = k;
    int* arrReturn = malloc( sizeof(int) * k );
    for( int i = 0; i < k; i++ ){
        arrReturn[i] = nums[i];
    }

    // obter os índices correspondentes aos maiores elementos selecionados
    int* arrIndexes = malloc( sizeof(int) * k );
    for( int i = 0; i < k; i++ ) {
        for( int j = 0; j < numsSize; j++ ) {
            if(arrReturn[i] == arrNotSorted[j]) {
                arrIndexes[i] = j;
            }
        }
    }

    // ordenar os indices em ordem crescente
    selectionSortAsc( arrIndexes, k );

    // passar os valores na posicao correta
    for ( int i = 0; i < k; i++ ) {
        arrReturn[i] = arrNotSorted[arrIndexes[i]];
    }

    free( arrNotSorted );
    free( arrIndexes );
    

    return arrReturn;
}

void menu(){
    printf( "1) teste 1\n" );
    printf( "2) teste 2\n" );
    printf( "3) teste 3\n" );
    printf( "4) sair   \n" );
}


void resultado ( int *answer, int k ){
    printf("\n");
    printf( "sequencia de k elementos com maior soma: \n" );
    for( int i = 0; i < k; i++ ) {
        printf( "%d ", answer[i] );
    }
    printf("\n");
    printf("\n");
    printf("\n");

}

int main(){

    int option = 0;
    do{
        menu();
        scanf( "%d", &option );

        switch ( option )
        {
            case 1:
            {
                int numsSize = 4;
                int values[4] = {2, 1, 3, 3};
                int k = 2;
                int* nums = malloc( sizeof(int) * numsSize );
                int* answer = NULL;
                int* returnSize = malloc( sizeof(int) );
                
                for( int i = 0; i < numsSize; i++ ){
                    nums[i] = values[i];
                }

                answer = maxSubsequence( nums, numsSize, k, returnSize );

                resultado( answer, k );
                free( returnSize );
                free( answer );
                free( nums );
                break;
            }
            
            case 2:
            {
                
                int numsSize = 4;
                int values[4] = {-1, -2, 3, 4};
                int k = 3;
                int* nums = malloc( sizeof(int) * numsSize );
                int* answer = NULL;
                int* returnSize = malloc( sizeof(int) );
                
                for( int i = 0; i < numsSize; i++ ) {
                    nums[i] = values[i];
                }

                answer = maxSubsequence( nums, numsSize, k, returnSize );

                resultado( answer, k );
                free( returnSize );
                free( answer );
                free( nums );
                break;
            }
            case 3:
            {
                int numsSize = 4;
                int values[4] = {3, 4, 3, 3};
                int k = 2;
                int* nums = malloc( sizeof(int) * numsSize );
                int* answer = NULL;
                int* returnSize = malloc( sizeof(int) );
                
                for( int i = 0; i < numsSize; i++ ) {
                    nums[i] = values[i];
                }

                answer = maxSubsequence( nums, numsSize, k, returnSize );

                resultado( answer, k );
                free( returnSize );
                free( answer );
                free( nums );
                break;
            }
            default:
                break;
        }
    } while ( option != 4 );

    return 0;
}
