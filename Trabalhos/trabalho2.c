#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int val;
    struct SNode *next;
} SNode;

typedef struct{
    SNode *pFirst;
    int qtdNodos;
} Lista; 

typedef struct{
    int valorPilha;
} ValoresPilha; 

typedef struct{
    ValoresPilha *valores;
    int limite;
    ValoresPilha *topo;
    ValoresPilha *base;
} Pilha;

bool isPalindrome(struct SNode* head);
void Menu();
bool Push(Lista *pLista, SNode *node, int index);
void PushPilha(Pilha *pilha, ValoresPilha *valorPilha);

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
                SNode *node = malloc(sizeof(SNode));
                printf("Digite numero: \n");
                scanf("%d", &node->val);
                printf("Posicao na lista: \n");
                scanf("%d", &index);

                resposta = Push(lista, node, index);
                if(resposta == true)
                    printf("Elemento adicionado com sucesso");
                else
                    printf("Falha na insercao \n");
                break;
            }
            case 2: 
            {
                int resposta = 0;
                resposta = isPalindrome((struct SNode *)lista->pFirst);
                printf("%d", resposta);
                break;
            }
            default:  
                break;
        }
        
    } while(option != 3);

    return 0;
}

void Menu(){
    printf("=======\n");
    printf("1) Inserir na lista\n");
    printf("2) Verificar se e palindromo\n");
}

bool Push(Lista *pLista, SNode *node, int index){
    SNode *nodoAnterior, *nodoAtual;


    if(index > pLista->qtdNodos){
        return false; 
    }

    if(pLista->pFirst == NULL && index != 0){
        printf("Posicao invalida ");
        return false;
    } else if(pLista->pFirst == NULL && index == 0){
        pLista->pFirst = node;
        pLista->pFirst->next = NULL; //aq ainda n vai ter proximo
        pLista->qtdNodos++;
        return true;
    } else if(index == 0){
        node->next = pLista->pFirst->next;
        pLista->pFirst = node;
        pLista->qtdNodos++;
        return true;
    } else{

        //aq caso n for na primeira posicao, tem q fazer aquilo do pAnterior e pAtual
        nodoAnterior = NULL;
        nodoAtual = pLista->pFirst;
          for (int i = 0; i < index; i++) {
            nodoAnterior = nodoAtual;
            nodoAtual = (SNode *)nodoAtual->next;
        }
        
        pLista->qtdNodos++;
        return true;
    }
\
    free(nodoAnterior);
    free(nodoAtual);

}

bool isPalindrome(struct SNode* head){
    SNode *pAtual = ( SNode *) head; 
    int count = 0; //CONTAGEM DE ELEMENTOS NA FILA
    ValoresPilha *valorPilha;
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->limite = 0;
    bool isPalindrome = false;
   
                                   
    while (pAtual != NULL) {
        valorPilha = (ValoresPilha *)pAtual->val;
        PushPilha(pilha, valorPilha);
        pAtual =  (SNode *)  pAtual->next; 
    }

    SNode *pAtualB =  (SNode *)  head;
    for(int i = 0; i < pilha->limite; i++){
        if(pAtual->val == pilha->valores[i].valorPilha){
            isPalindrome = true;
        } else{
            isPalindrome = false;
        }

        pAtualB = (SNode *)  pAtualB->next; 
    }

    return isPalindrome;
}

void PushPilha(Pilha *pilha, ValoresPilha *valorPilha){
    ValoresPilha *valores;

    pilha->limite++;
    valores = (ValoresPilha *)malloc(sizeof(ValoresPilha) * pilha->limite);

    size_t size = sizeof(ValoresPilha) * pilha->limite - 1;;
    memcpy(valores, pilha->valores, size);

    free(pilha->valores);

    pilha->valores = valores;

    pilha->valores[pilha->limite - 1] = *valorPilha;
    pilha->topo = &pilha->valores[pilha->limite - 1];
    pilha->base = pilha->valores;
}

// Pessoa *pessoas;

//     pilha->limite++;
//     pessoas = (Pessoa *)malloc(sizeof(Pessoa) * pilha->limite);