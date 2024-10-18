#include <stdio.h>
#define MAX 5

void inserir(int lista[], int *tamanho, int valor) {
  if (*tamanho < MAX) {
    lista[*tamanho] = valor;
    (*tamanho)++;
  } else {
    printf("Lista cheia\n");
  }
}

void remover(int lista[], int *tamanho, int valor) {
  if (*tamanho > 0) {
    for (int i = 0; i < *tamanho; i++) {
      if (lista[i] == valor) {
        lista[i] = 0;
      }
    }
  } else {
    printf("Lista vasia\n");
  }
}

void exibir(int lista[], int tamanho) {
  printf("Elementos da lista: \n");
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", lista[i]);
  }
  printf("\n");
}

int main(void) {
  int lista[MAX];
  int tamanho = 0;
  int valor;
  int opcao;

  while (1) {
    printf("Escolha opção\n");
    printf("1 - Inserir pedido\n");
    printf("2 - Remover pedido\n");
    scanf("%d", &opcao);
    switch (opcao) {
    case (1):
      printf("Faça seu pedido\n");
      scanf("%d", &valor);
      inserir(lista, &tamanho, valor);
      exibir(lista, tamanho);
      break;

    case (2):
      printf("Remova um pedido\n");
      scanf("%d", &valor);
      remover(lista, &tamanho, valor);
      exibir(lista, tamanho);
      break;
    default:
      printf("Opção inválida\n");
    } // swt
  }   // while
  return 0;
}
