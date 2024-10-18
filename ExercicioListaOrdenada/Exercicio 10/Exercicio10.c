#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Encomenda {
    char destinatario[100];
    float distancia;
    struct Encomenda* proximo;
} Encomenda;

Encomenda* criar_encomenda(char* destinatario, float distancia) {
    Encomenda* nova = (Encomenda*)malloc(sizeof(Encomenda));
    strcpy(nova->destinatario, destinatario);
    nova->distancia = distancia;
    nova->proximo = NULL;
    return nova;
}

void inserir_encomenda(Encomenda** cabeca, char* destinatario, float distancia) {
    Encomenda* nova = criar_encomenda(destinatario, distancia);
    if (*cabeca == NULL || (*cabeca)->distancia > distancia) {
        nova->proximo = *cabeca;
        *cabeca = nova;
    } else {
        Encomenda* atual = *cabeca;
        while (atual->proximo != NULL && atual->proximo->distancia < distancia) {
            atual = atual->proximo;
        }
        nova->proximo = atual->proximo;
        atual->proximo = nova;
    }
}

void exibir_encomendas(Encomenda* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma encomenda na fila.\n");
        return;
    }
    Encomenda* atual = cabeca;
    printf("Encomendas a serem entregues:\n");
    while (atual != NULL) {
        printf("Destinatário: %s - Distância: %.2f km\n", atual->destinatario, atual->distancia);
        atual = atual->proximo;
    }
}

void remover_encomenda(Encomenda** cabeca, char* destinatario) {
    if (*cabeca == NULL) {
        printf("Nenhuma encomenda para remover.\n");
        return;
    }
    Encomenda* atual = *cabeca;
    Encomenda* anterior = NULL;
    while (atual != NULL && strcmp(atual->destinatario, destinatario) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Encomenda para %s não encontrada.\n", destinatario);
        return;
    }
    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Encomenda para %s removida com sucesso.\n", destinatario);
}

int main() {
    Encomenda* fila = NULL;
    int opcao;
    char destinatario[100];
    float distancia;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir encomenda\n");
        printf("2. Exibir encomendas\n");
        printf("3. Remover encomenda\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o destinatário: ");
                scanf(" %[^\n]", destinatario);
                printf("Digite a distância (em km): ");
                scanf("%f", &distancia);
                inserir_encomenda(&fila, destinatario, distancia);
                break;
            case 2:
                exibir_encomendas(fila);
                break;
            case 3:
                printf("Digite o destinatário da encomenda a ser removida: ");
                scanf(" %[^\n]", destinatario);
                remover_encomenda(&fila, destinatario);
                break;
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    while (fila != NULL) {
        remover_encomenda(&fila, fila->destinatario);
    }

    return 0;
}
