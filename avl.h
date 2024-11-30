


//Função para realizar uma rotação à direita
//Função para realizar uma rotação à esquerda
//Função para balancear a árvore AVL







#ifndef AVL_H
#define AVL_H

#include "aluno.h"

extern int total_alunos;
extern Aluno* raiz;

// Função para calcular a altura de um nó
static inline int altura(Aluno* aluno_altura_analisada) {                                               
    if (aluno_altura_analisada == NULL) return 0;
    return aluno_altura_analisada->altura;
}

// Função para atualizar a altura de um nó
static inline void atualizar_altura(Aluno* nodo) {
    if (nodo) { 
        int altura_esquerda = altura(nodo->esquerda);
        int altura_direita = altura(nodo->direita);
        nodo->altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
    }
}

// Função para calcular o fator de balanceamento de um nó                                                               x
static inline int fator_balanceamento(Aluno* nodo) {    
    if (nodo == NULL) return 0;
    return altura(nodo->esquerda) - altura(nodo->direita);
}

// Função para realizar uma rotação à direita
static inline Aluno* rotacao_direita(Aluno* y) {
    Aluno* x = y->esquerda;  // O filho à esquerda de y
    Aluno* T2 = x->direita;  // O filho à direita de x

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza a altura dos nós
    atualizar_altura(y);
    atualizar_altura(x);

    return x;  // O novo nó raiz após a rotação
}

// Função para realizar uma rotação à esquerda
static inline Aluno* rotacao_esquerda(Aluno* x) {
    Aluno* y = x->direita;  // O filho à direita de x
    Aluno* T2 = y->esquerda;  // O filho à esquerda de y

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza a altura dos nós
    atualizar_altura(x);
    atualizar_altura(y);

    return y;  // O novo nó raiz após a rotação
}

// Função para balancear a árvore AVL
static inline Aluno* balancear(Aluno* nodo) {
    int balance = fator_balanceamento(nodo);  // Calcula o fator de balanceamento do nó

    // Verifica os casos de desbalanceamento e realiza as rotações necessárias
    if (balance > 1 && fator_balanceamento(nodo->esquerda) >= 0)
        return rotacao_direita(nodo);

    if (balance < -1 && fator_balanceamento(nodo->direita) <= 0)
        return rotacao_esquerda(nodo);

    if (balance > 1 && fator_balanceamento(nodo->esquerda) < 0) {
        nodo->esquerda = rotacao_esquerda(nodo->esquerda);
        return rotacao_direita(nodo);
    }

    if (balance < -1 && fator_balanceamento(nodo->direita) > 0) {
        nodo->direita = rotacao_direita(nodo->direita);
        return rotacao_esquerda(nodo);
    }

    return nodo;  // Retorna o nó inalterado caso esteja balanceado
}

// Função para inserir um aluno na árvore AVL
static inline Aluno* inserir_aluno(Aluno* raiz, Aluno* novo_aluno) {
    if (raiz == NULL) return novo_aluno;  // Se a árvore estiver vazia, o novo aluno é a raiz

    // Decisão de qual lado (esquerdo ou direito) o novo aluno deve ir
    if (novo_aluno->cartao_id < raiz->cartao_id) {
        raiz->esquerda = inserir_aluno(raiz->esquerda, novo_aluno);  // Insere à esquerda
    } else {
        raiz->direita = inserir_aluno(raiz->direita, novo_aluno);  // Insere à direita
    }

    atualizar_altura(raiz);  // Atualiza a altura do nó
    return balancear(raiz);  // Balanceia a árvore
}




#endif
