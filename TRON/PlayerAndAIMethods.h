#pragma once
#include "AIMethods.h"
#include "PlayerMethods.h"

//Variabile oltre il quale la IA valuta se girare o meno se è presente un muro disegnato da lei o dal giocatore.
#define CHG 4.5
//Offset oltre il quale la IA valuterà se girare per evitare di sbattersi contro i muri di delimitazione del gioco.
#define BORDEROFFSET 94

//FUNZIONI CON VERIFICHE DEI VALORI DEL GIOCATORE E DELL'IA.
/*Funzione di verifica collisioni del giocatore con i muri del gioco, con quelli lasciati da se stesso e dall'IA.*/
int verifyPlayerCollision();
/*Funzione di verifica collisioni dell'IA con i muri del gioco, con quelli lasciati da se stesso e dal giocatore.*/
int verifyAICollision();
/*Funzione di movimento automatico dell'IA.*/
void moveAI();