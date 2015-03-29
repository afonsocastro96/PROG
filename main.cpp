#include <iostream>
#include "tabuleiro.h"
#include "utils.h"
#include "ficheiros.h"

using namespace std;

int main(){
	/*  A fazer:
		Fazer as cenas opcionais */
	clrscr();

	string nomeFicheiroConf; /* Nome do ficheiro de configuracao */
	string nomeFicheiroTab; /* Nome do ficheiro que contem a informacao do tabuleiro */
	string modoFunc; /* Modo de funcionamento do programa (Manual / Automatico) */
	string formato; /* Formato dos ficheiros de texto especificados */
	string continuar = "N"; /* Variavel usada para confirmar se o utilizador pretende usar o nome dado ao ficheiro */
	bool validadorInputs = false; //Quando for a true, o input do utilizador a ser testado e valido

	setcolor(WHITE, BLACK);

	do{
		formato = "";
		cout << "Nome do ficheiro de configuracao? ";
		cin >> nomeFicheiroConf;

		/* Validar o nome do ficheiro de configuracao.*/
		for (uint8_t i = 0; i < nomeFicheiroConf.size(); i++){
			/*Encontrou um formato de ficheiro. Testa para ver se e txt */
			if (nomeFicheiroConf[i] == '.' && i != (nomeFicheiroConf.size() - 1)) {
				formato = nomeFicheiroConf.substr(i);
				/* Nao e? Perguntar ao utilizador se quer mesmo criar com esse formato de ficheiro */
				if (formato != ".txt"){
					do{
						cout << endl << "O formato \"" << formato << "\" nao e um formato de ficheiro de texto reconhecido." << endl << "Criar mesmo assim (S/N)? ";
						cin >> continuar;
						cout << endl;
						if (continuar != "S" && continuar != "s" && continuar != "N" && continuar != "n"){
							validadorInputs = false;
							cout << "Input invalido!" << endl;
						}
						else validadorInputs = true;
					} while (!validadorInputs);

					/* Nao quer, perguntar de novo o nome do ficheiro */
					if (continuar == "N" || continuar == "n")
					{
						cout << "Criacao do ficheiro de configuracao reiniciada." << endl << endl;
						validadorInputs = false;
						break;
					}
				}
				/* Tudo ok, o utilizador criou com o formato txt ou confirmou o formato de ficheiro */
				else {
					validadorInputs = true;
					break;
				}
			}
		}

		/* Se a variavel formato estiver vazia, o nome dado nao tem formato. Perguntar ao utilizador
		se quer criar ficheiro sem formato */

		if (formato.empty()){
			do{
				cout << endl << "O ficheiro nao tem formato definido. Criar mesmo assim (S/N)? ";
				cin >> continuar;
				cout << endl;
				if (continuar != "S" && continuar != "s" && continuar != "N" && continuar != "n"){
					validadorInputs = false;
					cout << endl << "Input invalido!" << endl;
				}
				else validadorInputs = true;
			} while (!validadorInputs);

			/* O utilizador nao quer criar, perguntar de novo o nome do ficheiro */
			if (continuar == "N" || continuar == "n")
			{
				cout << "Criacao do ficheiro de configuracao reiniciada." << endl << endl;
				validadorInputs = false;
			}
		}

	} while (!validadorInputs);

	/* Tudo ok, ficheiro pode ser criado! */
	cout << "Ficheiro de configuracao criado com sucesso!" << endl;

	do{
		formato = "";
		cout << endl << "Nome do ficheiro de tabuleiro? ";
		cin >> nomeFicheiroTab;

		/* Testar se o ficheiro ja existe */

		ofstream o_ficheiro(nomeFicheiroTab.c_str());

		if (o_ficheiro){
			do{
				cout << endl << "Ja existe um ficheiro com o nome " << nomeFicheiroTab << ". Continuar vai eliminar todo o";
				cout << endl << "conteudo atual do ficheiro. Tem a certeza que pretende criar o ficheiro (S/N)? ";
				cin >> continuar;

				if (continuar != "S" && continuar != "s" && continuar != "N" && continuar != "n"){
					validadorInputs = false;
					cout << endl << "Input invalido!" << endl;
				}
			} while (!validadorInputs);

			if (continuar == "S" || continuar == "s")
				break; /* Pressuponho que se o utilizador confirma a criacao do ficheiro, que o quer criar, mesmo que o formato nao seja txt */
			else {
				cout << endl << "Criacao do ficheiro de configuracao reiniciada." << endl;
				validadorInputs = false;
				continue;
			}
		}

		/* Validar o nome do ficheiro de tabuleiro.*/
		for (uint8_t i = 0; i < nomeFicheiroTab.size(); i++){
			/*Encontrou um formato de ficheiro. Testa para ver se e txt */
			if (nomeFicheiroTab[i] == '.' && i != (nomeFicheiroTab.size() - 1)) {
				formato = nomeFicheiroTab.substr(i + 1);
				/* Nao e? Perguntar ao utilizador se quer mesmo criar com esse formato de ficheiro */
				if (formato != "txt"){
					do{
						cout << endl << "O formato \"." << formato << "\" nao e um formato de ficheiro de texto reconhecido." << endl << "Criar mesmo assim (S/N)? ";
						cin >> continuar;
						cout << endl;
						if (continuar != "S" && continuar != "s" && continuar != "N" && continuar != "n"){
							validadorInputs = false;
							cout << "Input invalido!" << endl;
						}
						else validadorInputs = true;
					} while (!validadorInputs);

					/* Nao quer, perguntar de novo o nome do ficheiro */
					if (continuar == "N" || continuar == "n")
					{
						cout << "Criacao do ficheiro de configuracao reiniciada." << endl << endl;
						validadorInputs = false;
						break;
					}
				}
				/* Tudo ok, o utilizador criou com o formato txt ou confirmou o formato de ficheiro */
				else {
					validadorInputs = true;
					break;
				}
			}
		}

		/* Se a variavel formato estiver vazia, o nome dado nao tem formato. Perguntar ao utilizador
		se quer criar ficheiro sem formato */
		if (formato.empty()){
			do{
				cout << endl << "O ficheiro nao tem formato definido. Criar mesmo assim (S/N)? ";
				cin >> continuar;
				cout << endl;
				if (continuar != "S" && continuar != "s" && continuar != "N" && continuar != "n"){
					validadorInputs = false;
					cout << endl << "Input invalido!" << endl;
				}
				else validadorInputs = true;
			} while (!validadorInputs);

			/* O utilizador nao quer criar, perguntar de novo o nome do ficheiro */
			if (continuar == "N" || continuar == "n")
			{
				cout << "Criacao do ficheiro de configuracao reiniciada." << endl << endl;
				validadorInputs = false;
			}
		}

	} while (!validadorInputs);

	/* Tudo ok, ficheiro pode ser criado! */
	cout << "Ficheiro de tabuleiro criado com sucesso!" << endl;

	do{
		cout << endl << "Modo de funcionamento (M)anual ou (A)utomatico? ";
		cin >> modoFunc;
		if (modoFunc.size() == 1 && (modoFunc == "M" || modoFunc == "m" || modoFunc == "A" || modoFunc == "a"))
			validadorInputs = true;
		if (!validadorInputs) {
			cout << endl << "Modo de funcionamento invalido!" << endl;
		}
	} while (!validadorInputs);
	cout << endl;

	/* Leitura do ficheiro e inicializacao dos dados do tabuleiro contidos no ficheiro */
	Tabuleiro t = lerFicheiroConf(nomeFicheiroConf);

	/* Inicializacao dos restantes membros-dado do tabuleiro */
	setModoTabuleiro(t, modoFunc[0]);

	/* Inicio do ciclo de preenchimento do tabuleiro */
	uint8_t n = 0; /* Navio a ser atualmente tratado pelo programa */
	char linha; /* Coordenada y do navio */
	char coluna; /*Coordenada x do navio */
	char direccao; /* Direccao do navio (Horizontal/vertical) como especificada pelo utilizador */
	string posicaoDireccaoNavio; /* String que recebe o input do utilizador */
	modo orientacao; /* Orientacao do navio, da forma como e enviada para o construtor */
	uint8_t mesmoTipoRestantes = 0; /* Navios restantes do mesmo tipo, usado para output na consola */

	while (n < t.navios->size()){
		if (t.modoFuncionamento == MANUAL){
			imprimirTabuleiro(t);
			setcolor(t.navios->at(n).cor, BLACK);
			if (mesmoTipoRestantes == 0)
				mesmoTipoRestantes = calculaMesmoTipoRestante(*t.navios, n);

			/* Ciclo de colocacao dos tabuleiros no mapa */
			do{
				do{
					cout << t.navios->at(n).tipo << " - " << t.navios->at(n).nome << ". Tamanho = " << (int16_t)t.navios->at(n).tamanho << ". Falta(m) " << (int16_t)mesmoTipoRestantes << "." << endl; // Falta a parte do numero de navios que faltam
					setcolor(WHITE, BLACK);
					cout << endl << "LINHA (" << (char)65 << "..." << (char)(65 + t.tamanhoY - 1) << ") COLUNA (" << (char)97 << "..." << (char)(97 + t.tamanhoY - 1) << ") ORIENTACAO (H V)? ";
					cin >> posicaoDireccaoNavio;
					cout << endl;
					/* Pedir ao utilizador continuamente a informacao ate que a linha a coluna e a direccao
					sejam valores validos */
					if (posicaoDireccaoNavio.size() != 3){ /* Este check tem de ser feito separadamente para evitar acessos ilegais a memoria*/
						validadorInputs = false;
						cout << endl << "Input invalido, numero de caracteres tem de ser igual a 3!" << endl;
					}
					else {
						linha = posicaoDireccaoNavio[0];
						coluna = posicaoDireccaoNavio[1];
						direccao = posicaoDireccaoNavio[2];

						if ((linha < 65 || linha >(65 + t.tamanhoY))
							|| (coluna < 97 || coluna >(97 + t.tamanhoY))
							|| (direccao != 'H' && direccao != 'h' && direccao != 'V' && direccao != 'v'))
						{
							validadorInputs = false;
							cout << endl << "Input invalido, uma ou mais coordenadas nao existem, ou direccao invalida!" << endl;
						}
						else validadorInputs = true;
					}
				} while (!validadorInputs);

				/* Dados do utilizador respeitam as margens do tabuleiro e a direccao e valida*/
				if (direccao == 'H' || direccao == 'h')
					orientacao = HORIZONTAL;
				else orientacao = VERTICAL;
				/* Conversao ASCII - decimal*/
				linha -= 65;
				coluna -= 97;
				/* Testar se a colocacao dada e valida. Se nao for, perguntar de novo ao utilizador */
				if (!colocavel(t, linha * t.tamanhoX + coluna, orientacao, t.navios->at(n).tamanho)){
					validadorInputs = false;
					cout << "Coordenadas/direccao invalidas, o navio sai fora do tabuleiro!" << endl << endl;
				}
				else validadorInputs = true;
			} while (!validadorInputs);
		}
		else{ // Modo de funcionamento automatico
			srand((uint32_t)time(NULL));
			do{
				linha = rand() % t.tamanhoY;
				coluna = rand() % t.tamanhoX;
				orientacao = (modo)(rand() % 2); // Faz partido da equivalencia entre 0 e false e entre 1 e true, poupando 7 bits.
			} while (!colocavel(t, linha * t.tamanhoX + coluna, orientacao, t.navios->at(n).tamanho));
		}


		if (orientacao)
			direccao = 'H';
		else direccao = 'V';

		setPosicao(t.navios->at(n), linha, coluna, t.tamanhoX);
		setOr(t.navios->at(n), direccao);

		colocarNavioTabuleiro(t, t.navios->at(n));
		n++;
		mesmoTipoRestantes--;
	}

	imprimirTabuleiro(t);
	setcolor(WHITE, BLACK);
	cout << endl << "Tabuleiro criado com sucesso!" << endl;
	cout << endl << "Prima uma tecla para continuar...";

	criarFicheiroTabuleiro(nomeFicheiroTab, t); //Coloca a informacao do tabuleiro num ficheiro

	/* Pausar o programa ate que o utilizador prima uma tecla */
	cin.ignore((uint32_t)-1, '\n'); /*Mais uma vez, o -1 permite obter o maior valor positivo representavel com 32 bits */
	cin.get();
	cout << endl; //No caso de se correr o programa no terminal, impede que a proxima linha no terminal seja mostrada depois da frase "Prima uma tecla para continuar..."

	/*FIM*/
	return 0;
}