#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* pLeft;
    struct node* pRight;
} node_t;

node_t* new_node(int key) {
    node_t* node = (node_t*) malloc(sizeof(node_t));    // Criando um novo nó
    node->key = key;                                    // Setando a key
    node->pLeft = NULL;                                 //Arrumando os ponteiros
    node->pRight = NULL;
    return node;                                        // RETORNA O NÓ CRIADO SOMENTE!
                                                        // (ainda não é inserido)
}

node_t* insert(node_t* node, int key) {                 

    // Se a árvore estiver vazia, cria um novo nó e retorna
    if (node == NULL) {                                      // NODE vai ser a raiz, se for null ainda n tem nada na arvore
        return new_node(key);                           
    }

    // Caso contrário, segue pela subárvore esquerda ou direita
    if (key < node->key) {
        node->pLeft = insert(node->pLeft, key);
    } else {
        node->pRight = insert(node->pRight, key);
    }

    return node;                                            // Se chegar aqui, significa que achou a posição pra inserir! aí insere
}

node_t* search(node_t* node, int key) {
    // Se o nó for nulo ou o valor for encontrado, retorna o nó
    if (node == NULL || node->key == key) {                        
        return node;
    }

    // Se o valor for menor que o valor do nó atual, segue para a subárvore esquerda
    if (key < node->key) {
        return search(node->pLeft, key);
    }

    // Caso contrário, segue para a subárvore direita
    return search(node->pRight, key);
}

void print_tree(node_t* node, int indent) {
    if (node == NULL) {
        return;
    }
    // Imprime a subárvore direita com indentação
    print_tree(node->pRight, indent + 4);
    // Imprime o nó atual com indentação
    for (int i = 0; i < indent; i++) {
        printf(" ");
    }
    printf("%d\n", node->key);
    // Imprime a subárvore esquerda com indentação
    print_tree(node->pLeft, indent + 4);
}

node_t* delete_node(node_t* node, int key) {

    // ARVORE VAZIA? retorna NULL PQ N TEM OQ EXLCUIR
    if (node == NULL) {
        return NULL;
    }

    // Se o valor a ser removido é menor que o valor do nó atual, segue para a subárvore esquerda (MESMA COISA DOS OUTROS SÓ VAI SEGUINDO...)
    if (key < node->key) {
        node->pLeft = delete_node(node->pLeft, key);
    }
    // Se o valor a ser removido é maior que o valor do nó atual, segue para a subárvore direita (MESMA COISA DOS OUTROS SÓ VAI SEGUINDO...)
    else if (key > node->key) {
        node->pRight = delete_node(node->pRight, key);
    }
    else {                                                  // SE CHEGAR AQUI, ESSE É O NÓ A SER REMOVIDO
        /*
            Caso 1: o nó a ser removido não tem filhos
            Simplesmente remover ele :)
        */
        if (node->pLeft == NULL && node->pRight == NULL) {
            free(node);
            node = NULL;
        }
        /*
            Caso 2: o nó a ser removido tem apenas um filho
            Pode ta a direita, ou a esquerda
        */
        else if (node->pLeft == NULL) {     // SE TEM FILHO PRA DIREITA
            node_t* temp = node;            // passa aqui pra depois dar free    
            node = node->pRight;            //o nó atual vai passar a ser o nó que ta sendo apotando pelo pRight :)
            free(temp); 
        }
        else if (node->pRight == NULL) {      // SE TEM FILHO PRA ESQUERDA
            node_t* temp = node;              // passa aqui pra depois dar free    
            node = node->pLeft;               // NÓ ATUAL VAI SER O QUE ESTA A ESQUERDA
            free(temp);
        }
       /*
                Caso 3: o nó a ser removido tem dois filhos 

                SE O NÓ A SER REMOVIDO TIVER NA ESQUERDA
                    DEVE SER SUBSTITUIDO PELO NÓ MAIS A DIREITA DA SUBARVORE DIREITA (OU SEJA O MAIOR NÓ)
                SE O NO TIVER NA DIREITA
                    DEVE SER SUBSTITUIDO PELO NÓ MAIS A ESQUERDA DA SUBARVORE ESQUERDA (OU SEJA O MENOR NÓ)

       */
        else {
            // Encontra o sucessor do nó a ser removido (o menor valor na subárvore direita)
            node_t* temp = node->pRight;    //
            while (temp->pLeft != NULL) {   // PRA ENCONTRAR O MENOR VALOR NA SUBARVORE DA DIREITA
                temp = temp->pLeft;         
            }
            // Copia o valor do sucessor para o nó a ser removido
            node->key = temp->key;
            // Remove o sucessor
            node->pRight = delete_node(node->pRight, temp->key);
        }
    }
    return node;
}

void print_root(node_t* root) {
    printf("Raiz: %d\n", root->key);
}

void print_preorder(node_t* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->key);   // chega no nó e printa
    print_preorder(node->pLeft);
    print_preorder(node->pRight);
}

void print_central(node_t* node) {
    if (node == NULL) {
        return;
    }
    print_central(node->pLeft); //printa toda esquerda
    printf("%d ", node->key);
    print_central(node->pRight); //printa toda direita
}

void print_postorder(node_t* node) {
    if (node == NULL) {
        return;
    }
    print_postorder(node->pLeft);   //visita todas arvores e volta printando
    print_postorder(node->pRight);  
    printf("%d ", node->key);
}

// Função principal
int main() {
    node_t* root = NULL;

    // Inserindo valores na árvore
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 8);
    root = insert(root, 7);
    root = insert(root, 9);
    // root = insert(root, 6/0);
    // root = insert(root, 80);

    // Imprimindo a árvore em ordem
    printf("Árvore em ordem: \n");
    print_central(root);
    printf("\n");

    // Removendo um nó da árvore
    int key = 8;
    root = delete_node(root, key);

    // Imprimindo a árvore atualizada em ordem
    printf("Árvore atualizada em ordem: \n");
    print_postorder(root);
    // print_tree(root, 0);
    printf("\n");
    print_root(root);

    return 0;
}