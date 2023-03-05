#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int qtdMoves = 0;

bool JudgeCircle( char *moves ){

    int x = 0;
    int y = 0;

    for( int i = 0; i < qtdMoves; i++ ){
        if( moves[i] == 'D' ){
            //ir pra baixo
            y -= 1;
        }

        if( moves[i] == 'L' ){
            //ir pra esquerdad
            x -= 1;
        }

        if( moves[i] == 'R' ){
            //direita
            x += 1;
        }

        if( moves[i] == 'U' ){
            //cima
            y += 1;
        }
    }

    for( int i = 0; i < qtdMoves; i++ ){
        printf( "%c\n", moves[i] );
    }

    return x == 0 && y == 0 ? true : false;
}


int main(){
    bool resposta;

    char *moves = NULL;

    printf( "Quantos movimentos o robo vai fazer? \n" );
    scanf( "%d", &qtdMoves );
    
    moves = malloc( sizeof( char ) * qtdMoves );

    if( !moves ){
        printf( "Erro na alocacao de me5moria \n ");
        exit( 1 );
    }

    printf( "Digite os movimentos do robo: " );
    scanf( "%s", moves );

    resposta = JudgeCircle( moves );

    printf( "RESPOSTA: %d \n", resposta );

    return 0;
}