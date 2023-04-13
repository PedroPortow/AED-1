#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef long KEY_T;

typedef struct Register{
    KEY_T key;
    char nome[12];
    int idade;
    int telefone;
} Register;

typedef struct Node{
    Register reg;
    Pointer *pLeft;
    Pointer *pRight;
} Node;

typedef struct Node * Pointer;

void inicializa(Pointer *agenda);
void Push(Register reg, Pointer *agenda);

int main(){
    Pointer *agenda;

    incializa(agenda);



    return 0;
}

void Push(Register reg, Pointer *agenda){
    if(*agenda == NULL) { //se agenda ta vazia
        *agenda = (Pointer)malloc(sizeof(Node));
        (*agenda)->reg = reg;
        (*agenda)->pLeft = NULL;
        (*agenda)->pRight = NULL;
        return;
    }
    if(reg.key < (*agenda)->reg.key){
        Push(reg, &(*agenda)->pLeft);
    }
    if (reg.key > (*agenda)->reg.key){
        Push(reg, &(*agenda)->pRight);
    } else {
        printf("Registro ja tem na arvpre\n");
    }
}

void inicializa(Pointer *agenda){
    *agenda = NULL;
}

void Pesquisa(Register *reg, Pointer *agenda){
    if(agenda == NULL){
        printf("Registor nao esta presente na arvore\n");
    }
    if (reg->key < (*agenda)->reg.key){
        Pesquisa(reg, &(*agenda)->pLeft);
    }
    if (reg->key > (*agenda)->reg.key){
        Pesquisa(reg, &(*agenda)->pRight);
    }
    else *reg = (*agenda)->reg;
}

void Pop(Register reg, Pointer *agenda){
    Pointer aux;

    if(*agenda == NULL){
        printf("Erro nao esta presente na arvore");
        return;
    }
    if(reg.key < (*agenda)->reg.key) {
        Pop(reg, &(*agenda)->pLeft);
        return;
    }
    if(reg.key > (*agenda)->reg.key){
        Pop(reg, &(*agenda)->pRight);
        return;
    }
    if((*agenda)->pRight == NULL){
        aux = *agenda;
        *agenda = (*agenda)->pLeft;
        free(aux);
        return;
    }
    if((*agenda)->pLeft != NULL) {
        Antecessor(*agenda, &(*agenda)->pLeft);
        return;
    }
    // ((*agenda)->)
}