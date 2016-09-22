#include <stdlib.h>
#include "GL/glut.h"
#include "PlayerMethods.h"


//Variabili legate ai movimenti del giocatore.
//Angolo di rotazione della telecamera.
float angle;
//Posizione x e z della telecamera (osservatore).
float x_observer, z_observer;
//Vettore indicante la direzione della telecamera (posizione del VRP - View Reference Point).
float x_vrp, z_vrp;

//Variabile contenente la distanza della telecamera dal giocatore.
int cameraRadius=8;

//Variabili legate ai muri creati dal giocatore.
vector<vector<float> > playersWallsArray;
int sizePlayersWallsArray;

//Variabili legate alla collisione anteriore del giocatore.
float xLightCycleCollision = 0;
float zLightCycleCollision = 0;

//Implemento un meccanismo a parità, dovuto al fatto che i movimenti sono implementati a rotazioni di 90 gradi: come inizia il 
//gioco il giocatore si muoverà sempre parallelamente all'asse Z, come ruota si muoverà invece parallelamente all'asse X e così 
//via: si può quindi notare che per valori di i pari la Z è variabile e la X fissa, viceversa per valori dispari. Creo quindi
//una variabile PlayerParity che porrò a 0 quando il giocatore è parallelo all'asse Z e ad 1 quando è parallelo all'asse X.
int playerParity;

//Salvo il tasto premuto per ultimo.
char lastKeyPressed='a';

//Variabili di luminosità dei muri del giocatore.
GLfloat darkBlueWalls[] = { 0.102, 0.86, 0.98, 0.4 };
GLfloat lightBlueWalls[] = { 0.79, 0.945, 0.985, 0.9 };

/*Funzione di inizializzazione delle variabili del giocatore.*/
void initializePlayerVariables()
{
	vector<vector<float> > newVariable;
	//Resetto le variabili per la posizione del giocatore.
	angle = 0.0;
	//Il giocatore partirà da una posizione pari a (0,90) (in basso a sinistra della mappa).
	x_observer = 0; 
	z_observer = 90.0;
	//La telecamera sarà puntata alle sue spalle.
	x_vrp = 0;
	z_vrp = -cameraRadius;
	//Inizializzo la matrice contenente i muri creati dal giocatore.
	newVariable.resize(1);
	newVariable[0].resize(NUMCOL);
	//Swappo la variabile precedente con newVariable (precedentemente creata) per assicurare una pulizia completa della variabile.
	playersWallsArray.clear();
	playersWallsArray.swap(newVariable);
	//Azzero il numero di muri.
	sizePlayersWallsArray = 0;
	//Inizializzo il primo muro alla posizione iniziale del giocatore.
	playersWallsArray[0][0] = x_observer;
	playersWallsArray[0][1] = z_observer;
	//Resetto la parità.
	playerParity = 0;
}

/*Funzione di movimento automatico del giocatore.*/
void movePlayer()
{
	//Verifico la parità: se mi sto muovendo parallelamente all'asse Z entro qui.
	if (playerParity == 0)
	{
		//Se mi sto muovendo dalle Z positive verso quelle negative entro qui.
		if (playersWallsArray[sizePlayersWallsArray][3] >= playersWallsArray[sizePlayersWallsArray][1])
		{
			z_observer = z_observer + SPEED;
		}
		//Altrimenti se mi sto muovendo dalle Z negative verso quelle positive entro qui.
		else
		{
			z_observer = z_observer - SPEED;
		}
		//Aggiorno la posizione del muro alle spalle del giocatore (relativa solo a Z).
		playersWallsArray[sizePlayersWallsArray][3] = z_observer;
	}//Mentre se mi sto muovendo parallelamente all'asse X entro qui.
	else
	{
		//Se mi sto muovendo dalle X positive verso quelle negative entro qui.
		if (playersWallsArray[sizePlayersWallsArray][2] >= playersWallsArray[sizePlayersWallsArray][0])
		{
			x_observer = x_observer + SPEED;
		}
		//Altrimenti se mi sto muovendo dalle X negative verso quelle positive entro qui.
		else
		{
			x_observer = x_observer - SPEED;
		}
		//Aggiorno la posizione del muro alle spalle del giocatore (relativa solo a X).
		playersWallsArray[sizePlayersWallsArray][2] = x_observer;
	}
	return;
}

/*Funzione che aggiunge un nuovo muro al giocatore se cambia direzione.*/
void addNewPlayersWall(char key)
{
	//Incremento il numero di muri presenti ed inizializzo una nuova riga.
	sizePlayersWallsArray++;
	playersWallsArray.resize(sizePlayersWallsArray+1);
	playersWallsArray[sizePlayersWallsArray].resize(NUMCOL);
	//Salvo l'ultimo tasto premuto.
	lastKeyPressed = key;
	//Verifico parità e direzione del moto in modo da creare un muro che inizia esattamente dove l'altro finisce.
	//Se mi stavo muovendo parallelamente all'asse z.
	if (playerParity == 0)
	{
		//Devo aggiungere un nuovo muro: cambio il valore della parità (ora mi muoverò parallelamente all'asse x).
		playerParity = 1;
		//Segno la coordinata che resta fissa (Z).
		playersWallsArray[sizePlayersWallsArray][1] = playersWallsArray[sizePlayersWallsArray - 1][3];
		//Ora verifico se mi stavo muovendo dalle z negative verso quelle positive o viceversa.
		//Se mi stavo muovendo verso le z positive entro qui. 
		if (playersWallsArray[sizePlayersWallsArray-1][1]<=playersWallsArray[sizePlayersWallsArray - 1][3])
		{
			//Setto i valori iniziali del nuovo muro: se ho girato a destra entro qui.
			if (key == 'd'|| key == 'D')
			{
				playersWallsArray[sizePlayersWallsArray][0] = playersWallsArray[sizePlayersWallsArray - 1][2] + C;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				playersWallsArray[sizePlayersWallsArray][0] = playersWallsArray[sizePlayersWallsArray - 1][2] - C;
			}
		}
		else
		{
			//Setto i valori iniziali del nuovo muro: se ho girato a destra entro qui.
			if (key == 'd' || key == 'D')
			{
				playersWallsArray[sizePlayersWallsArray][0] = playersWallsArray[sizePlayersWallsArray - 1][2] - C;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				playersWallsArray[sizePlayersWallsArray][0] = playersWallsArray[sizePlayersWallsArray - 1][2] + C;
			}
		}
	}
	//Se invece mi stavo muovendo parallelamente all'asse x.
	else
	{
		//Devo aggiungere un nuovo muro: cambio il valore della parità (ora mi muoverò parallelamente all'asse z).
		playerParity = 0;
		//Segno la coordinata che resta fissa (X).
		playersWallsArray[sizePlayersWallsArray][0] = playersWallsArray[sizePlayersWallsArray - 1][2];
		//Ora verifico se mi stavo muovendo dalle x negative verso quelle positive o viceversa.
		//Se mi stavo muovendo verso le x positive entro qui. 
		if (playersWallsArray[sizePlayersWallsArray - 1][0] <= playersWallsArray[sizePlayersWallsArray - 1][2])
		{
			//Setto i valori iniziali del nuovo muro: se ho girato a destra entro qui.
			if (key == 'd' || key == 'D')
			{
				playersWallsArray[sizePlayersWallsArray][1] = playersWallsArray[sizePlayersWallsArray - 1][3] - C;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				playersWallsArray[sizePlayersWallsArray][1] = playersWallsArray[sizePlayersWallsArray - 1][3] + C;
			}
		}
		else
		{
			//Setto i valori iniziali del nuovo muro: se ho girato a destra entro qui.
			if (key == 'd' || key == 'D')
			{
				playersWallsArray[sizePlayersWallsArray][1] = playersWallsArray[sizePlayersWallsArray - 1][3] + C;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				playersWallsArray[sizePlayersWallsArray][1] = playersWallsArray[sizePlayersWallsArray - 1][3] - C;
			}
		}
	}
	//Setto i valori finali del nuovo muro.
	playersWallsArray[sizePlayersWallsArray][2] = playersWallsArray[sizePlayersWallsArray - 1][2];
	playersWallsArray[sizePlayersWallsArray][3] = playersWallsArray[sizePlayersWallsArray - 1][3];
}


/*Funzione di disegno dei muri lasciati dal giocatore.*/
void drawPlayersWalls()
{
	int i;
	//Creo le variabili di offset dello spessore cx e cz, in modo da creare due muri paralleli.
	float cx, cz;
	//Ciclo di disegno muri giocatore.
	for (i = 0; i <= sizePlayersWallsArray; i++)
	{
		//Resetto i valori delle variabili cx e cz.
		cx = 0;
		cz = 0;
		//Verifico la parità per settare cx e cz.
		if (i>0)
		{
			//Se la parità è 0 mi sto muovendo lungo z: setto cx a C in modo da avere un offset per creare uno 
			//spessore del muro rispetto alla coordinata z.
			if (playerParity==0)
			{
				cx = C;
			}
			//Altrimenti setto il valore di cz.
			else
			{
				cz = C;
			}
		}
		//Per i=0 si parte sempre dal primo muro: qui cambia solo z, quindi vario cx.
		else
		{
			cx = C;
		}
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, darkBlueWalls);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkBlueWalls);
		glColor4f(0.102, 0.86, 0.98, 0.3);
		//Disegno un muro leggermente a sinistra.
		glBegin(GL_QUADS);
		glVertex3f(playersWallsArray[i][0] - cx, WALLMAXHEIGHT, playersWallsArray[i][1] - cz); 
		glVertex3f(playersWallsArray[i][2] - cx, WALLMAXHEIGHT, playersWallsArray[i][3] - cz);
		glVertex3f(playersWallsArray[i][2] - cx, WALLMINHEIGHT, playersWallsArray[i][3] - cz); 
		glVertex3f(playersWallsArray[i][0] - cx, WALLMINHEIGHT, playersWallsArray[i][1] - cz);
		glEnd();
		//Disegno un muro leggermente a destra.
		glBegin(GL_QUADS);
		glVertex3f(playersWallsArray[i][0] + cx, WALLMAXHEIGHT, playersWallsArray[i][1] + cz); 
		glVertex3f(playersWallsArray[i][2] + cx, WALLMAXHEIGHT, playersWallsArray[i][3] + cz);
		glVertex3f(playersWallsArray[i][2] + cx, WALLMINHEIGHT, playersWallsArray[i][3] + cz); 
		glVertex3f(playersWallsArray[i][0] + cx, WALLMINHEIGHT, playersWallsArray[i][1] + cz);
		glEnd();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lightBlueWalls);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightBlueWalls);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lightBlueWalls);
		glColor4f(0.79, 0.945, 0.985, 0.9);
		//Disegno un muro in alto.
		glBegin(GL_QUADS);
		glVertex3f(playersWallsArray[i][0] + cx, WALLMAXHEIGHT, playersWallsArray[i][1] + cz);
		glVertex3f(playersWallsArray[i][2] + cx, WALLMAXHEIGHT, playersWallsArray[i][3] + cz);
		glVertex3f(playersWallsArray[i][2] - cx, WALLMAXHEIGHT, playersWallsArray[i][3] - cz);
		glVertex3f(playersWallsArray[i][0] - cx, WALLMAXHEIGHT, playersWallsArray[i][1] - cz);
		glEnd();
		//Disegno un muro in basso.
		glBegin(GL_QUADS);
		glVertex3f(playersWallsArray[i][0] + cx, WALLMINHEIGHT, playersWallsArray[i][1] + cz);
		glVertex3f(playersWallsArray[i][2] + cx, WALLMINHEIGHT, playersWallsArray[i][3] + cz);
		glVertex3f(playersWallsArray[i][2] - cx, WALLMINHEIGHT, playersWallsArray[i][3] - cz);
		glVertex3f(playersWallsArray[i][0] - cx, WALLMINHEIGHT, playersWallsArray[i][1] - cz);
		glEnd();
		//Disegno un muro nella parte anteriore.
		glBegin(GL_QUADS);
		glVertex3f(playersWallsArray[i][2] - cx, WALLMAXHEIGHT, playersWallsArray[i][3] - cz);
		glVertex3f(playersWallsArray[i][2] + cx, WALLMAXHEIGHT, playersWallsArray[i][3] + cz);
		glVertex3f(playersWallsArray[i][2] + cx, WALLMINHEIGHT, playersWallsArray[i][3] + cz);
		glVertex3f(playersWallsArray[i][2] - cx, WALLMINHEIGHT, playersWallsArray[i][3] - cz);
		glEnd();
		//Disegno un muro nella parte posteriore.
		glBegin(GL_QUADS);
		glVertex3f(playersWallsArray[i][0] - cx, WALLMAXHEIGHT, playersWallsArray[i][1] - cz);
		glVertex3f(playersWallsArray[i][0] + cx, WALLMAXHEIGHT, playersWallsArray[i][1] + cz);
		glVertex3f(playersWallsArray[i][0] + cx, WALLMINHEIGHT, playersWallsArray[i][1] + cz);
		glVertex3f(playersWallsArray[i][0] - cx, WALLMINHEIGHT, playersWallsArray[i][1] - cz);
		glEnd();

		//glColor3f(1, 0, 0);
		//Disegno un muro nella parte posteriore e anteriore(verifica collisioni).
		//glBegin(GL_QUADS);
		//glVertex3f(xLightCycleCollision -cx, 1, zLightCycleCollision - cz);
		//glVertex3f(xLightCycleCollision + cx, 1, zLightCycleCollision + cz);
		//glVertex3f(xLightCycleCollision + cx, WALLMINHEIGHT, zLightCycleCollision + cz);
		//glVertex3f(xLightCycleCollision - cx, WALLMINHEIGHT, zLightCycleCollision - cz);
		//glEnd();
		//glBegin(GL_QUADS);
		//glVertex3f(x_observer - cx, 1, z_observer - cz);
		//glVertex3f(x_observer + cx, 1, z_observer + cz);
		//glVertex3f(x_observer + cx, WALLMINHEIGHT, z_observer + cz);
		//glVertex3f(x_observer - cx, WALLMINHEIGHT, z_observer - cz);
		//glEnd();
		glPopMatrix();
	}
}