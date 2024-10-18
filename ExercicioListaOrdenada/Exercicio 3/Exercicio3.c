#include <stdio.h>
#include <stdbool.h>

#define MAX_ALUNOS 100

void inserirAluno(int alunos[], int *totalAlunos);
void exibirAlunos(int alunos[], int totalAlunos);
bool buscarAluno(int alunos[], int totalAlunos, int matricula);

int main() {
    int alunos[MAX_ALUNOS];  
    int totalAlunos = 0;     
    int opcao, matricula;
    bool encontrado;

    do {
        printf("\nSistema de Cadastro de Alunos\n");
        printf("1. Inserir novo aluno\n");
        printf("2. Exibir lista completa de alunos\n");
        printf("3. Buscar aluno por número de matrícula\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirAluno(alunos, &totalAlunos);
                break;
            case 2:
                exibirAlunos(alunos, totalAlunos);
                break;
            case 3:
                printf("Digite o número de matrícula do aluno: ");
                scanf("%d", &matricula);
                encontrado = buscarAluno(alunos, totalAlunos, matricula);
                if (encontrado) {
                    printf("Aluno de matrícula %d está cadastrado.\n", matricula);
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 4);

    return 0;
}

void inserirAluno(int alunos[], int *totalAlunos) {
    if (*totalAlunos < MAX_ALUNOS) {
        printf("Digite o número de matrícula do novo aluno: ");
        scanf("%d", &alunos[*totalAlunos]);
        (*totalAlunos)++;
        printf("Aluno inserido com sucesso!\n");
    } else {
        printf("Limite de alunos atingido.\n");
    }
}

void exibirAlunos(int alunos[], int totalAlunos) {
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        printf("Lista de alunos cadastrados:\n");
        for (int i = 0; i < totalAlunos; i++) {
            printf("Aluno %d: Matrícula %d\n", i + 1, alunos[i]);
        }
    }
}

bool buscarAluno(int alunos[], int totalAlunos, int matricula) {
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i] == matricula) {
            return true; 
        }
    }
    return false; 
}
