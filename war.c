#include <stdio.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main(void) {
    Territorio territorios[5];

    // Cadastro dos territórios
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

    // Exibição dos territórios cadastrados
    printf("\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
