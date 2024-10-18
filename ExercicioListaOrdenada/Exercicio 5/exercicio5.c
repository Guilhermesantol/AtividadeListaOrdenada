#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    char nome[100];
    struct Paciente* proximo;
} Paciente;

Paciente* criar_paciente(char* nome) {
    Paciente* novo = (Paciente*)malloc(sizeof(Paciente));
    strcpy(novo->nome, nome);
    novo->proximo = NULL;
    return novo;
}

void adicionar_paciente(Paciente** cabeca, char* nome) {
    Paciente* novo = criar_paciente(nome);
    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Paciente* atual = *cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void remover_paciente(Paciente** cabeca) {
    if (*cabeca == NULL) {
        printf("Nenhum paciente na fila.\n");
        return;
    }
    Paciente* removido = *cabeca;
    *cabeca = removido->proximo;
    printf("Paciente atendido: %s\n", removido->nome);
    free(removido);
}

void exibir_pacientes(Paciente* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhum paciente aguardando atendimento.\n");
        return;
    }
    Paciente* atual = cabeca;
    printf("Pacientes na fila:\n");
    while (atual != NULL) {
        printf("- %s\n", atual->nome);
        atual = atual->proximo;
    }
}

int main() {
    Paciente* fila = NULL;
    int opcao;
    char nome[100];

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar paciente\n");
        printf("2. Remover paciente atendido\n");
        printf("3. Exibir pacientes na fila\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do paciente: ");
                scanf(" %[^\n]", nome);
                adicionar_paciente(&fila, nome);
                break;
            case 2:
                remover_paciente(&fila);
                break;
            case 3:
                exibir_pacientes(fila);
                break;
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    while (fila != NULL) {
        remover_paciente(&fila);
    }

    return 0;
}
