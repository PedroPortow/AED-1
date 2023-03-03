#include <stdlib.h>
#include <stdio.h>

/*
•Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.
Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
Não pode usar struct em todo o programa.
Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
Implementar a base de dados da agenda usando lista duplamente ligada
Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.

*/

void *AdicionarPessoa( void *pBuffer );
void *RemoverPessoa( void *pBuffer );
void ListarPessoas( void *pBuffer );
void BuscarPessoa( void *pBuffer );


void Menu() {
    printf( "--- Selecione uma opcao --- \n" );
    printf( "1) Adicionar pessoa: \n" );
    printf( "2) Remover pessoa: \n" );
    printf( "3) Listar pessoas: \n" );
    printf( "4) Buscar pessoa:  \n" );
    printf( "5) Sair \n" );
}



//void pBuffer
//Endereço 1 vai ser pra opção

int main(){
    void *pBuffer = (int *)malloc(sizeof(int));
    int **pOption = (int*) &pBuffer;

    *pOption = &pBuffer[0];

    if(!pBuffer){
        printf("Erro na alocacao de memoria :(");
        exit(1);
    }

    do{
        Menu();
        scanf("%d", **pOption);
        getchar();

    } while (**pOption != 5);

  return 0;
}

