//HEAP

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// typedef struct {
//     char *nome[30];
//     int *idade;
//     struct SPessoa *pNext;
// } SPessoa;

// SPessoa *pInicioLista = NULL;

// //cria um novo nodo a ser inserido na lista
// SPessoa *novoNode(char *nome, int *idade){
//     SPessoa *pNode;
//     pNode = (SPessoa *) malloc(sizeof(SPessoa));
//     strcpy(pNode->nome, nome);
//     pNode->idade = (int *) malloc(sizeof(int));
//     pNode->idade = idade;
//     pNode->pNext = NULL; // por ewnquanto seta pra null pq n tem como saber qual vai ter q ser setado
//     return pNode; //retornando ponteiro pra esse node criado
// }

// void Push(SPessoa **inicioLista, SPessoa *novoNode){
//     SPessoa **tracer = inicioLista; //Criacao do ponteiro pra pont tracer, usado pra perfcorrer a lista
//     while((*tracer) && strcmp((*tracer) ->)) 
// }