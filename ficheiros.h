#pragma once

/* Funcoes relacionadas com leitura e escrita em ficheiros */

#include <fstream>
#include <sstream>
#include "symbolics.h"
#include "navio.h"
#include "tabuleiro.h"

using namespace std;

/* Cria um ficheiro com o nome fornecido pelo utilizador com a informacao default (a dada no enunciado do projeto)
caso o nome de ficheiro dado pelo utilizador nao exista. */
void criarFicheiroConf(string &fileName){
	ifstream o(fileName);

	if (!o){
		ofstream i;
		i.open(fileName.c_str());

		i << "tabuleiro: 10 x 10" << endl;
		i << "1 - Porta-avioes - 5 - P - Vermelho_claro" << endl;
		i << "1 - Fragata      - 4 - F - Magenta_claro" << endl;
		i << "2 - Cruzador     - 3 - C - Verde_claro" << endl;
		i << "3 - Submarino    - 2 - S - Castanho" << endl;
		i << "4 - Lancha       - 1 - L - Azul_claro";
	}

}

/* Depois de gerado o tabuleiro, cria um ficheiro com a informacao do tabuleiro para um nome de ficheiro fornecido
pelo utilizador. */
void criarFicheiroTabuleiro(string &fileName, Tabuleiro &t){
	stringstream ss;
	ss << itos(t.tamanhoX) << " x " << itos(t.tamanhoY);

	ofstream o_ficheiro;
	o_ficheiro.open(fileName.c_str());
	o_ficheiro << ss.str();
	for (uint8_t i = 0; i < t.navios->size(); i++){
		o_ficheiro << "\n";
		o_ficheiro << t.navios->at(i).tipo << " " << itos(t.navios->at(i).tamanho) << " " << posToCharacter(t, i, t.navios->at(i).posicao) << " ";
		if (t.navios->at(i).or == HORIZONTAL)
			o_ficheiro << "H";
		else o_ficheiro << "V";
	}

}

/* Le o ficheiro de configuracao fornecido pelo utilizador.
   Se o ficheiro nao existir, chama a funcao criaFicheiroConf() */
Tabuleiro lerFicheiroConf(string &fileName){
	Tabuleiro t;

	uint8_t tamanhoX; /*Tamanho X do tabuleiro*/
	uint8_t tamanhoY; /*Tamanho Y do tabuleiro*/
	string tamanhoXstr;/*Substring usada para obter do ficheiro o valor de tamanhoX */
	string tamanhoYstr; /*Substring usada para obter do ficheiro o valor de tamanhoY */

	uint8_t numero; /*Numero de navios de um tipo*/
	string numerostr; /*String com o numero de navios, para obter do ficheiro*/
	uint8_t tamanho; /* Tamanho do navio */
	string tamanhostr; /* String com o tamanho do navio */
	string nome; /*Nome do navio*/
	string simbolostr; /*Variavel temporaria para o simbolo do navio*/
	char simbolo; /*Simbolo do navio*/
	string cor; /*Cor do navio na consola*/

	string temp; /*Linha de um ficheiro*/

	ifstream o;

	o.open(fileName.c_str());

	if (!o){
		criarFicheiroConf(fileName);
		o.open(fileName.c_str());
	}


	getline(o, temp);

	int carater = 0;

	/* Tamanho X e Y*/
	while (!isANumber(temp[carater]))
		carater++;
	while (isANumber(temp[carater]))
	{
		tamanhoXstr.push_back(temp[carater]);
		carater++;
	}
	while (!isANumber(temp[carater]))
		carater++;
	while (isANumber(temp[carater])){
		tamanhoYstr.push_back(temp[carater]);
		carater++;
	}

	while (carater < temp.size()){
		if (isANumber(temp[carater])){
			cout << "Erro na leitura do ficheiro de configuracao, o tabuleiro tem de ser bidimensional." << endl;
			return novoTabuleiro(0, 0);
		}
		carater++;
	}

	tamanhoX = atoi(tamanhoXstr.c_str());
	tamanhoY = atoi(tamanhoYstr.c_str());

	/* Verificar se o tamanho nao excede o limite maximo de 26x26*/
	if (tamanhoX > 26 || tamanhoY > 26){
		cout << "Erro: O tabuleiro nao pode ter nenhum dos lados maior que 26" << endl;
		return novoTabuleiro(0, 0);
	}
	else if (tamanhoX == 0 || tamanhoY == 0){ //A leitura a partir do ficheiro ja impede tamanhos negativos, so e preciso compensar para este caso.
		cout << "Erro: O tabuleiro nao pode ter nenhum dos lados menor que 1" << endl;
		return novoTabuleiro(0, 0);
	}

	t = novoTabuleiro(tamanhoX, tamanhoY);

	/* Navios */
	while (!o.eof()){
		carater = 0;
		getline(o, temp);

		/* Quantidade do tipo de navio*/
		while (temp[carater] != '-'){
			numerostr.push_back(temp[carater]);
			carater++;
		}

		for (uint8_t i = 0; i < numerostr.size(); i++){
			if (!isANumber(numerostr[i])){
				numerostr.erase(numerostr.begin() + i);
				i--;
			}
		}

		/* Nome */
		carater++;

		while (temp[carater] == ' ' || temp[carater] == '-')
			carater++;

		while (temp[carater] != ' '){
			nome.push_back(temp[carater]);
			carater++;
		}

		for (uint8_t i = 0; i < nome.size(); i++){
			if (nome[i] == ' '){
				nome.erase(nome.begin() + i);
				i--;
			}
		}

		do{} while (temp[carater++] != '-');

		/* Tamanho */

		while (temp[carater] != '-'){
			tamanhostr.push_back(temp[carater]);
			carater++;
		}

		for (uint8_t i = 0; i < tamanhostr.size(); i++){
			if (!isANumber(tamanhostr[i])){
				tamanhostr.erase(tamanhostr.begin() + i);
				i--;
			}
		}

		/* Simbolo */

		carater++;

		while (temp[carater] != '-'){
			simbolostr.push_back(temp[carater]);
			carater++;
		}

		for (uint8_t i = 0; i < simbolostr.size(); i++){
			if (isupper(simbolostr[i])){
				simbolo = simbolostr[i];
				break;
			}
		}

		/* Verificar se simbolo ja existe */

		for (uint8_t i = 0; i < t.navios->size(); i++){
			if (t.navios->at(i).tipo == simbolo)
			{
				cout << "Erro: O simbolo " << simbolo << " ja existe." << endl;
				return novoTabuleiro(0, 0);
			}
		}

		/* Cor */
		carater++;
		cor = temp.substr(carater);

		for (uint8_t i = 0; i < cor.size(); i++){
			if (cor[i] == ' ' || cor[i] == '-')
			{
				cor.erase(cor.begin() + i);
				i--;
			}
		}

		/* Verificar validade da cor */
		if (interpretadorCor(cor) == (uint8_t)-1){
			cout << "Erro: a cor " << cor << "nao e reconhecida!" << endl;
			return novoTabuleiro(0, 0);
		}

		/* Depois de validado, verificar se cor ja existe */
		for (uint8_t i = 0; i < t.navios->size(); i++){
			if (t.navios->at(i).cor == interpretadorCor(cor)){ //A verificacao de validade permte fazer isto sem medo de um eventual -1
				cout << "Erro: A cor " << cor << " ja existe!" << endl;
				return novoTabuleiro(0, 0);
			}
		}

		/*Conversao String-> variavel */
		tamanho = atoi(tamanhostr.c_str());
		numero = atoi(numerostr.c_str());

		/*Colocar os navios no tabuleiro*/
		for (uint8_t i = 0; i < numero; i++){
			Navio n1 = novoNavio(nome, simbolo, tamanho, interpretadorCor(cor));
			inserirNavio(t, n1);
		}

		nome = "";
		tamanhostr = "";
		numerostr = "";
		simbolostr = "";
	}

	/* Por ultimo, testar se os navios tem espaco no tabuleiro especificado. */
	int espacoOcupado = 0;
	for (uint8_t i = 0; i < t.navios->size(); i++){
		espacoOcupado += t.navios->at(i).tamanho;
	}
	if (espacoOcupado >(t.tamanhoX * t.tamanhoY)){
		cout << "Erro: Os navios dados nao cabem no tabuleiro com o tamanho dado!" << endl;
		return novoTabuleiro(0, 0);
	}
	return t;
}