#include <stdio.h>

// Definindo a estrutura do tipo Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Criando 5 territórios pré-cadastrados
    Territorio territorios[5] = {
        {"America", "Azul", 6},
        {"Europa", "Verde", 8},
        {"Asia", "Vermelho", 10},
        {"Africa", "Amarelo", 7},
        {"Oceania", "Preto", 5}
    };

    // Exibindo o mapa do mundo
    printf("=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTERRITORIO %d:\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por Exercito %s\n", territorios[i].cor);
        printf("- Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
