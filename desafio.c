#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

void imprimir_tabuleiro(int tabuleiro[10][10]) {
    printf("   ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
        printf("%2d", c);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf("0 ");
            else if (tabuleiro[i][j] == 3)
                printf("3 ");
            else if (tabuleiro[i][j] == 5)
                printf("5 ");
        }
        printf("\n");
    }
}

int pode_posicionar(int tabuleiro[10][10], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);

        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

void posicionar_navio(int tabuleiro[10][10], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);
        tabuleiro[l][c] = 3;
    }
}

int pode_posicionar_diagonal(int tabuleiro[10][10], int linha, int coluna, int tamanho, char diagonal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = (diagonal == 'P') ? coluna + i : coluna - i;

        if (l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

void posicionar_diagonal(int tabuleiro[10][10], int linha, int coluna, int tamanho, char diagonal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = (diagonal == 'P') ? coluna + i : coluna - i;
        tabuleiro[l][c] = 3;
    }
}

void criar_cone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

void criar_cruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

void criar_octaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i - 2) + (j - 2) <= 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

void aplicar_habilidade(int tabuleiro[10][10], int habilidade[5][5], int origem_linha, int origem_coluna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int l = origem_linha - 2 + i;
                int c = origem_coluna - 2 + j;
                if (l >= 0 && l < 10 && c >= 0 && c < 10 && tabuleiro[l][c] == 0)
                    tabuleiro[l][c] = 5;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    if (!pode_posicionar(tabuleiro, 4, 4, TAMANHO_NAVIO, 'H') ||
        !pode_posicionar(tabuleiro, 5, 7, TAMANHO_NAVIO, 'V') ||
        !pode_posicionar_diagonal(tabuleiro, 0, 0, TAMANHO_NAVIO, 'P') ||
        !pode_posicionar_diagonal(tabuleiro, 0, 9, TAMANHO_NAVIO, 'S')) {
        printf("Erro ao posicionar um dos navios.\n");
        return 1;
    }

    posicionar_navio(tabuleiro, 4, 4, TAMANHO_NAVIO, 'H');
    posicionar_navio(tabuleiro, 5, 7, TAMANHO_NAVIO, 'V');
    posicionar_diagonal(tabuleiro, 0, 0, TAMANHO_NAVIO, 'P');
    posicionar_diagonal(tabuleiro, 0, 9, TAMANHO_NAVIO, 'S');

    int cone[5][5], cruz[5][5], octaedro[5][5];
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);

    aplicar_habilidade(tabuleiro, cone, 2, 2);
    aplicar_habilidade(tabuleiro, cruz, 6, 6);
    aplicar_habilidade(tabuleiro, octaedro, 8, 3);

    imprimir_tabuleiro(tabuleiro);

    return 0;
}
