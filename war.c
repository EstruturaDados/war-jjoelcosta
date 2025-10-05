#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

Territorio* alocarMapa(int n);
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirMapa(const Territorio* mapa, int n);
int escolherIndice(const char* rotulo, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main(void) {
    setbuf(stdout, NULL);
    srand((unsigned)time(NULL));

    int n = 5;
    Territorio* mapa = alocarMapa(n);
    if (!mapa) {
        printf("Falha ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    while (1) {
        exibirMapa(mapa, n);

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", n);
        int a;
        scanf("%d", &a);
        if (a == 0) break;

        printf("Escolha o territorio defensor (1 a %d): ", n);
        int d;
        scanf("%d", &d);

        if (a == d) {
            printf("Um territorio nao pode atacar a si mesmo!\n");
            continue;
        }
        if (strcmp(mapa[a - 1].cor, mapa[d - 1].cor) == 0) {
            printf("Nao e possivel atacar um territorio do mesmo exercito!\n");
            continue;
        }

        atacar(&mapa[a - 1], &mapa[d - 1]);

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar();
        getchar();
    }

    liberarMemoria(mapa);
    printf("\nJogo encerrado.\n");
    return 0;
}

Territorio* alocarMapa(int n) {
    return (Territorio*)calloc((size_t)n, sizeof(Territorio));
}

void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("=== Cadastro de Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf("%29s", mapa[i].nome);
        printf("Digite a cor do exercito (ex: Azul, Verde): ");
        scanf("%9s", mapa[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirMapa(const Territorio* mapa, int n) {
    printf("\n     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=========================================\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoA);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoD);

    if (dadoA >= dadoD) {
        defensor->tropas--;
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        if (defensor->tropas <= 0) {
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas--;
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n",
                   defensor->nome, defensor->cor);
        }
    } else {
        atacante->tropas--;
        printf("O ataque falhou! O atacante perdeu 1 tropa.\n");
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}