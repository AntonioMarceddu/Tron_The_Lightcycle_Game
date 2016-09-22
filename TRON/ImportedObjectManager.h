#pragma once
#include "ObjectImporter.h"
#include "EnvironmentMethods.h"
#include "PlayerAndAIMethods.h"

//Variabile di flag messa ad 1 quando tutti gli oggetti vengono disegnati per la prima volta e messi nella lista.
extern int listCreated;

//FUNZIONI DI CARICAMENTO ALL'INTERNO DEL GIOCO DEGLI OGGETTI REALIZZATI CON BLENDER.
/*Funzione di disegno della lightcycle del giocatore.*/
void drawPlayersLightCycle();
/*Funzione di disegno della lightcycle dell'IA.*/
void drawAILightCycle();