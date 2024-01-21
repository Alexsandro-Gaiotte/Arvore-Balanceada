#include <stdio.h>
#include <stdlib.h>

/*
   Nó para a Árvore AVL Balanceada
*/
typedef struct no {
    int valor;
    struct no* esquerdo;
    struct no* direito;
    int altura;
} No;

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
No* novoNo(int x) {
    No* novo = (No*)malloc(sizeof(No));

    if (novo) {
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 1; // Inicializa a altura como 1
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
int maior(int a, int b) {
    return (a > b) ? a : b;
}

/*
    Retorna a altura de um nó ou 0 caso ele seja null
*/
int alturaDoNo(No* no) {
    if (no == NULL)
        return 0;
    else
        return no->altura;
}

/*
    Calcula e retorna o fator de balanceamento de um nó
*/
int fatorDeBalanceamento(No* no) {
    if (no)
        return alturaDoNo(no->esquerdo) - alturaDoNo(no->direito);
    else
        return 0;
}

/*
   Função para atualizar a altura de um nó após inserção ou remoção
*/
void atualizarAltura(No* no) {
    if (no) {
        no->altura = 1 + maior(alturaDoNo(no->esquerdo), alturaDoNo(no->direito));
    }
}

/*
   Função de rotação simples à direita
*/
No* rotacaoDireita(No* y) {
    No* x = y->esquerdo;
    No* T2 = x->direito;

    // Realiza a rotação
    x->direito = y;
    y->esquerdo = T2;

    // Atualiza alturas
    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

/*
   Função de rotação simples à esquerda
*/
No* rotacaoEsquerda(No* x) {
    No* y = x->direito;
    No* T2 = y->esquerdo;

    // Realiza a rotação
    y->esquerdo = x;
    x->direito = T2;

    // Atualiza alturas
    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

/*
   Função para inserir um nó na árvore AVL
*/
No* inserir(No* no, int valor) {
    // Passo 1: Inserção normal de BST
    if (no == NULL)
        return novoNo(valor);

    if (valor < no->valor)
        no->esquerdo = inserir(no->esquerdo, valor);
    else if (valor > no->valor)
        no->direito = inserir(no->direito, valor);
    else // Duplicatas não são permitidas
        return no;

    // Passo 2: Atualizar a altura deste nó ancestral
    atualizarAltura(no);

    // Passo 3: Obter o fator de balanceamento deste nó ancestral para verificar o equilíbrio
    int balance = fatorDeBalanceamento(no);

    // Casos de desequilíbrio
    // Esquerda-Esquerda
    if (balance > 1 && valor < no->esquerdo->valor)
        return rotacaoDireita(no);

    // Direita-Direita
    if (balance < -1 && valor > no->direito->valor)
        return rotacaoEsquerda(no);

    // Esquerda-Direita
    if (balance > 1 && valor > no->esquerdo->valor) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }

    // Direita-Esquerda
    if (balance < -1 && valor < no->direito->valor) {
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Função para imprimir a árvore em ordem
void inorder(No* no) {
    if (no != NULL) {
        inorder(no->esquerdo);
        printf("%d ", no->valor);
        inorder(no->direito);
    }
}

// Função principal
int main() {
    No* raiz = NULL;
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);

    printf("Árvore AVL em ordem:\n");
    inorder(raiz);

    return 0;
}

