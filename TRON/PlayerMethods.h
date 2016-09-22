#pragma once

#include "WorldProperties.h"

#include <vector>
using std::vector;

#define _USE_MATH_DEFINES
#include <math.h>

//VARIABILI.
//Variabili legate ai movimenti del giocatore.
//Angolo di rotazione della telecamera.
extern float angle;
//Posizione x e z della telecamera (osservatore).
extern float x_observer, z_observer;
//Vettore indicante la direzione della telecamera (posizione del VRP - View Reference Point).
extern float x_vrp, z_vrp;

//Variabile contenente la distanza della telecamera dal giocatore.
extern int cameraRadius;

//Variabili legate ai muri creati dal giocatore.
extern vector<vector<float> > playersWallsArray;
extern int sizePlayersWallsArray;

//Variabile per meccanismo a parità.
extern int playerParity;
//Salvo il tasto premuto per ultimo.
extern char lastKeyPressed;

extern float xLightCycleCollision;
extern float zLightCycleCollision;

//METODI.
/*Funzione di inizializzazione delle variabili del giocatore.*/
void initializePlayerVariables();
/*Funzione di movimento automatico del giocatore.*/
void movePlayer();
/*Metodo di aggiunta nuovo muro giocatore.*/
void addNewPlayersWall(char key);
/*Funzione di disegno della light cycle del giocatore.*/
void drawPlayersLightCycle();
/*Funzione di disegno dei muri lasciati dal giocatore.*/
void drawPlayersWalls();