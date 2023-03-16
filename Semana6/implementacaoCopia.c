#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct{
    char nome[30];
    int idade;
} SPessoas; // Pessoas a serem inseridas na lista

typedef struct {   // struct de criacao dos nos da lista, contendo o conteudo (pessoa) e ponteiro pra
    SPessoas pessoa;    
    struct SNodo *pNext;
} SNodo;           

typedef struct {
    SNodo *pFirst; // lista vai ser um ponteiro pro primeiro elemento dela 
    int qtdNodos;
} SLista;

void Menu();
bool Push(SLista *pLista, SNodo *pNewNode, unsigned int nIndex);

int main(){
    int option;
    SLista *lista = malloc(sizeof(SLista));
    lista->pFirst = NULL;
    lista->qtdNodos = 0;

    do{
        Menu();
        scanf("%d", &option);


        switch ( option ){
            case 1:
            {
                
                int pos;
                SPessoas *pessoa = malloc(sizeof(SPessoas));
                SNodo *pNewNode = malloc(sizeof(pNewNode));
                bool resposta = false;
                printf("Nome: ");
                scanf("%s", pessoa->nome);
                printf("Idade: ");
                scanf("%d", &pessoa->idade);
                printf("Posicao: ");
                scanf("%d", &pos);
                pNewNode->pessoa = *pessoa;
                resposta = Push(lista, pNewNode, pos);
                if(resposta == true){
                    printf("PESSOA ADD");
                }
                break;
            }
                
           
        }    
    } while(option !=  6);


    return 0;
}

bool Push(SLista *pLista, SNodo *pNewNode, unsigned int nIndex){

    SNodo *pAtual, *pAnterior;

    if(pLista->pFirst == NULL && nIndex != 0 ){
        return false; //caso a lista for nula e o index pra ser inserido nao for 0 (o primeiro) retorna false
    } else if(pLista->pFirst == NULL && nIndex == 0){
        pLista->pFirst = pNewNode; // botando o nodo na lista
        pLista->pFirst->pNext = NULL; // ccomo e o primoeiro o pNext ainda vai ser nulo 
        return true;
    } else if(nIndex == 0){ //CASO JA TENHA COISA NA PILHA MAS QUERER INSERIR NO PRIMEIRO
        pNewNode->pNext = pLista->pFirst; // ponteiro next do novo node vai apontar pro atual primero elemento q vai ser pushed pra frente
        pLista->pFirst = pNewNode; // lista vai comecar agora com esse node 
        return true;
    }

    //caso nao for nenhum desses casos

    pAnterior = NULL;
    pAtual = pLista->pFirst;
    for(int nPos = 0; nPos <= nIndex; nPos++){ //ATE ENCONTRAR A POSICAO A SER INSERIDA
        pAnterior = pAtual; //a pos anterior vai passar a ser a atual
        pAtual = pAtual->pNext;
    }

    if(!pAtual) return 0; //pAtual nao tem elemento, ou seja n existe ainda

    pNewNode->pNext = pAtual;
    pAnterior->pNext = pNewNode;

    

    return true;
}

void Menu(){
    printf("=== SELECIONE UMA OPCAO ===\n");
    printf("1) Inserir pessoa\n");
    printf("3) Deletar pessoa\n");
    printf("4) Limpar pilha\n");
    printf("5) Listar pessoas\n");
    printf("6) Sair do programa \n");
}