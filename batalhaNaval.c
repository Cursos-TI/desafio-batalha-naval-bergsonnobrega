#include <stdio.h>
#include <locale.h>
#include <windows.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5

// Estrutura para representar uma habilidade
typedef struct {
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    const char* nome;
} Habilidade;

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para criar a habilidade Cone
Habilidade criarHabilidadeCone() {
    Habilidade cone = {{{0}}, "Cone"};
    
    // Criação dinâmica do padrão do cone
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // O cone começa com 1 no topo e expande para baixo
            if (i == 0 && j == TAMANHO_HABILIDADE/2) {
                cone.matriz[i][j] = 1;
            } else if (i > 0) {
                // Expande lateralmente conforme desce
                int largura = i * 2 + 1;
                int inicio = (TAMANHO_HABILIDADE - largura) / 2;
                if (j >= inicio && j < inicio + largura && j < TAMANHO_HABILIDADE) {
                    cone.matriz[i][j] = 1;
                }
            }
        }
    }
    return cone;
}

// Função para criar a habilidade Cruz
Habilidade criarHabilidadeCruz() {
    Habilidade cruz = {{{0}}, "Cruz"};
    
    // Criação dinâmica do padrão da cruz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Linha horizontal do meio
            if (i == TAMANHO_HABILIDADE/2) {
                cruz.matriz[i][j] = 1;
            }
            // Linha vertical do meio
            if (j == TAMANHO_HABILIDADE/2) {
                cruz.matriz[i][j] = 1;
            }
        }
    }
    return cruz;
}

// Função para criar a habilidade Octaedro
Habilidade criarHabilidadeOctaedro() {
    Habilidade octaedro = {{{0}}, "Octaedro"};
    
    // Criação dinâmica do padrão do octaedro
    int centro = TAMANHO_HABILIDADE/2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a distância Manhattan do centro
            int distancia = abs(i - centro) + abs(j - centro);
            if (distancia <= 2) {
                octaedro.matriz[i][j] = 1;
            }
        }
    }
    return octaedro;
}

// Função para aplicar uma habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      Habilidade habilidade, int linha, int coluna) {
    // Calcula o ponto inicial para centralizar a habilidade
    int inicioLinha = linha - TAMANHO_HABILIDADE/2;
    int inicioColuna = coluna - TAMANHO_HABILIDADE/2;
    
    // Aplica a matriz da habilidade no tabuleiro
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTab = inicioLinha + i;
            int colunaTab = inicioColuna + j;
            
            // Verifica se a posição está dentro dos limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO && 
                colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {
                if (habilidade.matriz[i][j] == 1) {
                    // Marca a área afetada apenas se não houver navio
                    if (tabuleiro[linhaTab][colunaTab] != NAVIO) {
                        tabuleiro[linhaTab][colunaTab] = AREA_AFETADA;
                    }
                }
            }
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
            // Diferentes símbolos para cada tipo de célula
            char simbolo;
            switch(tabuleiro[i][j]) {
                case NAVIO:
                    simbolo = 'N';
                    break;
                case AREA_AFETADA:
                    simbolo = '*';
                    break;
                default:
                    simbolo = '~';
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

// Função para exibir uma habilidade
void exibirHabilidade(Habilidade habilidade) {
    printf("\nHabilidade %s:\n", habilidade.nome);
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade.matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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

    // Criando as habilidades
    Habilidade cone = criarHabilidadeCone();
    Habilidade cruz = criarHabilidadeCruz();
    Habilidade octaedro = criarHabilidadeOctaedro();

    // Exibindo as matrizes das habilidades
    printf("\n=== Padroes das Habilidades ===\n");
    exibirHabilidade(cone);
    exibirHabilidade(cruz);
    exibirHabilidade(octaedro);

    // Exibindo o tabuleiro inicial
    printf("\n=== Tabuleiro Inicial ===\n");
    exibirTabuleiro(tabuleiro);

    // Aplicando cada habilidade em diferentes posições
    printf("\n=== Aplicando Habilidades ===\n");
    
    // Testando Cone
    printf("\nAplicando Cone na posicao (2,2):\n");
    aplicarHabilidade(tabuleiro, cone, 2, 2);
    exibirTabuleiro(tabuleiro);
    inicializarTabuleiro(tabuleiro); // Resetando para próximo teste
    
    // Posicionando navios novamente após reset
    for (int i = 0; i < 4; i++) {
        if (validarCoordenadas(navios[i].x, navios[i].y, navios[i].tamanho, navios[i].tipo, tabuleiro)) {
            posicionarNavio(navios[i].x, navios[i].y, navios[i].tamanho, navios[i].tipo, tabuleiro);
        }
    }

    // Testando Cruz
    printf("\nAplicando Cruz na posicao (5,5):\n");
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    exibirTabuleiro(tabuleiro);
    inicializarTabuleiro(tabuleiro); // Resetando para próximo teste
    
    // Posicionando navios novamente após reset
    for (int i = 0; i < 4; i++) {
        if (validarCoordenadas(navios[i].x, navios[i].y, navios[i].tamanho, navios[i].tipo, tabuleiro)) {
            posicionarNavio(navios[i].x, navios[i].y, navios[i].tamanho, navios[i].tipo, tabuleiro);
        }
    }

    // Testando Octaedro
    printf("\nAplicando Octaedro na posicao (4,4):\n");
    aplicarHabilidade(tabuleiro, octaedro, 4, 4);
    exibirTabuleiro(tabuleiro);

    return 0;
}