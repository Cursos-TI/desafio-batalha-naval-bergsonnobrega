#include <stdio.h>
#include <locale.h>
#include <windows.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3  // Alterado para 3 conforme requisito

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para validar as coordenadas do navio
int validarCoordenadas(int x, int y, int tamanho, int tipo, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int dx = 0, dy = 0;
    
    // Define a direção do navio
    switch(tipo) {
        case 0: // Horizontal
            dy = 1;
            break;
        case 1: // Vertical
            dx = 1;
            break;
        case 2: // Diagonal para baixo
            dx = 1;
            dy = 1;
            break;
        case 3: // Diagonal para cima
            dx = -1;
            dy = 1;
            break;
    }

    // Verifica limites do tabuleiro
    for (int i = 0; i < tamanho; i++) {
        int newX = x + (dx * i);
        int newY = y + (dy * i);
        
        if (newX < 0 || newX >= TAMANHO_TABULEIRO || newY < 0 || newY >= TAMANHO_TABULEIRO) {
            return 0;
        }
        
        // Verifica sobreposição
        if (tabuleiro[newX][newY] == NAVIO) {
            return 0;
        }
    }

    return 1;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int x, int y, int tamanho, int tipo, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int dx = 0, dy = 0;
    
    // Define a direção do navio
    switch(tipo) {
        case 0: // Horizontal
            dy = 1;
            break;
        case 1: // Vertical
            dx = 1;
            break;
        case 2: // Diagonal para baixo
            dx = 1;
            dy = 1;
            break;
        case 3: // Diagonal para cima
            dx = -1;
            dy = 1;
            break;
    }

    // Posiciona o navio
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[x + (dx * i)][y + (dy * i)] = NAVIO;
    }
}

// Função para exibir o tabuleiro
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
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Configurando o console para UTF-8
    SetConsoleOutputCP(CP_UTF8);
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Definindo as coordenadas dos navios
    struct {
        int x, y, tamanho, tipo;
        const char* direcao;
    } navios[] = {
        {1, 1, 3, 0, "horizontal"},    // Navio 1 - horizontal na parte superior
        {4, 7, 3, 1, "vertical"},      // Navio 2 - vertical na parte direita
        {2, 4, 3, 2, "diagonal"},      // Navio 3 - diagonal para baixo no centro
        {6, 2, 3, 3, "diagonal"}       // Navio 4 - diagonal para cima na parte inferior
    };

    // Posicionando os navios
    for (int i = 0; i < 4; i++) {
        if (validarCoordenadas(navios[i].x, navios[i].y, navios[i].tamanho, navios[i].tipo, tabuleiro)) {
            posicionarNavio(navios[i].x, navios[i].y, navios[i].tamanho, navios[i].tipo, tabuleiro);
            printf("Navio %s posicionado nas coordenadas (%d,%d)\n", 
                   navios[i].direcao, navios[i].x, navios[i].y);
        } else {
            printf("Erro: Nao foi possivel posicionar o navio %s nas coordenadas (%d,%d)\n", 
                   navios[i].direcao, navios[i].x, navios[i].y);
        }
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