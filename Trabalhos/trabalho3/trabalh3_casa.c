#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int key;
    struct Node *pLeft;
    struct Node *pRight;
} Node;

Node* createNode( int key );
Node* insertNode( Node* treeNode, int key );
int diameterOfBinaryTree( Node* root );
void printPreOrder( Node* node );
int nodeHeight( Node* treeNode );
int rootRightPath( Node* treeNode );
int rootLeftPath( Node* treeNode );
int maxValue( int a, int b );

int main(){
    Node* root = NULL;
    int diametro = 0;

    // Insert Normal na árvore Binária
    // int counter = 5;
    // int keys[] = {1,2,3,4, 5};

    // for(int i = 0; i < counter; i++){
    //     root = insertNode(root, keys[i]);
    // }
    
    // Insert feito na mão, usado no exemplo do problema

    //TESTE 1: 
    // root = createNode(1);
    // root->pLeft = createNode(2);
    // root->pRight = createNode(3);
    // root->pLeft->pLeft = createNode(4);
    // root->pLeft->pRight = createNode(5);

    //TESTE 2: 
    root = createNode(1);
    root->pLeft = createNode(2);
    root->pRight = createNode(3);
    
    root->pLeft->pLeft = createNode(20);

    root->pLeft->pRight = createNode(20);
    root->pLeft->pRight->pRight = createNode(20);
    root->pLeft->pRight->pRight->pRight = createNode(20);

    root->pLeft->pLeft->pLeft = createNode(4);
    root->pLeft->pLeft->pLeft->pRight = createNode(22);

    //TESTE 3:
    // root = createNode(1);
    // root->pRight = createNode(3);

    printf("\nArvore em preordem: ");
    printPreOrder(root);

    diametro = diameterOfBinaryTree(root);

    printf("Diametro: %d", diametro);

    return 0;
}

int maxValue( int a, int b ) { 
    return ( a > b ) ? a : b; 
}

void printPreOrder( Node* node ) {
    if ( node == NULL ) {
        return;
    }
    printf( "%d ", node->key );   // chega no nó e printa
    printPreOrder( node->pLeft );
    printPreOrder( node->pRight );
}


Node* createNode( int key ){
    Node* newNode = ( Node * )malloc( sizeof(Node) );
    newNode->key = key;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}


Node* insertNode( Node* treeNode, int key ){

    if( treeNode == NULL ){
        return createNode( key );
    }
    
    if( key < treeNode->key ){
        treeNode->pLeft = insertNode( treeNode->pLeft, key ); // DESCENDO PELA ESQUERDA
    } else if ( key > treeNode->key ){
        treeNode->pRight = insertNode( treeNode->pRight, key ); // DESCENDO PELA DIREITA
    } else if( treeNode->key == key ){ // ja ta na arvore
        return treeNode;
    }

    return treeNode;
}

int diameterOfBinaryTree( Node* root ){
    if( root == NULL ){
        return 0;
    }

    int leftHeight = nodeHeight( root->pLeft );
    int rightHeight = nodeHeight( root->pRight );

    int leftPathFromRoot = diameterOfBinaryTree(root->pLeft);
    int rightPathFromRoot = diameterOfBinaryTree(root->pRight);

    return maxValue(leftHeight + rightHeight, maxValue(leftPathFromRoot, rightPathFromRoot));
}


int nodeHeight( Node* treeNode ) {

   int leftHeight, rightHeight;

    if( treeNode == NULL )
        return 0;

    leftHeight  = nodeHeight( treeNode->pLeft );
    rightHeight = nodeHeight( treeNode->pRight );

    if( leftHeight > rightHeight ){
        return leftHeight + 1;          
    } else {
        return rightHeight + 1;
    }
}

