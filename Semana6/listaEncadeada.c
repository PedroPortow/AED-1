#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
Nao da pra simplesmente ficar fazendo *pNext++ ou algo do tipo pra ir peercorrendo a lista pq ela n ta
seguida na memória, está separada e é ligada somente pelo ponteiro *pNext;

diferença entre clear e reset => Clear vai limpar a pilha, não dar free nela por exemplo
reset vai fazer o clear, dar um free na pilha e retornar uma nova

*/

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
SNodo *Pop(SLista *pLista, SNodo *pNodo, unsigned int nIndex);
void Clear(SLista *pLista);
SLista *Reset(SLista *pLista);
void Listar(SLista *pLista);

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
            case 2:
            {
                int pos;
                SNodo *nodoPoped;
                printf("posicao para remover: ");
                scanf("%d", &pos);
                nodoPoped = (SNodo *) Pop(lista, nodoPoped, pos);
                if(!nodoPoped){
                    printf("\n PESSOA REMOVIDA \n");
                    printf("%s\n", nodoPoped->pessoa.nome);
                    printf("%d\n", nodoPoped->pessoa.idade);
                }
                free(nodoPoped);
                break;
            }
            case 3:
            {
                Listar(lista);
                break;
            }
            case 4:
            {
                lista = Reset(lista);
                break;
            }
            case 5:
            {
                Clear(lista);
                break;
            }
            default:
                break;
        }    
    } while(option !=  6);


    return 0;
}

SLista *Reset(SLista *pLista){
    Clear(pLista);

    free(pLista);
    pLista = (SLista *)malloc(sizeof(SLista));
    return pLista;
}

SNodo *Pop(SLista *pLista, SNodo *pNode, unsigned int nIndex){
    SNodo *pAnterior, *pAtual;

    if(pLista->pFirst == NULL || nIndex > pLista->qtdNodos){ //caso a lista ainda n exista ou a posição n esteja na lista
        return NULL;        
    } else if( nIndex == 0){
        pNode = pLista ->pFirst; //o nó vai ser o primeiro
        pLista->pFirst = (SNodo *)pLista->pFirst->pNext; //atualizando a pilha, o pFirst vai apontar pro proximo daquele q foi removido
        return pNode;
    } else{
        pAnterior = NULL;
        pAtual = pLista->pFirst;
        for(int nPos = 0; nPos < nIndex; nPos++){
            pAnterior = pAtual;
            pAtual = (SNodo *)pAtual->pNext;

            /*
             no fim desse loop, pAnterior vai apontar pra posição anterior do nodo a ser removido
             vai ter q atualizar o pNext desse cara
             pAtual vai ter a posição pra ser removida
            */
        }

        pAnterior->pNext = pAtual->pNext;
        pNode = pAtual;
        return pNode;
    } 

    

}

void Clear(SLista *pLista){
    SNodo *pAtual = pLista->pFirst; //ponteiro atual que vai ser incrementado, pois o clear precisa 
                                    //percorrer toda a lista e dando free em cada um dos nodos :(

    while (pAtual != NULL) {
        SNodo *pNext = (SNodo *)pAtual->pNext; //pega o proximo ponteiro, e manda pro pAtual 
        free(pAtual); // deleta o nodo atual
        pAtual = pNext; 
    }

    pLista->pFirst = NULL;
    pLista->qtdNodos = 0;
}

void Listar(SLista *pLista){
    SNodo *pAtual = pLista->pFirst; 
                                   
    while (pAtual != NULL) {
        printf("==========================");
        printf("%s\n", pAtual->pessoa.nome);
        printf("%d\n", pAtual->pessoa.idade);
        printf("==========================");
        pAtual = (SNodo *)pAtual->pNext; 
    }

}

bool Push(SLista *pLista, SNodo *pNewNode, unsigned int nIndex){

    SNodo *pAtual, *pAnterior;

    if(nIndex > pLista->qtdNodos){
        return false; 
    }

    if(pLista->pFirst == NULL && nIndex != 0 ){
        return false; //caso a lista for nula e o index pra ser inserido nao for 0 (o primeiro) retorna false
    } else if(pLista->pFirst == NULL && nIndex == 0){
        pLista->pFirst = pNewNode; // botando o nodo na lista
        pLista->pFirst->pNext = NULL; // ccomo e o primoeiro o pNext ainda vai ser nulo 
        return true;
    } else if(nIndex == 0){ //CASO JA TENHA COISA NA PILHA MAS QUERER INSERIR NO PRIMEIRO
        pNewNode->pNext = (struct SNodo *) pLista->pFirst; // ponteiro next do novo node vai apontar pro atual primero elemento q vai ser pushed pra frente
        pLista->pFirst = pNewNode; // lista vai comecar agora com esse node 
        return true;
    } else{
         // Percorrer a lista até o ponto de inserção
        pAnterior = NULL;
        pAtual = pLista->pFirst;
        for (int nPos = 0; nPos < nIndex; nPos++) {
            pAnterior = pAtual;
            pAtual = (SNodo *)pAtual->pNext;
        }
        // Inserir o novo nó após o nó anterior
        pNewNode->pNext = (struct SNodo *)pAtual;
        pAnterior->pNext = (struct SNodo *)pNewNode;
    }

    pLista->qtdNodos++;


    return true;
}

void Menu(){
    printf("=== SELECIONE UMA OPCAO ===\n");
    printf("1) Inserir pessoa\n");
    printf("2) Deletar pessoa\n");
    printf("3) Listar pessoas\n");
    printf("4) Limpar pessoas\n");
    printf("5) Sair do programa \n");
}