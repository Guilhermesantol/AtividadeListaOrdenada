#include <stdio.h>
#include <stdlib.h>

typedef struct Jogador {
    char nome[100];
    int pontuacao;
    struct Jogador* proximo;
} Jogador;

Jogador* criar_jogador(char* nome, int pontuacao) {
    Jogador* novo = (Jogador*)malloc(sizeof(Jogador));
    strcpy(novo->nome, nome);
    novo->pontuacao = pontuacao;
    novo->proximo = NULL;
    return novo;
}

void inserir_pontuacao(Jogador** cabeca, char* nome, int pontuacao) {
    Jogador* novo = criar_jogador(nome, pontuacao);
    if (*cabeca == NULL || (*cabeca)->pontuacao > pontuacao) {
        novo->proximo = *cabeca;
        *cabeca = novo;
    } else {
        Jogador* atual = *cabeca;
        while (atual->proximo != NULL && atual->proximo->pontuacao < pontuacao) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

void exibir_pontuacoes(Jogador* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma pontuação registrada.\n");
        return;
    }
    Jogador* atual = cabeca;
    while (atual != NULL) {
        printf("Jogador: %s - Pontuação: %d\n", atual->nome, atual->pontuacao);
        atual = atual->proximo;
    }
}

void remover_jogador(Jogador** cabeca, char* nome) {
    if (*cabeca == NULL) {
        printf("Lista vazia. Nenhum jogador para remover.\n");
        return;
    }
    Jogador* atual = *cabeca;
    Jogador* anterior = NULL;
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Jogador %s não encontrado.\n", nome);
        return;
    }
    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Jogador %s removido com sucesso.\n", nome);
}

int main() {
    Jogador* lista_jogadores = NULL;
    int opcao;
    char nome[100];
    int pontuacao;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir pontuação\n");
        printf("2. Exibir pontuações\n");
        printf("3. Remover jogador\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do jogador: ");
                scanf(" %[^\n]", nome);
                printf("Digite a pontuação do jogador: ");
                scanf("%d", &pontuacao);
                inserir_pontuacao(&lista_jogadores, nome, pontuacao);
                break;
            case 2:
                exibir_pontuacoes(lista_jogadores);
                break;
            case 3:
                printf("Digite o nome do jogador a ser removido: ");
                scanf(" %[^\n]", nome);
                remover_jogador(&lista_jogadores, nome);
                break;
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    Jogador* atual = lista_jogadores;
    while (atual != NULL) {
        Jogador* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
