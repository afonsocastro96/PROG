#pragma once

/* Informacao e funcoes referentes ao tabuleiro de jogo*/

#include <iostream>
#include <vector>

#include "navio.h"
#include "symbolics.h"
#include "utils.h"

using namespace std;

/* Struct Tabuleiro: Guarda a informacao referente a um tabuleiro de jogo */
typedef struct {
	vector<char> *tabuleiro; /* Vetor com a informacao referente ao tabuleiro de jogo */
	uint8_t tamanhoX; /* Largura do tabuleiro */
	uint8_t tamanhoY; /* Altura do tabuleiro */
	modo modoFuncionamento; /* Modo de gerar o tabuleiro (automatico/manual) */
	vector<Navio> *navios; /* Vetor com os navios no tabuleiro */
} Tabuleiro;

/* Cria um novo tabuleiro de jogo. A funcao espera um tabuleiro vazio, que modifica com os valores dados */
Tabuleiro novoTabuleiro(uint8_t tamanhoX, uint8_t tamanhoY){
	Tabuleiro t;
	
	uint16_t tam = tamanhoX*tamanhoY; //Usar 8 bits aqui podia dar problemas, dado que apenas permite tabuleiros com taamnho ate 15
	
	t.tabuleiro = new vector<char>;
	t.navios = new vector<Navio>;

	t.tamanhoX = tamanhoX;
	t.tamanhoY = tamanhoY;

	for (uint16_t i = 0; i < tam; i++){
		t.tabuleiro->push_back('.');
	}

	return t;
}

/* Define o modo de gerar o tabuleiro */
void setModoTabuleiro(Tabuleiro &t, char monoFuncionamento){
	if (monoFuncionamento == 'A' || monoFuncionamento == 'a'){ t.modoFuncionamento = AUTOMATICO; }
	else t.modoFuncionamento = MANUAL;
}

/* Insere um navio no vetor de navios */
void inserirNavio(Tabuleiro &t, Navio &n){
	t.navios->push_back(n);
}

/* Coloca os caracteres navio dado do vetor que contem o tabuleiro */
bool colocarNavioTabuleiro(Tabuleiro &t, Navio &n){
		if (n.posicao == -1) //Erro, as posicoes nao foram atribuidas ao navio, abortar
			return false;
		if (n.or == HORIZONTAL)
			for (uint8_t j = 0; j < n.tamanho; j++){
				t.tabuleiro->at(n.posicao + j) = n.tipo;
			}
		else
			for (uint8_t j = 0; j < n.tamanho; j++){
				t.tabuleiro->at(n.posicao + j*t.tamanhoX) = n.tipo;
			}
	return true;
}

/* Testa se o navio com posicao inicial pos, na orientacao or e com um tamanho
pode ser colocado no tabuleiro sem ultrapassar as bordas */
bool colocavel(Tabuleiro &t, uint16_t pos, orientacao or, uint8_t tamanho){
	uint8_t coluna = pos % t.tamanhoX; //Coluna do primeiro ponto do navio. Usada mais a frente para saber se o navio excede as bordas 
	uint8_t linha = pos / t.tamanhoX; //Linha do primeiro ponto do navio. Idem.

	if (or == HORIZONTAL)
		for (uint8_t j = 0; j < tamanho; j++){
			/* Check necessario porque as coordenadas de algum ponto do navio
			 podiam ultrapassar os limites do vetor, dando erros de out-of-range */
			if ((pos + j) >= (uint16_t)t.tabuleiro->size())
				return false;
			/* Se encontrarmos um caracter que nao seja '.' (ou seja, ha la alguma coisa)
			ou se houver uma mudanca de linha, a colocacao e invalida*/
			else if (t.tabuleiro->at(pos + j) != '.' || (((pos + j) / t.tamanhoX) != linha))
				return false;
		}
	else // A disposicao do navio e vertical
		for (uint8_t j = 0; j < tamanho; j++){
			/* Se encontrarmos um caracter que nao seja '.' (ou seja, ha la alguma coisa)
			ou se houver uma mudanca de coluna, a colocacao e invalida*/
			if ((pos + t.tamanhoX*j) >= (uint16_t)t.tabuleiro->size())
				return false;
			else if (t.tabuleiro->at(pos + j*t.tamanhoX) != '.' || (((pos + j*t.tamanhoX) % t.tamanhoX) != coluna))
				return false;
		}

	return true;
}

/* Converte uma posicao para uma string. Necessaria para guardar no ficheiro com o tabuleiro a posicao dos navios */
string posToCharacter(Tabuleiro &t, uint8_t vPos, uint16_t pos){
	uint8_t linha = t.navios->at(vPos).posicao / t.tamanhoX;
	uint8_t coluna = t.navios->at(vPos).posicao % t.tamanhoX;

	char ret[3] = { 65 + linha, 97 + coluna, 0 };

	return ret;
}

uint8_t calculaMesmoTipoRestante(vector<Navio> &navios, uint8_t &indice){
	uint8_t ret = 1;
	char simbolo = navios.at(indice).tipo;

	for (uint8_t n = indice+1; n < navios.size(); n++){
		if (navios[n].tipo != simbolo)
			return ret;
	}

	return ret;
}

/* Imprime o tabuleiro no ecra */
void imprimirTabuleiro(Tabuleiro &t){
	clrscr();

	/* Imprime as letras maiusculas na primeira coluna */
	for (uint8_t i = 0; i < t.tamanhoX; i++){
		gotoxy(i*2+1, 0);
		setcolor(WHITE, BLACK);
		cout << (char)(97 + i); //Codigos ASCII para as letras maiusculas 
	}

	/* Imprime as letras minusculas na primeira linha */
	for (uint8_t i = 0; i < t.tamanhoX; i++){
		gotoxy(0, i+1);
		setcolor(WHITE, BLACK);
		cout << (char)(65 + i); //Codigos ASCII para as letras minusculas
	}

	/* Imprime o tabuleiro em si no ecra. As somas de 1 sao necessarias por causa das letras referentes
	as coordenadas inseridas no ecra em cima */
	for (uint8_t i = 0; i < t.tamanhoX; i++){
		uint8_t j;
		for (j = 0; j < t.tamanhoY; j++){
			gotoxy(j*2+1, i+1);
			if (t.tabuleiro->at(i * t.tamanhoX + j) == '.')
				setcolor(LIGHTBLUE, LIGHTGRAY);
			else
				for (uint8_t k = 0; k < t.navios->size(); k++){
					if (t.navios->at(k).tipo == t.tabuleiro->at(i * t.tamanhoX + j))
						setcolor(t.navios->at(k).cor, LIGHTGRAY);
				}
			cout << t.tabuleiro->at(i * t.tamanhoX + j) << " ";
		}
	}
	cout << endl << endl;
}