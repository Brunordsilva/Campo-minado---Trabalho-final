#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 8

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
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int rr = r + i;
			int cc = c + j;
			if (rr >= 0 && rr < TAM && cc >= 0 && cc < TAM) {
				if (bomba[rr][cc] == 1)
					total++;
			}
		}
	}
	return total;
}

void abrirVazios(int bomba[TAM][TAM], int aberto[TAM][TAM], int numero[TAM][TAM], int r, int c) {
	if (r < 0 || r >= TAM || c < 0 || c >= TAM) return;
	if (aberto[r][c]) return;

	aberto[r][c] = 1;

	if (numero[r][c] == 0) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				abrirVazios(bomba, aberto, numero, r + i, c + j);
			}
		}
	}
}

void mostrar(int bomba[TAM][TAM], int aberto[TAM][TAM], int numero[TAM][TAM], int revelarTudo) {
	printf("   ");
	for (int i = 0; i < TAM; i++) printf("%2d ", i+1);
	printf("\n");

	for (int r = 0; r < TAM; r++) {
		printf("%2d ", r+1);
		for (int c = 0; c < TAM; c++) {
			if (revelarTudo) {
				if (bomba[r][c]) printf(" * ");
				else if (numero[r][c] == 0) printf(" . ");
				else printf(" %d ", numero[r][c]);
			} else {
				if (aberto[r][c]) {
					if (numero[r][c] == 0) printf(" . ");
					else printf(" %d ", numero[r][c]);
				} else {
					printf(" # ");
				}
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

int main() {
	int bomba[TAM][TAM] = {0};
	int aberto[TAM][TAM] = {0};
	int numero[TAM][TAM] = {0};

	srand(time(NULL));

	gerarBombas(bomba, 10);

	for (int r = 0; r < TAM; r++)
		for (int c = 0; c < TAM; c++)
			if (!bomba[r][c])
				numero[r][c] = contarVizinhas(bomba, r, c);

	while (1) {
		mostrar(bomba, aberto, numero, 0);

		int lr, lc;
		printf("Digite linha e coluna: ");
		scanf("%d %d", &lr, &lc);
		lr--;
		lc--;

		if (lr < 0 || lr >= TAM || lc < 0 || lc >= TAM) {
			printf("PosiC'C#o invC!lida!\n");
			continue;
		}

		if (bomba[lr][lc]) {
			printf("\nGame Over!\n");
			mostrar(bomba, aberto, numero, 1);
			break;
		}

		abrirVazios(bomba, aberto, numero, lr, lc);

		if (ganhou(aberto, bomba)) {
			printf("\nVocC* venceu!!\n");
			mostrar(bomba, aberto, numero, 1);
			break;
		}
	}

	return 0;
}
