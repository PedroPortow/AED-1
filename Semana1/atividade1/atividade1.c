#include <stdlib.h>
#include <stdio.h>

int* TwoSum( int* nums, int numsSize, int target, int* returnSize ) {
	*returnSize = 2; // [ , ] 
	int *arrayReturn = ( int * ) malloc( 2* ( sizeof (int) ));
	
	for( int i = 0; i < numsSize; i++ ) {
		for( int j = i + 1; j < numsSize; j++ ) {
			if( nums[i] + nums[j] == target ) {
				arrayReturn[0] = i;
				arrayReturn[1] = j;
				return arrayReturn;
			}
		}
	}

	return arrayReturn;
}

int main(){
	int *pNumbers, qtd, *returnSize , target, *answer;

	printf( "Digite a quantidade de elementos do Array: \n" );
	scanf( "%d", &qtd );

	pNumbers = (int *)malloc(qtd * sizeof(int));

	for( int i = 0; i < qtd; i++ ) {
		printf( "Digite o elemento para posicao %d: \n", i );
		scanf( "%d", &pNumbers[i] );
	}

	printf( "Digite o elemento target: \n" );
	scanf( "%d", &target );

	returnSize = (int *) malloc( sizeof(int) );

	answer = TwoSum( pNumbers, qtd, target, returnSize );

    printf("========== \n");

	for(int i = 0; i < *returnSize; i++){
        printf("%d\n", answer[i]);
    }

	free( pNumbers ) ;
	free( answer );
	free( returnSize );

	return 0;
}