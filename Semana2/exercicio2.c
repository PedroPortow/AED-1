#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* AdicionarNome ( char *listaNomes );
char* RemoverNome ( char *listaNomes );
void ListarNomes ( char *listaNomes );
void Sair ( char *listaNomes );

void Menu() {
	printf( "======= Selecione uma opcao ========= \n" );
	printf( "1) Adicionar nome \n" );
	printf( "2) Remover nome \n" );
	printf( "3) Listar \n" );
	printf( "4) Sair \n" );
}

int main() {
	int option;
	char* nomes = NULL;

	do{
		Menu();
		scanf( "%d", &option );
		getchar();

		switch ( option ) {
			case 1:
				nomes = AdicionarNome( nomes );
				break;
			case 2:
				nomes = RemoverNome( nomes );
				break;
			case 3:
				ListarNomes( nomes );
				break;
			case 4:
				Sair( nomes );
				break;
			default:
				break;      
		}
	} while ( option != 4 );

	free( nomes );
	return 0;
}

char* AdicionarNome ( char *listaNomes ) {

	int tamanhoNome = 30;

	char *nome = ( char * )malloc(( tamanhoNome ) * sizeof( char )); 

	printf( "Digite o nome: \n" );
	fflush( stdout ); 
	fgets( nome, tamanhoNome, stdin );
	nome[strcspn( nome, "\n" )] = 0; 
	strcat( nome, "-" );

	if( listaNomes == NULL ) { 
		listaNomes = ( char *)malloc(( strlen(nome) + 1 ) * sizeof( char ));
		strcpy( listaNomes, nome );
	} else { 
		listaNomes = ( char * )realloc( listaNomes, ( strlen( nome ) + strlen( listaNomes ) + 1 ) * sizeof( char )); //
		strcat( listaNomes, nome );
	}

	if( !listaNomes ){
		printf( "Nao foi possivel alocar mem" );
		exit(1);
	}

	free( nome );
	return listaNomes;
}


char* RemoverNome ( char *listaNomes ) {
	int tamanhoNome = 30;
	char *copiaLista = NULL;
	char *nomeDaLista = NULL;
	char *nomeRemover = NULL;
	char *novaLista = NULL;
	bool achouNome = false;

	if( listaNomes == NULL || strlen(listaNomes) == 0 ){
	printf("A lista de nomes esta vazia \n");
	exit(1);
	}

	nomeRemover = ( char *)malloc(( tamanhoNome ) * sizeof( char ));

	printf( "\nDigite o nome para ser removido: " );
	fflush( stdout );
	fgets( nomeRemover, tamanhoNome, stdin );
	nomeRemover[strcspn( nomeRemover, "\n" )] = 0; 

	copiaLista = ( char * )malloc( strlen( listaNomes ) * sizeof( char ));

	strcpy( copiaLista, listaNomes );

	nomeDaLista = strtok( copiaLista, "-" );

	while( nomeDaLista != NULL ){
		if( strcmp( nomeDaLista, nomeRemover ) != 0 ) {
			if( novaLista == NULL ){
				novaLista = ( char * )malloc(( strlen( nomeDaLista ) + 2 )  * sizeof( char ) );
				strcpy( novaLista, nomeDaLista );
			} else {
				novaLista = ( char * )realloc( novaLista, ( strlen( nomeDaLista ) + strlen( novaLista ) + 2 ));
				strcat( novaLista, nomeDaLista );
			}
			strcat( novaLista, "-" );
		} else {
			achouNome = true;
		}
		nomeDaLista = strtok( NULL, "-" );
	}

	if( achouNome == false ){
		printf( "o nome nao foi encontrado" );
	} else {
		listaNomes = ( char * )realloc( listaNomes, ( strlen( novaLista) + 1 ) * sizeof( char ));
		strcpy( listaNomes, novaLista );
	}


	free( nomeDaLista );
	free( copiaLista );
	free( novaLista );
	free( nomeRemover );
	return listaNomes;
}

void ListarNomes ( char *listaNomes ) {

	if ( listaNomes == NULL ) {
		printf( "\n A LISTA ESTA VAZIA \n" );
	} else {
		while ( *listaNomes ) {
			if ( *listaNomes != '-' ) {
				printf( "%c", *listaNomes++ );
			} else {
				listaNomes++;
				printf( "\n" );
			}
		}
	}
    
}

void Sair( char* listaNomes ) {
	free( listaNomes ); 
	listaNomes = NULL; 
}