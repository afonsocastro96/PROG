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

/* Altera a posicao de um navio. Usada quando o utilizador pretende editar a posicao de um navio */
void alteraPosicaoNavio(Navio &n1, uint8_t &posicao, orientacao &or){
	n1.posicao = posicao;
	n1.or = or;
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