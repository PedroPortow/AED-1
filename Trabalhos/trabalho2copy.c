#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int val;
    struct SNodeLista *next;
} SNodeLista;

typedef struct{
    SNodeLista *pFirst;
    int qtdNodos;
} Lista; 

typedef struct{
    int valorPilha;
} SNodePilha; 

typedef struct{
    SNodePilha *valores;
    SNodePilha *topo;
    SNodePilha *base;
    int limite;
} Pilha;

void Menu();
bool isPalindrome(struct SNodeLista* head);
bool PushLista(Lista *pLista, SNodeLista *node, int index);
void PushPilha(Pilha *pilha, SNodePilha *valorPilha);
bool EmptyPilha(Pilha *pilha);
void Listar(Lista *lista);
SNodePilha *PopPilha(Pilha *pilha);
void CopiaPilha(SNodePilha *valores, int limite, SNodePilha *pilhaNodes, int lastPos);

int main(){

    int option = 0;
    Lista *lista = malloc(sizeof(Lista));
    lista->pFirst = NULL;
    lista->qtdNodos = 0;

    do{
        Menu();
        scanf("%d", &option);

        switch ( option ){
            case 1:
            {
                int index;
                bool resposta;
                SNodeLista *node = malloc(sizeof(SNodeLista));
                printf("Digite numero: ");
                scanf("%d", &node->val);
                printf("Posicao na lista: ");
                scanf("%d", &index);

                resposta = PushLista(lista, node, index);
                if(resposta == true)
                    printf("Elemento adicionado com sucesso \n");
                else
                    printf("Falha na insercao\n");

                Listar(lista);
                break;
            }
            case 2: 
            {
                int resposta = 0;
                resposta = isPalindrome((struct SNodeLista *) lista->pFirst);
                if(resposta == 1){
                    printf("É palindromo\n");
                } else if(resposta == 0){
                    printf("Não é palindromo\n");
                }
                break;
            }
            default:  
                break;
        }
        
    } while(option != 3);

    return 0;
}

void Menu(){
    printf("-----------------------------------\n");
    printf("1) Inserir na lista\n");
    printf("2) Verificar se e palindromo\n");
    printf("-----------------------------------\n");
}

bool PushLista(Lista *pLista, SNodeLista *node, int index){
    SNodeLista *nodoAnterior, *nodoAtual;

    if(index > pLista->qtdNodos){
        return false; 
    } else if(pLista->pFirst == NULL && index == 0){
        pLista->pFirst = node;
        pLista->pFirst->next = NULL; 
        pLista->qtdNodos++;

        return true;
    } else if(index == 0){
        node->next = pLista->pFirst->next;
        pLista->pFirst = node;
        pLista->qtdNodos++;
        
        return true;
    } else{
        nodoAnterior = NULL;
        nodoAtual = pLista->pFirst;
        for (int i = 0; i < index; i++) {
            nodoAnterior = nodoAtual;
            nodoAtual = (SNodeLista *)nodoAtual->next;
        }
        
        node->next = (struct SNodeLista *)nodoAtual;
        nodoAnterior->next = (struct SNodeLista *)node;
        pLista->qtdNodos++;
    }

    free(nodoAnterior);
    free(nodoAtual);

    return true;
}

bool isPalindrome(struct SNodeLista* head){
    SNodeLista *pAtual = ( SNodeLista *) head; 
    int cont = 0; //CONTAGEM DE ELEMENTOS NA Lista

    SNodePilha *valorPilha;

    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->limite = 0;
    pilha->base = NULL;
    pilha->topo = NULL;
    pilha->valores = NULL;

    bool isPalindrome = false;
                                   
    while (pAtual != NULL) {
        valorPilha = (SNodePilha *)malloc(sizeof(SNodePilha));
        valorPilha->valorPilha = pAtual->val;
        PushPilha(pilha, valorPilha);
        pAtual = (SNodeLista *) pAtual->next;
        cont++;
        free(valorPilha);
    }

    SNodeLista *pAtualB =  (SNodeLista *) head;
    SNodePilha *valorPopPilha = malloc(sizeof(SNodePilha));
    
    for(int i = 0; i < cont && pAtualB != NULL; i++){ 
        valorPopPilha = (SNodePilha *) PopPilha(pilha);
        if(pAtualB->val != valorPopPilha->valorPilha){
            isPalindrome = false;
            break;
        } else{
            isPalindrome = true;
        }

        pAtualB = (SNodeLista *) pAtualB->next; 
    }

    free(pilha->valores);
    free(pilha);
    free(valorPilha);
    free(valorPopPilha);
    free(pAtualB);
    free(pAtual);

    return isPalindrome;
}

void Listar(Lista *pLista){
    SNodeLista *pAtual = pLista->pFirst; 

    printf("---- LISTA ATUAL ----\n");                        
    while (pAtual != NULL) {
        printf("%d\n", pAtual->val);
        pAtual = (SNodeLista *)pAtual->next; 
    }

}

void CopiaPilha(SNodePilha *valores, int limite, SNodePilha *pilhaNodes, int lastPos){
    size_t size = sizeof(SNodePilha) * lastPos;
    memcpy(valores, pilhaNodes, size);
}


void PushPilha(Pilha *pilha, SNodePilha *valorPilha){
    SNodePilha *nodesPilha;

    pilha->limite++;

    nodesPilha = (SNodePilha *)malloc(sizeof(SNodePilha) * pilha->limite);

    if(!nodesPilha){
        printf("Erro na alocacao");
    }

    CopiaPilha(nodesPilha, pilha->limite, pilha->valores, pilha->limite - 1); 

    if(pilha->valores){
        free(pilha->valores);
    }

    pilha->valores = nodesPilha;
    pilha->valores[pilha->limite - 1] = *valorPilha;
    pilha->topo = &pilha->valores[pilha->limite - 1];
    pilha->base = pilha->valores;
}


bool Empty(Pilha *pilha){
    return pilha->topo == NULL;
}

SNodePilha *PopPilha(Pilha *pilha){
    if(Empty(pilha)){
        return NULL;
    }

    SNodePilha *valorTopo;

    valorTopo = pilha->topo;
    pilha->limite--;
    pilha->topo = &pilha->valores[pilha->limite - 1];

    return valorTopo;
}

