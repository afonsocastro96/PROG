#pragma once

/* Constantes Simbolicas e Typedefs
   Criados para aumentar a legibilidade do codigo, (por exemplo no caso da orientacao,
   bool, true e false nao sao muito indicativos da orientacao de um navio...) */

typedef unsigned char uint8_t; //Inteiro sem sinal de 8 bits
typedef unsigned short uint16_t; //Inteiro sem sinal de 16 bits
typedef unsigned int uint32_t; //Inteiro sem sinal de 32 bits

typedef char int8_t; //Inteiro de 8 bits
typedef short int16_t; //Inteiro de 16 bits
typedef int int32_t; //Inteiro de 32 bits

typedef bool modo; //Modo de gerar os tabuleiros (Automatico/Manual)
typedef bool orientacao; // Orientacao dos navios (Horizontal/Vertical)

/* Constantes simbolicas referentes aos dois typedefs acima */

#define AUTOMATICO true
#define MANUAL false

#define HORIZONTAL true
#define VERTICAL false

/*Codigos de cores*/

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15