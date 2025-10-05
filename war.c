#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Protótipos */
Territorio* alocarMapa(int n);
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirMapa(const Territorio* mapa, int n);
int escolherIndice(const char* rotulo, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main(void) {
    setbuf(stdout, NULL);
    srand((unsigned)time(NULL));

    /* Para este nível, manteremos 5 posições, mas usando alocação dinâmica */
    int n = 5;
    Territorio* mapa = alocarMapa(n);
    if (!mapa) {
        printf("Falha ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    while (1) {
        exibirMapa(mapa, n);

        printf("\nFase de ataque, escolha atacante e defensor.\n");
        printf("Digite 0 para sair.\n");

        int a = escolherIndice("Atacante [1..5 ou 0 para sair]", n);
        if (a == -1) break;

        int d = escolherIndice("Defensor [1..5]", n);
        if (d == -1) {
            printf("Indice invalido para defensor.\n");
            continue;
        }

        if (a == d) {
            printf("Nao pode atacar a si mesmo.\n");
            continue;
        }
        if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
            printf("Nao pode atacar territorio da mesma cor.\n");
            continue;
        }
        if (mapa[a].tropas < 1) {
            printf("Atacante sem tropas para atacar.\n");
            continue;
        }
        if (mapa[d].tropas <= 0) {
            printf("Defensor sem tropas, escolha outro alvo.\n");
            continue;
        }

        atacar(&mapa[a], &mapa[d]);

        printf("\nMapa apos o ataque:\n");
        exibirMapa(mapa, n);
    }

    liberarMemoria(mapa);
    printf("Jogo encerrado.\n");
    return 0;
}

/* Aloca dinamicamente e zera os campos */
Territorio* alocarMapa(int n) {
    return (Territorio*)calloc((size_t)n, sizeof(Territorio));
}

/* Cadastro básico, igual ao nível Novato */
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("=== Cadastro de Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: ");
        scanf("%29s", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);
        printf("Tropas: ");
        if (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 0) {
            mapa[i].tropas = 0;
        }
    }
}

/* Apenas leitura, const para deixar claro */
void exibirMapa(const Territorio* mapa, int n) {
    printf("\nMAPA DO MUNDO, ESTADO ATUAL\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s, Exercito %s, Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* Lê índice, retorna -1 se o usuário digitar 0 na hora do atacante */
int escolherIndice(const char* rotulo, int n) {
    int idx;
    printf("%s: ", rotulo);
    if (scanf("%d", &idx) != 1) return -1;
    if (idx == 0) return -1;
    if (idx < 1 || idx > n) return -1;
    return idx - 1;
}

/* Simulação do ataque
   Regras:
   dadoA = 1..6, dadoD = 1..6
   empate favorece o atacante, ou seja, dadoA >= dadoD faz o defensor perder 1 tropa
   se defensor chegar a 0, muda de cor para a do atacante e recebe 1 tropa
   o atacante cede 1 tropa para ocupar, se tiver pelo menos 2
*/
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nResultado da batalha\n");
    printf("%s rolou: %d\n", atacante->nome, dadoA);
    printf("%s rolou: %d\n", defensor->nome, dadoD);

    if (dadoA >= dadoD) {
        if (defensor->tropas > 0) defensor->tropas -= 1;
        printf("Atacante venceu a rodada, defensor perde 1 tropa.\n");

        if (defensor->tropas == 0) {
            strcpy(defensor->cor, atacante->cor);
            if (atacante->tropas >= 2) {
                atacante->tropas -= 1;
                defensor->tropas = 1;
            } else {
                defensor->tropas = 1;
            }
            printf("Conquista, territorio agora pertence ao Exercito %s.\n", defensor->cor);
        }
    } else {
        if (atacante->tropas > 0) atacante->tropas -= 1;
        printf("Defensor venceu a rodada, atacante perde 1 tropa.\n");
    }
}

/* Libera a memória do vetor dinâmico */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

