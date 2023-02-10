#include <stdlib.h>
#include <stdio.h>

/*

 Os numeros de maior valor e mais distantes um do outro
 o calculo da area vai ser height * width
 height => altura do maior carinha (numero de maior valor)
 width => numero de maior index - index do carinha mais alto ?
 
 começar uma iteração do inicio do array e outra no final do array
 e calcular a area. Setar a area pra uma variavel, se na proxima iteração 
 o calculo for maior então aquela é a maior area

  area = highestNumber * width

*/

int MaxArea( int* height, int heightSize ){
  int width, rightPoint, leftPoint, area = 0, maxArea = 0, highestNumber;


  for( int i = 0; i < heightSize; i++ ) {
    for( int j = heightSize; j >= 0; j-- ) {
      if( height[i] < height[j] ) {
        highestNumber = height[i];
      } else {
        highestNumber = height[j];
      }
  
      area = highestNumber * ( j - i );

      if( maxArea < area ) {
        maxArea = area;
      }
    } 
  }

  return maxArea;
}

int main(){
	int *height, heightSize, answer;

	printf( "Quantos n o array vai ter \n" );
	scanf( "%d", &heightSize );

	height = (int *)malloc( heightSize * sizeof(int) );

	for(int i = 0; i < heightSize; i++) {
		printf( "Digite o n para posição %d: ", i );
		scanf( "%d", &height[i] );
	}

	answer = MaxArea( height, heightSize );


	printf( "%d", answer );
	return 0;
}