#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "ImportedObjectManager.h"

//VARIABILI RECANTI INFORMAZIONI SULLA SCHERMATA ATTUALE.
//Risoluzione schermo (iniziale e dopo ridimensionamenti).
extern int RES_X, RES_Y;

//Variabile di abilitazione e disabilitazione menu'.
extern int menu;
//Variabile contenente la direzione in cui è puntata la telecamera.
extern int actualCamera;
//Variabile di fine gioco, inizializzata a 0; se vince il giocatore viene posta ad 1, mentre se vince il computer viene posta a 2.
extern int endGame;
//Variabile flag di rotazione.
extern int rotation;
//Variabile memorizzazione angolo.
extern float actualAngle;


//Variabile contenente l'avvio della musica del menu'.
extern int musicStarted;

//Variabili contenenti le texture del menu'.
extern int MainMenuTex;
extern int newGameButtonTex;
extern int howToPlayButtonTex;
extern int creditsButtonTex;
extern int exitGameButtonTex;
extern int howToPlayMenuTex;
extern int creditsMenuTex;
extern int backButtonTex;
extern int youWinTex;
extern int youLoseTex;

//Definizione luci.
extern GLfloat LightSpecular[];
extern GLfloat LightDiffuse[];
extern GLfloat LightAmbient[];
extern GLfloat LightPosition0[];
extern GLfloat LightPosition1[];

/*Funzione di disegno del menu' principale.*/
void drawMainMenu();
/*Funzione di disegno del menu' How To Play.*/
void drawHowToPlayMenu();
/*Funzione di disegno del menu' Credits.*/
void drawCreditsMenu();
/*Funzione di disegno del gioco.*/
void drawGame();
/*Funzione di disegno al termine del gioco.*/
void outputEndGame();
