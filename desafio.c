#include <stdio.h>
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int pode_posicionar(int tabuleiro[10][10], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);

        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != 0) {
            return 0; 
        }
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

        if (l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != 0) {
            return 0;
        }
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

void imprimir_tabuleiro(int tabuleiro[10][10]) {
    printf("   ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
        printf("%d ", c);
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    int linhaH = 4, colunaH = 4;
    if (pode_posicionar(tabuleiro, linhaH, colunaH, TAMANHO_NAVIO, 'H')) {
        posicionar_navio(tabuleiro, linhaH, colunaH, TAMANHO_NAVIO, 'H');
    } else {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    int linhaV = 5, colunaV = 7;
    if (pode_posicionar(tabuleiro, linhaV, colunaV, TAMANHO_NAVIO, 'V')) {
        posicionar_navio(tabuleiro, linhaV, colunaV, TAMANHO_NAVIO, 'V');
    } else {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    int linhaDP = 0, colunaDP = 0;
    if (pode_posicionar_diagonal(tabuleiro, linhaDP, colunaDP, TAMANHO_NAVIO, 'P')) {
        posicionar_diagonal(tabuleiro, linhaDP, colunaDP, TAMANHO_NAVIO, 'P');
    } else {
        printf("Erro ao posicionar navio na diagonal principal.\n");
        return 1;
    }

    int linhaDS = 0, colunaDS = 9;
    if (pode_posicionar_diagonal(tabuleiro, linhaDS, colunaDS, TAMANHO_NAVIO, 'S')) {
        posicionar_diagonal(tabuleiro, linhaDS, colunaDS, TAMANHO_NAVIO, 'S');
    } else {
        printf("Erro ao posicionar navio na diagonal secundária.\n");
        return 1;
    }

    imprimir_tabuleiro(tabuleiro);

    return 0;
}
