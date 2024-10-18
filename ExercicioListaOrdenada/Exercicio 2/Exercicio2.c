#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Compromisso {
    char descricao[100];
    int horario; 
    struct Compromisso* proximo;
} Compromisso;

Compromisso* criar_compromisso(char* descricao, int horario) {
    Compromisso* novo = (Compromisso*)malloc(sizeof(Compromisso));
    strcpy(novo->descricao, descricao);
    novo->horario = horario;
    novo->proximo = NULL;
    return novo;
}

void inserir_compromisso(Compromisso** cabeca, char* descricao, int horario) {
    Compromisso* novo = criar_compromisso(descricao, horario);

    if (*cabeca == NULL || (*cabeca)->horario > horario) {
        novo->proximo = *cabeca;
        *cabeca = novo;
    } else {
        Compromisso* atual = *cabeca;
        while (atual->proximo != NULL && atual->proximo->horario < horario) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

void exibir_compromissos(Compromisso* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhum compromisso agendado.\n");
        return;
    }

    Compromisso* atual = cabeca;
    while (atual != NULL) {
        printf("Horário: %04d - Descrição: %s\n", atual->horario, atual->descricao);
        atual = atual->proximo;
    }
}

void remover_compromisso(Compromisso** cabeca, int horario) {
    if (*cabeca == NULL) {
        printf("Lista vazia. Nenhum compromisso para remover.\n");
        return;
    }

    Compromisso* atual = *cabeca;
    Compromisso* anterior = NULL;

    while (atual != NULL && atual->horario != horario) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Compromisso com horário %04d não encontrado.\n", horario);
        return;
    }

    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo; // Remove o nó do meio ou do fim
    }

    free(atual);
    printf("Compromisso com horário %04d removido com sucesso.\n", horario);
}

// Função principal
int main() {
    Compromisso* agenda = NULL;
    int opcao, horario;
    char descricao[100];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir compromisso\n");
        printf("2. Exibir compromissos\n");
        printf("3. Remover compromisso\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a descrição do compromisso: ");
                scanf(" %[^\n]", descricao);
                printf("Digite o horário (formato 24h, ex: 1300): ");
                scanf("%d", &horario);
                inserir_compromisso(&agenda, descricao, horario);
                break;
            case 2:
                exibir_compromissos(agenda);
                break;
            case 3:
                printf("Digite o horário do compromisso a ser removido (formato 24h, ex: 1300): ");
                scanf("%d", &horario);
                remover_compromisso(&agenda, horario);
                break;
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    // Libera a memória
    Compromisso* atual = agenda;
    while (atual != NULL) {
        Compromisso* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
