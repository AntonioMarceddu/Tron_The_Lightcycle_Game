#include <stdlib.h>
#include <time.h>
#include "GL/glut.h"
#include "PlayerMethods.h"

//Variabile di rotazione AI.
float angleAI;
//Variabili di posizione dell'IA.
float x_AI, z_AI;

//Vettore di dimensione fissa contenente le ultime tre rotazioni effettuate dall'IA.
//Il vettore contiene char fissati ad 'a' se la IA gira a sinistra e 'd' se la IA gira a destra.
char directions[3];

//Variabili legate ai muri creati dall'IA.
vector<vector<float> > AIWallsArray;
int sizeAIWallsArray;

//Variabili legate alla collisione anteriore del giocatore.
float xAILightCycleCollision = 0;
float zAILightCycleCollision = 0;

//Implemento un meccanismo a parità anche per la IA, come fatto per il giocatore.
int AIParity;

//Implemento due contatori a refresh per determinate scelte dell'IA.
int counterForAIDecision1;
int counterForAIDecision2;

//Variabili di luminosità dei muri dell'IA.
GLfloat darkOrangeWalls[] = { 0.95, 0.7148, 0.1367, 0.4 };
GLfloat lightOrangeWalls[] = { 0.9766, 0.996, 0.0937, 0.9 };

//Funzione di inizializzazione delle variabili del giocatore.
void initializeAIVariables()
{
	//Inizializzo il generatore di numeri random.
	srand(time(NULL));
	//Creo una nuova matrice dinamica. 
	vector<vector<float> > newVariable;
	//Resetto le variabili per la posizione dell'IA.
	x_AI = 0;
	z_AI = -90.0;
	angleAI = 0;
	//Inizializzo la matrice contenente i muri creati dall'IA.
	newVariable.resize(1);
	newVariable[0].resize(NUMCOL);
	//Swappo la variabile precedente con newVariable (precedentemente creata) per assicurare una pulizia completa della variabile.
	AIWallsArray.clear();
	AIWallsArray.swap(newVariable);
	//Azzero il numero di muri.
	sizeAIWallsArray = 0;
	//Inizializzo il primo muro alla posizione iniziale dell'IA.
	AIWallsArray[0][0] = x_AI;
	AIWallsArray[0][1] = z_AI;
	//Resetto la parità.
	AIParity = 0;
	//Creo un nuovo vettore dinamico. 
	directions[0] = 'd';
	directions[1] = 'a';
	directions[2] = 'd';
	//Resetto i contatori per le decisioni dell'IA.
	counterForAIDecision1 = 0;
	counterForAIDecision2 = 0;
}

//Funzione che aggiunge un nuovo muro al giocatore se cambia direzione.
void addNewAIWall()
{
	//Incremento il numero di muri presenti ed inizializzo una nuova riga.
	sizeAIWallsArray++;
	AIWallsArray.resize(sizeAIWallsArray + 1);
	AIWallsArray[sizeAIWallsArray].resize(NUMCOL);
	//Verifico parità e direzione del moto in modo da creare un muro che inizia esattamente dove l'altro finisce.
	//Se la IA si stava muovendo parallelamente all'asse Z.
	if (AIParity == 0)
	{
		//Devo aggiungere un nuovo muro: cambio il valore della parità (ora la IA si muoverà parallelamente all'asse z).
		AIParity = 1;
		//Segno la coordinata che resta fissa (Z).
		AIWallsArray[sizeAIWallsArray][1] = AIWallsArray[sizeAIWallsArray - 1][3];
		//Ora verifico se la IA si stava muovendo dalle Z negative verso quelle positive o viceversa.
		//Se si stava muovendo verso le Z positive entro qui. 
		if (AIWallsArray[sizeAIWallsArray - 1][1] <= AIWallsArray[sizeAIWallsArray - 1][3])
		{
			//Setto i valori iniziali del nuovo muro: se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				AIWallsArray[sizeAIWallsArray][0] = AIWallsArray[sizeAIWallsArray - 1][2] + C;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				AIWallsArray[sizeAIWallsArray][0] = AIWallsArray[sizeAIWallsArray - 1][2] - C;
			}
		}
		else
		{
			//Setto i valori iniziali del nuovo muro: se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				AIWallsArray[sizeAIWallsArray][0] = AIWallsArray[sizeAIWallsArray - 1][2] - C;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				AIWallsArray[sizeAIWallsArray][0] = AIWallsArray[sizeAIWallsArray - 1][2] + C;
			}
		}
	}
	//Se invece si stava muovendo parallelamente all'asse X.
	else
	{
		//Devo aggiungere un nuovo muro: cambio il valore della parità (ora la IA si muoverà parallelamente all'asse z).
		AIParity = 0;
		//Segno la coordinata che resta fissa (X).
		AIWallsArray[sizeAIWallsArray][0] = AIWallsArray[sizeAIWallsArray - 1][2];
		//Ora verifico se la IA si stava muovendo dalle X negative verso quelle positive o viceversa.
		//Se si stava muovendo verso le X positive entro qui. 
		if (AIWallsArray[sizeAIWallsArray - 1][0] <= AIWallsArray[sizeAIWallsArray - 1][2])
		{
			//Setto i valori iniziali del nuovo muro: se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				AIWallsArray[sizeAIWallsArray][1] = AIWallsArray[sizeAIWallsArray - 1][3] - C;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				AIWallsArray[sizeAIWallsArray][1] = AIWallsArray[sizeAIWallsArray - 1][3] + C;
			}
		}
		else
		{
			//Setto i valori iniziali del nuovo muro: se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				AIWallsArray[sizeAIWallsArray][1] = AIWallsArray[sizeAIWallsArray - 1][3] + C;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				AIWallsArray[sizeAIWallsArray][1] = AIWallsArray[sizeAIWallsArray - 1][3] - C;
			}
		}
	}
	//Setto i valori finali del nuovo muro.
	AIWallsArray[sizeAIWallsArray][2] = AIWallsArray[sizeAIWallsArray - 1][2];
	AIWallsArray[sizeAIWallsArray][3] = AIWallsArray[sizeAIWallsArray - 1][3];
}

//Metodo che salva nella posizione 2 del vettore directions la nuova direzione e swappa le precedenti
//in modo tale che nella posizione 2 ci sia sempre il valore piu' aggiornato.
void updateDirections(char dir)
{
	directions[0] = directions[1];
	directions[1] = directions[2];
	directions[2] = dir;
}

//Metodo che permette la rotazione della IA a sinistra.
void AITurnLeft()
{
	printf("AI Turn: Left.\n");
	//Salvo la direzione scelta.
	updateDirections('a');
	//Segno la variazione angolare apportata dalla rotazione.
	angleAI -= M_PI / 2;
	//Aggiungo un nuovo muro.
	addNewAIWall();
}

//Metodo che permette la rotazione della IA a destra.
void AITurnRight()
{
	printf("AI Turn: Right.\n");
	//Salvo la direzione scelta.
	updateDirections('d');
	//Segno la variazione angolare apportata dalla rotazione.
	angleAI += M_PI / 2;
	//Aggiungo un nuovo muro.
	addNewAIWall();
}

//Metodo che sceglie di far girare casualmente la IA a destra o sinistra. 
void RandomAIRotationLeftOrRight()
{
	//Tiro un numero casuale per scegliere di ruotare a destra o sinistra.
	if ((rand() % 100) < 50)
	{
		//Se la dimensione dei muri è almeno pari a 4 (ho svoltato 3 volte o piu' in precedenza) entro qui.
		if (sizeAIWallsArray>=3)
		{
			//Algoritmo semplificato anti-chiusura.
			//    |  |d__a   <- Obbligo di girare a destra dopo 3 volte che giro a sinistra (e viceversa).
			//    |     |       In questo modo evito che la IA si chiuda da sola.
			//   a|_____|a
			//Se le 3 volte precedenti la IA ha svoltato a sinistra, allora la faccio svoltare a destra.
			if ((directions[2] == 'a') && (directions[1] == 'a') && (directions[0] == 'a'))
			{
				printf(("AI message: I've turned three times to the left. I'll turn right now.\n"));
				AITurnRight();
			}
			//Altrimenti giro a sinistra.
			else
			{
				AITurnLeft();
			}
		}
		//Altrimenti giro a sinistra.
		else
		{
			AITurnLeft();
		}		
	}
	else
	{
		//Se la dimensione dei muri è almeno pari a 4 (ho svoltato 3 volte o piu' in precedenza) entro qui.
		if (sizeAIWallsArray >= 3)
		{
			//Se le 3 volte precedenti la IA ha svoltato a destra, allora la faccio svoltare a sinistra.
			if ((directions[2] == 'd') && (directions[1] == 'd') && (directions[0] == 'd'))
			{
				printf(("AI message: I've turned three times to the right. I'll turn left now.\n"));
				AITurnLeft();
			}
			//Altrimenti giro a destra.
			else
			{
				AITurnRight();
			}
		}
		//Altrimenti giro a destra.
		else
		{
			AITurnRight();
		}
	}
}

//Funzione che viene richiamata quando occorre la IA deve decidere se girare con una certa percentuale.
void chooseToTurnWithACertainPercentage(int percentage, char* message)
{
	//Decido di girare solo se il valore calcolato casualmente tra 0 e 100 è minore di percentage.
	if ((rand() % 100) < percentage)
	{
		printf(message);
		RandomAIRotationLeftOrRight();
	}
}

//Funzione di disegno dei muri lasciati dall'IA.
void drawAIWalls()
{
	int i;
	//Creo le variabili di offset dello spessore cx e cz, in modo da creare due muri paralleli.
	float cx, cz;
	//Ciclo di disegno muri giocatore.
	for (i = 0; i <= sizeAIWallsArray; i++)
	{
		//Resetto i valori delle variabili cx e cz.
		cx = 0;
		cz = 0;
		//Verifico la parità per settare cx e cz.
		if (i>0)
		{
			//Se la parità è 0 mi sto muovendo lungo z: setto cx a C in modo da avere un offset per creare uno 
			//spessore del muro rispetto alla coordinata z.
			if (AIParity == 0)
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
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, darkOrangeWalls);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkOrangeWalls);
		glColor4f(0.102, 0.86, 0.98, 0.4);
		//Disegno un muro leggermente a sinistra.
		glBegin(GL_QUADS);
		glVertex3f(AIWallsArray[i][0] - cx, WALLMAXHEIGHT, AIWallsArray[i][1] - cz);
		glVertex3f(AIWallsArray[i][2] - cx, WALLMAXHEIGHT, AIWallsArray[i][3] - cz);
		glVertex3f(AIWallsArray[i][2] - cx, WALLMINHEIGHT, AIWallsArray[i][3] - cz);
		glVertex3f(AIWallsArray[i][0] - cx, WALLMINHEIGHT, AIWallsArray[i][1] - cz);
		glEnd();
		//Disegno un muro leggermente a destra.
		glBegin(GL_QUADS);
		glVertex3f(AIWallsArray[i][0] + cx, WALLMAXHEIGHT, AIWallsArray[i][1] + cz);
		glVertex3f(AIWallsArray[i][2] + cx, WALLMAXHEIGHT, AIWallsArray[i][3] + cz);
		glVertex3f(AIWallsArray[i][2] + cx, WALLMINHEIGHT, AIWallsArray[i][3] + cz);
		glVertex3f(AIWallsArray[i][0] + cx, WALLMINHEIGHT, AIWallsArray[i][1] + cz);
		glEnd();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lightOrangeWalls);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightOrangeWalls);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lightOrangeWalls);
		glColor4f(0.79, 0.945, 0.985, 0.9);
		//Disegno un muro in alto.
		glBegin(GL_QUADS);
		glVertex3f(AIWallsArray[i][0] + cx, WALLMAXHEIGHT, AIWallsArray[i][1] + cz);
		glVertex3f(AIWallsArray[i][2] + cx, WALLMAXHEIGHT, AIWallsArray[i][3] + cz);
		glVertex3f(AIWallsArray[i][2] - cx, WALLMAXHEIGHT, AIWallsArray[i][3] - cz);
		glVertex3f(AIWallsArray[i][0] - cx, WALLMAXHEIGHT, AIWallsArray[i][1] - cz);
		glEnd();
		//Disegno un muro in basso.
		glBegin(GL_QUADS);
		glVertex3f(AIWallsArray[i][0] + cx, WALLMINHEIGHT, AIWallsArray[i][1] + cz);
		glVertex3f(AIWallsArray[i][2] + cx, WALLMINHEIGHT, AIWallsArray[i][3] + cz);
		glVertex3f(AIWallsArray[i][2] - cx, WALLMINHEIGHT, AIWallsArray[i][3] - cz);
		glVertex3f(AIWallsArray[i][0] - cx, WALLMINHEIGHT, AIWallsArray[i][1] - cz);
		glEnd();
		//Disegno un muro nella parte anteriore.
		glBegin(GL_QUADS);
		glVertex3f(AIWallsArray[i][2] - cx, WALLMAXHEIGHT, AIWallsArray[i][3] - cz);
		glVertex3f(AIWallsArray[i][2] + cx, WALLMAXHEIGHT, AIWallsArray[i][3] + cz);
		glVertex3f(AIWallsArray[i][2] + cx, WALLMINHEIGHT, AIWallsArray[i][3] + cz);
		glVertex3f(AIWallsArray[i][2] - cx, WALLMINHEIGHT, AIWallsArray[i][3] - cz);
		glEnd();
		//Disegno un muro nella parte posteriore.
		glBegin(GL_QUADS);
		glVertex3f(AIWallsArray[i][0] - cx, WALLMAXHEIGHT, AIWallsArray[i][1] - cz);
		glVertex3f(AIWallsArray[i][0] + cx, WALLMAXHEIGHT, AIWallsArray[i][1] + cz);
		glVertex3f(AIWallsArray[i][0] + cx, WALLMINHEIGHT, AIWallsArray[i][1] + cz);
		glVertex3f(AIWallsArray[i][0] - cx, WALLMINHEIGHT, AIWallsArray[i][1] - cz);
		glEnd();
		glColor4f(1, 0, 0, 1);
		//Disegno un muro nella parte posteriore (collisioni).
		//glBegin(GL_QUADS);
		//glVertex3f(xAILightCycleCollision -cx, 0, zAILightCycleCollision - cz);
		//glVertex3f(xAILightCycleCollision + cx, 0, zAILightCycleCollision + cz);
		//glVertex3f(xAILightCycleCollision + cx, WALLMINHEIGHT, zAILightCycleCollision + cz);
		//glVertex3f(xAILightCycleCollision - cx, WALLMINHEIGHT, zAILightCycleCollision - cz);
		//glEnd();
		//glBegin(GL_QUADS);
		//glVertex3f(x_AI - cx, 0, z_AI - cz);
		//glVertex3f(x_AI + cx, 0, z_AI + cz);
		//glVertex3f(x_AI + cx, WALLMINHEIGHT, z_AI + cz);
		//glVertex3f(x_AI - cx, WALLMINHEIGHT, z_AI - cz);
		//glEnd();
		glPopMatrix();
	}
}