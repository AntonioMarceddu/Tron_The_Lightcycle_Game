#pragma once

#include "WorldProperties.h"

#include <vector>
using std::vector;

#define _USE_MATH_DEFINES
#include <math.h>

//Variabile di rotazione AI.
extern float angleAI;
//Variabili di posizione dell'IA.
extern float x_AI, z_AI;

//Variabile recante la direzione di movimento (sinistra o destra).
extern char directions[3];

//Variabili legate ai muri creati dall'IA.
extern vector<vector<float> > AIWallsArray;
extern int sizeAIWallsArray;

//Variabili legate alla collisione anteriore del giocatore.
extern float xAILightCycleCollision;
extern float zAILightCycleCollision;

//Implemento un meccanismo a parità anche per la IA, come fatto per il giocatore.
extern int AIParity;

//Implemento due contatori a refresh per determinate scelte dell'IA.
extern int counterForAIDecision1;
extern int counterForAIDecision2;

//Funzione di inizializzazione delle variabili dell'IA.
void initializeAIVariables();
//Funzione che aggiunge un nuovo muro al giocatore se cambia direzione.
void addNewAIWall();
//Metodi che permettono la rotazione a sinistra e destra dell'IA. 
void AITurnLeft();
void AITurnRight();
//Funzione di rotazione casuale dell'IA a sinistra o destra.
void RandomAIRotationLeftOrRight();
//Funzione di disegno dei muri lasciati dall'IA.
void drawAIWalls();
//Funzione che viene richiamata quando occorre la IA deve decidere se girare con una certa percentuale.
void chooseToTurnWithACertainPercentage(int percentage, char* message);
