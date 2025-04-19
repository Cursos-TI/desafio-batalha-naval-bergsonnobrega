#include <stdio.h>
#include <locale.h>
#include <windows.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 1

// Funcao para inicializar o tabuleiro com agua
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Funcao para validar as coordenadas do navio
int validarCoordenadas(int x, int y, int tamanho, int horizontal, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    if (horizontal) {
        if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y + tamanho > TAMANHO_TABULEIRO) {
            return 0;
        }
    } else {
        if (x < 0 || x + tamanho > TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO) {
            return 0;
        }
    }

    for (int i = 0; i < tamanho; i++) {
        if (horizontal) {
            if (tabuleiro[x][y + i] == NAVIO) {
                return 0;
            }
        } else {
            if (tabuleiro[x + i][y] == NAVIO) {
                return 0;
            }
        }
    }

    return 1;
}

// Funcao para posicionar um navio no tabuleiro
void posicionarNavio(int x, int y, int tamanho, int horizontal, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < tamanho; i++) {
        if (horizontal) {
            tabuleiro[x][y + i] = NAVIO;
        } else {
            tabuleiro[x + i][y] = NAVIO;
        }
    }
}

// Funcao para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro atual:\n");
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%c ", tabuleiro[i][j] == AGUA ? '~' : 'N');
        }
        printf("\n");
    }
}

int main() {
    // Configurando o console para UTF-8
    SetConsoleOutputCP(CP_UTF8);
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Definindo as coordenadas dos navios (tamanho 3)
    int navio1_x = 1, navio1_y = 2;  // Vertical
    int navio2_x = 3, navio2_y = 0;  // Horizontal

    // Posicionando os navios apos validacao
    if (validarCoordenadas(navio1_x, navio1_y, 3, 0, tabuleiro)) {
        posicionarNavio(navio1_x, navio1_y, 3, 0, tabuleiro);
        printf("Navio vertical posicionado nas coordenadas (%d,%d)\n", navio1_x, navio1_y);
    } else {
        printf("Erro: Nao foi possivel posicionar o navio vertical nas coordenadas (%d,%d)\n", navio1_x, navio1_y);
    }

    if (validarCoordenadas(navio2_x, navio2_y, 3, 1, tabuleiro)) {
        posicionarNavio(navio2_x, navio2_y, 3, 1, tabuleiro);
        printf("Navio horizontal posicionado nas coordenadas (%d,%d)\n", navio2_x, navio2_y);
    } else {
        printf("Erro: Nao foi possivel posicionar o navio horizontal nas coordenadas (%d,%d)\n", navio2_x, navio2_y);
    }

    // Exibindo o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0