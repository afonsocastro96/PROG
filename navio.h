#pragma once

#include <iostream>
#include <string>
#include "symbolics.h"

using namespace std;

typedef struct {
	string nome;
	char tipo;
	uint8_t tamanho;
	uint8_t cor;
	uint16_t posicao;
	orientacao or; //Orientacao do navio
} Navio;

Navio* novoNavio(string nome, char tipo, uint8_t tamanho, uint8_t cor){
	Navio* n1 = (Navio*)malloc(sizeof(Navio));

	n1->nome = nome;
	n1->tipo = tipo;
	n1->tamanho = tamanho;
	n1->cor = cor;
	/* -1 em complemento para 2 = maior numero possivel de 16 bits sem sinal. Usado para verificacao de erros
	sem provocar acessos ilegais a memoria */
	n1->posicao = -1;

	return n1;
}

void apagarNavio(Navio* n1){
	free(n1);
}

void posicaoNavio(Navio* n1, uint16_t posicao, orientacao or){
	n1->posicao = posicao;
	n1->or = or;
}

void setPosicao(Navio* n, char linha, char coluna, uint8_t largura) {
	n->posicao = (65 - linha) * largura + (97 - coluna);
}

void setOr(Navio* n, char or){
	if (or == 'h' || or == 'H')
		n->or = HORIZONTAL;
	else n->or = VERTICAL;
}

uint8_t interpretadorCor(string color){

	if (color == "Preto")
		return BLACK;
	else if (color == "Azul")
		return BLUE;
	else if (color == "Verde")
		return GREEN;
	else if (color == "Ciano")
		return CYAN;
	else if (color == "Vermelho")
		return RED;
	else if (color == "Magenta")
		return MAGENTA;
	else if (color == "Castanho")
		return BROWN;
	else if (color == "Cinzento_claro")
		return LIGHTGRAY;
	else if (color == "Cinzento_escuro")
		return DARKGRAY;
	else if (color == "Azul_claro")
		return LIGHTBLUE;
	else if (color == "Verde_claro")
		return LIGHTGREEN;
	else if (color == "Ciano_claro")
		return LIGHTCYAN;
	else if (color == "Vermelho_claro")
		return LIGHTRED;
	else if (color == "Magenta_claro")
		return LIGHTMAGENTA;
	else if (color == "Amarelo")
		return YELLOW;
	else if (color == "White")
		return WHITE;
	else return -1;
}