#pragma once

#include <iostream>
#include <vector>

#include "navio.h"
#include "symbolics.h"
#include "characters.h"

using namespace std;

typedef struct{
	vector<char> tabuleiro;
	string fichTabuleiro;
	uint8_t tamanhoX;
	uint8_t tamanhoY;
	modo modoFuncionamento;
	vector<Navio*> navios;
} Tabuleiro;

Tabuleiro* novoTabuleiro(uint8_t tamanhoX, uint8_t tamanhoY){
	Tabuleiro* t = (Tabuleiro*)malloc(sizeof(Tabuleiro));
	uint16_t tam = tamanhoX*tamanhoY; //Usar 8 bits aqui podia dar problemas, dado que apenas permite tabuleiros com taamnho ate 15

	for (uint16_t i = 0; i < tam; i++){
		t->tabuleiro.push_back('i');
	}
	return t;
}

void setModoTabuleiro(Tabuleiro* t, char monoFuncionamento){
	if (monoFuncionamento == 'A' || monoFuncionamento == 'a'){ t->modoFuncionamento = AUTOMATICO; }
	else t->modoFuncionamento = MANUAL;
}

void setFicheiroTabuleiro(Tabuleiro* t, string fileName){
	t->fichTabuleiro = fileName;
}

void apagarTabuleiro(Tabuleiro* t){
	free(t);
}

void inserirNavio(Tabuleiro* t, Navio* n){
	t->navios.push_back(n);
}

bool colocarNavioTabuleiro(Tabuleiro* t, Navio* n){
		if (n->posicao == -1) //Erro, as posicoes nao foram atribuidas ao navio, abortar
			return false;
		if (n->or == HORIZONTAL)
			for (uint8_t j = 0; j < n->tamanho; j++){
				t->tabuleiro[n->posicao + j] = n->tipo;
			}
		else
			for (uint8_t j = 0; j < n->tamanho; j++){
				t->tabuleiro[n->posicao + j*t->tamanhoX] = n->tipo;
			}
	return true;
}

bool colocavel(Tabuleiro* t, Navio* n){
	uint16_t pos = n->posicao;
	uint8_t linha = pos / t->tamanhoX;
	uint8_t coluna = pos % t->tamanhoX;

	if (n->or == HORIZONTAL)
		for (uint8_t j = 0; j < n->tamanho; j++){
			/* Se encontrarmos um caracter que nao seja '.' (ou seja, ha la alguma coisa)
			ou se houver uma mudanca de linha, a colocacao e invalida*/
			if (t->tabuleiro[pos + j] != '.' || (t->tabuleiro[pos + j] / t->tamanhoX) != linha)
				return false;
		}
	else
		for (uint8_t j = 0; j < n->tamanho; j++){
			/* Se encontrarmos um caracter que nao seja '.' (ou seja, ha la alguma coisa)
			ou se houver uma mudanca de coluna, a colocacao e invalida*/
			if (t->tabuleiro[pos + j*t->tamanhoX] != '.' || (t->tabuleiro[pos + j*t->tamanhoX] / t->tamanhoX) != coluna)
				return false;
		}

	return true;
}

string posToCharacter(Tabuleiro* t, uint8_t vPos, uint16_t pos){
	uint8_t linha = t->navios[vPos]->posicao / t->tamanhoX;
	uint8_t coluna = t->navios[vPos]->posicao / t->tamanhoX;

	char ret[3];
	ret[0] = 65 + linha;
	ret[1] = 97 + coluna;
	ret[2] = 0;

	return ret;
}

void imprimirTabuleiro(Tabuleiro* t){
	clrscr();

	cout << " a b c d e f g h i j" << endl;

	for (uint8_t i = 1; i < t->tamanhoX; i++){
		gotoxy(i, 0);
		cout << (char)(96 + i); //Codigos ASCII para as letras
	}

	for (uint8_t i = 0; i < t->tamanhoX; i++){
		uint8_t j;
		for (j = 0; j < t->tamanhoY; j++){
			gotoxy(i, j);
			cout << t->tabuleiro[i * t->tamanhoX + j];
		}
	}
	cout << endl;
}