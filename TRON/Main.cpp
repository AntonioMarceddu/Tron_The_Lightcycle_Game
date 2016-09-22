#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "DrawMethods.h"

//Field Of View.
float fov=40;

//Variabile per la stabilizzazione degli fps.
int actualTime=0, pastTime=0;

/*Funzione di inizializzazione.*/
void initGL()
{
	//Carico la texture del pavimento.
	loadFloorTexture();
	//Carico le texture delle nuvole.
	loadSkyboxTextures();
	//Inizializzo l'oggetto scene. 
	initializeScene();
	//Carico tramite ASSIMP e DevIL gli oggetti creati con blender.
	//Carico la moto del giocatore.
	loadasset("..\\Models\\LightCyclePlayer.obj");
	LoadGLTextures(scene[0]);
	//Carico la moto dell'avversario.
	loadasset("..\\Models\\LightCycleIA.obj");
	LoadGLTextures(scene[1]);

	//Carico le texture necessarie al menu'.
	MainMenuTex = loadTexBMP("..\\MenuImages\\MainMenuImage.bmp");
	newGameButtonTex = loadTexBMP("..\\MenuImages\\NewGame.bmp");
	howToPlayButtonTex = loadTexBMP("..\\MenuImages\\HowToPlay.bmp");
	creditsButtonTex = loadTexBMP("..\\MenuImages\\Credits.bmp");
	exitGameButtonTex = loadTexBMP("..\\MenuImages\\Exit.bmp");
	howToPlayMenuTex = loadTexBMP("..\\MenuImages\\HowToPlayMenu.bmp");
	creditsMenuTex = loadTexBMP("..\\MenuImages\\CreditsMenu.bmp");	
	backButtonTex = loadTexBMP("..\\MenuImages\\Back.bmp");
	//Immagini interne al gioco, di vittoria o di sconfitta.
	youWinTex = loadTexBMP("..\\MenuImages\\youWin.bmp");
	youLoseTex = loadTexBMP("..\\MenuImages\\youLose.bmp");

	//Inizializzo le openGL.	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation
	glEnable(GL_NORMALIZE);
	//Imposto i parametri per le luci 1 e 2
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
}

/*Funzione di lettura dei comandi da tastiera.*/
void keyboardCommands(unsigned char key, int x, int y)
{
	//Se sono nel gioco e non è ancora terminato abilito i comandi per muovere il giocatore.
	if((menu==1)&&(endGame == 0))
	{
		//Se ho cliccato A o D attuo una rotazione del giocatore.
		if (key == 'a' || key == 'A' || key == 'd' || key == 'D')
		{
			//Aggiungo un nuovo muro per il giocatore.
			addNewPlayersWall(key);
			//Se ho cliccato A attuo una rotazione di -90 gradi.
			if (key == 'a' || key == 'A')
			{
				angle -= M_PI / 2;
			}
			//Se ho cliccato D attuo una rotazione di 90 gradi.
			if (key == 'd' || key == 'D')
			{
				angle += M_PI / 2;
			}
			rotation = 1;
		}
		//Se ho cliccato 1, imposto la telecamera di default 
		if (key == '1')
		{
			actualCamera = 2;
			cameraRadius = 8;
			x_vrp = sin(angle)*cameraRadius;
			z_vrp = -cos(angle)*cameraRadius;
		}
		if (key == '2')
		{
			actualCamera = 5;
			cameraRadius = 12;
			x_vrp = sin(angle)*cameraRadius;
			z_vrp = -cos(angle)*cameraRadius;
		}
		if (key == '3')
		{
			actualCamera = 30;
			cameraRadius = 40;
			x_vrp = sin(angle)*cameraRadius;
			z_vrp = -cos(angle)*cameraRadius;
		}
		if (key == '4')
		{
			actualCamera = 50;
			cameraRadius = 60;
			x_vrp = sin(angle)*cameraRadius;
			z_vrp = -cos(angle)*cameraRadius;
		}
		if (key == '5')
		{
			actualCamera = 70;
			cameraRadius = 80;
			x_vrp = sin(angle)*cameraRadius;
			z_vrp = -cos(angle)*cameraRadius;
		}
	}
	//Se ho cliccato invio metto il gioco a schermo intero.
	if (key == 13)
	{
		glutFullScreen();
	}
	//Se ho cliccato esc rimetto il gioco alla sua risoluzione iniziale.
	if (key == 27)
	{
		glutPositionWindow(10, 30);
		glutReshapeWindow(1280, 720);
	}
}

/*Funzione di gestione del mouse.*/
void mouseClick(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		//Se sono nel sottomenu' principale entrero' qui.
		if (menu == 0)
		{
			//Se sono nell'area corrispondente al bottone New Game.
			if ((x >= RES_X * 3/10) && (x <= RES_X * 7/10) && (y >= RES_Y * 8/25) && (y <= RES_Y * 23/50))
			{
				printf("New Game.\n");
				//Resetto a 0 il flag per la musica nel menu' principale.
				musicStarted = 0;
				//Faccio partire la musica del gioco.
				PlaySound("..\\Audio\\End_Of_Line_Daft_Punk.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
				//Inizializzo le variabili per il primo gioco.
				initializePlayerVariables();
				//Inizializzo le variabili legate all'IA. 
				initializeAIVariables();
				//Disegno il gioco vero e proprio.
				menu = 1;
			}
			//Se sono nell'area corrispondente al bottone How To Play.
			if ((x >= RES_X * 3/10) && (x <= RES_X * 7/10) && (y >= RES_Y * 49/100) && (y <= RES_Y * 63/100))
			{
				printf("How to play.\n");
				//Disegno il sottomenu' Credits.
				menu = 2;
			}
			//Se sono nell'area corrispondente al bottone Credits.
			if ((x >= RES_X * 3/10) && (x <= RES_X * 7/10) && (y >= RES_Y * 33/50) && (y <= RES_Y * 4/5))
			{
				printf("Credits.\n");
				//Disegno il sottomenu' Credits.
				menu = 3;
			}
			//Se sono nell'area corrispondente al bottone Exit.
			if ((x >= RES_X * 3/10) && (x <= RES_X * 7/10) && (y >= RES_Y * 83/100) && (y <= RES_Y * 97/100))
			{
				printf("Exit.\n");
				exit(0);
			}
		}
		//Se sono all'interno del gioco ed è terminato con la vittoria del giocatore o dell'IA entro qui.
		if ((menu == 1) && (endGame!=0))
		{
			//Se sono nell'area corrispondente al bottone Back.
			if ((x >= RES_X * 4/10) && (x <= RES_X * 6/10) && (y >= RES_Y * 17/24) && (y <= RES_Y * 5/6))
			{
				printf("Back.\n");
				//Ripristino lo stato del gioco a non finito.
				endGame = 0;
				//Disegno nuovamente il menu' principale.
				menu = 0;
			}
		}
		//Se sono nel sottomenu' How To Play o nel sottomenu' Credits entrero' qui.
		if ((menu == 2) || (menu== 3))
		{
			//Se sono nell'area corrispondente al bottone Back.
			if ((x >= RES_X * 3/4) && (x <= RES_X * 19/20) && (y >= RES_Y * 43/50) && (y <= RES_Y * 98/100))
			{
				printf("Back");
				//Disegno nuovamente il menu' principale.
				menu = 0;
			}
		}		
	}
}

/*Funzione di reshaping dello schermo.*/
void reshapeScreen(int width, int height)
{
	//Assegno la larghezza e l'altezza dello schermo alle variabili globali RES_X e RES_Y.
	RES_X = width;
	RES_Y = height;
	//Risetto la modalità della matrice a Projection (usata per settare la prospettiva dell'utente).
	glMatrixMode(GL_PROJECTION);
	//Carico il sistema di coordinate di default.
	glLoadIdentity();
	//Adeguo la viewport alla nuova dimensione (altrimenti vedrei parte dell'immagine o tutta ma non scalata).
	glViewport(0, 0, RES_X, RES_Y);
	//Setto la prospettiva.
	gluPerspective(fov, (GLfloat)RES_X / (GLfloat)RES_Y, 0.1, 2*SKYBOXSIZE);
	//Risetto la modalità della matrice a ModelView (adatta a compiere trasformazioni sugli oggetti).
	glMatrixMode(GL_MODELVIEW);
}

//Funzione di disegno a schermo.
void display()
{
	//Se la variabile menu' e' a 0 allora disegno il menu' principale.
	if (menu == 0)
	{
		//Se la musica del menu' non è ancora partita...
		if (musicStarted == 0)
		{
			//...la avvio una volta sola: metto il flag a 1.
			musicStarted = 1;
			//Avvio la musica del menu'.
			PlaySound("..\\Audio\\CUTS_Bunsen_Burner.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		}
		drawMainMenu();
	}
	//Se la variabile menu' e' a 1 allora disegno il gioco vero e proprio.
	if (menu == 1)
	{
		drawGame();
	}
	//Se la variabile menu' e' a 0 allora disegno il menu' How To Play.
	if (menu == 2)
	{
		drawHowToPlayMenu();
	}
	//Se la variabile menu' e' a 0 allora disegno il menu' Credits.
	if( menu == 3)
	{
		drawCreditsMenu();
	}

	//Inverto i buffers.
	glutSwapBuffers();
}

/*Funzione di idle che blocca gli fps a circa 30 al secondo.*/
void idleFunc()
{
	//Leggo il tempo attuale
	actualTime = glutGet(GLUT_ELAPSED_TIME);
	//Se son passati almeno 33 millisecondi entro qui.
	if (actualTime - pastTime>33)
	{
		//Aggiorno il valore del tempo passato.
		pastTime = actualTime;
		//Chiamo la funzione display per ridisegnare nuovamente la scena.
		display();
	}
}

int main(int argc, char**argv)
{
	//Inizializzo GLUT.
	glutInit(&argc, argv);
	//Setto la modalità di disegno.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//Creo una finestra di dimensione RES_X*RES_Y e recante come etichetta TRON
	glutInitWindowSize(RES_X, RES_Y);
	glutCreateWindow("TRON");
	printf("Loading game...\n");
	//Richiamo la funzione di inizializzazione.
	initGL();
	//Setto la funzione di disegno del display.
	glutDisplayFunc(display);
	//Setto la funzione di idle.
	glutIdleFunc(idleFunc);
	//Setto la funzione dei comandi da tastiera.
	glutKeyboardFunc(keyboardCommands);
	//Setto la funzione dei comandi da mouse.
	glutMouseFunc(mouseClick);
	//setto la funzione di reshape dello schermo.
	glutReshapeFunc(reshapeScreen);
	printf("Game Loaded.\n");
	//Avvio il ciclo di disegno OpenGL.
	glutMainLoop();

	//Pulizia: chiamare 'aiReleaseImport' è importante perchè la libreria tiene risorse interne finchè la scena
	// non viene nuovamente liberata. Non fare ciò può causare leaking di risorse di sistema.
	aiReleaseImport(scene[0]);
	aiReleaseImport(scene[1]);

	return 0;
}
