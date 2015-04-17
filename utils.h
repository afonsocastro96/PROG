#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

/* Funcoes utilitarias para o programa */

/*Conversor inteiro -> string */
string itos(int32_t integer){
	string ret;

	while (integer > 0){
		ret.push_back((integer % 10) + 48); //Mais conversoes ASCII -> Inteiro
		integer /= 10;
	}

	reverse(ret.begin(), ret.end());

	return ret;
}

/*Testa se o codigo ASCII enviado e correspondente a um numero */

bool isANumber(char c) {
	return (c >= 48 && c <= 57);
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

/* API DO PROFESSOR PARA AS CORES / COLOCACAO DO CURSOR NUM SITIO ESPECIFICO */
// PROG - MIEIC
// JAS
// Example of a program that prints colored characters on the console (in text mode)

//==========================================================================================
void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}
//==========================================================================================
// Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//==========================================================================================
// Set text color
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================
// Set text color & background
void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | background_color*16+color);
}