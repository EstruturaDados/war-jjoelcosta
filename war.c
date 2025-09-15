#include <stdio.h>

// Definindo a estrutura do tipo Territorio
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

        printf("Digite a cor do exercito (ex: Azul, Verde): ");
        scanf("%9s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição em formato de mapa do mundo
    printf("\n=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTERRITORIO %d:\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por Exercito %s\n", territorios[i].cor);
        printf("- Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
