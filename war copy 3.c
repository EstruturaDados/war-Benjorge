#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para atribuir missão aleatória
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função para verificar se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "Conquistar 3 territórios seguidos")) {
        int cont = 0;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                cont++;
                if (cont >= 2) return 1;
            } else {
                cont = 0;
            }
        }
    } else if (strstr(missao, "Eliminar todas as tropas da cor vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    // Outras missões podem ser adicionadas aqui
    return 0;
}

// Função para simular ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d\n", dado_atacante);
    printf("Dado do defensor: %d\n", dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("Resultado: Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("Resultado: Defensor resistiu ao ataque.\n");
        if (atacante->tropas > 0) atacante->tropas--;
    }
}

// Função para exibir o mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== Mapa Atualizado ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL));

    // Vetor de missões
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar todos os territórios com mais de 10 tropas",
        "Controlar os 3 primeiros territórios",
        "Ter pelo menos 2 territórios com mais de 15 tropas"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // Missão do jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para missão.\n");
        free(mapa);
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\nSua missão estratégica: %s\n", missaoJogador);

    // Loop de ataque
    int turno = 1;
    while (1) {
        printf("\n--- Turno %d ---\n", turno++);
        int a, d;
        printf("Escolha o território atacante (1 a %d): ", n);
        scanf("%d", &a);
        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &d);

        if (a < 1 || a > n || d < 1 || d > n || a == d) {
            printf("Ataque inválido.\n");
            continue;
        }

        if (strcmp(mapa[a - 1].cor, mapa[d - 1].cor) == 0) {
            printf("Não é possível atacar um território da mesma cor.\n");
            continue;
        }

        atacar(&mapa[a - 1], &mapa[d - 1]);
        exibirMapa(mapa, n);

        // Verificação de missão
        if (verificarMissao(missaoJogador, mapa, n)) {
            printf("\n🎉 Missão cumprida! Você venceu o jogo!\n");
            break;
        }
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}