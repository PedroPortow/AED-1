#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// MOVIMENTOS => R L U D

int qtdMoves = 4;

int judgeCircle(char *moves){

    int x = 0;
    int y = 0;

    char* D = "D";
    char* U = "U";
    char* L = "L";
    char* R = "R";


    for(int i = 0; i < qtdMoves; i++){
        if(moves[i] == *D){
            //ir pra baixo
            y -= 1;
        }

        if(moves[i] == *L){
            //ir pra esquerda
            x -= -1;
        }

        if(moves[i] == *R){
            //direita
            x += 1;
        }

        if(moves[i] == *U){
            //cima
            y += 1;
        }
    }

    for(int i = 0; i < qtdMoves; i++){
        printf("%c\n", moves[i]);
    }

    return x == 0 && y == 0 ? 1 : 0;
}


int main(){
    int resposta;

    //ALTERAR A VARIAVEL qtdMoves de acordo
    char *moves = {"DDUU"};
    // char *moves  = {"DLR"};
    // char *moves  = {"DLRU"};

    resposta = judgeCircle(moves);

    printf("RESPOSTA: %d \n", resposta);

    return 0;
}