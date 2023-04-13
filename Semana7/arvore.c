#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Depois fazer uma versão que o PUSH utiliza a função de pesquisar pra achar a posição de inserir      
*/


/*

                    4       
        1                   6
            3           5       7
        2
*/

typedef struct Registro {
    long chave;
    char nome[10];
    int idade;
    int telefone;
} Registro;

typedef struct Node * Pointer;

typedef struct Node {
    Registro registro;
    Pointer* pEsq;
    Pointer* pDir;
} Node;


void inicializa(Pointer *agenda);
void pesquisa(Registro *registroProcurar, Pointer pointer);
void retira(Registro registroRemover, Pointer *pointer);
void push(Registro registroAdicionar, Pointer *pointer);
void antecessor(Pointer nodoRemover, Pointer *leftNodo);
void inicializa(Pointer *agenda);
void menu();


int main(){
    Pointer *agenda; // Pointer vai ter tipo => Ponteiro que aponta pra um node
    incializa(agenda);
    int option = 0;

    do {
        menu();
        scanf("%d", &option);

        switch (option){
            case 1:
                Registro novoRegistro;
                printf("Digite chave do registro: ");
                scanf("%d", &novoRegistro.chave);
                printf("Digite nome do registro: ");
                scanf("%s", &novoRegistro.nome);

                push(novoRegistro, agenda);
                break;


            default:   
                break;
        }

    } while(option != 5);


    return 0;
}

void menu(){
    printf("\n selecione opcao \n");
    printf("\n 1) inserir");
    printf("\n 2) pesquisar");
    printf("\n 3) remover");
}

void pesquisa(Registro *registroProcurar, Pointer pointer){
    if (pointer == NULL){
        printf("Registro nao esta presente na arvore");
        return;
    }

    if(registroProcurar->chave < pointer->registro.chave){  
        /*
            Se a chave do elemento sendo procurado, é menor que a chave do node que o pointer ta apontando agora
            Então, tem que seguir na arvore PRA ESQUERDA (pq é menor, logo ta na esquerda) pra continuar procurando
            Então, a função vai ser chamada novamente, passando esse novo ponteiro da esquerda!!
        */
        pesquisa(registroProcurar, pointer->pEsq);
        return;
    }

    if(registroProcurar->chave > pointer->registro.chave){
        /*
            CHAVE ELEMENTO > CHAVE NODE (que pointer ta apontando no momento) 
            SEGUIR NA ARVORE PRA DIREITA, CHAMAR A FUNÇÃO DNV MANDANDO O PONTERO DA DIREITA
        */
        pesquisa(registroProcurar, pointer->pDir);
        return;
    }
    else {
        /*
            Se cair aqui, achou o elemento na árvore
        */
       *registroProcurar = pointer->registro;
    }
}

void push(Registro registroAdicionar, Pointer *pointer){
    //Lembrando, se pointer que vai percorrer a arvore for NULL, achou o lugar :)

    if (*pointer == NULL){                          // ACHOU ONDE INSERIR
        *pointer = (Pointer)malloc(sizeof(Node));   // alocando um espaço pra um Node, no lugar que pointer achou  
        (*pointer)->registro = registroAdicionar;   // adicionando nesse lugar
        (*pointer)->pEsq = NULL;                    // setando os ponteiros desse cara
        (*pointer)->pDir = NULL;
        return;

        /*
            Porque não tem que arrumar os ponteiros dos outros pra apontar pra esse Node?
            Pq já tem um ponteiro que aponta pra essa posição, tanto que foi assim que chegou aq
        */
    }

    if(registroAdicionar.chave < (*pointer)->registro.chave){
        /*
            CHAVE ELEMENTO < CHAVE NODO == TEM QUE SEGUIR PRA ESQUERDA NA ÁRVORE
        */
        push(registroAdicionar, &(*pointer)->pEsq); // passando o ENDEREÇO
        return;
    }

    if(registroAdicionar.chave > (*pointer)->registro.chave){
        /*
            CHAVE ELEMENTO > CHAVE NODO == TEM QUE SEGUIR PRA DIREITA NA ÁRVORE
        */
        push(registroAdicionar, &(*pointer)->pDir);
        return;
    } else {
        // Se cair aqui, é sinal que percorreu a arvore e parou exatamente no mesmo registro que já tava na arvore
        printf("Registro já ta na arvore pai");
    }
}

void retira(Registro registroRemover, Pointer *pointer){
    Pointer pAux;   // POINTER AUXILIAR

    if(*pointer == NULL){
        printf("Registro nao foi achado na arvore");
        return;
    }

     if(registroRemover.chave < (*pointer)->registro.chave){
        /*
            CHAVE ELEMENTO < CHAVE NODO == TEM QUE SEGUIR PRA ESQUERDA NA ÁRVORE
        */
        retira(registroRemover, &(*pointer)->pEsq); // passando o ENDEREÇO
        return;
    }

    if(registroRemover.chave > (*pointer)->registro.chave){
        /*
            CHAVE ELEMENTO > CHAVE NODO == TEM QUE SEGUIR PRA DIREITA NA ÁRVORE
        */
        retira(registroRemover, &(*pointer)->pDir);
        return;
    } 

    /*              
                    PASSOU PELAS DUAS SITUAÇÕES ACIMA?

                    ENTÃO ACHOU O NODO PRA REMOVER
    */

    if((*pointer)->pDir == NULL){       // SE NÃO TEM NODO NA DIREITA DESSE
        pAux = *pointer;                // PASSA O NODO PRA UM PONTEIRO AUXILIAR QUE VAI SER FREEADO
        *pointer = (*pointer)->pEsq;    // ARRUMA O PONTEIRO, O DA ESQUERDA VAI "SUBIR"
        free(pAux);
        return;


        /* REG REMOVER = 5 

                3
                    5   
                2         
                        
            (*pointer)->pEsq

                3
                    2   
        */
    }

    if((*pointer)->pEsq == NULL){       //SE NÃO TEM NODO NA ESQUERDA DESSE
        pAux = *pointer;                // PASSA O NODO PRA UM PONTEIRO AUXILIAR PRA FREE
        *pointer = (*pointer)->pDir;    // ARRUMA O PONTEIRO, O DA DIREITA VAI SUBIR
        free(pAux);
        return;

        /* REG REMOVER = 5 

                3           
                    5   
                        7        
                        
            (*pointer)->pDir

                3
                    7   
        */
    }

    if((*pointer)->pEsq != NULL){                   // SE TEM NODO FILHO, NA ESQUERDA DESSE
        antecessor(*pointer, &(*pointer)->pEsq);    // CHAMA FUNÇÃO ANTECESSOR
        return;
    }
    
    if((*pointer)->pDir != NULL){
        antecessor(*pointer, &(*pointer)->pDir);
        return;
    }
    
}

void antecessor(Pointer nodoRemover, Pointer *leftNodo){    // RECEBE O NODO A REMOVER, E O ENDEREÇO DO NODO QUE ESTÁ A ESQUERDA DELE
    Pointer pAux;                                           

    if((*leftNodo)->pDir != NULL){                            // SE TIVER UM NODO FILHO A DIREITA DESSE NODO
        antecessor(nodoRemover, &(*leftNodo)->pDir);          
        return;
    }
    
    nodoRemover->registro = (*leftNodo)->registro;          // 
    pAux = *leftNodo;
    *leftNodo = (*leftNodo)->pEsq;
    free(pAux);
}


void inicializa(Pointer *agenda){
    *agenda = NULL;
}