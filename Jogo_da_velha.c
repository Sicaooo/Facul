#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct coord {
    int l;
    int c;
};

struct jogadores {
    char X[20];
    char O[20];
};

struct placar {
    int X;
    int O;
};

void zerar_matriz(char matriz[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz[i][j] = ' ';
        }
    }
}

void printjogo(char matriz[3][3]) {
    printf("\n");
    printf(" %c | %c | %c\n", matriz[0][0], matriz[0][1], matriz[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", matriz[1][0], matriz[1][1], matriz[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", matriz[2][0], matriz[2][1], matriz[2][2]);;
}

int verificacao_partida(char matriz[3][3], int num_jogada, int x, int y) {
    if (matriz[x][0] == matriz[x][1] && matriz[x][0] == matriz[x][2]) return 1;
    else if (matriz[0][y] == matriz[1][y] && matriz[0][y] == matriz[2][y]) return 1;
    else if (x + y == 2 * x && matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2]) return 1;
    else if (x + y == 2 && matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0]) return 1;

    if (num_jogada == 9) return 2;

    return 0;
}

void entrada_nomes(char nomeX[20], char nomeO[20]) {
    printf("Insira o nome do jogador X: ");
    scanf("%s", nomeX);
    printf("Insira o nome do jogador O: ");
    scanf("%s", nomeO);
}

int main() {
    struct coord pos;
    struct jogadores player = { "\0", "Computador" };
    struct placar ponto = { 0, 0 };

    char jogada;
    int continuar;
    int confirmacao_jogadores;
    int qnt_jogadores;

    printf("Insira a quantidade de jogadores: ");
    scanf("%d", &qnt_jogadores);
    while (qnt_jogadores < 1 || qnt_jogadores > 2) {
        printf("Quantidade invalida, insira novamente: ");
        scanf("%d", &qnt_jogadores);
    }

    if (qnt_jogadores == 2) {
        entrada_nomes(player.X, player.O);
    }
    else {
        printf("Insira o nome do Jogador X: ");
        scanf("%s", player.X);
    }
    
    do {
        char jogo[3][3];
        zerar_matriz(jogo);

        int vez = 0;

        do {
            printf("\n");
            jogada = vez % 2 == 0 ? 'X' : 'O';
            vez++;

            if (qnt_jogadores == 2) {
                printf(jogada == 'X' ? "Jogador X\n" : "Jogador O\n");
                printf("Insira a jogada: ");
            }
            else if (jogada == 'X') printf("Jogador X\nInsira a jogada: ");

            if (jogada == 'X' || qnt_jogadores == 2) {
                scanf("%d %d", &pos.l, &pos.c);
                while (pos.l < 0 || pos.l > 2 || pos.c < 0 || pos.c > 2 || jogo[pos.l][pos.c] != ' ') {
                    printf("Posicao invalida, insira novamente: ");
                    scanf("%d %d", &pos.l, &pos.c);
                }
            }
            else {
                printf("Computador\n");
                do {
                    srand(time(NULL));
                    pos.l = rand() % 3;
                    srand(time(NULL));
                    pos.c = rand() % 3;
                } while (jogo[pos.l][pos.c] != ' ');
            }

            jogo[pos.l][pos.c] = jogada;

            printjogo(jogo);
        } while (verificacao_partida(jogo, vez, pos.l, pos.c) == 0);

        if (verificacao_partida(jogo, vez, pos.l, pos.c) == 2) printf("Empate\n");
        else {
            printf("Jogador %c ganhou\n", jogada);
            jogada == 'X' ? ponto.X++ : ponto.O++;
        }

        printf("\ninsira 1 para sim e 2 para nao\n");
        printf("Deseja continuar jogando?");
        scanf("%d", &continuar);
        while (continuar < 1 || continuar > 2) {
            printf("Opcao invalida, insira novamente: ");
            scanf("%d", &continuar);
        }

        if (continuar == 1) {
            printf("Sao os mesmos jogadores?\n");
            scanf("%d", &confirmacao_jogadores);
            while (confirmacao_jogadores < 1 || confirmacao_jogadores > 2) {
                printf("Opcao invalida, insira novamente: ");
                scanf("%d", &confirmacao_jogadores);
            }

            if (confirmacao_jogadores == 1) continue;

            printf("%s %d x %d %s\n", player.X, ponto.X, ponto.O, player.O);
            ponto.X = 0;
            ponto.O = 0;
            entrada_nomes(player.X, player.O);
        }
    } while (continuar == 1);

    printf("%s %d x %d %s\n", player.X, ponto.X, ponto.O, player.O);

    return 0;
}
