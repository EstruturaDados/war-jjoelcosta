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
