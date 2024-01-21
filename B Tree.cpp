#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura de um n� da �rvore AVL
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Fun��o auxiliar para calcular o m�ximo entre dois n�meros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fun��o para obter a altura de um n�
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Fun��o para criar um novo n�
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Fun��o para rotacionar � direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Fun��o para rotacionar � esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Fun��o para obter o fator de balanceamento de um n�
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Fun��o para inserir um novo n� na �rvore AVL
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fun��o para percorrer a �rvore em pr�-ordem
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++)
        root = insert(root, keys[i]);

    printf("Travessia pre-ordem da arvore AVL construida:\n");
    preOrder(root);

    return 0;
}
