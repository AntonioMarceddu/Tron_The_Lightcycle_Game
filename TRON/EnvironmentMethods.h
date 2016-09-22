#pragma once
#include "WorldProperties.h"
#include "TextureLoader.h"

/*Funzione di caricamento della texture del pavimento.*/
void loadFloorTexture();
/*Funzione di disegno della mappa e dei segnali a schermo.*/
void drawFloor();
/*Funzione che disegna i muri attorno all'area di gioco.*/
void addWallsAroundTheGameArea();
/*Funzione di caricamento delle texture della skybox.*/
void loadSkyboxTextures();
/*Funzione di disegno della skybox attorno all'area di gioco.*/
void drawSkybox();
/*Funzione di disegno dei gradoni dello stadio.*/
void drawSteps();
/*Funzione di disegno dei corrimano.*/
void drawHandRail();
/*Funzione di aggiunta dei decori in alto e delle luci dello stadio.*/
void addStadiumDecorationsAndLights();