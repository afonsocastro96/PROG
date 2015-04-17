#include <iostream>
#include "tabuleiro.h"
#include "utils.h"
#include "ficheiros.h"

using namespace std;

int main(){
	clrscr();

	string nomeFicheiroConf; /* Nome do ficheiro de configuracao */
	string nomeFicheiroTab; /* Nome do ficheiro que contem a informacao do tabuleiro */
	string modoFunc; /* Modo de funcionamento do programa (Manual / Automatico) */
	string formato = ""; /* Formato dos ficheiros de texto especificados */
	string continuar = ""; /* Variavel usada para confirmar se o utilizador pretende usar o nome dado ao ficheiro */
	bool validadorInputs = false; //Quando for a true, o input do utilizador a ser testado e valido

	setcolor(WHITE, BLACK);

	do{
		cout << "Nome do ficheiro de configuracao? ";
		cin >> nomeFicheiroConf;

		ifstream o_ficheiro(nomeFicheiroConf.c_str());

		if (o_ficheiro){
			validadorInputs = true;
			break;
		}

		else {
			cout << endl << "O ficheiro \"" << nomeFicheiroConf << "\" nao existe.";
			do{
				cout << endl << "Pretende escolher outro nome de ficheiro (se nao quiser o jogo vai criar um";
				cout << endl << "ficheiro com o nome " << nomeFicheiroConf << " com configuracoes pre-estabelecidas) (S / N)? ";
				cin >> continuar;
				if (continuar != "S" && continuar != "s" && continuar != "N" && continuar != "n"){
					validadorInputs = false;
					cout << endl << "Input invalido!" << endl;
				}
				else validadorInputs = true;
			} while (!validadorInputs);

			if (continuar == "S" || continuar == "s"){
				cout << endl << "Leitura do ficheiro de configuracao reiniciada." << endl << endl;
				validadorInputs = false;
				continue;
			}
			else{
				validadorInputs = true;
				continue;
			}
		}
	} while (!validadorInputs);

	/* Tudo ok, ficheiro pode ser criado! */
	cout << "Ficheiro de configuracao ";
	if (continuar == "N" || continuar == "n")
		cout << "criado e ";
	cout << "lido com sucesso!" << endl;

	do{
		formato = "";
		cout << endl << "Nome do ficheiro de tabuleiro? ";
		cin >> nomeFicheiroTab;

		/* Testar se o ficheiro ja existe */

		ifstream o_ficheiro(nomeFicheiroTab.c_str());

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
	string posicaoDireccaoNavio = ""; /* String que recebe o input do utilizador */
	modo orientacao; /* Orientacao do navio, da forma como e enviada para o construtor */
	uint8_t mesmoTipoRestantes = 0; /* Navios restantes do mesmo tipo, usado para output na consola */
	char linhaAntiga; /* No caso da modificacao de um navio, guarda a linha antiga */
	char colunaAntiga; /* No caso da modificacao de um navio, guarda a linha antiga */
	uint8_t navioAAlterar = -1; /* No caso da modificacao de um navio, guarda a posicao no vetor de navios a alterar */
	bool limparErros = false;

	while (n < t.navios->size()){
		clrscr();
		if (t.modoFuncionamento == MANUAL){
			if (mesmoTipoRestantes == 0)
				mesmoTipoRestantes = calculaMesmoTipoRestante(*t.navios, n);

			/* Ciclo de colocacao dos tabuleiros no mapa */
			do{
				do{
					imprimirTabuleiro(t);
					setcolor(t.navios->at(n).cor, BLACK);
					cout << t.navios->at(n).tipo << " - " << t.navios->at(n).nome << ". Tamanho = " << (int16_t)t.navios->at(n).tamanho << ". Falta(m) " << (int16_t)mesmoTipoRestantes << "." << endl; // Falta a parte do numero de navios que faltam
					setcolor(WHITE, BLACK);
					cout << endl << "Para novo navio: LINHA (" << (char)65 << "..." << (char)(65 + t.tamanhoY - 1) << ") COLUNA (" << (char)97 << "..." << (char)(97 + t.tamanhoY - 1) << ") ORIENTACAO (H V) " << endl;
					cout << endl << "Para alterar posicao de navio: NOVA_LINHA NOVA_COLUNA ORIENTACAO ANTIGA_LINHA ANTIGA_COLUNA" << endl;
					cout << "Accao:                                          ";
					gotoxy(7, 18);
					if (posicaoDireccaoNavio.size() != 0) //Ou seja, o utilizador ja se enganou uma vez no input
						limparErros = true;  //Impede que os erros se comecem a acumular no ecra
					cin >> posicaoDireccaoNavio;
					cout << endl;
					/* Pedir ao utilizador continuamente a informacao ate que a linha a coluna e a direccao
					sejam valores validos */
					if (!(posicaoDireccaoNavio.size() == 3 || posicaoDireccaoNavio.size() == 5)){ /* Este check tem de ser feito separadamente para evitar acessos ilegais a memoria*/
						validadorInputs = false;
						cout << endl << "ERRO: Input invalido, numero de caracteres tem de ser igual a 3 ou 5!" << endl;
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
							cout << endl << "ERRO: Input invalido, uma ou mais coordenadas nao existem, ou direccao invalida!" << endl;
						}
						else validadorInputs = true;
					}
					/* Se o tamanho da string for 6, quer dizer que e uma alteracao, verificar e preparar as variaveis para tal */
					if (posicaoDireccaoNavio.size() == 5) {
						linhaAntiga = posicaoDireccaoNavio[3] - 65;
						colunaAntiga = posicaoDireccaoNavio[4] - 97;

						if ((linhaAntiga < 0 || linhaAntiga > t.tamanhoY)
							|| (colunaAntiga < 0 || colunaAntiga > t.tamanhoY))
						{
							if (validadorInputs) // Impede que a mensagem abaixo seja mostrada duas vezes, por causa do check feito 10 linhas atras
								cout << endl << "ERRO: Input invalido, uma ou mais coordenadas nao existem, ou direccao invalida!" << endl;
							validadorInputs = false;
						}
						else {
							for (uint8_t i = 0; i < t.navios->size(); i++){
								if (linhaAntiga * t.tamanhoX + colunaAntiga == t.navios->at(i).posicao){
									navioAAlterar = i;
									apagarNavioTabuleiro(t, t.navios->at(i));
									break;
								}
							}
							if (navioAAlterar == -1) //Nao foi encontrado, ou seja, a posicao dada pelo utilizador e invalida
							{
								cout << "ERRO: Input invalido, a posicao dada nao contem um navio!" << endl;
								validadorInputs = false;
							}
							else validadorInputs = true;
						}
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
					cout << "ERRO: Coordenadas/direccao invalidas, o navio sai fora do tabuleiro!" << endl << endl;
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


		if (orientacao == HORIZONTAL)
			direccao = 'H';
		else direccao = 'V';

		/* Se o utilizador inseriu um navio novo, coloca-lo */
		if (posicaoDireccaoNavio.size() == 3 || t.modoFuncionamento == AUTOMATICO){
			setPosicao(t.navios->at(n), linha, coluna, t.tamanhoX);
			setOr(t.navios->at(n), direccao);
			colocarNavioTabuleiro(t, t.navios->at(n));
			n++;
			mesmoTipoRestantes--;
		}
		/*Se vai alterar um navio, altera-lo*/
		else{
			setPosicao(t.navios->at(navioAAlterar), linha, coluna, t.tamanhoX);
			setOr(t.navios->at(navioAAlterar), direccao);
			colocarNavioTabuleiro(t, t.navios->at(navioAAlterar));
		}
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