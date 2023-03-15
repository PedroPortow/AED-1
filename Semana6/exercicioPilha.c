#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char nome[30];
    int idade;
} Pessoa; //struct dos nos da pilha

typedef struct{
    Pessoa *pessoas;
    Pessoa *topo;
    Pessoa *base;
    int limite;
} Pilha; //struct da pilha (limite é topo + 1)

void Menu();
bool Push(Pilha *pilha, Pessoa *pessoa); 
void Pop(Pilha *pilha);
bool Full(Pilha *pilha);
bool Empty(Pilha *pilha);
void Reset(Pilha *pilha);
void Listar(Pilha *pilha);

bool RemovePessoaPorNome(Pilha *pilha, char *nome);

int main(){
    int option;
    Pilha *pilha;

    pilha = malloc(sizeof(Pilha));

    do{
        Menu();
        scanf("%d", &option);

        switch ( option ){
            case 1:
            {
                Pessoa *pessoa = malloc(sizeof(Pessoa));
                bool resposta = false;
                printf("Nome: ");
                scanf("%s", (char *)&pessoa->nome);
                printf("Idade: ");
                scanf("%d", &pessoa->idade);
                resposta = Push(pilha, pessoa);
                if(resposta == true){
                    printf("PESSOA ADD");
                }
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
                scanf("%s", &nome);
                resposta = RemovePessoaPorNome(pilha, nome);
                if(resposta == true){
                    printf("PESSOA ADD");
                }
                break;
            }

            case 4:
                Reset(pilha);
            case 5:
                Listar(pilha);
            case 6:
                free(pilha);
                exit(1);
                
        }    
    } while(option !=  6);

}

void CopiaPilha(Pessoa *pessoas, int limite, Pessoa *pilhaPessoas, int lastPos){
    size_t size = sizeof(Pessoa) * lastPos;
    memcpy(pessoas, pilhaPessoas, size);
}

void Menu(){
    printf("=== SELECIONE UMA OPCAO ===\n");
    printf("1) Inserir pessoa\n");
    printf("2) Delete pessoa do topo\n");
    printf("3) Deletar pessoa por nome\n");
    printf("4) Limpar pilha\n");
    printf("5) Listar pessoas\n");
    printf("6) Sair do programa \n");
}

bool Push(Pilha *pilha, Pessoa *pessoa){
    Pessoa *pessoas;

    pilha->limite++;
    pessoas = (Pessoa *)malloc(sizeof(Pessoa) * pilha->limite);

    if(!pessoas){
        printf("Erro na alocacao");
        return false;
    }

    CopiaPilha(pessoas, pilha->limite, pilha->pessoas, pilha->limite - 1); //copiando as pessoas

    if(pilha->pessoas){
        free(pilha->pessoas);
    }

    pilha->pessoas = pessoas;

    pilha->pessoas[pilha->limite - 1] = *pessoa;
    pilha->topo = &pilha->pessoas[pilha->limite - 1];
    pilha->base = pilha->pessoas;

    return true;
}

bool Empty(Pilha *pilha){
    return pilha->topo == 0;
}



void Pop(Pilha *pilha){
    if(Empty(pilha)){
        return;
    }
    Pessoa *pessoa;

    pessoa = pilha->topo; //acessando a pessoa a ser removida

    Pessoa *pessoas; 
    pilha->limite--;

    if(pilha->limite == 0){
        free(pilha->pessoas);
        Reset(pilha);
        return;
    }

    size_t size = sizeof(Pessoa) * pilha->limite; //o tamanho da nova pessoa
                                                // * a quantidadende pessoas
    pessoas = (Pessoa *)malloc(size);

    if(!pessoas){
        printf("erro na alocacao");
        exit(1);
    }    

    CopiaPilha(pessoas, pilha->limite, pilha->pessoas, pilha->limite + 1);
    free(pilha->pessoas);

    pilha->pessoas = pessoas;
    pilha->topo = &pilha->pessoas[pilha->limite - 1];
    pilha->base = pilha->pessoas;

    return;
}

void Reset(Pilha *pilha){
    pilha->topo = NULL;
    pilha->base = NULL;
    pilha->pessoas = NULL;
    pilha->limite = NULL; 
}

void Listar(Pilha *pilha){
    Pilha *pilhaAux = malloc(sizeof(Pilha));
    pilhaAux->limite = pilha->limite;
    pilhaAux->pessoas = malloc(sizeof(pilha->pessoas));

    for(int i = 0; i < pilha->limite; i++){
        Pessoa *pessoa = &pilha->pessoas[pilha->limite - i - 1];
        memcpy(&pilhaAux->pessoas[i], pessoa, sizeof(Pessoa));
    }

    for(int i = 0; i < pilhaAux->limite; i++){
        printf("%s", pilhaAux->pessoas[i].nome);
        printf("%d",pilhaAux->pessoas[i].idade);
    }


    free(pilhaAux->pessoas);
    free(pilhaAux);
}

bool RemovePessoaPorNome(Pilha *pilha, char *nome){
    if(Empty(pilha)){
        printf("Pilha vazia.");
        return false;
    }

    bool removed = false;

    Pilha *pilhaAux = malloc(sizeof(Pilha));
    pilhaAux->limite = pilha->limite;
    pilhaAux->pessoas = malloc(sizeof(pilha->pessoas));

    for(int i = 0; i < pilha->limite; i++){
        if(!(strcmp(pilha->pessoas[i].nome, nome) == 0)){
            Pessoa *pessoa = malloc(sizeof(Pessoa));
            strcpy(pessoa->nome, pilha->pessoas[i].nome);
            strcpy(pessoa->idade, pilha->pessoas[i].idade);
            Push(pilhaAux, pessoa); 
        } else{
            Pop(pilha);
            removed = true;
            break;
        }
    }

    if(removed){
        for(int i = 0; i < pilhaAux->limite; i++){
            Push(pilha, &pilhaAux->pessoas[i]);
        }
    }

    return removed;
}
