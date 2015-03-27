#include <iostream>
#include "tabuleiro.h"
#include "utils.h"
#include "ficheiros.h"

using namespace std;

int main(){
	/*  A fazer:
		E preciso compensar todas as situacoes de erro possiveis nos inputs do utilizador
		Falta tambem por cores na CLI.
		Corrigir o bug horrivel de se o ficheiro de configuracao ja existir, e mal lido.
		(opcional) Meter o ficheiro de configuracao com o formato que o prof quer 
		(opcional) Fazer as cenas opcionais */
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
	Tabuleiro t = lerFicheiroConf(nomeFicheiroConf);

	/* Inicializacao dos restantes membros-dado do tabuleiro */
	setModoTabuleiro(t, modoFunc);
	setFicheiroTabuleiro(t, nomeFicheiroTab);

	/* Inicio do ciclo de preenchimento do tabuleiro */
	uint8_t n = 0;
	uint8_t faltam = 0;
	char linha;
	char coluna;
	char direccao;
	modo temp;

	while (n < t.navios->size()){
		if (t.modoFuncionamento == MANUAL){
			imprimirTabuleiro(t);
			do{
				do{
					cout << t.navios->at(n).tipo << " - " << t.navios->at(n).nome << ". Tamanho = " << (int)t.navios->at(n).tamanho << "." << endl; // Falta a parte do numero de navios que faltam
					cout << "LINHA (" << (char)65 << "..." << (char)(65 + t.tamanhoY-1) << ") COLUNA (" << (char)97 << "..." << (char)(97 + t.tamanhoY-1) << ") ORIENTACAO (H V)? ";
					cin >> linha >> coluna >> direccao;
					cout << endl;
					/* Pedir ao utilizador continuamente a informacao ate que a linha a coluna e a direccao
					sejam valores validos */
				} while ((linha < 65 || linha >(65 + t.tamanhoY))
					|| (coluna < 97 || coluna >(97 + t.tamanhoY))
					|| (direccao != 'H' && direccao != 'h' && direccao != 'V' && direccao != 'v'));
				if (direccao == 'H' || direccao == 'h')
					temp = HORIZONTAL;
				else temp = VERTICAL;
				/* Conversao ASCII - decimal*/
				linha -= 65;
				coluna -= 97;
			} while (!colocavel(t, linha * t.tamanhoX + coluna, temp, t.navios->at(n).tamanho));
		}
		else{ // Modo de funcionamento automatico
			srand(time(NULL));
			do{
				linha = rand() % t.tamanhoY;
				coluna = rand() % t.tamanhoX;
				temp = (rand() % 2); // Faz partido da equivalencia entre 0 e false e entre 1 e true, poupando 7 bits.
			} while (!colocavel(t, linha * t.tamanhoX + coluna, temp, t.navios->at(n).tamanho));
		}


		if ((bool)temp)
			direccao = 'H';
		else direccao = 'V';

		setPosicao(t.navios->at(n), linha, coluna,t.tamanhoX);
		setOr(t.navios->at(n), direccao);

		colocarNavioTabuleiro(t, t.navios->at(n));
		n++;
	}

	imprimirTabuleiro(t);
	cout << endl << "Tabuleiro criado com sucesso!" << endl;
	cout << endl << "Prima uma tecla para continuar...";

	criarFicheiroTabuleiro(nomeFicheiroTab, t); //Coloca a informacao do tabuleiro num ficheiro

	/* Pausar o programa ate que o utilizador prima uma tecla */
	cin.ignore((uint32_t)-1,'\n');
	cin.get();
	cout << endl; //No caso de se correr o programa no terminal, impede que a proxima linha no terminal seja mostrada depois da frase "Prima uma tecla para continuar..."

	/*FIM*/
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
