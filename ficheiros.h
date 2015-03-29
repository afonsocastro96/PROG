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
		i << "4 - Lancha       - 1 - L - Azul_claro" << endl;
	}

}

/* Depois de gerado o tabuleiro, cria um ficheiro com a informacao do tabuleiro para um nome de ficheiro fornecido
pelo utilizador. */
void criarFicheiroTabuleiro(string &fileName, Tabuleiro &t){
	//ifstream i_ficheiro(fileName);
	stringstream ss;
	ss << itos(t.tamanhoX) << " x " << itos(t.tamanhoY);

	//if (!i_ficheiro){
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

	//}

}

/* Le o ficheiro de configuracao fornecido pelo utilizador.
   Se o ficheiro nao existir, chama a funcao criaFicheiroConf() */
Tabuleiro lerFicheiroConf(string &fileName){
	uint8_t tamanhoX;
	uint8_t tamanhoY;

	uint8_t numero;
	string numerostr;
	uint8_t tamanho;
	string tamanhostr;
	string nome;
	char simbolo;
	string cor;

	string temp;
	string tempsubstr;
	ifstream o;

	o.open(fileName.c_str());

	if (!o){
		criarFicheiroConf(fileName);
		o.open(fileName.c_str());
	}


	getline(o, temp);

	for (uint8_t i = 11; i < temp.size(); i++){
		if (temp[i] != ' ')
			tempsubstr.push_back(temp[i]);
		else temp = temp.substr(i + 3);
	}
	tamanhoX = atoi(tempsubstr.c_str());
	tamanhoY = atoi(temp.c_str());

	Tabuleiro t;
	novoTabuleiro(t, tamanhoX, tamanhoY);


	while (!o.eof()){

		getline(o, temp);

		for (uint8_t i = 0; i < temp.size(); i++)
			if (temp[i] != ' ')
				numerostr.push_back(temp[i]);
			else {
				temp = temp.substr(i + 3);
				break;
			}

		for (uint8_t i = 0; i < temp.size(); i++){
			if (temp[i] != ' ')
				nome.push_back(temp[i]);
			else {
				temp = temp.substr(i);
				break;
			}
		}

		uint8_t nEspacos;
		for (nEspacos = 0; nEspacos < temp.size(); nEspacos++){
			if ((temp[nEspacos] > 48) && (temp[nEspacos] < 57))
				break;
		}
		temp = temp.substr(nEspacos);

		for (uint8_t i = 0; i < temp.size(); i++){
			if (temp[i] != ' ')
				tamanhostr.push_back(temp[i]);
			else {
				temp = temp.substr(i + 3);
				break;
			}
		}

		simbolo = temp[0];
		temp = temp.substr(4);

		tamanho = atoi(tamanhostr.c_str());
		numero = atoi(numerostr.c_str());
		cor = temp.c_str();

		for (uint8_t i = 0; i < numero; i++){
			Navio n1;
			novoNavio(n1, nome, simbolo, tamanho, interpretadorCor(cor));
			inserirNavio(t, n1);
		}

		nome = "";
		tamanhostr = "";
		numerostr = "";

	}

	return t;
}