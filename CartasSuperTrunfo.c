#include <stdio.h>
#include <string.h>

/* ================================================================
   SISTEMA INTEGRADO - SUPER TRUNFO + MOVIMENTOS DE XADREZ
   Autor: Luiz Fernando Gachet
   Descrição:
     - Menu principal para escolher entre dois desafios.
     - Super Trunfo com comparação de dois atributos e menus dinâmicos.
     - Movimentos de Xadrez com recursividade e loops complexos.
   ================================================================ */

/* ================================================================
   ESTRUTURA DO SUPER TRUNFO
   ================================================================ */
typedef struct {
    char nome[30];
    int populacao;
    float area;
    float pib;
    float densidade;
} Carta;

// Função para comparar cartas com dois atributos
void compararCartas(Carta c1, Carta c2) {
    int opcao1, opcao2;
    float valor1_c1 = 0, valor1_c2 = 0;
    float valor2_c1 = 0, valor2_c2 = 0;
    float soma_c1 = 0, soma_c2 = 0;

    printf("\nEscolha o primeiro atributo:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Densidade Demográfica\n");
    printf("Opção: ");
    scanf("%d", &opcao1);

    printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
    switch (opcao1) {
        case 1:
            printf("2 - Área\n3 - PIB\n4 - Densidade Demográfica\n");
            break;
        case 2:
            printf("1 - População\n3 - PIB\n4 - Densidade Demográfica\n");
            break;
        case 3:
            printf("1 - População\n2 - Área\n4 - Densidade Demográfica\n");
            break;
        case 4:
            printf("1 - População\n2 - Área\n3 - PIB\n");
            break;
        default:
            printf("Opção inválida! Encerrando.\n");
            return;
    }
    printf("Opção: ");
    scanf("%d", &opcao2);

    // Atribuir valores dos atributos
    switch (opcao1) {
        case 1: valor1_c1 = c1.populacao; valor1_c2 = c2.populacao; break;
        case 2: valor1_c1 = c1.area; valor1_c2 = c2.area; break;
        case 3: valor1_c1 = c1.pib; valor1_c2 = c2.pib; break;
        case 4: valor1_c1 = c1.densidade; valor1_c2 = c2.densidade; break;
    }
    switch (opcao2) {
        case 1: valor2_c1 = c1.populacao; valor2_c2 = c2.populacao; break;
        case 2: valor2_c1 = c1.area; valor2_c2 = c2.area; break;
        case 3: valor2_c1 = c1.pib; valor2_c2 = c2.pib; break;
        case 4: valor2_c1 = c1.densidade; valor2_c2 = c2.densidade; break;
    }

    // Mostrar comparação individual
    printf("\nComparando cartas:\n");
    printf("%s vs %s\n\n", c1.nome, c2.nome);
    printf("Atributo 1 (%d): %.2f vs %.2f\n", opcao1, valor1_c1, valor1_c2);
    printf("Atributo 2 (%d): %.2f vs %.2f\n", opcao2, valor2_c1, valor2_c2);

    // Comparação com regras (densidade menor vence)
    float pontos_c1 = 0, pontos_c2 = 0;

    pontos_c1 += (opcao1 == 4) ? (valor1_c1 < valor1_c2) : (valor1_c1 > valor1_c2);
    pontos_c2 += (opcao1 == 4) ? (valor1_c2 < valor1_c1) : (valor1_c2 > valor1_c1);

    pontos_c1 += (opcao2 == 4) ? (valor2_c1 < valor2_c2) : (valor2_c1 > valor2_c2);
    pontos_c2 += (opcao2 == 4) ? (valor2_c2 < valor2_c1) : (valor2_c2 > valor2_c1);

    soma_c1 = valor1_c1 + valor2_c1;
    soma_c2 = valor1_c2 + valor2_c2;

    printf("\nSoma dos atributos: %.2f ( %s ) | %.2f ( %s )\n",
           soma_c1, c1.nome, soma_c2, c2.nome);

    if (soma_c1 > soma_c2)
        printf("\n>>> %s venceu a rodada!\n", c1.nome);
    else if (soma_c2 > soma_c1)
        printf("\n>>> %s venceu a rodada!\n", c2.nome);
    else
        printf("\n>>> Empate!\n");
}

// Função principal do Super Trunfo
void superTrunfo() {
    Carta c1 = {"Brasil", 213, 8516.0, 2200.0, 25.0};
    Carta c2 = {"Japão", 126, 378.0, 5400.0, 334.0};

    printf("\n=== SUPER TRUNFO ===\n");
    printf("Comparando %s e %s\n", c1.nome, c2.nome);

    compararCartas(c1, c2);
}

/* ================================================================
   MOVIMENTOS DE XADREZ (COM RECURSIVIDADE E LOOPS COMPLEXOS)
   ================================================================ */
void moverTorre(int casas, int atual) {
    if (atual > casas) return;
    printf("Direita (%d)\n", atual);
    moverTorre(casas, atual + 1);
}

void moverBispo(int casas, int atual) {
    if (atual > casas) return;
    for (int v = 0; v < 1; v++) {
        for (int h = 0; h < 1; h++) {
            printf("Diagonal Superior Direita (%d)\n", atual);
        }
    }
    moverBispo(casas, atual + 1);
}

void moverRainha(int casas, int atual) {
    if (atual > casas) return;
    printf("Cima (%d)\n", atual);
    printf("Direita (%d)\n", atual);
    moverRainha(casas, atual + 1);
}

void moverCavalo() {
    int movimentos = 3;
    for (int i = 1; i <= movimentos; i++) {
        for (int j = 1; j <= 3; j++) {
            if (j == 1 || j == 2) {
                printf("Cima (%d,%d)\n", i, j);
                continue;
            } else if (j == 3) {
                printf("Direita (%d,%d)\n", i, j);
                break;
            }
        }
    }
}

void movimentosXadrez() {
    int casas = 3;

    printf("\n=== MOVIMENTOS DE XADREZ ===\n");

    printf("\nTorre:\n");
    moverTorre(casas, 1);

    printf("\nBispo:\n");
    moverBispo(casas, 1);

    printf("\nRainha:\n");
    moverRainha(casas, 1);

    printf("\nCavalo:\n");
    moverCavalo();

    printf("\n--- Fim dos Movimentos ---\n");
}

/* ================================================================
   MENU PRINCIPAL
   ================================================================ */
int main() {
    int opcao;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Super Trunfo\n");
        printf("2 - Movimentos de Xadrez\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                superTrunfo();
                break;
            case 2:
                movimentosXadrez();
                break;
            case 0:
                printf("\nSaindo do sistema... Até logo, mestre Luiz!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

    
