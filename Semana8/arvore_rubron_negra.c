#include <stdlib.h>
#include <stdio.h>

enum Color {RED, BLACK};

typedef struct Node {
    int key;
    enum Color color;
    struct Node *pLeft;
    struct Node *pRight;
    struct Node *parent;
} Node;

Node* insert_case4(Node* treeNode);
Node* createNode(int key);
Node* createRoot(int key);
Node* getGrandparent(Node* treeNode);
Node* getTio(Node* treeNode);
Node* RSE (Node* node);
Node* RSD (Node* node);
Node* insert(Node* treeNode, int key);
Node* insert_case1(Node* treeNode);
Node* insert_case2(Node* treeNode);
Node* insert_case3(Node* treeNode);
Node* insert_case4(Node* treeNode);
Node* insert_case5(Node* treeNode);


void print_preorder(Node* node) {
   if (node == NULL) {
        return;
    }
    char* color_str = (node->color == RED) ? "RED" : "BLACK";
    printf("(%d, %s) ", node->key, color_str);
    print_preorder(node->pLeft);
    print_preorder(node->pRight);
}

void print_central(Node* node) {
    if (node == NULL) {
        return;
    }
    print_central(node->pLeft); //printa toda esquerda
    printf("%d ", node->key);
    print_central(node->pRight); //printa toda direita
}

int main(){
    Node* root = NULL;

    root = insert(root, 11);
    root = insert(root, 2);
    root = insert(root, 14);
    root = insert(root, 1);
    root = insert(root, 7);
    root = insert(root, 13);

    printf("preorder: ");
    print_preorder(root);
    printf("\n");
    printf("central: ");
    print_central(root);
    printf("\n");


    return 0;
}

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;
    return newNode;
}


Node* createRoot(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    newNode->parent = NULL;
    return newNode;
}

Node* getGrandparent(Node* treeNode){
    if((treeNode != NULL) && (treeNode->parent != NULL)){  // pra ter vô tem q ter pai ne
        return treeNode->parent->parent;
    } else {
        return NULL;
    }
}

Node* getTio(Node* treeNode){
    //lembrando que o tio pode ta na direita ou na esquerda, aqui n tem como saber onde o nó ta sendo inserido

    Node *grandparent = getGrandparent(treeNode); // pega o vô

    /*  INSERINDO Z:

                    B ( VÔ )
        D ( TIO )               A   (PAI)
                        Z (cara inserido) 
    */

    if(grandparent == NULL){
        return NULL;    //sem vô == sem tio
    } else if (treeNode->parent == grandparent->pLeft){     // aqui vamo descobrir se o tio ta pra direita ou pra esquerda
        return grandparent->pRight;                         // se o pai ta a esquerda do vô, significa que tio vai ta a direita do vô    
    } else {
        return grandparent->pLeft;                          // se não, vai ta na esquerda do vô
    }
}

Node* RSE (Node* node) {
    Node* right_child = node->pRight;
    Node* left_grandchild = right_child->pLeft;

    right_child->pLeft = node;
    node->pRight = left_grandchild;

    return right_child;
}

Node* RSD (Node* node) {
    Node* left_child = node->pLeft;
    Node* right_grandchild = left_child->pRight;

    left_child->pRight = node;
    node->pLeft = right_grandchild;

    return left_child;
}


Node* insert(Node* treeNode, int key){

    if(treeNode == NULL){
        return createRoot(key);
    }


    if(key < treeNode->key){
        treeNode->pLeft = insert(treeNode->pLeft, key);
    } else if( key > treeNode->key){
        treeNode->pRight = insert(treeNode->pRight, key);
    } else if( key == treeNode->key){
        return treeNode;
    }
    // Agora tem que checar o balanceamento...
    return insert_case1(treeNode);
}

Node* insert_case1(Node* treeNode){ /* CASO 1: RAIZ */
    if(treeNode->parent == NULL){
        treeNode->color = BLACK;
        return treeNode;
    } else {
        return insert_case2(treeNode);
    }
}

Node* insert_case2(Node* treeNode){ /* CASO 2: PAI É PRETO */
    if(treeNode->parent->color == BLACK){
        return treeNode;
    } else {
        return insert_case3(treeNode);
    }
}

Node* insert_case3(Node* treeNode){ /* CASO 3: O TIO DO ELEMENTO É VERMELHO, TEM QUE RECOLORIR */
    Node* tio = getTio(treeNode);

    if((tio != NULL) && (tio->color == RED)){   // tem tio e cor dele é vermelho, tem que pintar o tio e o pai
        Node* grandparent = getGrandparent(treeNode);

        treeNode->parent->color = BLACK;
        tio->color = BLACK;
        grandparent->color = RED;   // beleza pintou o vô, mas pode da merda pra cima, então tem que voltar pra primeira função passando o vô 
        return insert_case1(grandparent);
    } else {
        return insert_case4(treeNode);
    }
}

Node* insert_case4(Node* treeNode){ /* CASO 4: O TIO DO ELEMENTO É PRETO E O ELEMENTO É UM FILHO PRA ESQUERDA */
    Node* grandparent = getGrandparent(treeNode);

    if((treeNode == treeNode->parent->pRight) && (treeNode->parent == grandparent->pLeft)){   // pai ta pra esquerda do vô e filho ta pra direita do pai
        treeNode->parent = RSE(treeNode->parent);   // rotaciona pai pra esquerda
        treeNode = treeNode->pLeft;                 // o nodo vai ser o que tava pra esquerda
    } else if ((treeNode == treeNode->parent->pLeft) && ( treeNode->parent == grandparent->pRight)) { //pai ta pra esquerda e filho ta pra 
        treeNode->parent = RSD(treeNode->parent);   // rotaciona pai pra DIREITA
        treeNode = treeNode->pRight;                 // o nodo vai ser o que tava pra direita
    }
    //vai ter q ir pro outro caso, pra arrumar o reflexo

    return insert_case5(treeNode);
}

Node* insert_case5(Node* treeNode){
    Node* grandparent = getGrandparent(treeNode);

    if((treeNode == treeNode->parent->pLeft) && (treeNode->parent == grandparent->pLeft)){
        treeNode = RSD(treeNode);
    } else {
        treeNode = RSE(treeNode);
    }

    treeNode->parent->color = BLACK;
    grandparent->color = RED;
    return treeNode;
}


