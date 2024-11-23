#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_PLANO 20

extern int total_alunos;  // Declaração da variável externa total_alunos

typedef struct Aluno {
    int id;
    int cartao_id;
    char nome[MAX_NOME];
    char plano[MAX_PLANO];
    int pagamento_em_dia;  // 1 para em dia, 0 para atrasado
    int ativo;  // 1 para ativo, 0 para inativo
    int altura;  // Altura para balanceamento da árvore AVL
    struct Aluno* esquerda;
    struct Aluno* direita;
} Aluno;

// Função para criar um novo aluno
static inline Aluno* criar_aluno(char nome[], char plano[], int pagamento_em_dia) {
    Aluno* novo_aluno = (Aluno*)malloc(sizeof(Aluno));  // Aloca memória para o novo aluno
    novo_aluno->id = ++total_alunos;  // ID gerado automaticamente
    novo_aluno->cartao_id = total_alunos;  // O ID do cartão é igual ao do aluno
    strcpy(novo_aluno->nome, nome);  // Copia o nome para o novo aluno
    strcpy(novo_aluno->plano, plano);  // Copia o plano do aluno
    novo_aluno->pagamento_em_dia = pagamento_em_dia;  // Definindo se o pagamento está em dia
    novo_aluno->ativo = 1;  // O aluno é inicialmente ativo
    novo_aluno->altura = 1;  // Altura para balanceamento AVL
    novo_aluno->esquerda = NULL;  // Inicializa as referências para os filhos
    novo_aluno->direita = NULL;
    return novo_aluno;  // Retorna o novo aluno
}

// Função para listar todos os alunos
static inline void listar_alunos(Aluno* raiz) {
    if (raiz != NULL) {
        listar_alunos(raiz->esquerda);  // Percorre a subárvore esquerda
        if (raiz->ativo) {  // Só lista alunos ativos
            printf("ID: %d, Nome: %s, Plano: %s, Pagamento: %s, Status: %s\n",
                   raiz->cartao_id, raiz->nome, raiz->plano, 
                   (raiz->pagamento_em_dia ? "Em dia" : "Atrasado"),
                   (raiz->ativo ? "Ativo" : "Inativo"));
        }
        listar_alunos(raiz->direita);  // Percorre a subárvore direita
    }
}

// Função para encontrar um aluno pela cartao_id
static inline Aluno* encontrar_aluno(Aluno* raiz, int cartao_id) {
    if (raiz == NULL || raiz->cartao_id == cartao_id) {
        return raiz;
    }

    if (cartao_id < raiz->cartao_id) {
        return encontrar_aluno(raiz->esquerda, cartao_id);  // Busca à esquerda
    } else {
        return encontrar_aluno(raiz->direita, cartao_id);  // Busca à direita
    }
}

// Função para atualizar o nome de um aluno
static inline Aluno* atualizar_nome(Aluno* raiz, int cartao_id, const char* novo_nome) {
    Aluno* aluno = encontrar_aluno(raiz, cartao_id);
    if (aluno != NULL) {
        strcpy(aluno->nome, novo_nome);  // Atualiza o nome do aluno
    }
    return aluno;
}

// Função para atualizar o plano de um aluno
static inline Aluno* atualizar_plano(Aluno* raiz, int cartao_id, const char* novo_plano) {
    Aluno* aluno = encontrar_aluno(raiz, cartao_id);
    if (aluno != NULL) {
        strcpy(aluno->plano, novo_plano);  // Atualiza o plano do aluno
    }
    return aluno;
}

// Função para atualizar o status de pagamento de um aluno
static inline Aluno* atualizar_pagamento(Aluno* raiz, int cartao_id, int pagamento_em_dia) {
    Aluno* aluno = encontrar_aluno(raiz, cartao_id);
    if (aluno != NULL) {
        aluno->pagamento_em_dia = pagamento_em_dia;  // Atualiza o status de pagamento
    }
    return aluno;
}

// Função para desativar um aluno
static inline Aluno* desativar_aluno(Aluno* raiz, int cartao_id) {
    Aluno* aluno = encontrar_aluno(raiz, cartao_id);
    if (aluno != NULL) {
        aluno->ativo = 0;  // Marca o aluno como inativo
    }
    return aluno;
}

// Função para excluir um aluno
static inline Aluno* excluir_aluno(Aluno* raiz, int cartao_id) {
    if (raiz == NULL) {
        return NULL;
    }

    if (cartao_id < raiz->cartao_id) {
        raiz->esquerda = excluir_aluno(raiz->esquerda, cartao_id);
    } else if (cartao_id > raiz->cartao_id) {
        raiz->direita = excluir_aluno(raiz->direita, cartao_id);
    } else {
        if (raiz->esquerda == NULL) {
            Aluno* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Aluno* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Aluno* temp = raiz->direita;
        while (temp && temp->esquerda != NULL) {
            temp = temp->esquerda;
        }

        raiz->cartao_id = temp->cartao_id;
        raiz->direita = excluir_aluno(raiz->direita, temp->cartao_id);
    }

    return raiz;
}


// Função de debug para imprimir as alturas dos nós
static inline void debug_alturas(Aluno* raiz) {
    if (raiz != NULL) {
        debug_alturas(raiz->esquerda);  // Percorre a subárvore esquerda
        printf("ID: %d, Nome: %s, Altura: %d\n", raiz->cartao_id, raiz->nome, raiz->altura);
        debug_alturas(raiz->direita);  // Percorre a subárvore direita
    }
}


#endif
