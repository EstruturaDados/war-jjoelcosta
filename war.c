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
void pausar(void);

int validarAtaque(const Territorio* atacante, const Territorio* defensor);
void atacar(Territorio* atacante, Territorio* defensor);

void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissaoTopo(const char* missao, const char* corJogador);
int verificarMissaoCumprida(const char* missao, const char* corJogador, const Territorio* mapa, int n);

void liberarTudo(Territorio* mapa, char* missao);

int menu(void);

int main(void) {
    setbuf(stdout, NULL);
    srand((unsigned)time(NULL));

    int n = 5;
    Territorio* mapa = alocarMapa(n);
    if (!mapa) { printf("Falha ao alocar memoria.\n"); return 1; }

    char corJogador[10];
    printf("Digite a sua cor de exercito, ex: Azul, Verde: ");
    scanf("%9s", corJogador);

    cadastrarTerritorios(mapa, n);

    char* missoes[] = {
        "Destruir o exercito Verde.",
        "Conquistar 3 territorios.",
        "Eliminar o exercito Vermelho.",
        "Alcancar total de 15 tropas.",
        "Dominar todos os territorios."
    };
    int totalMissoes = (int)(sizeof(missoes) / sizeof(missoes[0]));

    char* missao = (char*)malloc(96);
    if (!missao) { printf("Falha ao alocar memoria para a missao.\n"); liberarTudo(mapa, NULL); return 1; }
    atribuirMissao(missao, missoes, totalMissoes);

    /* loop principal com o mesmo fluxo visual do professor */
    while (1) {
        /* mapa */
        printf("\n============= MAPA DO MUNDO =============\n");
        for (int i = 0; i < n; i++) {
            printf("%d. %-10s (Exercito: %-8s, Tropas: %d)\n",
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        printf("=========================================\n");

        /* missao no topo, igual ao print */
        exibirMissaoTopo(missao, corJogador);

        /* menu */
        int opc = menu();
        if (opc == 0) break;

        if (opc == 1) {
            int a, d;
            printf("\n--- FASE DE ATAQUE ---\n");
            printf("Escolha o territorio atacante (1 a %d): ", n);
            scanf("%d", &a);
            printf("Escolha o territorio defensor (1 a %d): ", n);
            scanf("%d", &d);

            if (a < 1 || a > n || d < 1 || d > n) { printf("Indice invalido.\n"); pausar(); continue; }
            a -= 1; d -= 1;

            if (!validarAtaque(&mapa[a], &mapa[d])) { pausar(); continue; }

            /* resultado no formato do professor */
            int dadoA = (rand() % 6) + 1;
            int dadoD = (rand() % 6) + 1;
            printf("\n--- RESULTADO DA BATALHA ---\n");
            printf("Ataque (%s): %d | Defesa (%s): %d\n", mapa[a].nome, dadoA, mapa[d].nome, dadoD);

            /* regra para combinar com o print: atacante vence, defensor perde 1 tropa; se zerar, conquista e move 1 tropa */
            if (dadoA >= dadoD) {
                if (mapa[d].tropas > 0) mapa[d].tropas -= 1;
                printf("VITORIA DO ATAQUE. O defensor perdeu 1 tropa.\n");
                if (mapa[d].tropas == 0) {
                    strcpy(mapa[d].cor, mapa[a].cor);
                    mapa[d].tropas = 1;
                    if (mapa[a].tropas > 0) mapa[a].tropas -= 1;
                    printf("CONQUISTA. %s agora pertence ao Exercito %s.\n", mapa[d].nome, mapa[d].cor);
                }
            } else {
                if (mapa[a].tropas > 0) mapa[a].tropas -= 1;
                printf("VITORIA DA DEFESA. O atacante perdeu 1 tropa.\n");
            }

            /* checa missao silenciosamente ao fim do turno */
            if (verificarMissaoCumprida(missao, corJogador, mapa, n)) {
                printf("\nMISSAO CUMPRIDA. Vitoria do exercito %s.\n", corJogador);
                break;
            }

            pausar();
        } else if (opc == 2) {
            /* igual ao print: “Voce ainda nao cumpriu sua missao…” */
            if (verificarMissaoCumprida(missao, corJogador, mapa, n)) {
                printf("Parabens. Sua missao foi cumprida.\n");
            } else {
                printf("Voce ainda nao cumpriu sua missao. Continue a lutar!\n");
            }
            pausar();
        }
    }

    liberarTudo(mapa, missao);
    printf("\nJogo encerrado.\n");
    return 0;
}

/* =================== Funcoes =================== */

Territorio* alocarMapa(int n) { return (Territorio*)calloc((size_t)n, sizeof(Territorio)); }

void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\n=== Cadastro de Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: "); scanf("%29s", mapa[i].nome);
        printf("Cor do exercito: "); scanf("%9s", mapa[i].cor);
        printf("Tropas: "); if (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 0) mapa[i].tropas = 0;
    }
}

void exibirMissaoTopo(const char* missao, const char* corJogador) {
    printf("\n--- SUA MISSAO (Exercito %s) ---\n", corJogador);
    printf("%s\n", missao);
}

int menu(void) {
    int op;
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha sua acao: ");
    if (scanf("%d", &op) != 1) return 0;
    return op;
}

int validarAtaque(const Territorio* atacante, const Territorio* defensor) {
    if (atacante == defensor) { printf("Nao pode atacar a si mesmo.\n"); return 0; }
    if (strcmp(atacante->cor, defensor->cor) == 0) { printf("Nao pode atacar territorio da mesma cor.\n"); return 0; }
    if (atacante->tropas < 1) { printf("Atacante sem tropas.\n"); return 0; }
    if (defensor->tropas <= 0) { printf("Defensor sem tropas.\n"); return 0; }
    return 1;
}

/* não usada diretamente pois formatamos o print “Ataque | Defesa”, mas mantida se quiser reaproveitar */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;
    if (dadoA >= dadoD) {
        if (defensor->tropas > 0) defensor->tropas -= 1;
        if (defensor->tropas == 0) {
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            if (atacante->tropas > 0) atacante->tropas -= 1;
        }
    } else {
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int i = rand() % totalMissoes;
    strcpy(destino, missoes[i]);
}

int verificarMissaoCumprida(const char* missao, const char* corJogador, const Territorio* mapa, int n) {
    int terrJog = 0, tropasJog = 0, temVermelho = 0, todosDoJog = 1;
    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            terrJog++; tropasJog += mapa[i].tropas;
        } else {
            todosDoJog = 0;
        }
        if (strcmp(mapa[i].cor, "Vermelho") == 0) temVermelho = 1;
    }
    if (strstr(missao, "Destruir o exercito Verde") != NULL) {
        int temVerde = 0;
        for (int i = 0; i < n; i++) if (strcmp(mapa[i].cor, "Verde") == 0) temVerde = 1;
        return temVerde == 0;
    }
    if (strstr(missao, "Conquistar 3 territorios") != NULL) return terrJog >= 3;
    if (strstr(missao, "Eliminar o exercito Vermelho") != NULL) return temVermelho == 0;
    if (strstr(missao, "Alcancar total de 15 tropas") != NULL) return tropasJog >= 15;
    if (strstr(missao, "Dominar todos os territorios") != NULL) return todosDoJog;
    return 0;
}

void pausar(void) {
    printf("\nPressione Enter para continuar...");
    int c;
    do { c = getchar(); } while (c != '\n' && c != EOF);
    if (c != '\n') { while ((c = getchar()) != '\n' && c != EOF) {} }
}

void liberarTudo(Territorio* mapa, char* missao) {
    if (mapa) free(mapa);
    if (missao) free(missao);
}
