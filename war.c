#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[5]; // vetor com 3 territórios

    // Preenchendo os dados
    for (int i = 0; i < 5; i++) {
        
        printf("---Território---\n");

        printf("Digite o nome do território %d: ", i + 1);
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do território %d: ", i + 1);
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas do território %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);
    }

    // Exibindo os dados
    printf("\n=== Lista de Territórios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
};