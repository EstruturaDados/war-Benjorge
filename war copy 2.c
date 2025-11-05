#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// Função para simular o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = rand() % 6 + 1; // valor entre 1 e 6
    int dado_defensor = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d\n", dado_atacante);
    printf("Dado do defensor: %d\n", dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("Resultado: Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor); // muda a cor do território
        defensor->tropas = atacante->tropas / 2; // transfere metade das tropas
    } else {
        printf("Resultado: Defensor resistiu ao ataque.\n");
        atacante->tropas--; // atacante perde uma tropa
    }
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio* territorios = (Territorio*)calloc(n, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", territorios[i].nome);
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição inicial
    printf("\n=== Territórios Cadastrados ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d - Nome: %s | Cor: %s | Tropas: %d\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }

    // Simulação de ataque
    int idx_atacante, idx_defensor;
    printf("\nEscolha o índice do território atacante (1 a %d): ", n);
    scanf("%d", &idx_atacante);
    printf("Escolha o índice do território defensor (1 a %d): ", n);
    scanf("%d", &idx_defensor);

    // Validação
    if (idx_atacante == idx_defensor || idx_atacante < 1 || idx_defensor < 1 || idx_atacante > n || idx_defensor > n) {
        printf("Índices inválidos para ataque.\n");
    } else if (strcmp(territorios[idx_atacante - 1].cor, territorios[idx_defensor - 1].cor) == 0) {
        printf("Não é possível atacar um território da mesma cor.\n");
    } else {
        atacar(&territorios[idx_atacante - 1], &territorios[idx_defensor - 1]);
    }

    // Exibição pós-ataque
    printf("\n=== Territórios Atualizados ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d - Nome: %s | Cor: %s | Tropas: %d\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }

    // Liberação de memória
    free(territorios);
    return 0;
}