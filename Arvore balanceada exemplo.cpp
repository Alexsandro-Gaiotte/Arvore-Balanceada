#include <stdio.h>
#include <stdlib.h>

/*
   N� para a �rvore AVL Balanceada
*/
typedef struct no {
    int valor;
    struct no* esquerdo;
    struct no* direito;
    int altura;
} No;

/*
    Fun��o que cria um novo n�
    x -> valor a ser inserido no n�
    Retorna: o endere�o do n� criado
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
        printf("\nERRO ao alocar n� em novoNo!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois n�s da �rvore
*/
int maior(int a, int b) {
    return (a > b) ? a : b;
}

/*
    Retorna a altura de um n� ou 0 caso ele seja null
*/
int alturaDoNo(No* no) {
    if (no == NULL)
        return 0;
    else
        return no->altura;
}

/*
    Calcula e retorna o fator de balanceamento de um n�
*/
int fatorDeBalanceamento(No* no) {
    if (no)
        return alturaDoNo(no->esquerdo) - alturaDoNo(no->direito);
    else
        return 0;
}

/*
   Fun��o para atualizar a altura de um n� ap�s inser��o ou remo��o
*/
void atualizarAltura(No* no) {
    if (no) {
        no->altura = 1 + maior(alturaDoNo(no->esquerdo), alturaDoNo(no->direito));
    }
}

/*
   Fun��o de rota��o simples � direita
*/
No* rotacaoDireita(No* y) {
    No* x = y->esquerdo;
    No* T2 = x->direito;

    // Realiza a rota��o
    x->direito = y;
    y->esquerdo = T2;

    // Atualiza alturas
    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

/*
   Fun��o de rota��o simples � esquerda
*/
No* rotacaoEsquerda(No* x) {
    No* y = x->direito;
    No* T2 = y->esquerdo;

    // Realiza a rota��o
    y->esquerdo = x;
    x->direito = T2;

    // Atualiza alturas
    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

/*
   Fun��o para inserir um n� na �rvore AVL
*/
No* inserir(No* no, int valor) {
    // Passo 1: Inser��o normal de BST
    if (no == NULL)
        return novoNo(valor);

    if (valor < no->valor)
        no->esquerdo = inserir(no->esquerdo, valor);
    else if (valor > no->valor)
        no->direito = inserir(no->direito, valor);
    else // Duplicatas n�o s�o permitidas
        return no;

    // Passo 2: Atualizar a altura deste n� ancestral
    atualizarAltura(no);

    // Passo 3: Obter o fator de balanceamento deste n� ancestral para verificar o equil�brio
    int balance = fatorDeBalanceamento(no);

    // Casos de desequil�brio
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

// Fun��o para imprimir a �rvore em ordem
void inorder(No* no) {
    if (no != NULL) {
        inorder(no->esquerdo);
        printf("%d ", no->valor);
        inorder(no->direito);
    }
}

// Fun��o principal
int main() {
    No* raiz = NULL;
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);

    printf("�rvore AVL em ordem:\n");
    inorder(raiz);

    return 0;
}

