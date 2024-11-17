#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    int id; // ID do aluno gerado automaticamente
    char nome[50];
    int cartao_id; // ID do cartão, igual ao ID do aluno
    char plano[20];
    int pagamento_em_dia;
    int ativo;
    int altura; // Altura do nó para balanceamento AVL
    struct Aluno *esquerda;
    struct Aluno *direita;
} Aluno;

Aluno* raiz = NULL;  // A raiz da árvore AVL

int total_alunos = 0; // Contador para gerar IDs automáticos

// Função para obter a altura de um nó
int altura(Aluno* nodo) {
    return nodo == NULL ? 0 : nodo->altura;
}

// Função para atualizar a altura de um nó
void atualizar_altura(Aluno* nodo) {
    if (nodo != NULL) {
        nodo->altura = 1 + (altura(nodo->esquerda) > altura(nodo->direita) ? altura(nodo->esquerda) : altura(nodo->direita));
    }
}

// Função para calcular o fator de balanceamento
int fator_balanceamento(Aluno* nodo) {
    return nodo == NULL ? 0 : altura(nodo->esquerda) - altura(nodo->direita);
}

// Rotação simples à direita
Aluno* rotacao_direita(Aluno* y) {
    Aluno* x = y->esquerda;
    Aluno* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizar_altura(y);
    atualizar_altura(x);

    return x;
}

// Rotação simples à esquerda
Aluno* rotacao_esquerda(Aluno* x) {
    Aluno* y = x->direita;
    Aluno* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    atualizar_altura(x);
    atualizar_altura(y);

    return y;
}

// Função para balancear um nó
Aluno* balancear(Aluno* nodo) {
    int balance = fator_balanceamento(nodo);

    // Caso de rotação direita
    if (balance > 1 && fator_balanceamento(nodo->esquerda) >= 0)
        return rotacao_direita(nodo);

    // Caso de rotação esquerda
    if (balance < -1 && fator_balanceamento(nodo->direita) <= 0)
        return rotacao_esquerda(nodo);

    // Caso de rotação esquerda-direita
    if (balance > 1 && fator_balanceamento(nodo->esquerda) < 0) {
        nodo->esquerda = rotacao_esquerda(nodo->esquerda);
        return rotacao_direita(nodo);
    }

    // Caso de rotação direita-esquerda
    if (balance < -1 && fator_balanceamento(nodo->direita) > 0) {
        nodo->direita = rotacao_direita(nodo->direita);
        return rotacao_esquerda(nodo);
    }

    return nodo;
}

// Função para criar um novo nó de aluno
Aluno* criar_aluno(char nome[], char plano[], int pagamento_em_dia) {
    Aluno* novo_aluno = (Aluno*)malloc(sizeof(Aluno));
    novo_aluno->id = ++total_alunos;
    novo_aluno->cartao_id = total_alunos;
    strcpy(novo_aluno->nome, nome);
    strcpy(novo_aluno->plano, plano);
    novo_aluno->pagamento_em_dia = pagamento_em_dia;
    novo_aluno->ativo = 1;
    novo_aluno->altura = 1;
    novo_aluno->esquerda = novo_aluno->direita = NULL;
    return novo_aluno;
}

// Função para inserir um aluno na árvore AVL
Aluno* inserir_aluno(Aluno* raiz, Aluno* novo_aluno) {
    if (raiz == NULL) return novo_aluno;

    if (novo_aluno->cartao_id < raiz->cartao_id) {
        raiz->esquerda = inserir_aluno(raiz->esquerda, novo_aluno);
    } else {
        raiz->direita = inserir_aluno(raiz->direita, novo_aluno);
    }

    atualizar_altura(raiz);
    return balancear(raiz);
}

// Função para buscar um aluno pelo ID do cartão
Aluno* buscar_aluno(Aluno* raiz, int cartao_id) {
    if (raiz == NULL || raiz->cartao_id == cartao_id)
        return raiz;
    if (cartao_id < raiz->cartao_id)
        return buscar_aluno(raiz->esquerda, cartao_id);
    else
        return buscar_aluno(raiz->direita, cartao_id);
}

// Função para listar todos os alunos
void listar_alunos(Aluno* raiz) {
    if (raiz != NULL) {
        listar_alunos(raiz->esquerda);
        if (raiz->ativo) { // Apenas lista alunos ativos
            printf("ID: %d, Nome: %s, Plano: %s, Pagamento: %s, status: %s\n",
                   raiz->cartao_id, raiz->nome, raiz->plano, 
                   (raiz->pagamento_em_dia ? "em dia" : "atrasado"),
                   (raiz->ativo ? "ativo" : "inativo"));
        }
        listar_alunos(raiz->direita);
    }
}

// Função para liberar acesso
void liberar_acesso() {
    int cartao_id;
    
    printf("\n=== Alunos Cadastrados ===\n");
    listar_alunos(raiz);  // Exibe a lista de alunos
    
    if (raiz == NULL) {
        printf("Nao ha alunos cadastrados!\n");
        return;
    }

    printf("Escolha o ID do cartao para liberar acesso: ");
    scanf("%d", &cartao_id);

    Aluno* aluno = buscar_aluno(raiz, cartao_id);
    
    if (aluno != NULL) {
        if (aluno->ativo && aluno->pagamento_em_dia) {
            printf("Acesso liberado para %s\n", aluno->nome);
        } else {
            printf("Acesso negado. Aluno inativo ou pagamento atrasado.\n");
        }
    } else {
        printf("Aluno nao encontrado!\n");
    }
}

// Função para exibir o menu de opções
void exibir_menu() {
    printf("\n=== Sistema de Transporte Escolar ===\n");
    printf("1. Cadastrar Aluno\n");
    printf("2. Alterar Plano\n");
    printf("3. Alterar Status de Pagamento\n");
    printf("4. Alterar Nome do Aluno\n");
    printf("5. Desativar Aluno\n");
    printf("6. Excluir Aluno\n");
    printf("7. Liberar Acesso\n");
    printf("8. Listar Alunos\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para alterar o plano de um aluno
void alterar_plano(Aluno* aluno) {
    char novo_plano[20];
    printf("Digite o novo plano (mensal/trimestral/anual): ");
    scanf("%s", novo_plano);
    strcpy(aluno->plano, novo_plano);
    printf("Plano do aluno %s atualizado para %s.\n", aluno->nome, aluno->plano);
}

// Função para alterar o status de pagamento de um aluno
void alterar_status_pagamento(Aluno* aluno) {
    int novo_pagamento;
    printf("O pagamento esta em dia? (1 para sim, 0 para nao): ");
    scanf("%d", &novo_pagamento);
    aluno->pagamento_em_dia = novo_pagamento;
    printf("Status de pagamento do aluno %s atualizado.\n", aluno->nome);
}

// Função para alterar o nome de um aluno
void alterar_nome(Aluno* aluno) {
    char novo_nome[50];
    printf("Digite o novo nome do aluno: ");
    scanf(" %[^\n]", novo_nome); // Para ler espaços no nome
    strcpy(aluno->nome, novo_nome);
    printf("Nome do aluno atualizado para %s.\n", aluno->nome);
}

// Função para desativar um aluno
void desativar_aluno(Aluno* aluno) {
    aluno->ativo = 0;
    printf("Aluno %s desativado.\n", aluno->nome);
}

// Função para excluir um aluno
Aluno* excluir_aluno(Aluno* raiz, int cartao_id) {
    if (raiz == NULL) {
        printf("Aluno nao encontrado!\n");
        return raiz;
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

    atualizar_altura(raiz);
    return balancear(raiz);
}

int main() {
    int opcao;
    int cartao_id;
    char nome[50], plano[20];
    int pagamento;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do aluno: ");
                scanf("%s", nome);
                printf("Digite o plano do aluno (mensal/trimestral/anual): ");
                scanf("%s", plano);
                printf("O pagamento esta em dia? (1 para sim, 0 para nao): ");
                scanf("%d", &pagamento);
                raiz = inserir_aluno(raiz, criar_aluno(nome, plano, pagamento));
                printf("Aluno cadastrado com sucesso.\n");
                break;

            case 2:
                printf("Escolha o ID do cartao do aluno para alterar o plano: ");
                scanf("%d", &cartao_id);
                Aluno* aluno_plano = buscar_aluno(raiz, cartao_id);
                if (aluno_plano != NULL) {
                    alterar_plano(aluno_plano);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;

            case 3:
                printf("Escolha o ID do cartao do aluno para alterar o status de pagamento: ");
                scanf("%d", &cartao_id);
                Aluno* aluno_pagamento = buscar_aluno(raiz, cartao_id);
                if (aluno_pagamento != NULL) {
                    alterar_status_pagamento(aluno_pagamento);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;

            case 4:
                printf("Escolha o ID do cartao do aluno para alterar o nome: ");
                scanf("%d", &cartao_id);
                Aluno* aluno_nome = buscar_aluno(raiz, cartao_id);
                if (aluno_nome != NULL) {
                    alterar_nome(aluno_nome);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;

            case 5:
                listar_alunos(raiz);
                printf("Escolha o ID do cartao do aluno para desativar: ");
                scanf("%d", &cartao_id);
                Aluno* aluno_desativar = buscar_aluno(raiz, cartao_id);
                if (aluno_desativar != NULL) {
                    desativar_aluno(aluno_desativar);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;

            case 6:
                printf("Escolha o ID do cartao do aluno para excluir: ");
                scanf("%d", &cartao_id);
                raiz = excluir_aluno(raiz, cartao_id);
                printf("Aluno excluido.\n");
                break;

            case 7:
                liberar_acesso();
                break;

            case 8:
                listar_alunos(raiz);
                break;

            case 0:
                printf("Saindo do sistema.\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
