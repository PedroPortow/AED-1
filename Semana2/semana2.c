#include <stdlib.h>
#include <stdio.h>

//exercicios programacao descomplicada alocao de memoria

void exercicio1(){
    int *arr = malloc(5 * sizeof(int));


    for(int i = 0; i < 5; i++){
    printf("Digite numero para pos %i", i);
    scanf("%d", arr+i);
    }

    for(int j = 0; j < 5; j++){
    printf("%d  ", arr[j]);
    }

    free(arr);

}

void exercicio3(){
     int tamanhoMem;
    int *memoria;
    int option;

    printf("Digite o tamanho da memoria\n");
    scanf("%d", &tamanhoMem);

    memoria = malloc(sizeof(int) * tamanhoMem);

    /*for(int i = 0; i < 5; i++){
        printf("Digite numero para pos %i", i);
        scanf("%d\n", memoria+i);
    }*/

   

    do{
    printf("\n ================== \n");
    printf("1) Inserir valor e determinada posicao em memoria\n");
    printf("2) Consultar valor em determinada pos de mem\n");
    scanf("%d", &option);
        switch(option){
            case(1):
            int valor;
            int pos;
            printf("valor a ser inserido: \n");
            scanf("%d", &valor);
            printf("pos \n");
            scanf("%d", &pos);

            if(pos <= tamanhoMem){
                memoria[pos] = valor;
                for(int j = 0; j < tamanhoMem; j++){
                    printf("%d  ", memoria[j]);
                }
            } else {
                printf("pos invalid");
            }
            

            break;
        case(2):   
            int posi; 
            printf("Digite a pos pra ocnsultar");
            scanf("%d", &posi);

            if(pos > tamanhoMem){
                printf("Pos invlaida");
            } else{
                printf("%d", memoria[posi]);
            }
            
            break;
        default:
            break;
    }
    } while(option != 3);

}

void exercicio2(){


    int tamString;
    char* string;

    printf("Digite o tamanho da string");
    scanf("%d", &tamString);

    string = malloc(sizeof(char) * (tamString + 1));

    printf("Digite a stirng");
    scanf("%s", string);

    printf("%s", string);
}

// fim ex alocacao de memoria

int main (){

    //exercicio1();
    //exercicio2();
    int *arr;
    arr = malloc(sizeof(int) * 5);
    arr[0] = 8;
    arr[1] = 4;
    arr[2] = 9;
    arr[3] = 2;
    arr[4] = 1;
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int aux;

    for(int i = 0; i < arrSize; i++){
        for(int j = 1; j < arrSize; j++){
            if(arr[i] < arr[j]){
                aux = arr[i];
                arr[i] = arr[j];
                arr[i + 1] = aux;
            }
        }
    }

    for(int j = 0; j < arrSize; j++){
        printf("%d  ", arr[j]);
    }

   

    return 0;
}