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

Navio* apagarNavio(Navio* n1){
	free(n1);
}

void posicaoNavio(Navio* n1, uint16_t posicao, orientacao or){
	n1->posicao = posicao;
	n1->or = or;
}