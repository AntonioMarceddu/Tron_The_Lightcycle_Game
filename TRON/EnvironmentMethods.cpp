#include <math.h>
#include "EnvironmentMethods.h"

/*Skybox Textures.*/
#define SKYBOX_FRONT 0
#define SKYBOX_BACK 1
#define SKYBOX_LEFT 2
#define SKYBOX_RIGHT 3
#define SKYBOX_UP 4

/*Textures.*/
int skybox[5];
int floorTex;

/*Variabili di luminosità dei muri di confine.*/
GLfloat darkBlueBoundWalls[] = { 0.031, 0.56, 0.745, 0.8 };
GLfloat lightBlueBoundWalls[] = { 0.79, 0.945, 0.985, 1 };

/*Variabili di luminosità dei corrimano.*/
GLfloat Color1HandRail[] = { 1, 0.06, 0.06, 0.8 };
GLfloat Color2HandRail[] = { 1, 0.58, 0.58, 1 };

/*Variabile contenente il colore delle luci dello stadio.*/
GLfloat StadioLights[] = { 1, 1, 1, 1};

/*Funzione di caricamento della texture del pavimento.*/
void loadFloorTexture()
{
	floorTex = loadTexBMP("..\\Textures\\Floor.bmp");
}

/*Funzione di disegno della mappa e dei segnali a schermo.*/
void drawFloor()
{
	glColor4f(1, 1, 1, 0.8);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, floorTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);	glVertex3i( -WORLDSIZE, MINHEIGHT, -WORLDSIZE);
	glTexCoord2i(1, 0); glVertex3i(WORLDSIZE, MINHEIGHT, -WORLDSIZE);
	glTexCoord2i(1, 1); glVertex3i(WORLDSIZE, MINHEIGHT, WORLDSIZE);
	glTexCoord2i(0, 1); glVertex3i( -WORLDSIZE, MINHEIGHT, WORLDSIZE);
	glEnd();
	glPopMatrix();
}

/*Funzione che disegna i muri attorno all'area di gioco.*/
void addWallsAroundTheGameArea()
{
	glPushMatrix();
	//Colore Muro.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, darkBlueBoundWalls);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkBlueBoundWalls);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Disegno il muro in alto.
	glBegin(GL_QUADS);
	glVertex3i( -WORLDSIZE, MINHEIGHT, -WORLDSIZE);
	glVertex3i(WORLDSIZE, MINHEIGHT, -WORLDSIZE);
	glVertex3i(WORLDSIZE, MAXHEIGHT, -WORLDSIZE);
	glVertex3i( -WORLDSIZE, MAXHEIGHT, -WORLDSIZE);
	glEnd();
	//Disegno il muro in basso.
	glBegin(GL_QUADS);
	glVertex3i( -WORLDSIZE, MINHEIGHT, WORLDSIZE);
	glVertex3i(WORLDSIZE, MINHEIGHT, WORLDSIZE);
	glVertex3i(WORLDSIZE, MAXHEIGHT, WORLDSIZE);
	glVertex3i( -WORLDSIZE, MAXHEIGHT, WORLDSIZE);
	glEnd();
	//Disegno il muro a sinistra.
	glBegin(GL_QUADS);
	glVertex3i( -WORLDSIZE, MINHEIGHT, -WORLDSIZE);
	glVertex3i( -WORLDSIZE, MAXHEIGHT, -WORLDSIZE);
	glVertex3i( -WORLDSIZE, MAXHEIGHT, WORLDSIZE);
	glVertex3i( -WORLDSIZE, MINHEIGHT, WORLDSIZE);
	glEnd();
	//Disegno il muro a destra.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE, MINHEIGHT, -WORLDSIZE);
	glVertex3i(WORLDSIZE, MAXHEIGHT, -WORLDSIZE);
	glVertex3i(WORLDSIZE, MAXHEIGHT, WORLDSIZE);
	glVertex3i(WORLDSIZE, MINHEIGHT, WORLDSIZE);
	glEnd();

	//Colore spessore.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lightBlueBoundWalls);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightBlueBoundWalls);
	glColor4f(0.79, 0.945, 0.985, 1);
	//Disegno lo spessore superiore in alto.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEOFFSET, MAXHEIGHT, -WORLDSIZEOFFSET);
	glVertex3f(-WORLDSIZEOFFSET, MAXHEIGHT, -WORLDSIZE);
	glVertex3f(WORLDSIZEOFFSET, MAXHEIGHT, -WORLDSIZE);
	glVertex3f(WORLDSIZEOFFSET, MAXHEIGHT, -WORLDSIZEOFFSET);
	glEnd();
	//Disegno lo spessore superiore in basso.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEOFFSET, MAXHEIGHT, WORLDSIZEOFFSET);
	glVertex3f(-WORLDSIZEOFFSET, MAXHEIGHT, WORLDSIZE);
	glVertex3f(WORLDSIZEOFFSET, MAXHEIGHT, WORLDSIZE);
	glVertex3f(WORLDSIZEOFFSET, MAXHEIGHT, WORLDSIZEOFFSET);
	glEnd();
	//Disegno lo spessore superiore a sinistra.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEOFFSET, MAXHEIGHT, -WORLDSIZEOFFSET);
	glVertex3f(-WORLDSIZE, MAXHEIGHT, -WORLDSIZE);
	glVertex3f(-WORLDSIZE, MAXHEIGHT, WORLDSIZE);
	glVertex3f(-WORLDSIZEOFFSET, MAXHEIGHT, WORLDSIZEOFFSET);
	glEnd();
	//Disegno lo spessore superiore a destra.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEOFFSET, MAXHEIGHT, -WORLDSIZEOFFSET);
	glVertex3f(WORLDSIZE, MAXHEIGHT, -WORLDSIZE);
	glVertex3f(WORLDSIZE, MAXHEIGHT, WORLDSIZE);
	glVertex3f(WORLDSIZEOFFSET, MAXHEIGHT, WORLDSIZEOFFSET);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*Funzione di caricamento delle texture della skybox.*/
void loadSkyboxTextures()
{
	skybox[SKYBOX_FRONT] = loadTexBMP("..\\Textures\\GrayCloud_ft.bmp"); //0
	skybox[SKYBOX_BACK] = loadTexBMP("..\\Textures\\GrayCloud_bk.bmp"); //3
	skybox[SKYBOX_LEFT] = loadTexBMP("..\\Textures\\GrayCloud_lf.bmp"); //2
	skybox[SKYBOX_RIGHT] = loadTexBMP("..\\Textures\\GrayCloud_rt.bmp"); //1	
	skybox[SKYBOX_UP] = loadTexBMP("..\\Textures\\GrayCloud_up.bmp"); //4
}

/*Funzione di disegno della skybox attorno all'area di gioco.*/
void drawSkybox()
{
	glColor3f(1, 1, 1);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	/*Parte frontale.*/
	glBindTexture(GL_TEXTURE_2D, skybox[SKYBOX_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f( + SKYBOXSIZE, - SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(1, 0); glVertex3f( + SKYBOXSIZE, - SKYBOXSIZE, + SKYBOXSIZE);
	glTexCoord2i(1, 1); glVertex3f( + SKYBOXSIZE, + SKYBOXSIZE, + SKYBOXSIZE);
	glTexCoord2i(0, 1); glVertex3f( + SKYBOXSIZE, + SKYBOXSIZE, - SKYBOXSIZE);
	glEnd();
	/*Parte sinistra.*/
	glBindTexture(GL_TEXTURE_2D, skybox[SKYBOX_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f( + SKYBOXSIZE, - SKYBOXSIZE, + SKYBOXSIZE);
	glTexCoord2i(1, 0); glVertex3f( - SKYBOXSIZE, - SKYBOXSIZE, + SKYBOXSIZE);
	glTexCoord2i(1, 1); glVertex3f( - SKYBOXSIZE, + SKYBOXSIZE, + SKYBOXSIZE);
	glTexCoord2i(0, 1); glVertex3f(SKYBOXSIZE, + SKYBOXSIZE, + SKYBOXSIZE);
	glEnd();
	/*Parte destra.*/
	glBindTexture(GL_TEXTURE_2D, skybox[SKYBOX_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f( - SKYBOXSIZE, - SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(1, 0); glVertex3f( + SKYBOXSIZE, - SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(1, 1); glVertex3f( + SKYBOXSIZE, + SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(0, 1); glVertex3f( - SKYBOXSIZE, + SKYBOXSIZE, - SKYBOXSIZE);
	glEnd();
	/*Parte posteriore.*/
	glBindTexture(GL_TEXTURE_2D, skybox[SKYBOX_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f( - SKYBOXSIZE, - SKYBOXSIZE, SKYBOXSIZE);
	glTexCoord2i(1, 0); glVertex3f( - SKYBOXSIZE, - SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(1, 1); glVertex3f( - SKYBOXSIZE, SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(0, 1); glVertex3f( - SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	glEnd();
	/*Parte alta.*/
	glBindTexture(GL_TEXTURE_2D, skybox[SKYBOX_UP]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f( - SKYBOXSIZE, SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(1, 0); glVertex3f(SKYBOXSIZE, SKYBOXSIZE, - SKYBOXSIZE);
	glTexCoord2i(1, 1); glVertex3f(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	glTexCoord2i(0, 1); glVertex3f( - SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

/*Funzione di disegno dei gradoni dello stadio.*/
void drawSteps()
{
	glPushMatrix();
	//GRADONI IN - Z.
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 1.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, - 2, -WORLDSIZE);
	glVertex3i(-WORLDSIZEBORDER - 1, - 2, -WORLDSIZE - 4);
	glVertex3i(WORLDSIZEBORDER + 1, - 2, -WORLDSIZE - 4);
	glVertex3i(WORLDSIZEBORDER + 1, - 2, -WORLDSIZE);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 1.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, - 2, -WORLDSIZE - 4);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 4);
	glVertex3i(WORLDSIZEBORDER + 1, 0, -WORLDSIZE - 4);
	glVertex3i(WORLDSIZEBORDER + 1, - 2, -WORLDSIZE - 4);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 2.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 4);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 6);
	glVertex3i(WORLDSIZEBORDER + 1, 0, - WORLDSIZE - 6);
	glVertex3i(WORLDSIZEBORDER + 1, 0, - WORLDSIZE - 4);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 2.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 6);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, -WORLDSIZE - 6);
	glVertex3i(WORLDSIZEBORDER + 1, 2, -WORLDSIZE - 6);
	glVertex3i(WORLDSIZEBORDER + 1, 0, -WORLDSIZE - 6);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 3.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, -WORLDSIZE - 6);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, -WORLDSIZE - 8);
	glVertex3i(WORLDSIZEBORDER + 1, 2, -WORLDSIZE - 8);
	glVertex3i(WORLDSIZEBORDER + 1, 2, -WORLDSIZE - 6);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 3.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, -WORLDSIZE - 8);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, -WORLDSIZE - 8);
	glVertex3i(WORLDSIZEBORDER + 1, 4, - WORLDSIZE - 8);
	glVertex3i(WORLDSIZEBORDER + 1, 2, - WORLDSIZE - 8);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 4.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, -WORLDSIZE - 8);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 4, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 4, -WORLDSIZE - 8);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 4.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, -WORLDSIZE - 10);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 6, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 4, -WORLDSIZE - 10);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 5.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, -WORLDSIZE - 10);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, -WORLDSIZE - 12);
	glVertex3i(WORLDSIZEBORDER + 1, 6, -WORLDSIZE - 12);
	glVertex3i(WORLDSIZEBORDER + 1, 6, -WORLDSIZE - 10);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 5.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, -WORLDSIZE - 12);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, -WORLDSIZE - 12);
	glVertex3i(WORLDSIZEBORDER + 1, 8, -WORLDSIZE - 12);
	glVertex3i(WORLDSIZEBORDER + 1, 6, -WORLDSIZE - 12);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 6.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, -WORLDSIZE - 12);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, -WORLDSIZE - 14);
	glVertex3i(WORLDSIZEBORDER + 1, 8, -WORLDSIZE - 14);
	glVertex3i(WORLDSIZEBORDER + 1, 8, -WORLDSIZE - 12);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 6.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, -WORLDSIZE - 14);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, -WORLDSIZE - 14);
	glVertex3i(WORLDSIZEBORDER + 1, 10, -WORLDSIZE - 14);
	glVertex3i(WORLDSIZEBORDER + 1, 8, -WORLDSIZE - 14);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 7.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, -WORLDSIZE - 14);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, -WORLDSIZE - 16);
	glVertex3i(WORLDSIZEBORDER + 1, 10, -WORLDSIZE - 16);
	glVertex3i(WORLDSIZEBORDER + 1, 10, -WORLDSIZE - 14);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 7.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, -WORLDSIZE - 16);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, -WORLDSIZE - 16);
	glVertex3i(WORLDSIZEBORDER + 1, 12, -WORLDSIZE - 16);
	glVertex3i(WORLDSIZEBORDER + 1, 10, -WORLDSIZE - 16);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 8.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, -WORLDSIZE - 16);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, -WORLDSIZE - 18);
	glVertex3i(WORLDSIZEBORDER + 1, 12, -WORLDSIZE - 18);
	glVertex3i(WORLDSIZEBORDER + 1, 12, -WORLDSIZE - 16);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 8.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, -WORLDSIZE - 18);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, -WORLDSIZE - 18);
	glVertex3i(WORLDSIZEBORDER + 1, 14, -WORLDSIZE - 18);
	glVertex3i(WORLDSIZEBORDER + 1, 12, -WORLDSIZE - 18);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 9.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, -WORLDSIZE - 18);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, -WORLDSIZE - 20);
	glVertex3i(WORLDSIZEBORDER + 1, 14, -WORLDSIZE - 20);
	glVertex3i(WORLDSIZEBORDER + 1, 14, -WORLDSIZE - 18);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 9.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, -WORLDSIZE - 20);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, -WORLDSIZE - 20);
	glVertex3i(WORLDSIZEBORDER + 1, 16, -WORLDSIZE - 20);
	glVertex3i(WORLDSIZEBORDER + 1, 14, -WORLDSIZE - 20);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 10.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, -WORLDSIZE - 20);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, -WORLDSIZE - 22);
	glVertex3i(WORLDSIZEBORDER + 1, 16, -WORLDSIZE - 22);
	glVertex3i(WORLDSIZEBORDER + 1, 16, -WORLDSIZE - 20);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 10.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, -WORLDSIZE - 22);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, -WORLDSIZE - 22);
	glVertex3i(WORLDSIZEBORDER + 1, 18, -WORLDSIZE - 22);
	glVertex3i(WORLDSIZEBORDER + 1, 16, -WORLDSIZE - 22);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 11.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, -WORLDSIZE - 22);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, -WORLDSIZE - 24);
	glVertex3i(WORLDSIZEBORDER + 1, 18, -WORLDSIZE - 24);
	glVertex3i(WORLDSIZEBORDER + 1, 18, -WORLDSIZE - 22);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 11.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, -WORLDSIZE - 24);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, -WORLDSIZE - 24);
	glVertex3i(WORLDSIZEBORDER + 1, 20, -WORLDSIZE - 24);
	glVertex3i(WORLDSIZEBORDER + 1, 18, -WORLDSIZE - 24);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 12.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, -WORLDSIZE - 24);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, -WORLDSIZE - 26);
	glVertex3i(WORLDSIZEBORDER + 1, 20, -WORLDSIZE - 26);
	glVertex3i(WORLDSIZEBORDER + 1, 20, -WORLDSIZE - 24);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 12.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, -WORLDSIZE - 26);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, -WORLDSIZE - 26);
	glVertex3i(WORLDSIZEBORDER + 1, 22, -WORLDSIZE - 26);
	glVertex3i(WORLDSIZEBORDER + 1, 20, -WORLDSIZE - 26);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 13.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, -WORLDSIZE - 26);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, -WORLDSIZE - 28);
	glVertex3i(WORLDSIZEBORDER + 1, 22, -WORLDSIZE - 28);
	glVertex3i(WORLDSIZEBORDER + 1, 22, -WORLDSIZE - 26);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 13.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, -WORLDSIZE - 28);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, -WORLDSIZE - 28);
	glVertex3i(WORLDSIZEBORDER + 1, 28, -WORLDSIZE - 28);
	glVertex3i(WORLDSIZEBORDER + 1, 22, -WORLDSIZE - 28);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 14 (negativo).
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, -WORLDSIZE - 28);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 28, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 28, -WORLDSIZE - 28);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 14.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, -WORLDSIZE - 10);
	glVertex3i(-WORLDSIZEBORDER - 1, 34, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 34, -WORLDSIZE - 10);
	glVertex3i(WORLDSIZEBORDER + 1, 28, -WORLDSIZE - 10);
	glEnd();


	//GRADONI IN + Z.
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 1.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, - 2, WORLDSIZE);
	glVertex3i(-WORLDSIZEBORDER - 1, - 2, WORLDSIZE + 4);
	glVertex3i(WORLDSIZEBORDER + 1, - 2, WORLDSIZE + 4);
	glVertex3i(WORLDSIZEBORDER + 1, - 2, WORLDSIZE);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 1.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, - 2, WORLDSIZE + 4);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 4);
	glVertex3i(WORLDSIZEBORDER + 1, 0, WORLDSIZE + 4);
	glVertex3i(WORLDSIZEBORDER + 1, - 2, WORLDSIZE + 4);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 2.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 4);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 6);
	glVertex3i(WORLDSIZEBORDER + 1, 0, WORLDSIZE + 6);
	glVertex3i(WORLDSIZEBORDER + 1, 0, WORLDSIZE + 4);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 2.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 6);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, WORLDSIZE + 6);
	glVertex3i(WORLDSIZEBORDER + 1, 2, WORLDSIZE + 6);
	glVertex3i(WORLDSIZEBORDER + 1, 0, WORLDSIZE + 6);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 3.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, WORLDSIZE + 6);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, WORLDSIZE + 8);
	glVertex3i(WORLDSIZEBORDER + 1, 2, WORLDSIZE + 8);
	glVertex3i(WORLDSIZEBORDER + 1, 2, WORLDSIZE + 6);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 3.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 2, WORLDSIZE + 8);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, WORLDSIZE + 8);
	glVertex3i(WORLDSIZEBORDER + 1, 4, WORLDSIZE + 8);
	glVertex3i(WORLDSIZEBORDER + 1, 2, WORLDSIZE + 8);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 4.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, WORLDSIZE + 8);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 4, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 4, WORLDSIZE + 8);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 4.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 4, WORLDSIZE + 10);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 6, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 4, WORLDSIZE + 10);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 5.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, WORLDSIZE + 10);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, WORLDSIZE + 12);
	glVertex3i(WORLDSIZEBORDER + 1, 6, WORLDSIZE + 12);
	glVertex3i(WORLDSIZEBORDER + 1, 6, WORLDSIZE + 10);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 5.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 6, WORLDSIZE + 12);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, WORLDSIZE + 12);
	glVertex3i(WORLDSIZEBORDER + 1, 8, WORLDSIZE + 12);
	glVertex3i(WORLDSIZEBORDER + 1, 6, WORLDSIZE + 12);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 6.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, WORLDSIZE + 12);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, WORLDSIZE + 14);
	glVertex3i(WORLDSIZEBORDER + 1, 8, WORLDSIZE + 14);
	glVertex3i(WORLDSIZEBORDER + 1, 8, WORLDSIZE + 12);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 6.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 8, WORLDSIZE + 14);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, WORLDSIZE + 14);
	glVertex3i(WORLDSIZEBORDER + 1, 10, WORLDSIZE + 14);
	glVertex3i(WORLDSIZEBORDER + 1, 8, WORLDSIZE + 14);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 7.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, WORLDSIZE + 14);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, WORLDSIZE + 16);
	glVertex3i(WORLDSIZEBORDER + 1, 10, WORLDSIZE + 16);
	glVertex3i(WORLDSIZEBORDER + 1, 10, WORLDSIZE + 14);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 7.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 10, WORLDSIZE + 16);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, WORLDSIZE + 16);
	glVertex3i(WORLDSIZEBORDER + 1, 12, WORLDSIZE + 16);
	glVertex3i(WORLDSIZEBORDER + 1, 10, WORLDSIZE + 16);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 8.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, WORLDSIZE + 16);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, WORLDSIZE + 18);
	glVertex3i(WORLDSIZEBORDER + 1, 12, WORLDSIZE + 18);
	glVertex3i(WORLDSIZEBORDER + 1, 12, WORLDSIZE + 16);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 8.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 12, WORLDSIZE + 18);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, WORLDSIZE + 18);
	glVertex3i(WORLDSIZEBORDER + 1, 14, WORLDSIZE + 18);
	glVertex3i(WORLDSIZEBORDER + 1, 12, WORLDSIZE + 18);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 9.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, WORLDSIZE + 18);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, WORLDSIZE + 20);
	glVertex3i(WORLDSIZEBORDER + 1, 14, WORLDSIZE + 20);
	glVertex3i(WORLDSIZEBORDER + 1, 14, WORLDSIZE + 18);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 9.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 14, WORLDSIZE + 20);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, WORLDSIZE + 20);
	glVertex3i(WORLDSIZEBORDER + 1, 16, WORLDSIZE + 20);
	glVertex3i(WORLDSIZEBORDER + 1, 14, WORLDSIZE + 20);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 10.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, WORLDSIZE + 20);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, WORLDSIZE + 22);
	glVertex3i(WORLDSIZEBORDER + 1, 16, WORLDSIZE + 22);
	glVertex3i(WORLDSIZEBORDER + 1, 16, WORLDSIZE + 20);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 10.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 16, WORLDSIZE + 22);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, WORLDSIZE + 22);
	glVertex3i(WORLDSIZEBORDER + 1, 18, WORLDSIZE + 22);
	glVertex3i(WORLDSIZEBORDER + 1, 16, WORLDSIZE + 22);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 11.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, WORLDSIZE + 22);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, WORLDSIZE + 24);
	glVertex3i(WORLDSIZEBORDER + 1, 18, WORLDSIZE + 24);
	glVertex3i(WORLDSIZEBORDER + 1, 18, WORLDSIZE + 22);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 11.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 18, WORLDSIZE + 24);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, WORLDSIZE + 24);
	glVertex3i(WORLDSIZEBORDER + 1, 20, WORLDSIZE + 24);
	glVertex3i(WORLDSIZEBORDER + 1, 18, WORLDSIZE + 24);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 12.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, WORLDSIZE + 24);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, WORLDSIZE + 26);
	glVertex3i(WORLDSIZEBORDER + 1, 20, WORLDSIZE + 26);
	glVertex3i(WORLDSIZEBORDER + 1, 20, WORLDSIZE + 24);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 12.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 20, WORLDSIZE + 26);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, WORLDSIZE + 26);
	glVertex3i(WORLDSIZEBORDER + 1, 22, WORLDSIZE + 26);
	glVertex3i(WORLDSIZEBORDER + 1, 20, WORLDSIZE + 26);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 13.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, WORLDSIZE + 26);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, WORLDSIZE + 28);
	glVertex3i(WORLDSIZEBORDER + 1, 22, WORLDSIZE + 28);
	glVertex3i(WORLDSIZEBORDER + 1, 22, WORLDSIZE + 26);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 13.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 22, WORLDSIZE + 28);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, WORLDSIZE + 28);
	glVertex3i(WORLDSIZEBORDER + 1, 28, WORLDSIZE + 28);
	glVertex3i(WORLDSIZEBORDER + 1, 22, WORLDSIZE + 28);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 14 (negativo).
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, WORLDSIZE + 28);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 28, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 28, WORLDSIZE + 28);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 14.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZEBORDER - 1, 28, WORLDSIZE + 10);
	glVertex3i(-WORLDSIZEBORDER - 1, 34, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 34, WORLDSIZE + 10);
	glVertex3i(WORLDSIZEBORDER + 1, 28, WORLDSIZE + 10);
	glEnd();


	//GRADONI IN - X.
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 1.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE, -2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 4, -2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 4, -2, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE, -2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 1.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 4, -2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 4, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 4, 0, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 4, -2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 2.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 4, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 6, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 6, 0, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 4, 0, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 2.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 6, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 6, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 6, 2, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 6, 0, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 3.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 6, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 8, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 8, 2, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 6, 2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 3.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 8, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 8, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 8, 4, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 8, 2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 4.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 8, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 4, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 8, 4, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 4.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 10, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 6, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 10, 4, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 5.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 10, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 12, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 12, 6, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 10, 6, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 5.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 12, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 12, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 12, 8, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 12, 6, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 6.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 12, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 14, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 14, 8, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 12, 8, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 6.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 14, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 14, 10, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 14, 8, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 7.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 16, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 16, 10, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 14, 10, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 7.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 16, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 16, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 16, 12, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 16, 10, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 8.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 16, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 18, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 18, 12, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 16, 12, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 8.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 18, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 18, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 18, 14, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 18, 12, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 9.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 18, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 20, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 20, 14, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 18, 14, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 9.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 20, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 20, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 20, 16, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 20, 14, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 10.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 20, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 22, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 22, 16, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 20, 16, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 10.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 22, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 22, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 22, 18, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 22, 16, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 11.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 22, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 24, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 24, 18, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 22, 18, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 11.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 24, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 24, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 24, 20, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 24, 18, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 12.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 24, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 26, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 26, 20, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 24, 20, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 12.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 26, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 26, 22, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 26, 20, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 13.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 28, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 28, 22, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 26, 22, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 13.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 28, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 28, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 28, 28, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 28, 22, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 14 (negativo).
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 28, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 28, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 28, 28, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 14.
	glBegin(GL_QUADS);
	glVertex3i(-WORLDSIZE - 10, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 34, -WORLDSIZEBORDER - 1);
	glVertex3i(-WORLDSIZE - 10, 34, WORLDSIZEBORDER + 1);
	glVertex3i(-WORLDSIZE - 10, 28, WORLDSIZEBORDER + 1);
	glEnd();


	//GRADONI IN + X.
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 1.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE, -2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 4, -2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 4, -2, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE, -2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 1.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 4, -2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 4, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 4, 0, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 4, -2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 2.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 4, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 6, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 6, 0, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 4, 0, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 2.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 6, 0, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 6, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 6, 2, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 6, 0, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 3.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 6, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 8, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 8, 2, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 6, 2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 3.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 8, 2, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 8, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 8, 4, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 8, 2, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 4.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 8, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 4, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 8, 4, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 4.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 10, 4, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 6, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 10, 4, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 5.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 10, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 12, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 12, 6, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 10, 6, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 5.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 12, 6, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 12, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 12, 8, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 12, 6, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 6.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 12, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 14, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 14, 8, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 12, 8, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 6.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 14, 8, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 14, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 14, 10, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 14, 8, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 7.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 14, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 16, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 16, 10, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 14, 10, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 7.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 16, 10, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 16, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 16, 12, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 16, 10, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 8.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 16, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 18, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 18, 12, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 16, 12, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 8.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 18, 12, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 18, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 18, 14, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 18, 12, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 9.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 18, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 20, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 20, 14, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 18, 14, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 9.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 20, 14, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 20, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 20, 16, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 20, 14, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 10.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 20, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 22, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 22, 16, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 20, 16, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 10.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 22, 16, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 22, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 22, 18, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 22, 16, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 11.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 22, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 24, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 24, 18, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 22, 18, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 11.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 24, 18, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 24, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 24, 20, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 24, 18, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 12.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 24, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 26, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 26, 20, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 24, 20, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 12.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 26, 20, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 26, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 26, 22, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 26, 20, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	//Gradone orizzontale 13.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 26, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 28, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 28, 22, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 26, 22, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.14, 0.14, 0.14);
	//Gradone verticale 13.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 28, 22, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 28, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 28, 28, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 28, 22, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.12, 0.12, 0.12);
	//Gradone orizzontale 14 (negativo).
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 28, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 28, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 28, 28, WORLDSIZEBORDER + 1);
	glEnd();
	glColor3f(0.16, 0.16, 0.16);
	//Gradone verticale 14.
	glBegin(GL_QUADS);
	glVertex3i(WORLDSIZE + 10, 28, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 34, -WORLDSIZEBORDER - 1);
	glVertex3i(WORLDSIZE + 10, 34, WORLDSIZEBORDER + 1);
	glVertex3i(WORLDSIZE + 10, 28, WORLDSIZEBORDER + 1);
	glEnd();

	glPopMatrix();
}


/*Funzione di disegno dei corrimano.*/
void drawHandRail()
{
	glPushMatrix();

	//CORRIMANI IN -Z.
	/*Corrimano 1.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, -WORLDSIZE - 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, -WORLDSIZE - 2);
	glEnd();

	//Palo in centro.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, -WORLDSIZE - 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, -WORLDSIZE - 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, -WORLDSIZE - 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, -WORLDSIZE - 26.5);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 1, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER - 1, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER, 0, -WORLDSIZE - 2);
	glEnd();


	/*Corrimano 2.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, -WORLDSIZE - 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, -WORLDSIZE - 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, -WORLDSIZE - 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, -WORLDSIZE - 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, -WORLDSIZE - 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, -WORLDSIZE - 26.5);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 67, 0, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 67, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 67, -0.5, -WORLDSIZE - 2);
	glVertex3f(-WORLDSIZEBORDER + 67, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 24, -WORLDSIZE - 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 0, -WORLDSIZE - 2);
	glEnd();


	/*Corrimano 3.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, -WORLDSIZE - 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, -WORLDSIZE - 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, -WORLDSIZE - 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, -WORLDSIZE - 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, -WORLDSIZE - 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, -WORLDSIZE - 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, -WORLDSIZE - 26.5);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66, 24, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 24, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, -0.5, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, -0.5, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 67, 0, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 67, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, -0.5, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 66, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66, 24, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 66, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 67, -0.5, -WORLDSIZE - 2);
	glVertex3f(WORLDSIZEBORDER - 67, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 24, -WORLDSIZE - 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 0, -WORLDSIZE - 2);
	glEnd();


	/*Corrimano 4.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, -WORLDSIZE - 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, -WORLDSIZE - 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0.25, -WORLDSIZE - 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, -WORLDSIZE - 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, -WORLDSIZE - 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, -WORLDSIZE - 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.5, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, -WORLDSIZE - 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.5, -WORLDSIZE - 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.75, -WORLDSIZE - 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, -WORLDSIZE - 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, -WORLDSIZE - 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.5, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, -WORLDSIZE - 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.5, -WORLDSIZE - 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.75, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, -WORLDSIZE - 26.5);
	glEnd();

	//Corrimano, parte superiore.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 24, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER, 24, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, -0.5, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, -0.5, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER, 0, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER, -0.5, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, -0.5, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 1, 24, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER + 1, 0, -WORLDSIZE - 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER, -0.5, -WORLDSIZE - 2);
	glVertex3f(+WORLDSIZEBORDER, 23.5, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER, 24, -WORLDSIZE - 26.5);
	glVertex3f(+WORLDSIZEBORDER, 0, -WORLDSIZE - 2);
	glEnd();



	//CORRIMANI IN +Z.
	/*Corrimano 1.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, WORLDSIZE + 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 0.75, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 0.25, -2, WORLDSIZE + 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, WORLDSIZE + 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 10, WORLDSIZE + 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, WORLDSIZE + 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.75, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 0.25, 22, WORLDSIZE + 26.5);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER - 1, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER - 1, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 1, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER - 1, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER, 0, WORLDSIZE + 2);
	glEnd();


	/*Corrimano 2.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, WORLDSIZE + 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66.25, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66.75, -2, WORLDSIZE + 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, WORLDSIZE + 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.5, WORLDSIZE + 14);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 10, WORLDSIZE + 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, WORLDSIZE + 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.25, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.5, WORLDSIZE + 26);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66.75, 22, WORLDSIZE + 26.5);
	glEnd();

	//Corrimano, parte superiore.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 67, 0, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 67, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 66, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 66, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 66, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 67, -0.5, WORLDSIZE + 2);
	glVertex3f(-WORLDSIZEBORDER + 67, 23.5, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 24, WORLDSIZE + 26.5);
	glVertex3f(-WORLDSIZEBORDER + 67, 0, WORLDSIZE + 2);
	glEnd();


	/*Corrimano 3.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, WORLDSIZE + 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66.25, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66.75, -2, WORLDSIZE + 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.5, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.5, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, WORLDSIZE + 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, WORLDSIZE + 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.5, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.5, WORLDSIZE + 14);
	glVertex3f(WORLDSIZEBORDER - 66.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 10, WORLDSIZE + 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.5, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.5, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, WORLDSIZE + 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.5, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.25, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.5, WORLDSIZE + 26);
	glVertex3f(WORLDSIZEBORDER - 66.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66.75, 22, WORLDSIZE + 26.5);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66, 24, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 24, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, -0.5, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66, 23.5, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 23.5, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, -0.5, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 67, 0, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 67, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 66, -0.5, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 66, 23.5, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66, 24, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 66, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 67, -0.5, WORLDSIZE + 2);
	glVertex3f(WORLDSIZEBORDER - 67, 23.5, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 24, WORLDSIZE + 26.5);
	glVertex3f(WORLDSIZEBORDER - 67, 0, WORLDSIZE + 2);
	glEnd();
	

	/*Corrimano 4.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, WORLDSIZE + 2.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0.25, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 0.75, -2, WORLDSIZE + 2);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0.25, WORLDSIZE + 2.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 0.25, -2, WORLDSIZE + 2);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.5, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.5, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, WORLDSIZE + 14);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, WORLDSIZE + 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.5, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 11.75, WORLDSIZE + 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 10, WORLDSIZE + 14.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.5, WORLDSIZE + 14);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 11.75, WORLDSIZE + 14.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 10, WORLDSIZE + 14.5);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.5, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.5, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, WORLDSIZE + 26);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.5, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 23.75, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.75, 22, WORLDSIZE + 26.5);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.5, WORLDSIZE + 26);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 23.75, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 0.25, 22, WORLDSIZE + 26.5);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 24, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER, 24, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, -0.5, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 23.5, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER, 23.5, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, -0.5, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER, 0, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER, -0.5, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER + 1, -0.5, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER + 1, 23.5, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 1, 24, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER + 1, 0, WORLDSIZE + 2);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(+WORLDSIZEBORDER, -0.5, WORLDSIZE + 2);
	glVertex3f(+WORLDSIZEBORDER, 23.5, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER, 24, WORLDSIZE + 26.5);
	glVertex3f(+WORLDSIZEBORDER, 0, WORLDSIZE + 2);
	glEnd();




	//CORRIMANI IN -X.
	/*Corrimano 1.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER - 0.25);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER - 1);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER);
	glEnd();


	/*Corrimano 2.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER + 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 2, -2, -WORLDSIZEBORDER + 66.75);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER + 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 14.5, 10, -WORLDSIZEBORDER + 66.75);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER + 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(-WORLDSIZE - 26.5, 22, -WORLDSIZEBORDER + 66.75);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER + 67);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 67);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER + 67);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER + 67);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 67);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER + 67);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER + 66);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 66);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, -WORLDSIZEBORDER + 67);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, -WORLDSIZEBORDER + 67);
	glVertex3f(-WORLDSIZE - 26.5, 24, -WORLDSIZEBORDER + 67);
	glVertex3f(-WORLDSIZE - 2, 0, -WORLDSIZEBORDER + 67);
	glEnd();


	/*Corrimano 3.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 66.75);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 66.75);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 66.75);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER - 67);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 67);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER - 67);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 67);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 67);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 67);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER - 66);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 66);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 67);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER - 67);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER - 67);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 67);
	glEnd();


	/*Corrimano 4.*/
	//Palo in basso.	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2.5, -2, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2.5, 0.25, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 2, -2, WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 14, 10, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14, 11.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14.5, 11.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 14.5, 10, WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 26, 22, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26, 23.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26.5, 23.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(-WORLDSIZE - 26.5, 22, WORLDSIZEBORDER - 0.25);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER - 1);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER - 1);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 2, -0.5, WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 26.5, 23.5, WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 26.5, 24, WORLDSIZEBORDER);
	glVertex3f(-WORLDSIZE - 2, 0, WORLDSIZEBORDER);
	glEnd();




	//CORRIMANI IN +X.
	/*Corrimano 1.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER - 0.25);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER - 1);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER);
	glEnd();


	/*Corrimano 2.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER + 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 2, -2, -WORLDSIZEBORDER + 66.75);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER + 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 14, 11.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 14.5, 10, -WORLDSIZEBORDER + 66.75);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER + 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER + 66.25);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER + 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 26, 23.5, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, -WORLDSIZEBORDER + 66.75);
	glVertex3f(WORLDSIZE + 26.5, 22, -WORLDSIZEBORDER + 66.75);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER + 67);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 67);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER + 67);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER + 67);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 67);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER + 67);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER + 66);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 66);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, -WORLDSIZEBORDER + 67);
	glVertex3f(WORLDSIZE + 26.5, 23.5, -WORLDSIZEBORDER + 67);
	glVertex3f(WORLDSIZE + 26.5, 24, -WORLDSIZEBORDER + 67);
	glVertex3f(WORLDSIZE + 2, 0, -WORLDSIZEBORDER + 67);
	glEnd();


	/*Corrimano 3.*/
	//Palo in basso.	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 66.75);
	glEnd();

	//Palo in centro.	
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 66.75);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 66.75);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 66.25);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 66.25);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 66.75);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 66.75);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER - 67);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 67);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER - 67);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 67);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 67);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 67);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER - 66);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 66);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 67);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER - 67);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER - 67);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 67);
	glEnd();


	/*Corrimano 4.*/
	//Palo in basso.
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color2HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color2HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2.5, -2, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2.5, 0.25, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 2, -2, WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in centro.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 14, 10, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14, 11.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14.5, 11.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 14.5, 10, WORLDSIZEBORDER - 0.25);
	glEnd();

	//Palo in alto.
	//Palo Frontale.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Posteriore.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 0.25);
	glEnd();
	//Palo Sinistro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 0.75);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 0.75);
	glEnd();
	//Palo Destro.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 26, 22, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26, 23.5, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26.5, 23.75, WORLDSIZEBORDER - 0.25);
	glVertex3f(WORLDSIZE + 26.5, 22, WORLDSIZEBORDER - 0.25);
	glEnd();

	//Corrimano, parte superiore. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte inferiore. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte frontale. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER);
	glEnd();
	//Corrimano, parte sinistra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER - 1);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER - 1);
	glEnd();
	//Corrimano, parte destra. 
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 2, -0.5, WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 26.5, 23.5, WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 26.5, 24, WORLDSIZEBORDER);
	glVertex3f(WORLDSIZE + 2, 0, WORLDSIZEBORDER);
	glEnd();


	glPopMatrix();
}

/*Funzione di aggiunta dei decori in alto e delle luci dello stadio.*/
void addStadiumDecorationsAndLights()
{
	glPushMatrix();

	/*Linee di decoro nella parte alta dello stadio.*/
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color1HandRail);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Color1HandRail);
	glColor4f(0.031, 0.56, 0.745, 0.8);
	//Disegno una riga lunga in -Z.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE, 29, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZE, 29, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZE, 30, -WORLDSIZE - 9.95);
	glVertex3f(-WORLDSIZE, 30, -WORLDSIZE - 9.95);
	glEnd();
	//Disegno una riga lunga in +Z.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE, 29, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZE, 29, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZE, 30, WORLDSIZE + 9.95);
	glVertex3f(-WORLDSIZE, 30, WORLDSIZE + 9.95);
	glEnd();
	//Disegno una riga lunga in -X.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 9.95, 29, -WORLDSIZE);
	glVertex3f(-WORLDSIZE - 9.95, 30, -WORLDSIZE);
	glVertex3f(-WORLDSIZE - 9.95, 30, WORLDSIZE);
	glVertex3f(-WORLDSIZE - 9.95, 29, WORLDSIZE);
	glEnd();
	//Disegno una riga lunga in +X.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 9.95, 29, -WORLDSIZE);
	glVertex3f(WORLDSIZE + 9.95, 30, -WORLDSIZE);
	glVertex3f(WORLDSIZE + 9.95, 30, WORLDSIZE);
	glVertex3f(WORLDSIZE + 9.95, 29, WORLDSIZE);
	glEnd();


	/*Luci dello stadio.*/
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, StadioLights);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, StadioLights);
	glColor4f(1, 1, 1, 1);

	/*Luci in -Z.*/
	//Luce 1.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 16.66, 31, -WORLDSIZE - 9.95);
	glVertex3f(-WORLDSIZEBORDER + 49.98, 31, -WORLDSIZE - 9.95);
	glVertex3f(-WORLDSIZEBORDER + 49.98, 33, -WORLDSIZE - 9.95);
	glVertex3f(-WORLDSIZEBORDER + 16.66, 33, -WORLDSIZE - 9.95);
	glEnd();
	//Luce 2.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 83.33, 31, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZEBORDER - 83.33, 31, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZEBORDER - 83.33, 33, -WORLDSIZE - 9.95);
	glVertex3f(-WORLDSIZEBORDER + 83.33, 33, -WORLDSIZE - 9.95);
	glEnd();
	//Luce 3.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 16.66, 31, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZEBORDER - 49.98, 31, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZEBORDER - 49.98, 33, -WORLDSIZE - 9.95);
	glVertex3f(WORLDSIZEBORDER - 16.66, 33, -WORLDSIZE - 9.95);
	glEnd();

	/*Luci in +Z.*/
	//Luce 1.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 16.66, 31, WORLDSIZE + 9.95);
	glVertex3f(-WORLDSIZEBORDER + 49.98, 31, WORLDSIZE + 9.95);
	glVertex3f(-WORLDSIZEBORDER + 49.98, 33, WORLDSIZE + 9.95);
	glVertex3f(-WORLDSIZEBORDER + 16.66, 33, WORLDSIZE + 9.95);
	glEnd();
	//Luce 2.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZEBORDER + 83.33, 31, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZEBORDER - 83.33, 31, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZEBORDER - 83.33, 33, WORLDSIZE + 9.95);
	glVertex3f(-WORLDSIZEBORDER + 83.33, 33, WORLDSIZE + 9.95);
	glEnd();
	//Luce 3.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZEBORDER - 16.66, 31, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZEBORDER - 49.98, 31, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZEBORDER - 49.98, 33, WORLDSIZE + 9.95);
	glVertex3f(WORLDSIZEBORDER - 16.66, 33, WORLDSIZE + 9.95);
	glEnd();

	/*Luci in -X.*/
	//Luce 1.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 9.95, 31, -WORLDSIZEBORDER + 16.66);
	glVertex3f(-WORLDSIZE - 9.95, 31, -WORLDSIZEBORDER + 49.98);
	glVertex3f(-WORLDSIZE - 9.95, 33, -WORLDSIZEBORDER + 49.98);
	glVertex3f(-WORLDSIZE - 9.95, 33, -WORLDSIZEBORDER + 16.66);
	glEnd();
	//Luce 2.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 9.95, 31, -WORLDSIZEBORDER + 83.33);
	glVertex3f(-WORLDSIZE - 9.95, 31, WORLDSIZEBORDER - 83.33);
	glVertex3f(-WORLDSIZE - 9.95, 33, WORLDSIZEBORDER - 83.33);
	glVertex3f(-WORLDSIZE - 9.95, 33, -WORLDSIZEBORDER + 83.33);
	glEnd();
	//Luce 3.
	glBegin(GL_QUADS);
	glVertex3f(-WORLDSIZE - 9.95, 31, WORLDSIZEBORDER - 16.66);
	glVertex3f(-WORLDSIZE - 9.95, 31, WORLDSIZEBORDER - 49.98);
	glVertex3f(-WORLDSIZE - 9.95, 33, WORLDSIZEBORDER - 49.98);
	glVertex3f(-WORLDSIZE - 9.95, 33, WORLDSIZEBORDER - 16.66);
	glEnd();

	/*Luci in +X.*/
	//Luce 1.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 9.95, 31, -WORLDSIZEBORDER + 16.66);
	glVertex3f(WORLDSIZE + 9.95, 31, -WORLDSIZEBORDER + 49.98);
	glVertex3f(WORLDSIZE + 9.95, 33, -WORLDSIZEBORDER + 49.98);
	glVertex3f(WORLDSIZE + 9.95, 33, -WORLDSIZEBORDER + 16.66);
	glEnd();
	//Luce 2.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 9.95, 31, -WORLDSIZEBORDER + 83.33);
	glVertex3f(WORLDSIZE + 9.95, 31, WORLDSIZEBORDER - 83.33);
	glVertex3f(WORLDSIZE + 9.95, 33, WORLDSIZEBORDER - 83.33);
	glVertex3f(WORLDSIZE + 9.95, 33, -WORLDSIZEBORDER + 83.33);
	glEnd();
	//Luce 3.
	glBegin(GL_QUADS);
	glVertex3f(WORLDSIZE + 9.95, 31, WORLDSIZEBORDER - 16.66);
	glVertex3f(WORLDSIZE + 9.95, 31, WORLDSIZEBORDER - 49.98);
	glVertex3f(WORLDSIZE + 9.95, 33, WORLDSIZEBORDER - 49.98);
	glVertex3f(WORLDSIZE + 9.95, 33, WORLDSIZEBORDER - 16.66);
	glEnd();

	glPopMatrix();
}