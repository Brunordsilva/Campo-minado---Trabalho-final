#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
	int bomba;
	int aberta;
	int vizinho;
} campo;

campo minado[8][8];
int l,c,tam = 8;
void iniciar() {
	for(l = 0; l < tam; l++) {
		for(l = 0; l < tam; l++) {
			minado[l][c].bomba = 0;
			minado[l][c].aberta = 0;
			minado[l][c].vizinho = 0;
		}
	}
}
void localBombas(int n){
    for(int i = 1;i <= n;i++){
       l = rand() % 8;
    }
}
int main()
{
  iniciar();

	return 0;
}
