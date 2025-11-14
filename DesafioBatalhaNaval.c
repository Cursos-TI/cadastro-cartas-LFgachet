#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

/* Valores no tabuleiro */
#define WATER 0
#define SHIP  3
#define AFFECT 5

/* Função auxiliar para inicializar tabuleiro com água */
void init_board(int board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            board[r][c] = WATER;
}

/* Função que imprime o tabuleiro no console */
void print_board(int board[ROWS][COLS], int affected[ROWS][COLS]) {
    printf("Tabuleiro (0=agua, 3=navio, 5=area afetada):\n\n");
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            /* Evitamos sobrescrever navio com 5 para manter ambos visíveis.
               Como simplificação (conforme enunciado), neste exemplo as
               áreas foram posicionadas para não cobrir navios. */
            if (affected[r][c] && board[r][c] == WATER)
                printf("%d ", AFFECT);
            else
                printf("%d ", board[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Cria a matriz do CONE (aponta para baixo). 
   size deve ser ímpar preferencialmente (ex: 5 ou 7). 
   A matriz é preenchida dinamicamente com 0/1 usando condicionais. */
void build_cone(int size, int cone[size][size]) {
    int center = size / 2;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            /* largura teórica do cone na linha i: 1 + 2*i, mas não ultrapassar size.
               Isso produz um cone que se expande para baixo; linhas inferiores capam
               no tamanho máximo. */
            int width = 1 + 2 * i;
            if (width > size) width = size;
            int halfWidth = width / 2;
            int left = center - halfWidth;
            int right = center + halfWidth;
            if (j >= left && j <= right)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

/* Cria a matriz da CRUZ (cruz + central). size deve ser ímpar (ex:5). */
void build_cross(int size, int cross[size][size]) {
    int center = size / 2;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            /* Posição é afetada se estiver na linha central ou na coluna central */
            if (i == center || j == center)
                cross[i][j] = 1;
            else
                cross[i][j] = 0;
        }
    }
}

/* Cria a matriz do OCTAEDRO vista frontal (losango/diamond).
   Usa a condição |i-c| + |j-c| <= radius para formar o losango. */
void build_octa(int size, int octa[size][size]) {
    int center = size / 2;
    int radius = center; /* para cobrir do centro até as pontas */
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int dist = abs(i - center) + abs(j - center);
            if (dist <= radius)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }
}

/* Sobrepõe uma matriz de habilidade (values 0/1) no tabuleiro, centrando-a
   no ponto origin_row, origin_col. A sobreposição preenche o array affected[][] */
void apply_skill(int board[ROWS][COLS], int affected[ROWS][COLS],
                 int skill_rows, int skill_cols, int skill[skill_rows][skill_cols],
                 int origin_row, int origin_col) {

    int skill_center_row = skill_rows / 2;
    int skill_center_col = skill_cols / 2;

    for (int i = 0; i < skill_rows; ++i) {
        for (int j = 0; j < skill_cols; ++j) {
            if (skill[i][j] == 1) {
                int br = origin_row + (i - skill_center_row);
                int bc = origin_col + (j - skill_center_col);
                /* Verifica limites do tabuleiro antes de aplicar */
                if (br >= 0 && br < ROWS && bc >= 0 && bc < COLS) {
                    /* Marca como afetado (1). Não sobrescrevemos o valor do tabuleiro
                       aqui — apenas registramos na matriz affected. */
                    affected[br][bc] = 1;
                }
            }
        }
    }
}

int main() {
    int board[ROWS][COLS];
    int affected[ROWS][COLS];

    /* Inicialização */
    init_board(board);
    memset(affected, 0, sizeof(affected));

    /* Exemplo: posições fixas de alguns navios (valor 3).
       (Simplificação pedida: posicionadas diretamente no código.) */
    board[0][2] = SHIP;
    board[0][3] = SHIP;
    board[2][0] = SHIP;
    board[9][9] = SHIP;
    board[4][4] = SHIP;
    board[7][1] = SHIP;

    /* Definimos os tamanhos das matrizes de habilidade */
    const int coneSize = 7;   /* razoável para um cone que se expande */
    const int crossSize = 5;
    const int octaSize = 7;

    /* Criamos as matrizes (valores 0/1) */
    int cone[coneSize][coneSize];
    int cross[crossSize][crossSize];
    int octa[octaSize][octaSize];

    /* Construção dinâmica das formas usando condicionais e loops aninhados */
    build_cone(coneSize, cone);
    build_cross(crossSize, cross);
    build_octa(octaSize, octa);

    /* Posições de origem (linha, coluna) no tabuleiro para cada habilidade.
       Valores escolhidos para visibilidade e para não sobrepor navios neste exemplo. */
    int cone_origin_r = 1, cone_origin_c = 2;  /* cone perto do topo-esquerdo */
    int cross_origin_r = 6, cross_origin_c = 5;/* cruz em parte central-direita */
    int octa_origin_r = 4, octa_origin_c = 8; /* octaedro à direita */

    /* Aplicamos as habilidades sobre o tabuleiro (preenchendo 'affected') */
    apply_skill(board, affected, coneSize, coneSize, cone, cone_origin_r, cone_origin_c);
    apply_skill(board, affected, crossSize, crossSize, cross, cross_origin_r, cross_origin_c);
    apply_skill(board, affected, octaSize, octaSize, octa, octa_origin_r, octa_origin_c);

    /* Exibe tabuleiro: imprimimos 0 (agua), 3 (navio) e 5 (area afetada).
       Se uma posição for navio (3) e também afetada, por simplicidade neste
       exemplo imprimimos o navio (3) — as habilidades foram colocadas para
       não cobrir navios. */
    print_board(board, affected);

    /* Mostramos também as matrizes de habilidade (opcional, para conferência) */
    printf("Matriz - Cone (%dx%d):\n", coneSize, coneSize);
    for (int i = 0; i < coneSize; ++i) {
        for (int j = 0; j < coneSize; ++j) {
            printf("%d ", cone[i][j] ? 3 : 0); /* exemplo visual usando '3' para mostrar afinidade com exemplo */
        }
        printf("\n");
    }
    printf("\n");

    printf("Matriz - Cruz (%dx%d):\n", crossSize, crossSize);
    for (int i = 0; i < crossSize; ++i) {
        for (int j = 0; j < crossSize; ++j) {
            printf("%d ", cross[i][j] ? 3 : 0);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matriz - Octaedro (%dx%d):\n", octaSize, octaSize);
    for (int i = 0; i < octaSize; ++i) {
        for (int j = 0; j < octaSize; ++j) {
            printf("%d ", octa[i][j] ? 3 : 0);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}
