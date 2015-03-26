#include <iostream>
#include "tabuleiro.h"
#include "characters.h"
#include "ficheiros.h"

using namespace std;

int main(){
	/*  E preciso compensar todas as situacoes de erro possiveis
		Falta tambem por cores na CLI. */
	clrscr();
	
	string nomeFicheiroConf;
	string nomeFicheiroTab;
	char modoFunc;

	cout << "Nome do ficheiro de configuracao? ";
	cin >> nomeFicheiroConf;

	cout << endl << "Nome do ficheiro de tabuleiro?";
	cin >> nomeFicheiroTab;

	cout << endl << "Modo de funcionamento (M)anual ou (A)utomatico? ";
	cin >> modoFunc;
	cout << endl;
	
	/* Leitura do ficheiro e inicializacao dos dados do tabuleiro contidos no ficheiro */
	Tabuleiro* t = lerFicheiroConf(nomeFicheiroConf);

	/* Inicializacao dos restantes membros-dado do tabuleiro */
	setModoTabuleiro(t, modoFunc);
	setFicheiroTabuleiro(t, nomeFicheiroTab);

	/* Inicio do ciclo de preenchimento do tabuleiro */
	uint8_t n = 0;
	uint8_t faltam = 0;
	char linha;
	char coluna;
	char direccao;

	while (n != t->navios.size()){
		imprimirTabuleiro(t);
		
		cout << t->navios[n]->tipo << " - " << t->navios[n]->nome << ". Tamanho = " << t->navios[n]->tamanho << "." << endl; // Falta a parte do numero de navios que faltam
		cout << "LINHA (" << (char)65 << "..." << (char)65 + t->tamanhoY << ") COLUNA (" << (char)97 << "..." << (char)97 + t->tamanhoY << ") ORIENTACAO (H V)? ";
		cin >> linha >> coluna >> direccao;
		cout << endl;

		setPosicao(t->navios[n], linha, coluna,t->tamanhoX);
		setOr(t->navios[n], direccao);

		colocarNavioTabuleiro(t, t->navios[n]);
	}

	imprimirTabuleiro(t);

	/*FIM*/

	criarFicheiroTabuleiro(nomeFicheiroTab, t);
	return 0;
}

//==========================================================================================
// Fill the screen with colored numbers
	/*srand((unsigned int)time(NULL));
	for (int x = 0; x < 80; x++)
		for (int y = 0; y < 24; y++)
		{
			gotoxy(x, y);
			if (rand() % 2 == 0)
				setcolor(x % 15 + 1);
			else
				setcolor(y % 15 + 1, rand() % 2);
			cout << x % 10;
		}*/
