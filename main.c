#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Variavel global para o tamanho do tabuleiro
int tamanho_tabuleiro;

//Sctruct para armazenar os dados do jogador
typedef struct Jogador
{
    char nome[50];
    int vitorias;
    int derrotas;
    int empates;
} Jogador;

// Funcao para criar e inicializar o tabuleiro
char** criarTabuleiro() {

    char** tabuleiro = (char**)malloc(tamanho_tabuleiro * sizeof(char*));

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        tabuleiro[i] = (char*)malloc(tamanho_tabuleiro * sizeof(char));

        for (int j = 0; j < tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
    return tabuleiro;
}

// Funcao para liberar a memoria do tabuleiro
void liberarTabuleiro(char** tabuleiro) {

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        free(tabuleiro[i]);
    }

    free(tabuleiro);
}

// Funcao para imprimir o tabuleiro
void imprimirTabuleiro(char** tabuleiro) {

    printf("\n");

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        printf(" ");

        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%c", tabuleiro[i][j]);

            if (j < tamanho_tabuleiro - 1)
                printf(" | ");
        }

        printf("\n");

        if (i < tamanho_tabuleiro - 1) {
            for (int j = 0; j < tamanho_tabuleiro; j++) {
                printf("---");

                if (j < tamanho_tabuleiro - 1)
                    printf("|");
            }

            printf("\n");
        }
    }

    printf("\n");
}

// Funcao para verificar se houve vencedor
int verificarVencedor(char** tabuleiro, char jogador) {

    // Verificar linhas
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        int vitoriaLinha = 1;

        for (int j = 0; j < tamanho_tabuleiro; j++) {
            if (tabuleiro[i][j] != jogador) {
                vitoriaLinha = 0;

                break;
            }
        }

        if (vitoriaLinha) 
            return 1;
    }
    
    // Verificar colunas
    for (int j = 0; j < tamanho_tabuleiro; j++) {
        int vitoriaColuna = 1;

        for (int i = 0; i < tamanho_tabuleiro; i++) {
            if (tabuleiro[i][j] != jogador) {
                vitoriaColuna = 0;

                break;
            }
        }

        if (vitoriaColuna) 
            return 1;
    }
    
    // Verificar diagonal 1
    int vitoriaDiagonal1 = 1;
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        if (tabuleiro[i][i] != jogador) {
            vitoriaDiagonal1 = 0;

            break;
        }
    }

    if (vitoriaDiagonal1) 
        return 1;
    
    // Verificar diagonal 2
    int vitoriaDiagonal2 = 1;

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        if (tabuleiro[i][tamanho_tabuleiro - 1 - i] != jogador) {
            vitoriaDiagonal2 = 0;

            break;
        }
    }
    if (vitoriaDiagonal2) 
        return 1;
    
    return 0;
}

// Funcao para verificar empate
int verificarEmpate(char** tabuleiro) {

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

// Funcao para jogada do computador
void jogadaComputador(char** tabuleiro) {

    // Primeiro, verifica se pode vencer
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            if (tabuleiro[i][j] == ' ') {
                tabuleiro[i][j] = 'O';

                if (verificarVencedor(tabuleiro, 'O')) {
                    return;
                }
                tabuleiro[i][j] = ' ';
            }
        }
    }
    
    // Depois, verifica se precisa bloquear o jogador
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            if (tabuleiro[i][j] == ' ') {
                tabuleiro[i][j] = 'X';

                if (verificarVencedor(tabuleiro, 'X')) {
                    tabuleiro[i][j] = 'O';

                    return;
                }
                tabuleiro[i][j] = ' ';
            }
        }
    }
    
    // Se nao houver jogada estrategica, escolhe uma posicao aleatoria vazia
    int posicoes_vazias = 0;

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            if (tabuleiro[i][j] == ' ') 
                posicoes_vazias++;
        }
    }
    
    if (posicoes_vazias > 0) {

        int posicao_aleatoria = rand() % posicoes_vazias;
        int contador = 0;
        
        for (int i = 0; i < tamanho_tabuleiro; i++) {
            for (int j = 0; j < tamanho_tabuleiro; j++) {
                if (tabuleiro[i][j] == ' ') {
                    if (contador == posicao_aleatoria) {
                        tabuleiro[i][j] = 'O';

                        return;
                    }
                    contador++;
                }
            }
        }
    }
}

int menu(){
    int menuInt;

    printf("1 - Jogar\n");
    printf("2 - Creditos\n");
    printf("3 - Placar\n");
    printf("4 - Sair\n");
    printf("Escolha uma opção: ");

    scanf("%d", &menuInt);
    return menuInt;
}

void anotarPlacar(int resultado) {
    FILE *placar = fopen("placar.txt", "r");
    Jogador player[100];
    int numJogadores = 0;
    char nome[50];

    // Lê o nome do jogador
    printf("Digite seu nome: ");
    scanf("%49s", nome);

    // Se o arquivo existe, lê todos os jogadores
    if (placar != NULL) {
        while (fscanf(placar, "%49s %d %d %d", 
                     player[numJogadores].nome, 
                     &player[numJogadores].vitorias, 
                     &player[numJogadores].derrotas, 
                     &player[numJogadores].empates) == 4) {
            numJogadores++;
        }
        fclose(placar);
    }

    // Procura se o jogador já existe
    int jogadorIndex = -1;
    for (int i = 0; i < numJogadores; i++) {
        if (strcmp(player[i].nome, nome) == 0) {
            jogadorIndex = i;
            break;
        }
    }

    // Se jogador não existe, adiciona novo jogador
    if (jogadorIndex == -1) {
        jogadorIndex = numJogadores;
        strcpy(player[jogadorIndex].nome, nome);
        player[jogadorIndex].vitorias = 0;
        player[jogadorIndex].derrotas = 0;
        player[jogadorIndex].empates = 0;
        numJogadores++;
    }

    // Atualiza a pontuação do jogador
    switch (resultado) {
        case 1: // Vitória
            player[jogadorIndex].vitorias++;
            break;
        case 2: // Derrota
            player[jogadorIndex].derrotas++;
            break;
        case 3: // Empate
            player[jogadorIndex].empates++;
            break;
        default:
            printf("Resultado inválido!\n");
            return;
    }

    // Abre o arquivo para escrita
    placar = fopen("placar.txt", "w");
    if (placar == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        return;
    }

    // Salva todos os jogadores no arquivo
    for (int i = 0; i < numJogadores; i++) {
        fprintf(placar, "%s %d %d %d\n", 
                player[i].nome, 
                player[i].vitorias, 
                player[i].derrotas, 
                player[i].empates);
    }

    fclose(placar);
    printf("Placar atualizado com sucesso!\n");
}

void exibirPlacar(){
    FILE *placar = fopen("placar.txt", "r");
    Jogador player;

    if (placar == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    while (fscanf(placar, "%49s %d %d %d", player.nome, &player.vitorias, &player.derrotas, &player.empates) != EOF)
    {
        printf("Nome: %s\nVitorias: %d\nDerrotas: %d\nEmpates: %d\n", player.nome, player.vitorias, player.derrotas, player.empates);
    }
}

int main() {
    srand(time(NULL));

    while (1)
    {
        int menuInt = menu();
        if (menuInt == 1) {
            // Solicita o tamanho do tabuleiro
            do {
                printf("Escolha o tamanho do tabuleiro (3 ou 5): ");
                scanf("%d", &tamanho_tabuleiro);
            } while (tamanho_tabuleiro != 3 && tamanho_tabuleiro != 5);
            
            char** tabuleiro = criarTabuleiro();
            int linha, coluna;
            int jogadas = 0;
            
            printf("\n=== Jogo da Velha %dx%d ===\n", tamanho_tabuleiro, tamanho_tabuleiro);
            printf("Você: X\nComputador: O\n");
            
            while (1) {
                imprimirTabuleiro(tabuleiro);
                
                // Jogada do usuario
                printf("Sua vez!\n");
                do {
                    printf("Digite a linha (0-%d): ", tamanho_tabuleiro - 1);
                    scanf("%d", &linha);
                    printf("Digite a coluna (0-%d): ", tamanho_tabuleiro - 1);
                    scanf("%d", &coluna);
                    
                    if (linha < 0 || linha >= tamanho_tabuleiro || coluna < 0 || coluna >= tamanho_tabuleiro) {
                        printf("Posição inválida! Tente novamente.\n");
                        continue;
                    }
                    
                    if (tabuleiro[linha][coluna] != ' ') {
                        printf("Posição já ocupada! Tente novamente.\n");
                        continue;
                    }
                    
                    break;
                } while (1);
                
                tabuleiro[linha][coluna] = 'X';
                jogadas++;
                
                if (verificarVencedor(tabuleiro, 'X')) {
                    imprimirTabuleiro(tabuleiro);
                    anotarPlacar(1);
                    printf("Parabéns! Você venceu!\n");
                    break;
                }
                
                if (verificarEmpate(tabuleiro)) {
                    imprimirTabuleiro(tabuleiro);
                    anotarPlacar(3);
                    printf("Empate! O jogo acabou.\n");
                    break;
                }
                
                // Jogada do computador
                printf("\nVez do computador...\n");
                jogadaComputador(tabuleiro);
                jogadas++;
                
                if (verificarVencedor(tabuleiro, 'O')) {
                    imprimirTabuleiro(tabuleiro);
                    anotarPlacar(2);
                    printf("O computador venceu!\n");
                    break;
                }
                
                if (verificarEmpate(tabuleiro)) {
                    imprimirTabuleiro(tabuleiro);
                    anotarPlacar(3);
                    printf("Empate! O jogo acabou.\n");
                    break;
                }
            }
            
            liberarTabuleiro(tabuleiro);
        }
        else if (menuInt == 2)
        {
            printf("Desenvolvido por: Rony\n");
        }
        else if (menuInt == 3)
        {
            printf("Placar: \n");
            exibirPlacar();
        }
        else if (menuInt == 4)
        {
            return 0;
        }
    }
    
    return 0;
}