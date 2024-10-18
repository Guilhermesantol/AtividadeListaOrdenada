#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VISITANTES 100
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
} Visitante;

void inserirVisitante(Visitante fila[], int *fim);
void removerVisitante(Visitante fila[], int *inicio, int *fim);
void exibirFila(Visitante fila[], int inicio, int fim);

int main() {
    Visitante fila[MAX_VISITANTES]; 
    int inicio = 0, fim = 0; 
    int opcao;

    do {
        printf("\nSistema de Fila do Parque de Diversões\n");
        printf("1. Inserir visitante no final da fila\n");
        printf("2. Remover visitante que acabou de usar o brinquedo\n");
        printf("3. Exibir a lista completa de pessoas aguardando\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirVisitante(fila, &fim);
                break;
            case 2:
                removerVisitante(fila, &inicio, &fim);
                break;
            case 3:
                exibirFila(fila, inicio, fim);
                break;
            case 4:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 4);

    return 0;
}

void inserirVisitante(Visitante fila[], int *fim) {
    if (*fim < MAX_VISITANTES) {
        printf("Digite o nome do visitante: ");
        scanf("%s", fila[*fim].nome);
        (*fim)++;
        printf("Visitante inserido com sucesso!\n");
    } else {
        printf("A fila está cheia. Não é possível adicionar mais visitantes.\n");
    }
}

void removerVisitante(Visitante fila[], int *inicio, int *fim) {
    if (*inicio == *fim) {
        printf("Nenhum visitante na fila.\n");
    } else {
        printf("Visitante %s saiu da fila.\n", fila[*inicio].nome);
        (*inicio)++;
    }
}

void exibirFila(Visitante fila[], int inicio, int fim) {
    if (inicio == fim) {
        printf("Nenhum visitante aguardando na fila.\n");
    } else {
        printf("Lista de visitantes aguardando:\n");
        for (int i = inicio; i < fim; i++) {
            printf("%d. %s\n", i - inicio + 1, fila[i].nome);
        }
    }
}
