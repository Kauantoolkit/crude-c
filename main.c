#include "aluno.h"
#include "avl.h"

int total_alunos = 0;  // Inicializa a variável total_alunos
Aluno* raiz = NULL;  // Raiz da árvore AVL

void exibir_menu() {
    printf("\n=== Sistema de Transporte Escolar ===\n");
    printf("1. Cadastrar Aluno\n");
    printf("2. Alterar Nome\n");
    printf("3. Alterar Plano\n");
    printf("4. Alterar Status de Pagamento\n");
    printf("5. Desativar Aluno\n");
    printf("6. Excluir Aluno\n");
    printf("7. Listar Alunos\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;
    int cartao_id;
    char nome[50], plano[20];
    int pagamento;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o nome do aluno: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;  // Remove a quebra de linha

                printf("Digite o plano do aluno: ");
                fgets(plano, sizeof(plano), stdin);
                plano[strcspn(plano, "\n")] = 0;  // Remove a quebra de linha

                printf("Digite o status de pagamento (1 para em dia, 0 para atrasado): ");
                scanf("%d", &pagamento);
                getchar();

                raiz = inserir_aluno(raiz, criar_aluno(nome, plano, pagamento));
                printf("Aluno cadastrado com sucesso!\n");
                break;

            case 2:
                printf("Digite o ID do aluno para alterar o nome: ");
                scanf("%d", &cartao_id);
                getchar();

                printf("Digite o novo nome do aluno: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                atualizar_nome(raiz, cartao_id, nome);
                printf("Nome atualizado com sucesso!\n");
                break;

            case 3:
                printf("Digite o ID do aluno para alterar o plano: ");
                scanf("%d", &cartao_id);
                getchar();

                printf("Digite o novo plano do aluno: ");
                fgets(plano, sizeof(plano), stdin);
                plano[strcspn(plano, "\n")] = 0;

                atualizar_plano(raiz, cartao_id, plano);
                printf("Plano atualizado com sucesso!\n");
                break;

            case 4:
                printf("Digite o ID do aluno para alterar o status de pagamento: ");
                scanf("%d", &cartao_id);
                getchar();

                printf("Digite o novo status de pagamento (1 para em dia, 0 para atrasado): ");
                scanf("%d", &pagamento);
                getchar();

                atualizar_pagamento(raiz, cartao_id, pagamento);
                printf("Status de pagamento atualizado com sucesso!\n");
                break;

            case 5:
                printf("Digite o ID do aluno para desativar: ");
                scanf("%d", &cartao_id);
                getchar();

                desativar_aluno(raiz, cartao_id);
                printf("Aluno desativado com sucesso!\n");
                break;

            case 6:
                printf("Digite o ID do aluno para excluir: ");
                scanf("%d", &cartao_id);
                getchar();

                raiz = excluir_aluno(raiz, cartao_id);
                printf("Aluno excluído com sucesso!\n");
                break;

            case 7:
                printf("Lista de alunos:\n");
                listar_alunos(raiz);
                break;

            case 0:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
                debug_alturas(raiz);
        }
    }

    return 0;
}
