#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int key;
    struct Node* pLeft;
    struct Node* pRight;
} Node;

Node* createNode(int key);
int calculateHeight(Node* node);
int calculateFb(Node* treeNode);
Node* RSE (Node* node);
Node* RSD (Node* node);
Node* insert(Node* treeNode, int key);
Node* balanceTree(Node *treeNode);
void print_root(Node* root);
void print_preorder(Node* node);
void print_central(Node* node);
void print_postorder(Node* node);

int main(){
    Node* root = NULL;

    root = insert(root, 7);
    printf("%d\n", root->key);
    root = insert(root, 6);
    printf("%d\n", root->key);
    root = insert(root, 5);
    printf("%d\n", root->key);
        root = insert(root, 4);
    printf("%d\n", root->key);
        root = insert(root, 3);
    printf("%d\n", root->key);
        root = insert(root, 2);
    printf("%d\n", root->key);
        root = insert(root, 1);
    printf("%d\n", root->key);

    printf("preorder: ");
    print_preorder(root);
    printf("\n");
    printf("central: ");
    print_central(root);
        printf("\n");
    printf("postorder: ");
    print_postorder(root);
    printf("\n");
    printf("raizzz: ");
    printf("%d", root->key);
    printf("\n");
}

Node* createNode(int key){
    Node* newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}

int calculateHeight(Node* node){
      if (node == NULL) {
        return 0;
    }

    int left_height = calculateHeight(node->pLeft);
    int right_height = calculateHeight(node->pRight);

    if (left_height > right_height){
        return 1 + left_height;
    } else {
        return 1 + right_height;
    }
}

int calculateFb(Node* treeNode){
    if (treeNode == NULL) {
        return 0;
    }

    int leftHeight = calculateHeight(treeNode->pLeft);
    int rightHeight = calculateHeight(treeNode->pRight);

    return leftHeight - rightHeight;
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
        return createNode(key);
    }


    if(key < treeNode->key){
        treeNode->pLeft = insert(treeNode->pLeft, key);
    } else if( key > treeNode->key){
        treeNode->pRight = insert(treeNode->pRight, key);
    } else if( key == treeNode->key){
        return treeNode;
    }
    // Agora tem que checar o balanceamento...
    return balanceTree(treeNode);
}

Node* balanceTree(Node *treeNode){
    if(treeNode == NULL){
        return treeNode;
    }

    int fb = calculateFb(treeNode);

    if(fb > 1) {
        if(calculateFb(treeNode->pLeft) < 0){
            treeNode->pLeft = RSE(treeNode->pLeft);
        }

        return RSD(treeNode);
    } else if (fb < -1){
           if(calculateFb(treeNode->pRight) > 0){
            treeNode->pRight = RSE(treeNode->pRight);
        }

        return RSE(treeNode);
    }

    return treeNode;
}

void print_root(Node* root) {
 if (root == NULL) {
        printf("Raiz nula\n");
    } else {
        printf("Raiz: %d\n", root->key);
    }
}

void print_preorder(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->key);   // chega no nó e printa
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

void print_postorder(Node* node) {
    if (node == NULL) {
        return;
    }
    print_postorder(node->pLeft);   //visita todas arvores e volta printando
    print_postorder(node->pRight);  
    printf("%d ", node->key);
}

int isAVLTree(Node* root){
    int fb;

    if(root == NULL){
        return 1;
    } 

    if(!isAVLTree(root->pLeft)){
        return 0;
    }
    if(!isAVLTree(root->pRight)){
        return 0;
    }

    fb = calculateFb(root);

    if((fb > 1) || (fb< - 1)){
        return 0;
    } else {
        return 1;
    }
    
}