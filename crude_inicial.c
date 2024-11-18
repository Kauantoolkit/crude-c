#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    int id;
    int cartao_id;
    char nome[50];
    char plano[20];
    int pagamento_em_dia;  // 1 para em dia, 0 para atrasado
    int ativo;  // 1 para ativo, 0 para inativo
    int altura;  // Altura para balanceamento da árvore AVL
    struct Aluno* esquerda;
    struct Aluno* direita;
} Aluno;

int total_alunos = 0;  // Para controlar os IDs dos alunos
Aluno* raiz = NULL;  // Raiz da árvore AVL

// Função para calcular a altura de um nó
int altura(Aluno* aluno_altura_analisada) {
    if (aluno_altura_analisada == NULL) return 0;
    return aluno_altura_analisada->altura;
}

// Função para atualizar a altura de um nó
void atualizar_altura(Aluno* nodo) {
    if (nodo) {
        int altura_esquerda = altura(nodo->esquerda);
        int altura_direita = altura(nodo->direita);
        nodo->altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
    }
}

// Função para calcular o fator de balanceamento de um nó
int fator_balanceamento(Aluno* nodo) {
    if (nodo == NULL) return 0;
    return altura(nodo->esquerda) - altura(nodo->direita);
}

// Função para criar um novo aluno
Aluno* criar_aluno(char nome[], char plano[], int pagamento_em_dia) {
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

// Função para realizar uma rotação à direita
Aluno* rotacao_direita(Aluno* y) {
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
Aluno* rotacao_esquerda(Aluno* x) {
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
Aluno* balancear(Aluno* nodo) {
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
Aluno* inserir_aluno(Aluno* raiz, Aluno* novo_aluno) {
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

// Função para listar todos os alunos
void listar_alunos(Aluno* raiz) {
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

// Função para exibir o menu
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

// Função principal
int main() {
    int opcao;
    int cartao_id;
    char nome[50], plano[20];
    int pagamento;

    // Teste de inserção
    raiz = inserir_aluno(raiz, criar_aluno("Aluno 1", "mensal", 1));
    raiz = inserir_aluno(raiz, criar_aluno("Aluno 2", "trimestral", 1));
    raiz = inserir_aluno(raiz, criar_aluno("Aluno 3", "anual", 0));
    raiz = inserir_aluno(raiz, criar_aluno("Aluno 4", "mensal", 1));
    raiz = inserir_aluno(raiz, criar_aluno("Aluno 5", "mensal", 1));

    // Verificar o balanceamento após as inserções
    if (fator_balanceamento(raiz)) {
        printf("A árvore está balanceada.\n");
    } else {
        printf("A árvore NÃO está balanceada.\n");
    }

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
            case 8:
                listar_alunos(raiz);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
