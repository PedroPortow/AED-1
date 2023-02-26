#include <stdlib.h>
#include <stdio.h>

//n degraus e passos pra chegar no topo
// 1 <= n <= 45
// saida numero de possibilidades pra chegar no topo
// sendo que pode subir 1 ou 2 degraus de uma vezes

// para 4 passos
// 1 1 1 1
// 2 2
// 2 1 1
// 1 2 1
// 1 1 2

// para 5 
// 1 1 1 1 1
// 1 1 1 2
// 2 2 1
// 1 2 2
// 2 1 2
// 2 1 1 1
// 1 2 1 1
// 1 1 2 1 

int subirEscada (int degraus){
    int possiblidades = 0; // possiblidade default => subir a escada um por um 
    int umDegrau = 1;
    int doisDegraus = 2;


    if(degraus == 2){
        return 2;
    }

    if(degraus == 3){
        return 3;
    }


    if(degraus >= 4){
        for(int i = 3; i <= degraus; i++){
            possiblidades = umDegrau + doisDegraus;
            umDegrau = doisDegraus;
            doisDegraus = possiblidades;
        }

        return possiblidades;
    }

    return possiblidades;
}

int main(){
    int degraus;
    int resposta;

    printf("Quantos degraus voce quer subir? (1 - 45) \n");
    scanf("%d", &degraus);

    if(degraus > 45){
        printf("O valor max deve ser ate 45");
        exit(1);
    }

    resposta = subirEscada(degraus);

    printf("%d", resposta);

    return 0;
}