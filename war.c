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
void exibirMissaoTopo(const char* missao, const char* corJogador);
int validarAtaque(const Territorio* atacante, const Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissaoCumprida(const char* missao, const char* corJogador, const Territorio* mapa, int n);
void liberarTudo(Territorio* mapa, char* missao);

/* Funções auxiliares */
static int ler_int(const char* prompt, int min, int max, int permite_zero);
static void ler_string(const char* prompt, char* buffer, int tamanho);
static void pausar(void);
static int menu(void);

int main(void) {
    setbuf(stdout, NULL);
    srand((unsigned)time(NULL));

    int n = 5;
    Territorio* mapa = alocarMapa(n);
    if (!mapa) {
        printf("Falha ao alocar memoria.\n");
        return 1;
    }

    char corJogador[10];
    ler_string("Digite a sua cor de exercito (ex: Azul, Verde): ", corJogador, sizeof(corJogador));
    cadastrarTerritorios(mapa, n);

    char* missoes[] = {
        "Destruir o exercito Verde.",
        "Conquistar 3 territorios.",
        "Eliminar o exercito Vermelho.",
        "Alcancar total de 15 tropas.",
        "Dominar todos os territorios."
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    char* missao = (char*)malloc(96);
    if (!missao) {
        printf("Falha ao alocar memoria para a missao.\n");
        liberarTudo(mapa, NULL);
        return 1;
    }
    atribuirMissao(missao, missoes, totalMissoes);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); /* limpeza do buffer */

    while (1) {
        printf("\n============= MAPA DO MUNDO =============\n");
        for (int i = 0; i < n; i++) {
            printf("%d. %-10s (Exercito: %-8s, Tropas: %d)\n",
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        printf("=========================================\n");

        exibirMissaoTopo(missao, corJogador);

        int opc = menu();
        if (opc == 0) break;

        if (opc == 1) {
            int a, d;
            printf("\n--- FASE DE ATAQUE ---\n");

            char prompt_ataque[64];
            sprintf(prompt_ataque, "Escolha o territorio atacante (1 a %d, 0 para voltar): ", n);
            a = ler_int(prompt_ataque, 1, n, 1);
            if (a == 0) continue;

            sprintf(prompt_ataque, "Escolha o territorio defensor (1 a %d, 0 para voltar): ", n);
            d = ler_int(prompt_ataque, 1, n, 1);
            if (d == 0) continue;

            a--; d--;

            if (!validarAtaque(&mapa[a], &mapa[d])) {
                pausar();
                continue;
            }

            int dadoA = (rand() % 6) + 1;
            int dadoD = (rand() % 6) + 1;
            printf("\n--- RESULTADO DA BATALHA ---\n");
            printf("Ataque (%s): %d | Defesa (%s): %d\n", mapa[a].nome, dadoA, mapa[d].nome, dadoD);

            if (dadoA >= dadoD) { /* atacante vence no empate */
                if (mapa[d].tropas > 0) mapa[d].tropas--;
                if (mapa[d].tropas < 0) mapa[d].tropas = 0;
                printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

                if (mapa[d].tropas == 0) {
                    strcpy(mapa[d].cor, mapa[a].cor);
                    mapa[d].tropas = 1;
                    if (mapa[a].tropas > 0) mapa[a].tropas--;
                    if (mapa[a].tropas < 0) mapa[a].tropas = 0;
                    printf("CONQUISTA! %s agora pertence ao Exercito %s.\n", mapa[d].nome, mapa[d].cor);
                }
            } else {
                if (mapa[a].tropas > 0) mapa[a].tropas--;
                if (mapa[a].tropas < 0) mapa[a].tropas = 0;
                printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
            }

            if (verificarMissaoCumprida(missao, corJogador, mapa, n)) {
                printf("\nMISSAO CUMPRIDA! Vitoria do exercito %s!\n", corJogador);
                break;
            }

            pausar();
        } 
        else if (opc == 2) {
            if (verificarMissaoCumprida(missao, corJogador, mapa, n))
                printf("Parabens! Sua missao foi cumprida.\n");
            else
                printf("Voce ainda nao cumpriu sua missao. Continue a lutar!\n");
            pausar();
        }
    }

    liberarTudo(mapa, missao);
    printf("\nJogo encerrado.\n");
    return 0;
}

/* =================== Funções Auxiliares =================== */

static void ler_string(const char* prompt, char* buffer, int tamanho) {
    printf("%s", prompt);
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

static int ler_int(const char* prompt, int min, int max, int permite_zero) {
    char buf[64];
    long v;
    char *end;

    while (1) {
        if (prompt && *prompt) printf("%s", prompt);
        if (!fgets(buf, sizeof buf, stdin)) return 0;

        v = strtol(buf, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') end++;

        if (*end == '\0') {
            if (permite_zero && v == 0) return 0;
            if (v >= min && v <= max) return (int)v;
        }
        printf("Entrada invalida. Por favor, tente novamente.\n");
    }
}

static void pausar(void) {
    printf("\nPressione Enter para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Territorio* alocarMapa(int n) {
    return (Territorio*)calloc((size_t)n, sizeof(Territorio));
}

void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\n=== Cadastro de Territorios ===\n");
    for (int i = 0; i < n; i++) {
        char buffer_nome[30], buffer_cor[10];
        printf("\nTerritorio %d\n", i + 1);
        ler_string("Nome: ", buffer_nome, sizeof(buffer_nome));
        strcpy(mapa[i].nome, buffer_nome);
        ler_string("Cor do exercito: ", buffer_cor, sizeof(buffer_cor));
        strcpy(mapa[i].cor, buffer_cor);
        mapa[i].tropas = ler_int("Tropas: ", 1, 99, 0);
    }
}

void exibirMissaoTopo(const char* missao, const char* corJogador) {
    printf("\n--- SUA MISSAO (Exercito %s) ---\n", corJogador);
    printf("%s\n", missao);
}

static int menu(void) {
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair do Jogo\n");
    return ler_int("Escolha sua acao: ", 0, 2, 1);
}

int validarAtaque(const Territorio* atacante, const Territorio* defensor) {
    if (atacante == defensor) {
        printf("Erro: Nao pode atacar o proprio territorio.\n");
        return 0;
    }
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Nao pode atacar um territorio aliado.\n");
        return 0;
    }
    if (atacante->tropas < 2) {
        printf("Erro: Territorio atacante precisa de pelo menos 2 tropas.\n");
        return 0;
    }
    return 1;
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int i = rand() % totalMissoes;
    strcpy(destino, missoes[i]);
}

int verificarMissaoCumprida(const char* missao, const char* corJogador, const Territorio* mapa, int n) {
    int terrJog = 0, tropasJog = 0;
    int temVerde = 0, temVermelho = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            terrJog++;
            tropasJog += mapa[i].tropas;
        }
        if (strcmp(mapa[i].cor, "Verde") == 0) temVerde = 1;
        if (strcmp(mapa[i].cor, "Vermelho") == 0) temVermelho = 1;
    }

    if (strstr(missao, "Destruir o exercito Verde")) return !temVerde;
    if (strstr(missao, "Conquistar 3 territorios")) return terrJog >= 3;
    if (strstr(missao, "Eliminar o exercito Vermelho")) return !temVermelho;
    if (strstr(missao, "Alcancar total de 15 tropas")) return tropasJog >= 15;
    if (strstr(missao, "Dominar todos os territorios")) return terrJog == n;
    
    return 0;
}

void liberarTudo(Territorio* mapa, char* missao) {
    if (mapa) free(mapa);
    if (missao) free(missao);
}