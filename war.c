#include <stdio.h>

int main(void) {
    printf("Cadastro de Territorios\n");
    return 0;
}
#include <stdio.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main(void) {
    // Vetor para armazenar 5 territorios
    Territorio territorios[5];

    printf("Estrutura criada e vetor alocado.\n");
    return 0;
}
#include <stdio.h>

// Struct simples para o cadastro
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main(void) {
    Territorio territorios[5];

    printf("=== Cadastro de Territorios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);

        // Leitura simples, sem espaços, com limites de tamanho
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\nCadastro concluido.\n");
    return 0;
}
#include <stdio.h>

// Struct Territorio conforme solicitado
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main(void) {
    Territorio territorios[5];

    // Cadastro
    printf("=== Cadastro de Territorios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição
    printf("\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
