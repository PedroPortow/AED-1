#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.

Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.

Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
Não pode usar struct em todo o programa.

Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.

Implementar a base de dados da agenda usando lista duplamente ligada
Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.

    CADA PESSOA VAI TER ALOCAR ESPAÇO PRA 
        NOME DA PESSOA (char * 12)
        IDADE DA PESSOA (int)
        TELEFONE DA PESSOA (int)
        ponteiro pra proxima? 
        ponteiro pra antes?

        da pra fazer esses dois serem um ponteiro pra ponteiro
        pessoa.ponteiro -> pessoa2.ponteiro ...


                PESSOA
         NOME | IDADE | TELEFONE  | pPessoaAnterior | pProximaPessoa
    tamanho pra acessar esses 2 ponteiros em uma tem q ser definido 
    \
    
                                          VAI SER O NOME
    pBuffer = OPCAO | CONTAGEM PESSOAS | PESSOA SER REMOVIDA | PESSOAS..
*/

#define TAMANHO_OPCAO (sizeof(int)) //opcao do menu
#define TAMANHO_CONTADOR (sizeof(int)) //CONTAGEM PESSOAS
#define TAMANHO_REMOVE (sizeof(char) * 12) // PESSOA A SER REMOVIDA


#define TAMANHO_NOME (sizeof(char) * 12)
#define TAMANHO_IDADE (sizeof(int))
#define TAMANHO_TELEFONE (sizeof(int))

#define TAMANHO_PONTEIROS_ORDEM (sizeof(void **) * 2) //pro malloc

#define PESSOA TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + TAMANHO_PONTEIROS_ORDEM //tamanho de uma PESSOA

#define P_NEXT_PERSON (TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + sizeof(void **)) //pra acessar na pessoa, o ponteiro ** que aponta pra proxima
#define P_PREVIOUS_PERSON (TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE)  //pra acessar na pessoa, o ponteiro ** que aponta pra ANTERIOR

void PushPessoa( void *pBuffer );
void RemoverPessoa( void *pBuffer );
void ListarPessoas( void *pBuffer );
void BuscarPessoa( void *pBuffer );
void ResetPessoas( void *pBuffer );

void Menu() {
    printf( "--- Selecione uma opcao --- \n" );
    printf( "1) Adicionar pessoa \n" );
    printf( "2) Remover pessoa \n" );
    printf( "3) Listar pessoas \n" );
    printf( "4) Buscar pessoa  \n" );
    printf( "5) Resetar \n" );
    printf( "6) Sair \n" );
}

int main(){
    void *pBuffer = NULL;
    pBuffer = malloc(TAMANHO_OPCAO + TAMANHO_CONTADOR + TAMANHO_REMOVE );
    *(int *)(pBuffer + TAMANHO_OPCAO) = 0; //INICIALIZAND OCONTADOR DE PESSOAS COMO 0

    if(!pBuffer){
        printf("Erro na alocacao de memoria :(");
        exit(1);
    }

    do{
        Menu();
        scanf("%d", (int *)(pBuffer));
        getchar();

        switch(*(int *)(pBuffer)){
            case 1:
            {
                PushPessoa(pBuffer);
                break;
            }
            case 2:
            {
                RemoverPessoa(pBuffer);
                break;
            }
            case 3:
            {
                ListarPessoas(pBuffer);
                break;
            }
            case 4:
            {
                BuscarPessoa(pBuffer);
                break;
            }
            case 5:
            {
                ResetPessoas(pBuffer);
                break;
            }
            case 6:
            {
                ResetPessoas(pBuffer);
                free(pBuffer);
                exit(1);
            }
        }

    } while (*(int *)(pBuffer) != 7);

  return 0;
}

void PushPessoa( void *pBuffer ){
    int *qtdPessoas = (int *)( pBuffer + TAMANHO_OPCAO);
    void **head = (void **) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO + TAMANHO_REMOVE);

    /*
                        PESSOA
        NOME | IDADE | TELEFONE  | **pPessoaAnterior | **pProximaPessoa
    
    */

    //CRIANDO UM "NODO" PRA PESSOA
    void *pessoa = malloc(PESSOA); 

    if(!pessoa){
        printf("erro na alocacao");
        exit(1);
    }

    printf("Nome da pessoa: ");
    scanf("%s", (char *) pessoa); //nome vai ser escrito no primeiro endereço de memoria que vai ser o nome :)

    printf("Idade: ");
    scanf("%d", &*(int *)(pessoa + TAMANHO_NOME)); //vai ser escrito depois do nome

    printf("Telefone: ");
    scanf("%d", &*(int *)(pessoa + TAMANHO_NOME + TAMANHO_IDADE)); //vai ser escrito depois do nome

    // CASO DE NÃO TER PESSOA AINDA
    if(*qtdPessoas == 0){
        *(void **)(pessoa + P_PREVIOUS_PERSON) = NULL; 
        *(void **)(pessoa + P_NEXT_PERSON) = NULL;
        *head = pessoa;
    } else {
        void *pAtual = *head;
        void *pAnterior = NULL;

        //quando esse loop parar, vai ter a posição pra inserir essa pessoa
        while(pAtual != NULL){
            if(strcmp((char *) pAtual, (char *) pessoa) > 0){
                printf("xota");
                break;
            }
            pAnterior = pAtual;
            void **pProximaPessoa = (void **)(pAtual + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + sizeof(void **));
            pAtual = *pProximaPessoa;
        }

        //inserção no inicio da lista
        if(pAtual == *head){
            *(void **)(pessoa + P_PREVIOUS_PERSON) = NULL; // NÃO VAI TER PESSOA ANTES DESSA
            *(void **)(pessoa + P_NEXT_PERSON) = *head; // VAI APONTAR PRA PESSOA QUE TA NO HEAD AGORA
            *(void **)(*head + P_PREVIOUS_PERSON) = pessoa; // A PESSOA QUE TA NO HEAD NO MOMENTO, VAI APONTAR PRA ESSA QUE VAI SER INSERIDA ANTES
            *head = pessoa;
        } else if(pAtual == NULL){ // INSERÇÃO FIM DA LISTA
            //aqui pAnterior vai ser a proxima pessoa
            *(void **)(pessoa + P_PREVIOUS_PERSON) = pAnterior; // vai apontar pro ultimo elemento atuaçmente na lista, que vai ser o penultimo agr
            *(void **)(pessoa + P_NEXT_PERSON) = NULL; // não vai ter próxima pessoa
            *(void **)(pAnterior + P_NEXT_PERSON) = pessoa; // ajustando ponteiro da pessoa anterior pra apontar pra essa nova pessoa
        } else{ //entre duas pessoas
            *(void **)(pessoa + P_NEXT_PERSON) = pAtual;
            *(void **)(pessoa + P_PREVIOUS_PERSON) = pAnterior;
            *(void **)(pAnterior + P_NEXT_PERSON) = pessoa;
            *(void **)(pAtual + P_PREVIOUS_PERSON) = pessoa;
        }
    }

    (*qtdPessoas)++;
}

void RemoverPessoa(void *pBuffer){
    int *qtdPessoas = (int *)( pBuffer + TAMANHO_OPCAO);
    void **head = (void **) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO + TAMANHO_REMOVE);
    char *pessoaRemover = (char *) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO);

    if(*qtdPessoas == 0){
        printf("\nAgenda ta vazia!\n");
        return;
    }

    printf("Nome para remover: ");
    scanf("%s", (char *)pessoaRemover);

    void *pAtual = *head;
    void *pAnterior = NULL;

    //quando esse loop parar, vai ter a posição pra remover
    while(pAtual != NULL){
        void **pProximaPessoa = (void **)(pAtual + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + sizeof(void **));
       
        if(strcmp((char *) pAtual, (char *) pessoaRemover) == 0){
            void *pNextDaPessoaRemover = *pProximaPessoa;
            if(pAtual == *head && pNextDaPessoaRemover != NULL){ //pessoa do inicio ser removida, mas não tem só ela na lista
                *(void **)(pNextDaPessoaRemover + P_PREVIOUS_PERSON) = NULL;
                *head = pNextDaPessoaRemover;
                pAtual = NULL;
            } else if(pAtual == *head && pNextDaPessoaRemover == NULL){ //pessoa do inicio a ser removida, e só tem ela :)
                pAtual = NULL;
                free(*head);
                free(pAtual);
            } else if(pNextDaPessoaRemover == NULL){ // pessoa a ser removida é a ultima
                *(void **)(pAnterior + P_NEXT_PERSON) = NULL;
                pAtual = NULL;
                free(pAtual);
            } else{
                *(void **)(pAnterior + P_NEXT_PERSON) = pNextDaPessoaRemover;
                *(void **)(pNextDaPessoaRemover + P_PREVIOUS_PERSON) = pAnterior;
                free(pAtual);
            }

            (*qtdPessoas)--;
            return;
            break;
        }

        pAnterior = pAtual;
        pAtual = *pProximaPessoa;
    }

    /*
        LOOP TERMINADO
        pAtual = pessoa que tem que ser removida
        pAnterior = pessoa anterior a que tem que ser removida
        tem que arrumar o ponteiro da pessoa depois tbm
    */

}

void ListarPessoas(void *pBuffer){
    int *qtdPessoas = (int *)( pBuffer + TAMANHO_OPCAO);
    void **head = (void **) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO + TAMANHO_REMOVE);

    if (*qtdPessoas == 0) {
        printf("\nAgenda ta vazia!\n");
        return;
    }

    void *pAtual = *head;
    while (pAtual != NULL) {
        char *nome = (char *)pAtual;
        int *idade = (int *)(pAtual + TAMANHO_NOME);
        int *telefone = (int *)(pAtual + TAMANHO_NOME + TAMANHO_IDADE);
        void **pProximaPessoa = (void **)(pAtual + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + sizeof(void **));

        printf("-----------------\n");
        printf("Nome: %s\n", nome);
        printf("Idade: %d\n", *idade);
        printf("Telefone: %d\n", *telefone);
        printf("-----------------\n");

        pAtual = *pProximaPessoa;
    }
}

void ResetPessoas(void *pBuffer){ 
    void **head = (void **) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO + TAMANHO_REMOVE);

    if(!head){
        printf("Ta vazia \n");
        return;
    }

    void *pAtual = *head;
    int *qtdPessoas = (int *)( pBuffer + TAMANHO_OPCAO);
    *qtdPessoas = 0;

    while (pAtual != NULL) {
        void **pProximaPessoa = (void **)(pAtual + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + sizeof(void **));
        pAtual = *pProximaPessoa;
        void *pFree = pAtual;
        free(pFree);
    }
}

void BuscarPessoa( void *pBuffer ){
    int *qtdPessoas = (int *)( pBuffer + TAMANHO_OPCAO);
    void **head = (void **) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO + TAMANHO_REMOVE);
    char *pessoaProcurar = (char *) (pBuffer + TAMANHO_CONTADOR + TAMANHO_OPCAO);

    if(*qtdPessoas == 0){
        printf("\nAgenda ta vazia!\n");
        return;
    }

    printf("Nome para procurar: ");
    scanf("%s", (char *)pessoaProcurar);

    void *pAtual = *head;
    void *pAnterior = NULL;

    while(pAtual != NULL){
        void **pProximaPessoa = (void **)(pAtual + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE + sizeof(void **));
       
        if(strcmp((char *) pAtual, (char *) pessoaProcurar) == 0){
            char *nome = (char *)pAtual;
            int *idade = (int *)(pAtual + TAMANHO_NOME);
            int *telefone = (int *)(pAtual + TAMANHO_NOME + TAMANHO_IDADE);

            printf("-----------------\n");
            printf("Nome: %s\n", nome);
            printf("Idade: %d\n", *idade);
            printf("Telefone: %d\n", *telefone);
            printf("-----------------\n");
            
            return;   
            break;
        }

        printf("Pessoa não encontrada na agenda\n");
        
        pAnterior = pAtual;
        pAtual = *pProximaPessoa;
    }
}