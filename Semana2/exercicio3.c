#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NAME_SIZE 10
#define TEL_SIZE 12

typedef struct {
    char nome[NAME_SIZE];
    int idade;
    char telefone[TEL_SIZE];
} Pessoa;

void menu();
void *adicionarPessoa(void *pBuffer, int *qtdPessoas);
void *removerPessoa(void *pBuffer, int *qtdPessoas);
void listarPessoas(void *pBuffer, int *qtdPessoas);
void buscarPessoa(void *pBuffer, int *qtdPessoas);


int main(){
  int option;
  void *pBuffer = NULL;
  int *qtdPessoas;

  qtdPessoas = (int *) malloc(sizeof(int));
  if(!qtdPessoas){
    printf("Alocação de mem falhou");
    return 0;
  }
  *qtdPessoas = 0;

  do{
    menu();
    scanf("%d", &option);
    getchar();

      switch (option){
        case 1:
          pBuffer = adicionarPessoa(pBuffer, qtdPessoas);
          break;
        case 2:
          pBuffer = removerPessoa(pBuffer, qtdPessoas);
          break;
        case 3:
          listarPessoas(pBuffer, qtdPessoas);
          break;
        case 4:
          buscarPessoa(pBuffer, qtdPessoas);
          break;
        default:
          free(qtdPessoas);
          free(pBuffer);
          break;
      }
    } while (option != 5);



  return 0;
}

void menu() {
  printf("--Selecione uma opcao-- \n");
  printf("1) Adicionar pessoa: \n");
  printf("2) Remover pessoa: \n");
  printf("3) Listar pessoas: \n");
  printf("4) Buscar pessoa:  \n");
  printf("5) Sair \n");
}


void *adicionarPessoa(void *pBuffer, int *qtdPessoas) {
    Pessoa *pessoa;

    char nome[NAME_SIZE];
    int idade;
    char telefone[TEL_SIZE];

    pBuffer = realloc(pBuffer, sizeof(int) + (*qtdPessoas + 1) * sizeof(Pessoa)); //alocando memória pra nova pessoa

    if(!pBuffer){
      printf("Erro na alocação de memoria");
      exit(1);
    }

    pessoa = (Pessoa *) (pBuffer + sizeof(int)); //Faz com que a pessoa criada, aponte para o endereço de memoria que a nova pessoa vais ser armazenada

    printf("Nome: ");
    // scanf("%s", nome);
    fgets(nome, NAME_SIZE, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &idade);
    getchar();

    printf("Telefone: ");
    // scanf("%s", telefone);
    fgets(telefone, TEL_SIZE, stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    sprintf(pessoa[*qtdPessoas].nome, "%s", nome);
    pessoa[*qtdPessoas].idade = idade;
    sprintf(pessoa[*qtdPessoas].telefone, "%s", telefone);

    (*qtdPessoas)++;

    printf("Pessoa adicionada\n");

    return pBuffer;
}

void listarPessoas(void *pBuffer, int *qtdPessoas) {
  Pessoa *pessoas;

  if (!pBuffer || *qtdPessoas == 0) {
      printf("Não há pessoas cadastradas.\n");
      return;
  }

  pessoas = (Pessoa *) (pBuffer + sizeof(int));

  printf("Pessoas cadastradas:\n");

  for (int i = 0; i < *qtdPessoas; i++) {
      printf("\n\n");
      printf("Nome: %s\n", pessoas[i].nome);
      printf("Idade: %d\n", pessoas[i].idade);
      printf("Telefone: %s\n", pessoas[i].telefone);
      printf("\n\n");
  }
}

void* removerPessoa(void *pBuffer, int *qtdPessoas){
  bool encontrouPessoa = false;
  Pessoa *pessoa;
  pessoa = (Pessoa *) (pBuffer + sizeof(int));

  if(!pBuffer || *qtdPessoas == 0){
    printf("\nLista de pessoas esta vazia");
    exit(1);
  }

  char pessoaRemover[NAME_SIZE];

  printf("Nome da pessoa para remover: \n");
  fgets(pessoaRemover, NAME_SIZE, stdin);
  pessoaRemover[strcspn(pessoaRemover, "\n")] = '\0';


  for(int i = 0; i < *qtdPessoas; i++){
    if(strcmp(pessoa[i].nome, pessoaRemover) == 0){
      for(int j = i; j < *qtdPessoas - 1; j++){
        pessoa[j] = pessoa[j + 1];
      }
      encontrouPessoa = true;
      (*qtdPessoas)--;
      pBuffer = realloc(pBuffer, sizeof(int) + (*qtdPessoas) * sizeof(Pessoa));

      if(!pBuffer){
        printf("Alocação de mem falhou \n");
        return 0;
      }

      printf("Pessoa %s removida \n", pessoaRemover);
      return pBuffer;
    } 
  }  

  if(encontrouPessoa == false){
    printf("Pessoa não foi encontrada na lista de Pessoas");
  }

  return pBuffer;
}

void buscarPessoa(void *pBuffer, int *qtdPessoas){
  bool achouPessoa = false;

  Pessoa *pessoas;
  pessoas = (Pessoa *) (pBuffer + sizeof(int));

  char pessoaBuscar[NAME_SIZE];

  if(!pBuffer || *qtdPessoas == 0){
    printf("\nLista de pessoas esta vazia");
    exit(1);
  }

  printf("Nome da pessoa para buscar: \n");
  fgets(pessoaBuscar, NAME_SIZE, stdin);
  pessoaBuscar[strcspn(pessoaBuscar, "\n")] = '\0';

  for(int i = 0 ; i < *qtdPessoas; i++){
    if(strcmp(pessoas[i].nome, pessoaBuscar) == 0){
      achouPessoa = true;
      printf("\n\n");
      printf("Nome: %s\n", pessoas[i].nome);
      printf("Idade: %d\n", pessoas[i].idade);
      printf("Telefone: %s\n", pessoas[i].telefone);
      printf("\n\n");
    }
  }

  if(achouPessoa == false){
    printf("Pessoa não encontrada na lista \n");
    exit(1);
  }

}