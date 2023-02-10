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
	int *p, qtd, *returnSize , target, *answer;

	printf( "Digite a quantidade de elementos do Array: \n" );
	scanf( "%d", &qtd );

	p = (int *)malloc(qtd * sizeof(int));

	for( int i = 0; i < qtd; i++ ) {
		printf( "Digite o elemento para posição %d: \n", i );
		scanf( "%d", &p[i] );
	}

	printf( "Digite o elemento target: \n" );
	scanf( "%d", &target );

	returnSize = (int *) malloc( sizeof(int) );

	answer = TwoSum( p, qtd, target, returnSize );

	printf( "Elementos: %d %d\n", answer[0], answer[1] );

	free( p) ;
	free( answer );
	free( returnSize );

	return 0;
}