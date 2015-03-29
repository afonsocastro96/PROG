#pragma once

/* Funcoes relacionadas com leitura e escrita em ficheiros */

#include <fstream>
#include <sstream>
#include "symbolics.h"
#include "navio.h"
#include "tabuleiro.h"

using namespace std;

/* ESTRUTURA DO FICHEIRO CONF (optei por usar uma diferente visto que e mais simples e mais eficiente)
 - TamanhoX
 - TamanhoY
 - NumeroNavio1
 - NomeNavio1
 - TamanhoNavio1
 - SimboloNavio1
 - CorNavio1
 - NumeroNavio2
 - NomeNavio2
 - TamanhoNavio2
 - SimboloNavio2
 - CorNavio2
 ...
 */

/* ESTRUTURA DO FICHEIRO COM O TABULEIRO
 - TamanhoX
 - TamanhoY
 - SimboloNavio1
 - TamanhoNavio1
 - PosicaoX PosicaoY (1)
 - Orientacao1
 - SimboloNavio2
 - TamanhoNavio2
 - PosicaoX PosicaoY (2)
 - Orientacao2
 ...
*/

/* Cria um ficheiro com o nome fornecido pelo utilizador com a informacao default (a dada no enunciado do projeto)
caso o nome de ficheiro dado pelo utilizador nao exista. */
void criarFicheiroConf(string &fileName){
	ifstream o(fileName);

	if (!o){
		ofstream i;
		i.open(fileName.c_str());

		i << "10" << endl; // Tamanho X
		i << "10" << endl; // Tamanho Y
		i << "1" << endl; // Numero de navios
		i << "Porta-avioes" << endl; // Nome do navio
		i << "5" << endl; // Tamanho do navio
		i << "P" << endl; // Simbolo
		i << "Vermelho_claro" << endl; // Cor
		i << "1" << endl; // Numero de navios
		i << "Fragata" << endl; // Nome do navio
		i << "4" << endl; // Tamanho do navio
		i << "F" << endl; // Simbolo
		i << "Magenta_claro" << endl; // Cor
		i << "2" << endl; // Numero de navios
		i << "Cruzador" << endl; // Nome do navio
		i << "3" << endl; // Tamanho do navio
		i << "C" << endl; // Simbolo
		i << "Verde_claro" << endl; // Cor
		i << "3" << endl; // Numero de navios
		i << "Submarino" << endl; // Nome do navio
		i << "2" << endl; // Tamanho do navio
		i << "S" << endl; // Simbolo
		i << "Castanho" << endl; // Cor
		i << "4" << endl; // Numero de navios
		i << "Lancha" << endl; // Nome do navio
		i << "1" << endl; // Tamanho do navio
		i << "L" << endl; // Simbolo
		i << "Azul_claro" << endl; // Cor
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
	uint8_t tamanho;
	string nome;
	char simbolo;
	string cor;

	string temp;
	ifstream o;

	if (!o)
		criarFicheiroConf(fileName);

	o.open(fileName.c_str());

	getline(o, temp);
	tamanhoX = atoi(temp.c_str());

	getline(o, temp);
	tamanhoY = atoi(temp.c_str());

	Tabuleiro t;
	novoTabuleiro(t, tamanhoX, tamanhoY);


	while(!o.eof()){

		getline(o, temp);
		numero = atoi(temp.c_str());

		getline(o, nome);

		getline(o, temp);
		tamanho = atoi(temp.c_str());

		getline(o, temp);
		simbolo = temp[0];

		getline(o, temp);
		cor = temp.c_str();

		for (uint8_t i = 0; i < numero; i++){
			Navio n1;
			novoNavio(n1, nome, simbolo, tamanho, interpretadorCor(cor));
			inserirNavio(t, n1);
		}

	}

	return t;
}