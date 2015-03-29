#pragma once

/* Informacao e funcoes referentes aos navios do jogo */

#include <iostream>
#include <string>
#include "symbolics.h"

using namespace std;

/* Struct navio: Guarda a informacao referente a um navio. */
typedef struct {
	string nome; /*Nome do navio */
	char tipo; /* Simbolo do navio */
	uint8_t tamanho; /* Tamanho do navio */
	uint8_t cor; /* Cor do navio na consola */
	uint16_t posicao; /* Posicao da primeira coordenada do navio */
	orientacao or; /* Orientacao do navio (horizontal / vertical) */
} Navio;

/* Construtor de um navio. Recebe como argumento um navio vazio, e altera esse navio com a informacao fornecida */
Navio novoNavio(string &nome, char &tipo, uint8_t &tamanho, uint8_t cor){
	Navio n1;

	n1.nome = nome;
	n1.tipo = tipo;
	n1.tamanho = tamanho;
	n1.cor = cor;
	/* -1 em complemento para 2 = maior numero possivel de 16 bits sem sinal. Usado para verificacao de erros
	sem provocar acessos ilegais a memoria */
	n1.posicao = -1;

	return n1;
}

/* Inicializa os membros do navio que o construtor nao inicializa */
void posicaoNavio(Navio &n1, uint16_t &posicao, orientacao &or){
	n1.posicao = posicao;
	n1.or = or;
}

/* Recebendo um valor para a linha e coluna, bem como a largura do tabuleiro, calcula a posicao a colocar o navio */
void setPosicao(Navio &n, char &linha, char &coluna, uint8_t &largura) {
	n.posicao = linha * largura + coluna;
}

/* Define a orientacao do navio com base na informacao dada pelo utilizador */
void setOr(Navio &n, char &or){
	if (or == 'h' || or == 'H')
		n.or = HORIZONTAL;
	else n.or = VERTICAL;
}

/* Converte a nomenculatura de cor dos ficheiros para a da API do Windows */
uint8_t interpretadorCor(const string color){
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
	else if (color == "Branco")
		return WHITE;
	else return -1;
}