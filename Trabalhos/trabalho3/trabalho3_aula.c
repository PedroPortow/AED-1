#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int key;
    struct Node *pLeft;
    struct Node *pRight;
} Node;

Node* createNode(int key);
Node* insertNode(Node* treeNode, int key);
int diameterOfBinaryTree(Node* root);
void printPreOrder(Node* node) ;

int main(){
    Node* root = NULL;
    int diametro = 0;
    int counter = 4;
    int keys[] = {4,2,7,9};

    for(int i = 0; i < counter; i++){
        root = insertNode(root, keys[i]);
    }
    

    /*
        4
    2       7
                9
    */

//     root = insertNode(root, 4);
//     root = insertNode(root, 2);
//     root = insertNode(root, 7);
//     root = insertNode(root, 9);

    printf("arvore em preordem: ");
    printPreOrder(root);

    diametro = diameterOfBinaryTree(root);

    printf("Diametro: %d", diametro);

    return 0;
}

void printPreOrder(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->key);   // chega no nó e printa
    printPreOrder(node->pLeft);
    printPreOrder(node->pRight);
}


Node* createNode(int key){
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}


Node* insertNode(Node* treeNode, int key){

    if(treeNode == NULL){
        return createNode(key);
    }
    
    if(key < treeNode->key){
        treeNode->pLeft = insertNode(treeNode->pLeft, key); // DESCENDO PELA ESQUERDA
    } else if ( key > treeNode->key){
        treeNode->pRight = insertNode(treeNode->pRight, key); // DESCENDO PELA DIREITA
    } else if( treeNode->key == key ){ // ja ta na arvore
        return treeNode;
    }

    return treeNode;
}

int diameterOfBinaryTree(Node* root){
    int contLeft = 0;
    int contRight = 0;
   
    if(root->pRight != NULL && root->pLeft != NULL){
        Node* leftTree = root;
        Node* rightTree = root;

        do{
            if(leftTree->pLeft != NULL){
                leftTree = leftTree->pLeft;
            } else if (leftTree->pRight != NULL) {
                leftTree = leftTree->pRight;
            }

            contLeft++;
        } while(leftTree->pLeft != NULL || leftTree->pRight != NULL);

        do{
            if(rightTree->pRight != NULL){
                rightTree = rightTree->pRight;
            } else if (rightTree->pLeft != NULL) {
                rightTree = rightTree->pLeft;
            }
            
            contRight++;
        } while(rightTree->pLeft != NULL || rightTree->pRight != NULL);

        return (contLeft + contRight);
    } else if(root->pRight == NULL) { // so tem pra  esquerda
        Node* leftTree = root;

        do{
            if(leftTree->pLeft != NULL){
                leftTree = leftTree->pLeft;
            } else if (leftTree->pRight != NULL) {
                leftTree = leftTree->pRight;
            }

            contLeft++;
        } while(leftTree->pLeft != NULL || leftTree->pRight != NULL);
        return contLeft;
    } else { //so tem pra direita
        Node* rightTree = root;

       do{
            if(rightTree->pRight != NULL){
                rightTree = rightTree->pRight;
            } else if (rightTree->pLeft != NULL) {
                rightTree = rightTree->pLeft;
            }
            
            contRight++;
        } while(rightTree->pLeft != NULL || rightTree->pRight != NULL);
        return contRight;
    }
}