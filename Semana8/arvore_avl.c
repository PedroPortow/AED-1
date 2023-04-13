#include <stdlib.h>
#include <stdio.h>

/*
    Fator de balanceamento: altura(left sub tree) - altura(right sub tree)

    Altura: Caminho da raiz até nó mais distante

    Insert: Inserir normalmente, calcular o FB, fazer balanceamento

*/

typedef struct Node {
    int key;
    struct Node* pLeft;
    struct Node* pRight;
} Node;

Node* create_node(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->pRight = NULL;
    newNode->pLeft = NULL;
    return newNode;
}

Node* insert(Node* treeNode, int key){

    // raiz nula => arvore vazia, só criar a raiz
    if (treeNode == NULL) {
        return create_node(key);
    }
    
    //  procura a chave na subárvore esquerda, se for menor que a chave da raiz
    if (key < treeNode->key) {
        treeNode->pLeft = insert(treeNode->pLeft, key);
    }
    // procura a chave na subárvore direita, se for maior que a chave da raiz
    else if (key > treeNode->key) {
        treeNode->pRight = insert(treeNode->pRight, key);
    }
    // retorna a raiz, se o node já ta na árvore. (naõ tem q balancear pqn  vai mudar nada
    else {
        return treeNode;
    }

    /*
        chegou aqui? achou a posição pra inserir. Vai ta no treeNode
    */

    // calcula o fator de balanceamento do nó atual
    int fb = FB(treeNode);

    /*   -1 <= FB <= 1 
        key = nó a ser incluido na posição certa já

        Rotação simples pra direita =  FB > 1 && key < root->Left->key 
            (significa que a subarvore  )

    */

    // realiza o rebalanceamento da árvore, se necessário
    if (fb > 1 && treeNode->pLeft->key > key) {
        // se o fator de balanceamento é maior que 1 e a chave é menor que a chave do filho esquerdo
        // realiza uma rotação simples para a direita
        return rotate_right(treeNode);
    }
    if (fb < -1 && treeNode->pRight->key < key) {
        // se o fator de balanceamento é menor que -1 e a chave é maior que a chave do filho direito
        // realiza uma rotação simples para a esquerda
        return rotate_left(treeNode);
    }
    if (fb > 1 && treeNode->pLeft->key < key) {
        // se o fator de balanceamento é maior que 1 e a chave é maior que a chave do filho esquerdo
        // realiza uma rotação dupla: uma rotação simples para a esquerda seguida por uma rotação simples para a direita
        treeNode->pLeft = rotate_left(treeNode->pLeft);
        return rotate_right(treeNode);
    }
    if (fb < -1 && treeNode->pRight->key > key) {
        // se o fator de balanceamento é menor que -1 e a chave é menor que a chave do filho direito
        // realiza uma rotação dupla: uma rotação simples para a direita seguida por uma rotação simples para a esquerda
        treeNode->pRight = rotate_right(treeNode->pRight);
        return rotate_left(treeNode);
    }

    // retorna a raiz atualizada
    return treeNode;
}

int FB (Node* treeNode){
    if(treeNode == NULL)
        return 0;

    return Altura(treeNode->pLeft) - Altura(treeNode->pRight);  //vai calcular a altura, -1 <= FB <= 1
}

int Altura(Node* root){

    int heightLeft, heightRight;

    if(root == NULL)
        return 0;

    heightLeft  = Altura(root->pLeft);
    heightRight = Altura(root->pRight);

    if( heightLeft > heightRight ){
        return heightLeft + 1;          //Somando altura do nó atual :)
    } else {
        return heightRight + 1;
    }
}




int main(){



    return 0;
}