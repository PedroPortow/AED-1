#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char *nome;
    char *numero;
    int idade;
} SNodo;

typedef struct{
    int limite;
    SNodo *nodos;
    SNodo *top;
    SNodo *bottom;
} SPilha;

void Menu();

int main(){
    int option;
    SPilha *pilha;

    pilha = malloc(sizeof(SPilha));

    do{
        Menu();
        scanf("%d", &option);

        switch ( option ){
            case 1:
            {
                SNodo *nodo = malloc(sizeof(SNodo));
                char nome;
                bool resposta = false;

                printf("Nome: ");
                scanf("%s", &nome);
                nodo->nome = malloc(sizeof(strlen(nome) + 1));
                nodo->nome = nome;
                printf("Idade: ");
                scanf("%d", &nodo->idade);
                resposta = Push(pilha, nodo);
               
                break;
            }
                
            case 2:
            {
                Pop(pilha);
                break;
            }
            case 3:
            {
                char *nome = malloc(sizeof(char) * 30);
                bool resposta = false;
                printf("Nome: ");
                scanf("%s", nome);
                resposta = RemovePessoaPorNome(pilha, nome);
                if(resposta == true){
                    printf("PESSOA ADD");
                }
                break;
            }

            case 4:
                Reset(pilha);
                break;
            case 5:
                Listar(pilha);
                break;
            case 6:
                free(pilha);
                exit(1);
                break;
        }    
    } while(option !=  6);

    return 0;
}