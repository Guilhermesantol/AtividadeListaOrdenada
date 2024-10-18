#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro {
    int codigo;
    char titulo[100];
    struct Livro* proximo;
} Livro;

Livro* criarLivro(int codigo, const char* titulo) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
    novoLivro->codigo = codigo;
    strcpy(novoLivro->titulo, titulo);
    novoLivro->proximo = NULL;
    return novoLivro;
}

void adicionarLivro(Livro** cabeca, int codigo, const char* titulo) {
    Livro* novoLivro = criarLivro(codigo, titulo);
    novoLivro->proximo = *cabeca;
    *cabeca = novoLivro;
}

void exibirLivros(Livro* cabeca) {
    Livro* atual = cabeca;
    printf("Livros disponíveis:\n");
    while (atual != NULL) {
        printf("Código: %d, Título: %s\n", atual->codigo, atual->titulo);
        atual = atual->proximo;
    }
}

void removerLivro(Livro** cabeca, int codigo) {
    if (*cabeca == NULL) return;

    if ((*cabeca)->codigo == codigo) {
        Livro* temp = *cabeca;
        *cabeca = (*cabeca)->proximo;
        free(temp);
        return;
    }

    Livro* atual = *cabeca;
    while (atual->proximo != NULL && atual->proximo->codigo != codigo) {
        atual = atual->proximo;
    }

    if (atual->proximo != NULL) {
        Livro* temp = atual->proximo;
        atual->proximo = atual->proximo->proximo;
        free(temp);
    }
}

int main() {
    Livro* acervo = NULL;
    int opcao, codigo;
    char titulo[100];

    do {
        printf("\n1. Adicionar livro\n2. Exibir livros\n3. Remover livro danificado\n4. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Digite o código do livro: ");
                scanf("%d", &codigo);
                getchar(); 
                printf("Digite o título do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                adicionarLivro(&acervo, codigo, titulo);
                break;
            case 2:
                exibirLivros(acervo);
                break;
            case 3:
                printf("Digite o código do livro danificado a ser removido: ");
                scanf("%d", &codigo);
                removerLivro(&acervo, codigo);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    while (acervo != NULL) {
        Livro* temp = acervo;
        acervo = acervo->proximo;
        free(temp);
    }

    return 0;
}
