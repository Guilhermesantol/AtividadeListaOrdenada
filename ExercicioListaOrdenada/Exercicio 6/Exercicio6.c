#include <stdio.h>
#include <stdlib.h>

typedef struct Produto {
    float preco;
    struct Produto* proximo;
} Produto;

Produto* criarProduto(float preco) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->preco = preco;
    novoProduto->proximo = NULL;
    return novoProduto;
}

void inserirProduto(Produto** cabeca, float preco) {
    Produto* novoProduto = criarProduto(preco);
    if (*cabeca == NULL || (*cabeca)->preco >= preco) {
        novoProduto->proximo = *cabeca;
        *cabeca = novoProduto;
    } else {
        Produto* atual = *cabeca;
        while (atual->proximo != NULL && atual->proximo->preco < preco) {
            atual = atual->proximo;
        }
        novoProduto->proximo = atual->proximo;
        atual->proximo = novoProduto;
    }
}

void exibirProdutos(Produto* cabeca) {
    Produto* atual = cabeca;
    printf("Produtos disponíveis:\n");
    while (atual != NULL) {
        printf("Preço: %.2f\n", atual->preco);
        atual = atual->proximo;
    }
}

void removerProduto(Produto** cabeca, float preco) {
    if (*cabeca == NULL) return;

    if ((*cabeca)->preco == preco) {
        Produto* temp = *cabeca;
        *cabeca = (*cabeca)->proximo;
        free(temp);
        return;
    }

    Produto* atual = *cabeca;
    while (atual->proximo != NULL && atual->proximo->preco != preco) {
        atual = atual->proximo;
    }

    if (atual->proximo != NULL) {
        Produto* temp = atual->proximo;
        atual->proximo = atual->proximo->proximo;
        free(temp);
    }
}

int main() {
    Produto* listaProdutos = NULL;
    int opcao;
    float preco;

    do {
        printf("\n1. Inserir produto\n2. Exibir produtos\n3. Remover produto\n4. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o preço do produto: ");
                scanf("%f", &preco);
                inserirProduto(&listaProdutos, preco);
                break;
            case 2:
                exibirProdutos(listaProdutos);
                break;
            case 3:
                printf("Digite o preço do produto a ser removido: ");
                scanf("%f", &preco);
                removerProduto(&listaProdutos, preco);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    while (listaProdutos != NULL) {
        Produto* temp = listaProdutos;
        listaProdutos = listaProdutos->proximo;
        free(temp);
    }

    return 0;
}
