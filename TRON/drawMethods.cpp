#include "DrawMethods.h"

//VARIABILI RECANTI INFORMAZIONI SULLA SCHERMATA ATTUALE.
//Risoluzione schermo (iniziale e dopo ridimensionamenti).
int RES_X = 1280, RES_Y = 720;

//Variabile di abilitazione e disabilitazione menu'.
int menu = 0;
//Variabile contenente la direzione in cui è puntata la telecamera.
int actualCamera = 2;
//Variabile di fine gioco, inizializzata a 0; se vince il giocatore viene posta ad 1, mentre se vince il computer viene posta a 2.
int endGame = 0;

//Variabile flag di rotazione.
int rotation;
//Variabile memorizzazione angolo.
float actualAngle;

//Variabile contenente l'avvio della musica del menu'.
int musicStarted = 0;

//Variabili contenenti le texture del menu'.
int MainMenuTex;
int newGameButtonTex;
int howToPlayButtonTex;
int creditsButtonTex;
int exitGameButtonTex;
int howToPlayMenuTex;
int creditsMenuTex;
int backButtonTex;
int youWinTex;
int youLoseTex;

//Definizione luci.
GLfloat LightSpecular[] = { 1, 1, 1, 0.5f };
GLfloat LightDiffuse[] = { 1, 1, 1, 0.5f };
GLfloat LightAmbient[] = { 0.0, 0.0, 0.0, 0.0f };
GLfloat LightPosition0[] = { 0.5, 0.5, 0.5, 0.0f };
GLfloat LightPosition1[] = { -0.5, 0.5, -0.5, 0.0f };

/*Funzione di disegno del menu' principale.*/
void drawMainMenu()
{
	GLfloat x1, x2;
	actualAngle = 0.0;
	rotation = 0;
	//Salvo la matrice di proiezione e quella di modello.
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//Reimposto le coordinate di identità.
	glLoadIdentity();
	//Imposto la dimensione della finestra 2D.
	gluOrtho2D(0, RES_X, RES_Y, 0);
	//Disabilito la profondita' e le facce posteriori e abilito le texture.
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	//Imposto il colore dei riquadri che disegno in seguito.
	glColor3f(1, 1, 1);

	//(0, 0) bottom left corner
	//(0, 1) upper left corner
	//(1, 0) bottom right corner
	//(1, 1) upper right corner
	//Altezza bottoni: 87,5 px (rapporto 1:1); spazio interbottone: 15 px; larghezza bottone: 400px  

	//Calcolo la dimensione dei bottoni rispetto ad x (4/10 della lunghezza dello schermo fissi).
	x1 = RES_X * 3 / 10;
	x2 = RES_X * 7 / 10;

	//Disegno il Menu' principale.
	glBindTexture(GL_TEXTURE_2D, MainMenuTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(0, 0, 0.0f);
	glTexCoord2i(0, 0); glVertex3f(0, RES_Y, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(RES_X, RES_Y, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(RES_X, 0, 0.0f);
	glEnd();
	//Disegno il pulsante New Game e applico una texture su di esso.
	glBindTexture(GL_TEXTURE_2D, newGameButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(x1, RES_Y * 8 / 25, 0.0f);
	glTexCoord2i(0, 0); glVertex3f(x1, RES_Y * 23 / 50, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(x2, RES_Y * 23 / 50, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(x2, RES_Y * 8 / 25, 0.0f);
	glEnd();
	//Disegno il pulsante How To Play e applico una texture su di esso.
	glBindTexture(GL_TEXTURE_2D, howToPlayButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(x1, RES_Y * 49 / 100, 0.0f);
	glTexCoord2i(0, 0);	glVertex3f(x1, RES_Y * 63 / 100, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(x2, RES_Y * 63 / 100, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(x2, RES_Y * 49 / 100, 0.0f);
	glEnd();
	//Disegno il pulsante Credits e applico una texture su di esso.
	glBindTexture(GL_TEXTURE_2D, creditsButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(x1, RES_Y * 33 / 50, 0.0f);
	glTexCoord2i(0, 0);	glVertex3f(x1, RES_Y * 4 / 5, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(x2, RES_Y * 4 / 5, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(x2, RES_Y * 33 / 50, 0.0f);
	glEnd();
	//Disegno il pulsante Esci e applico una texture su di esso.
	glBindTexture(GL_TEXTURE_2D, exitGameButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(x1, RES_Y * 83 / 100, 0.0f);
	glTexCoord2i(0, 0);	glVertex3f(x1, RES_Y * 97 / 100, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(x2, RES_Y * 97 / 100, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(x2, RES_Y * 83 / 100, 0.0f);
	glEnd();
	//Abilito la profondita' e le facce posteriori e disabilito le texture.
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	//Ripristino la matrice di proiezione e quella di modello.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

/*Funzione di disegno del menu' How To Play.*/
void drawHowToPlayMenu()
{
	//Salvo la matrice di proiezione e quella di modello.
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//Reimposto le coordinate di identità.
	glLoadIdentity();
	//Imposto la dimensione della finestra 2D.
	gluOrtho2D(0, RES_X, RES_Y, 0);
	//Disabilito la profondita' e le facce posteriori e abilito le texture.
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	//Imposto il colore dei riquadri che disegno in seguito.
	glColor3f(1, 1, 1);

	//Disegno il menu' How To Play.
	glBindTexture(GL_TEXTURE_2D, howToPlayMenuTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(0, 0, 0.0f);
	glTexCoord2i(0, 0); glVertex3f(0, RES_Y, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(RES_X, RES_Y, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(RES_X, 0, 0.0f);
	glEnd();
	//Disegno il pulsante Back e applico una texture su di esso.
	glBindTexture(GL_TEXTURE_2D, backButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(RES_X * 3 / 4, RES_Y * 43 / 50, 0.0f);
	glTexCoord2i(0, 0);	glVertex3f(RES_X * 3 / 4, RES_Y * 98 / 100, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(RES_X * 19 / 20, RES_Y * 98 / 100, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(RES_X * 19 / 20, RES_Y * 43 / 50, 0.0f);
	glEnd();
	//Abilito la profondita' e le facce posteriori e disabilito le texture.
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	//Ripristino la matrice di proiezione e quella di modello.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


/*Funzione di disegno del menu' Credits.*/
void drawCreditsMenu()
{
	//Salvo la matrice di proiezione e quella di modello.
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//Reimposto le coordinate di identità.
	glLoadIdentity();
	//Imposto la dimensione della finestra 2D.
	gluOrtho2D(0, RES_X, RES_Y, 0);
	//Disabilito la profondita' e le facce posteriori e abilito le texture.
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	//Imposto il colore dei riquadri che disegno in seguito.
	glColor3f(1, 1, 1);

	//Disegno il menu' Credits.
	glBindTexture(GL_TEXTURE_2D, creditsMenuTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(0, 0, 0.0f);
	glTexCoord2i(0, 0); glVertex3f(0, RES_Y, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(RES_X, RES_Y, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(RES_X, 0, 0.0f);
	glEnd();
	//Disegno il pulsante Back e applico una texture su di esso.
	glBindTexture(GL_TEXTURE_2D, backButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(RES_X * 3 / 4, RES_Y * 43 / 50, 0.0f);
	glTexCoord2i(0, 0);	glVertex3f(RES_X * 3 / 4, RES_Y * 98 / 100, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(RES_X * 19 / 20, RES_Y * 98 / 100, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(RES_X * 19 / 20, RES_Y * 43 / 50, 0.0f);
	glEnd();
	//Abilito la profondita' e le facce posteriori e disabilito le texture.
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	//Ripristino la matrice di proiezione e quella di modello.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

/*Funzione di disegno del gioco.*/
void drawGame()
{
	glPushMatrix();
	//Coloro del colore indicato nel metodo initialization l'area.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//Muovo il giocatore solo se la partita non è finita.
	if (endGame == 0)
	{
		movePlayer();
		moveAI();
		//Se la vriabile rotation è stata posta ad 1 ruoto lentamente la telecamera.
		if (rotation == 1)
		{
			//Attuo la rotazione.
			x_vrp = sin(actualAngle)*cameraRadius;
			z_vrp = -cos(actualAngle)*cameraRadius;
			//Se l'errore assoluto tra angolo attuale e quello totale è inferiore a un certo valore blocco la rotazione.
			if (fabs(actualAngle - angle) < 0.00001)
			{
				rotation = 0;
				//Mi assicuro che l'angolo attuale sia esattamente uguale a quello totale.
				actualAngle = angle;
			}
			else
			{
				//Se l'angolo attuale è inferiore a quello totale, attuo un incremento della variabile attuale.
				if (actualAngle<angle)
				{
					actualAngle = actualAngle + M_PI / 30;
				}
				//Altrimenti attuo un decremento della variabile attuale.
				else
				{
					actualAngle = actualAngle - M_PI / 30;
				}
			}
		}
	}

	//Setto la telecamera utente. Aggiungo una risposta presa da Stackoverflow per chiarezza sul GluLookAt.
	//The simple example is for rotating in xy - plane(up = z).
	//In order to circle around the object(at origin) at distance R, you use LookAt = 0, 0, 0; Position = R*cos(a), R*sin(a), 0;
	//To rotate camera instead, the equations are LookAt = x + cos(a), y + sin(a), 0; Position = x, y, 0; `
	//It's basically vector math, where the vector origin and target change place.
	gluLookAt(x_observer - x_vrp, actualCamera, z_observer - z_vrp, //La posizione della telecamera effettiva (occhio), traslata indietro.
		x_observer, 1.0, z_observer,//Posizione dell'oggetto da seguire 
		0.0, 1.0, 0.0);

	//Disegno il pavimento.
	drawFloor();
	//Disegno il cielo.
	drawSkybox();
	//Disegno i gradini dello stadio.
	drawSteps();

	//Abilito il sistema di illuminazione.
	glEnable(GL_LIGHTING);
	//Abilito le luci 0 ed 1.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//Disegno la Light Cycle del giocatore.
	drawPlayersLightCycle();
	//Disegno la Light Cycle del giocatore.
	drawAILightCycle();
	//Disabilito le luci 0 ed 1 per tracciare i muri lasciati dal giocatore. 
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	//Abilito la trasparenza.
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Disegno i corrimano sugli spalti.
	drawHandRail();
	//Disegno le decorazioni e le luci degli spalti.
	addStadiumDecorationsAndLights();
	//Funzione di aggiunta di muri attorno all'area di gioco.
	addWallsAroundTheGameArea();
	//Disegno i muri lasciati dall'IA.
	drawAIWalls();
	//Disegno i muri lasciati dal giocatore.
	drawPlayersWalls();
	//Disabilito la trasparenza.
	glDepthMask(GL_TRUE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
	//Disabilito il sistema di illuminazione.
	glDisable(GL_LIGHTING);

	//Se il gioco non è ancora terminato, verifico le collisioni del giocatore con i muri lasciati da se stesso e con quelli
	//periferici del gioco (solo se il gioco non è ancora finito).
	if (endGame == 0)
	{
		endGame = verifyPlayerCollision();
		if (endGame == 0)
		{
			endGame = verifyAICollision();
		}
	}
	//Altrimenti scrivo un messaggio a schermo.
	else
	{
		outputEndGame();
	}
	glPopMatrix();
}

/*Funzione di disegno al termine del gioco.*/
void outputEndGame()
{
	int len, i;
	//Salvo la matrice di proiezione e quella di modello.
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//Reimposto le coordinate di identità.
	glLoadIdentity();
	//Imposto la dimensione della finestra 2D.
	gluOrtho2D(0.0, RES_X, RES_Y, 0.0);
	//Disabilito la profondita' e le facce posteriori e abilito le texture.
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	//Imposto il colore dei riquadri che disegno in seguito.
	glColor3f(1, 1, 1);

	//(0, 0) bottom left corner
	//(0, 1) upper left corner
	//(1, 0) bottom right corner
	//(1, 1) upper right corner

	//Disegno o la scritta "YOU WIN!" o la scritta "YOU LOSE!" in base a chi ha vinto la partita.
	if (endGame == 1)
	{
		glBindTexture(GL_TEXTURE_2D, youWinTex);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, youLoseTex);
	}
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3i(RES_X * 1 / 4, RES_Y * 3 / 8, 0.0f);
	glTexCoord2i(0, 0);	glVertex3i(RES_X * 1 / 4, RES_Y * 5 / 8, 0.0f);
	glTexCoord2i(1, 0); glVertex3i(RES_X * 3 / 4, RES_Y * 5 / 8, 0.0f);
	glTexCoord2i(1, 1); glVertex3i(RES_X * 3 / 4, RES_Y * 3 / 8, 0.0f);
	glEnd();
	//Disegno il pulsante back per tornare al menu' principale.
	glBindTexture(GL_TEXTURE_2D, backButtonTex);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1); glVertex3f(RES_X * 4 / 10, RES_Y * 17 / 24, 0.0f);
	glTexCoord2i(0, 0);	glVertex3f(RES_X * 4 / 10, RES_Y * 5 / 6, 0.0f);
	glTexCoord2i(1, 0); glVertex3f(RES_X * 6 / 10, RES_Y * 5 / 6, 0.0f);
	glTexCoord2i(1, 1); glVertex3f(RES_X * 6 / 10, RES_Y * 17 / 24, 0.0f);
	glEnd();

	//Abilito la profondita' e le facce posteriori e disabilito le texture.
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	//Ripristino la matrice di proiezione e quella di modello.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}