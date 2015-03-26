#pragma once

#include <fstream>
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

void criarFicheiroConf(string fileName){
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

void criarFicheiroTabuleiro(string fileName, Tabuleiro* t){
	ifstream i_ficheiro(fileName);

	if (!i_ficheiro){
		ofstream o_ficheiro;
		o_ficheiro.open(fileName.c_str());

		o_ficheiro << t->tamanhoX << " x " << t->tamanhoY << endl;
		for (uint8_t i = 0; i < t->navios.size(); i++){
			
			o_ficheiro << t->navios[i]->tipo << " " << t->navios[i]->tamanho << " " << posToCharacter(t, i, t->navios[i]->posicao) << " ";
			if (t->navios[i]->or == HORIZONTAL)
				o_ficheiro << "H";
			else o_ficheiro << "V";

			o_ficheiro << "\n";
		}

	}

}

Tabuleiro* lerFicheiroConf(string fileName){
	/* Falta considerar a quantidade como numero de navios a inserir no vetor */
	uint8_t tamanhoX;
	uint8_t tamanhoY;

	uint8_t numero;
	uint8_t tamanho;
	string nome;
	char simbolo;
	string cor;

	string temp;
	ifstream o(fileName.c_str());

	if (!o)
		return NULL;

	getline(o, temp);
	tamanhoX = atoi(temp.c_str());

	getline(o, temp);
	tamanhoY = atoi(temp.c_str());

	Tabuleiro* t = novoTabuleiro(tamanhoX, tamanhoY);


	while(!o.eof()){

		getline(o, temp);
		numero = atoi(temp.c_str());

		getline(o, nome);

		getline(o, temp);
		tamanho = atoi(temp.c_str());

		getline(o, temp);
		if (temp.size() > 1){
			return NULL;
		}
		simbolo = (char)temp.c_str();

		getline(o, temp);
		if (temp.size() > 1){
			return NULL;
		}
		cor = temp.c_str();

		for (uint8_t i = 0; i < numero; i++)
			inserirNavio(t, novoNavio(nome, simbolo, tamanho, interpretadorCor(cor)));

	}

	return t;
}