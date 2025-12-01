#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TAM 8
#define MAX_LINE 100

void gerarBombas(int bomba[TAM][TAM], int qtd) {
    int colocadas = 0;
    while (colocadas < qtd) {
        int r = rand() % TAM;
        int c = rand() % TAM;
        if (bomba[r][c] == 0) {
            bomba[r][c] = 1;
            colocadas++;
        }
    }
}

int contarVizinhas(int bomba[TAM][TAM], int r, int c) {
    int total = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            int rr = r + i;
            int cc = c + j;
            if (rr >= 0 && rr < TAM && cc >= 0 && cc < TAM)
                if (bomba[rr][cc]) total++;
        }
    return total;
}

void abrirVazios(int bomba[TAM][TAM], int aberto[TAM][TAM], int numero[TAM][TAM], int r, int c) {
    if (r < 0 || r >= TAM || c < 0 || c >= TAM) return;
    if (aberto[r][c]) return;
    aberto[r][c] = 1;
    if (numero[r][c] == 0)
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                abrirVazios(bomba, aberto, numero, r + i, c + j);
}

void mostrar(int bomba[TAM][TAM], int aberto[TAM][TAM], int numero[TAM][TAM], int bandeira[TAM][TAM], int revelar) {
    printf("   ");
    for (int i = 0; i < TAM; i++) printf("%2d ", i+1);
    printf("\n");
    for (int r = 0; r < TAM; r++) {
        printf("%2d ", r+1);
        for (int c = 0; c < TAM; c++) {
            if (revelar) {
                if (bomba[r][c]) printf(" * ");
                else if (numero[r][c] == 0) printf(" . ");
                else printf(" %d ", numero[r][c]);
            } else {
                if (bandeira[r][c]) printf(" F ");
                else if (aberto[r][c]) {
                    if (numero[r][c] == 0) printf(" . ");
                    else printf(" %d ", numero[r][c]);
                } else printf(" # ");
            }
        }
        printf("\n");
    }
}

int ganhou(int aberto[TAM][TAM], int bomba[TAM][TAM]) {
    for (int r = 0; r < TAM; r++)
        for (int c = 0; c < TAM; c++)
            if (!bomba[r][c] && !aberto[r][c])
                return 0;
    return 1;
}

void trim(char *s) {
    int i = 0, j = strlen(s) - 1;
    while (i <= j && isspace((unsigned char)s[i])) i++;
    while (j >= i && isspace((unsigned char)s[j])) j--;
    int k = 0;
    for (; i <= j; i++) s[k++] = s[i];
    s[k] = '\0';
}

int main() {
    int bomba[TAM][TAM] = {0};
    int aberto[TAM][TAM] = {0};
    int bandeira[TAM][TAM] = {0};
    int numero[TAM][TAM] = {0};
    char linha[MAX_LINE];
    srand(time(NULL));

    gerarBombas(bomba, 10);

    for (int r = 0; r < TAM; r++)
        for (int c = 0; c < TAM; c++)
            if (!bomba[r][c])
                numero[r][c] = contarVizinhas(bomba, r, c);

    while (1) {
        mostrar(bomba, aberto, numero, bandeira, 0);
        printf("\nDigite a jogada: ");

        if (!fgets(linha, sizeof(linha), stdin)) break;
        trim(linha);
        if (linha[0] == '\0') {
            printf("Entrada inválida.\n");
            continue;
        }

        int lr = -1, lc = -1;

        if (linha[0] == 'f' || linha[0] == 'F') {
            if (sscanf(linha + 1, "%d %d", &lr, &lc) != 2) {
                printf("Entrada inválida.\n");
                continue;
            }
            lr--; lc--;
            if (lr < 0 || lr >= TAM || lc < 0 || lc >= TAM) {
                printf("Posição inválida.\n");
                continue;
            }
            bandeira[lr][lc] = !bandeira[lr][lc];
            continue;
        } else {
            if (sscanf(linha, "%d %d", &lr, &lc) != 2) {
                printf("Entrada inválida.\n");
                continue;
            }
            lr--; lc--;
            if (lr < 0 || lr >= TAM || lc < 0 || lc >= TAM) {
                printf("Posição inválida.\n");
                continue;
            }
            if (bandeira[lr][lc]) {
                printf("Remova a bandeira.\n");
                continue;
            }
            if (bomba[lr][lc]) {
                printf("\nGame Over!\n");
                mostrar(bomba, aberto, numero, bandeira, 1);
                break;
            }
            abrirVazios(bomba, aberto, numero, lr, lc);
            if (ganhou(aberto, bomba)) {
                printf("\nVocê venceu!\n");
                mostrar(bomba, aberto, numero, bandeira, 1);
                break;
            }
        }
    }
    return 0;
}
