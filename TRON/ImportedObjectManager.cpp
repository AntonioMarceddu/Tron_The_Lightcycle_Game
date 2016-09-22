#include "importedObjectManager.h"

//Costante di traslazione della LightCycle rispetto al muro.
#define LIGHTCYCLETRANSLCONST 2.6
//Dev'essere piu' grande di LIGHTCYCLETRANSLCONST (lo metto al doppio).
#define COLLISIONTRANSLCONST 5 

int listCreated=0;

/*Funzione di disegno della lightcycle del giocatore.*/
void drawPlayersLightCycle()
{
	glPushMatrix();

	//Se mi sto muovendo parallelamente all'asse z entro qui.
	if (playerParity == 0)
	{
		//Assegno ad X la posizione centrale del muro che sto costruendo.
		xLightCycleCollision = x_observer;
		//Se la direzione di crescita è positiva entro qui.
		if (playersWallsArray[sizePlayersWallsArray][3] >= playersWallsArray[sizePlayersWallsArray][1])
		{
			//Ora devo calcolare la traslazione rispetto a Z, sia per disegnare la moto che per le collisioni. 
			//Se ho girato a destra entro qui.
			if (lastKeyPressed == 'd' || lastKeyPressed == 'D')
			{
				//Posiziono la moto.
				glTranslatef(x_observer, -1, z_observer + LIGHTCYCLETRANSLCONST);
				//Aggiorno la posizione frontale della moto per le collisioni.
				zLightCycleCollision = z_observer + COLLISIONTRANSLCONST;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_observer, -1, z_observer + LIGHTCYCLETRANSLCONST);
				//Aggiorno la posizione frontale della moto per le collisioni.
				zLightCycleCollision = z_observer + COLLISIONTRANSLCONST;
			}
		}
		//Altrimenti entro qui.
		else
		{
			//Se ho girato a destra entro qui.
			if (lastKeyPressed == 'd' || lastKeyPressed == 'D')
			{
				
				//Posiziono la moto.
				glTranslatef(x_observer, -1, z_observer - LIGHTCYCLETRANSLCONST);
				//Aggiorno la posizione frontale della moto per le collisioni.
				zLightCycleCollision = z_observer - COLLISIONTRANSLCONST;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_observer, -1, z_observer - LIGHTCYCLETRANSLCONST);
				//Aggiorno la posizione frontale della moto per le collisioni.
				zLightCycleCollision = z_observer - COLLISIONTRANSLCONST;
			}
		}
	}
	//Se invece mi stavo muovendo parallelamente all'asse x.
	else
	{
		//Assegno a Z la posizione centrale del muro che sto costruendo.
		zLightCycleCollision = z_observer;
		//Se la direzione di crescita è positiva entro qui.
		if (playersWallsArray[sizePlayersWallsArray][2] >= playersWallsArray[sizePlayersWallsArray][0])
		{
			//Ora devo calcolare la traslazione rispetto a X, sia per disegnare la moto che per le collisioni.
			//Se ho girato a destra entro qui.
			if (lastKeyPressed == 'd' || lastKeyPressed == 'D')
			{
				//Posiziono la moto.
				glTranslatef(x_observer + LIGHTCYCLETRANSLCONST, -1, z_observer);
				xLightCycleCollision = x_observer + COLLISIONTRANSLCONST;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_observer + LIGHTCYCLETRANSLCONST, -1, z_observer);
				xLightCycleCollision = x_observer + COLLISIONTRANSLCONST;
			}
		}
		//Altrimenti entro qui.
		else
		{
			//Se ho girato a destra entro qui.
			if (lastKeyPressed == 'd' || lastKeyPressed == 'D')
			{
				//Posiziono la moto.
				glTranslatef(x_observer - LIGHTCYCLETRANSLCONST, -1, z_observer);
				xLightCycleCollision = x_observer - COLLISIONTRANSLCONST;
			}
			//Se invece ho girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_observer - LIGHTCYCLETRANSLCONST, -1, z_observer);
				xLightCycleCollision = x_observer - COLLISIONTRANSLCONST;
			}
		}
	}

	//Controrotazione per ruotare la moto in modo concorde alla visuale.
	glRotatef(-(angle*(180 / M_PI)), 0.0, 1.0, 0.0);

	// if the display list has not been made yet, create a new one and
	// fill it with scene contents
	if (listCreated == 0)
	{
		scene_list[0] = glGenLists(1);
		glNewList(scene_list[0], GL_COMPILE);
		// now begin at the root node of the imported data and traverse
		// the scenegraph by multiplying subsequent local transforms
		// together on GL's matrix stack.
		recursive_render(scene[0], scene[0]->mRootNode, 1.0);
		glEndList();
	}
	glCallList(scene_list[0]);
	glPopMatrix();
}

/*Funzione di disegno della lightcycle dell'IA.*/
void drawAILightCycle()
{
	glPushMatrix();

	//Se la IA si sta muovendo parallelamente all'asse z entro qui.
	if (AIParity == 0)
	{
		//Assegno ad X la posizione centrale del muro che la AI sta costruendo.
		xAILightCycleCollision = x_AI;
		//Se la direzione di crescita è positiva entro qui.
		if (AIWallsArray[sizeAIWallsArray][3] >= AIWallsArray[sizeAIWallsArray][1])
		{
			//Ora devo calcolare la traslazione rispetto a Z, sia per disegnare la moto che per le collisioni. 
			//Se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				//Posiziono la moto.
				glTranslatef(x_AI, -1, z_AI + LIGHTCYCLETRANSLCONST);
				zAILightCycleCollision = z_AI + COLLISIONTRANSLCONST;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_AI, -1, z_AI + LIGHTCYCLETRANSLCONST);
				zAILightCycleCollision = z_AI + COLLISIONTRANSLCONST;
			}
		}
		//Altrimenti entro qui.
		else
		{
			//Se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				//Posiziono la moto.
				glTranslatef(x_AI, -1, z_AI - LIGHTCYCLETRANSLCONST);
				zAILightCycleCollision = z_AI - COLLISIONTRANSLCONST;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_AI, -1, z_AI - LIGHTCYCLETRANSLCONST);
				zAILightCycleCollision = z_AI - COLLISIONTRANSLCONST;
			}
		}
	}
	//Se invece la AI si sta muovendo parallelamente all'asse x.
	else
	{
		//Assegno a Z la posizione centrale del muro che la AI sta costruendo.
		zAILightCycleCollision = z_AI;
		//Se la direzione di crescita è positiva entro qui.
		if (AIWallsArray[sizeAIWallsArray][2] >= AIWallsArray[sizeAIWallsArray][0])
		{
			//Ora devo calcolare la traslazione rispetto a X, sia per disegnare la moto che per le collisioni.
			//Se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				//Posiziono la moto.
				glTranslatef(x_AI + LIGHTCYCLETRANSLCONST, -1, z_AI);
				xAILightCycleCollision = x_AI + COLLISIONTRANSLCONST;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_AI + LIGHTCYCLETRANSLCONST, -1, z_AI);
				xAILightCycleCollision = x_AI + COLLISIONTRANSLCONST;
			}
		}
		//Altrimenti entro qui.
		else
		{
			//Se la IA ha girato a destra entro qui.
			if (directions[2] == 'd')
			{
				//Posiziono la moto.
				glTranslatef(x_AI - LIGHTCYCLETRANSLCONST, -1, z_AI);
				xAILightCycleCollision = x_AI - COLLISIONTRANSLCONST;
			}
			//Se invece ha girato a sinistra entro qui.
			else
			{
				//Posiziono la moto.
				glTranslatef(x_AI - LIGHTCYCLETRANSLCONST, -1, z_AI);
				xAILightCycleCollision = x_AI - COLLISIONTRANSLCONST;
			}
		}
	}

	//Controrotazione per ruotare la moto in modo concorde alla visuale.
	glRotatef(-(angleAI*(180 / M_PI)), 0.0, 1.0, 0.0);

	// if the display list has not been made yet, create a new one and
	// fill it with scene contents
	if (listCreated == 0)
	{
		scene_list[1] = glGenLists(1);
		glNewList(scene_list[1], GL_COMPILE);
		// now begin at the root node of the imported data and traverse
		// the scenegraph by multiplying subsequent local transforms
		// together on GL's matrix stack.
		recursive_render(scene[1], scene[1]->mRootNode, 1.0);
		glEndList();
		listCreated = 1;
	}
	glCallList(scene_list[1]);
	glPopMatrix();
}