#include "PlayerAndAIMethods.h"

//VERIFICA COLLISIONI.
//E' possibile notare come sia possibile solamente confrontare l'intersezione dell'ultimo segmento che sto creando
//con tutti i segmenti creati in precedenza per ottenere una verifica ottimale delle collisioni.
//
// z       _________S2_______
// ^   zmax| _____________  |
// |       | |            | | S3
// |     S1| |____________| |
// |       | *______________|  <-- Collisione tra S4 ed S1: notare che nel punto di collisione si ha la stessa x (intorno se
// |       | |      S4             consideriamo spessore muro), mentre la z è compresa tra la zmin e la zmax del segmento S1
// |   zmin| |
// |________________________>
//                          x
//  

/*Funzione di verifica collisione del giocatore con i muri lasciati da se stesso, con i muri del gioco e con 
la lightcycle e i muri lasciati dall'IA, Se si rileva un'intersezione viene restituito due: il PC ha vinto.*/
int verifyPlayerCollision()
{
	int i, init, end = sizePlayersWallsArray - 1;
	//Verifica collisioni ottimizzata: siccome ho collisione solo tra muri perpendicolari fra loro, se sono parallelo all'asse
	//z verifico le collisioni solo con i muri paralleli all'asse x, viceversa le verifico solo con i muri paralleli all'asse z.
	//Per far ciò devo variare in modo corretto il valore iniziale del for ed incrementare di due ad ogni ciclo.
	if (playerParity == 0)
	{
		init = 1;
	}
	else
	{
		init = 0;
	}

	//COLLISIONE DEL GIOCATORE CON I MURI CREATI DAL GIOCATORE STESSO.
	//Faccio un ciclo partendo da init sino ad arrivare al terzultimo muro (altrimenti viene rilevata
	//una collisione tra due muri se il nuovo muro è parallelo all'asse z).
	for (i = init; i < end; i = i + 2)
	{
		//Se playerParity è uguale a 0 allora il muro che sto disegnando è parallelo all'asse z (z variante, x fissa).
		if (playerParity == 0)
		{
			//Verifico se il valore della z finale della LightCycle è compreso tra quelli assunti dalla z (spessore) del segmento (muro) i.
			if (((zLightCycleCollision >= playersWallsArray[i][3] - C) && (zLightCycleCollision <= playersWallsArray[i][3] + C))
				|| ((z_observer >= playersWallsArray[i][3] - C) && (z_observer <= playersWallsArray[i][3] + C)))
			{
				//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
				//Prima però verifico se il muro i è stato tracciato dai valori di x piu' piccoli verso quelli piu'
				//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
				if (playersWallsArray[i][2] >= playersWallsArray[i][0])
				{
					//Se il valore attuale della x della LightCycle è compreso tra il valore piu' piccolo del muro i e il valore 
					//piu' grande ho un'intersezione.
					if (((xLightCycleCollision >= playersWallsArray[i][0]) && (xLightCycleCollision <= playersWallsArray[i][2]))
						|| ((x_observer >= playersWallsArray[i][0]) && (x_observer <= playersWallsArray[i][2])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with Player's Wall.\n");
						return 2;
					}
				}
				else
				{
					//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((xLightCycleCollision >= playersWallsArray[i][2]) && (xLightCycleCollision <= playersWallsArray[i][0]))
						|| ((x_observer >= playersWallsArray[i][2]) && (x_observer <= playersWallsArray[i][0])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with Player's Wall.\n");
						return 2;
					}
				}
			}
		}
		//Se playerParity è pari ad 1 il muro è parallelo all'asse x (x variante, z fissa). 
		else
		{
			//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
			if (((xLightCycleCollision >= playersWallsArray[i][2] - C) && (xLightCycleCollision <= playersWallsArray[i][2] + C))
				|| ((x_observer >= playersWallsArray[i][2] - C) && (x_observer <= playersWallsArray[i][2] + C)))
			{
				//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
				//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
				//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
				if (playersWallsArray[i][3] >= playersWallsArray[i][1])
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zLightCycleCollision >= playersWallsArray[i][1]) && (zLightCycleCollision <= playersWallsArray[i][3]))
						|| ((z_observer >= playersWallsArray[i][1]) && (z_observer <= playersWallsArray[i][3])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with Player's Wall.\n");
						return 2;
					}
				}
				else
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zLightCycleCollision >= playersWallsArray[i][3]) && (zLightCycleCollision <= playersWallsArray[i][1]))
						|| ((z_observer >= playersWallsArray[i][3]) && (z_observer <= playersWallsArray[i][1])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with Player's Wall.\n");
						return 2;
					}
				}
			}
		}
	}

	//COLLISIONE DEL GIOCATORE CON I MURI CREATI DAL PC.
	//Faccio un ciclo partendo da init sino ad arrivare al terzultimo muro (altrimenti viene rilevata
	//una collisione tra due muri se il nuovo muro è parallelo all'asse z).
	for (i = 0; i <= sizeAIWallsArray; i++)
	{
		//Se playerParity è uguale a 0 allora il muro che sto disegnando è parallelo all'asse z (z variante, x fissa).
		if (playerParity == 0)
		{
			//Verifico se il valore della z finale della LightCycle è compreso tra quelli assunti dalla z (spessore) del segmento (muro) i.
			if (((zLightCycleCollision >= AIWallsArray[i][3] - C) && (zLightCycleCollision <= AIWallsArray[i][3] + C))
				|| ((z_observer >= AIWallsArray[i][3] - C) && (z_observer <= AIWallsArray[i][3] + C)))
			{
				//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
				//Prima però verifico se il muro i è stato tracciato dai valori di x piu' piccoli verso quelli piu'
				//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
				if (AIWallsArray[i][2] >= AIWallsArray[i][0])
				{
					//Se il valore attuale della x della LightCycle è compreso tra il valore piu' piccolo del muro i e il valore 
					//piu' grande ho un'intersezione.
					if (((xLightCycleCollision >= AIWallsArray[i][0]) && (xLightCycleCollision <= AIWallsArray[i][2]))
						|| ((x_observer >= AIWallsArray[i][0]) && (x_observer <= AIWallsArray[i][2])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with AI's Wall.\n");
						return 2;
					}
				}
				else
				{
					//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((xLightCycleCollision >= AIWallsArray[i][2]) && (xLightCycleCollision <= AIWallsArray[i][0]))
						|| ((x_observer >= AIWallsArray[i][2]) && (x_observer <= AIWallsArray[i][0])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with AI's Wall.\n");
						return 2;
					}
				}
			}
		}
		//Se playerParity è pari ad 1 il muro è parallelo all'asse x (x variante, z fissa). 
		else
		{
			//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
			if (((xLightCycleCollision >= AIWallsArray[i][2] - C) && (xLightCycleCollision <= AIWallsArray[i][2] + C))
				|| ((x_observer >= AIWallsArray[i][2] - C) && (x_observer <= AIWallsArray[i][2] + C)))
			{
				//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
				//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
				//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
				if (AIWallsArray[i][3] >= AIWallsArray[i][1])
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zLightCycleCollision >= AIWallsArray[i][1]) && (zLightCycleCollision <= AIWallsArray[i][3]))
						|| ((z_observer >= AIWallsArray[i][1]) && (z_observer <= AIWallsArray[i][3])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with AI's Wall.\n");
						return 2;
					}
				}
				else
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zLightCycleCollision >= AIWallsArray[i][3]) && (zLightCycleCollision <= AIWallsArray[i][1]))
						|| ((z_observer >= AIWallsArray[i][3]) && (z_observer <= AIWallsArray[i][1])))
					{
						//INTERSEZIONE!
						printf("Player: Intersection with AI's Wall.\n");
						return 2;
					}
				}
			}
		}
	}

	//VERIFICA COLLISIONI CON MOTO AI.
	//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
	if (((xLightCycleCollision >= xAILightCycleCollision - C) && (xLightCycleCollision <= xAILightCycleCollision + C))
		|| ((x_observer >= x_AI - C) && (x_observer <= x_AI + C)))
	{
		//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
		//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
		//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
		if (zAILightCycleCollision >= z_AI)
		{
			//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((zLightCycleCollision >= zAILightCycleCollision) && (zLightCycleCollision <= z_AI))
				|| ((z_observer >= zAILightCycleCollision) && (z_observer <= z_AI)))
			{
				//INTERSEZIONE!
				printf("Player: Intersection with AI Lightcycle.\n");
				return 2;
			}
		}
		else
		{
			//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((zLightCycleCollision >= z_AI) && (zLightCycleCollision <= zAILightCycleCollision))
				|| ((z_observer >= z_AI) && (z_observer <= zAILightCycleCollision)))
			{
				//INTERSEZIONE!
				printf("Player: Intersection with AI Lightcycle.\n");
				return 2;
			}
		}
	}
	//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
	if (((zLightCycleCollision >= zAILightCycleCollision - C) && (zLightCycleCollision <= zAILightCycleCollision + C))
		|| ((z_observer >= z_AI - C) && (z_observer <= z_AI + C)))
	{
		//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
		//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
		//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
		if (xAILightCycleCollision >= x_AI)
		{
			//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((xLightCycleCollision >= xAILightCycleCollision) && (xLightCycleCollision <= x_AI))
				|| ((x_observer >= xAILightCycleCollision) && (x_observer <= x_AI)))
			{
				//INTERSEZIONE!
				printf("Player: Intersection with AI Lightcycle.\n");
				return 2;
			}
		}
		else
		{
			//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((xLightCycleCollision >= x_AI) && (xLightCycleCollision <= xAILightCycleCollision))
				|| ((x_observer >= x_AI) && (x_observer <= xAILightCycleCollision)))
			{
				//INTERSEZIONE!
				printf("Player: Intersection with AI Lightcycle.\n");
				return 2;
			}
		}
	}


	//COLLISIONE CON MURO ESTERNO.
	//VERIFICO ANCHE CHE IL VALORE ASSUNTO DALLA Z E DALLA X SIA INFERIORE ALLA DIMENSIONE DEL MONDO.
	//Se supero la dimensione del mondo lungo l'asse z ho un'intersezione: il PC ha vinto.
	if ((zLightCycleCollision >= WORLDSIZE) || (zLightCycleCollision <= -WORLDSIZE))
	{
		printf("Player: Intersection with Edge's Wall.\n");
		return 2;
	}
	//Se supero la dimensione del mondo lungo l'asse x ho un'intersezione: il PC ha vinto.
	if ((xLightCycleCollision >= WORLDSIZE) || (xLightCycleCollision <= -WORLDSIZE))
	{
		printf("Player: Intersection with Edge's Wall.\n");
		return 2;
	}
	return 0;
}

/*Funzione di verifica collisione dell'IA con i muri lasciati dall'IA stessa, con i muri del gioco e con la lightcycle
e i muri lasciati dal giocatore, Se si rileva un'intersezione viene restituito uno: il giocatore ha vinto.*/
int verifyAICollision()
{
	//SI SFRUTTA LO STESSO ALGORITMO USATO PER IL GIOCATORE. 
	int i, init, end = sizeAIWallsArray - 1;
	//Verifica collisioni ottimizzata: siccome ho collisione solo tra muri perpendicolari fra loro, se sono parallelo all'asse
	//z verifico le collisioni solo con i muri paralleli all'asse x, viceversa le verifico solo con i muri paralleli all'asse z.
	//Per far ciò devo variare in modo corretto il valore iniziale del for ed incrementare di due ad ogni ciclo.
	if (AIParity == 0)
	{
		init = 1;
	}
	else
	{
		init = 0;
	}
	//COLLISIONE DELLA IA CON I MURI CREATI DALLA STESSA IA.
	//Faccio un ciclo partendo da init sino ad arrivare al terzultimo muro (altrimenti viene rilevata
	//una collisione tra due muri se il nuovo muro è parallelo all'asse z).
	for (i = init; i < end; i = i + 2)
	{
		//Se AIParity è uguale a 0 allora il muro che sto disegnando è parallelo all'asse z (z variante, x fissa).
		if (AIParity == 0)
		{
			//Verifico se il valore della z finale della LightCycle è compreso tra quelli assunti dalla z (spessore) del segmento (muro) i.
			if (((zAILightCycleCollision >= AIWallsArray[i][3] - C) && (zAILightCycleCollision <= AIWallsArray[i][3] + C))
				|| ((z_AI >= AIWallsArray[i][3] - C) && (z_AI <= AIWallsArray[i][3] + C)))
			{
				//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
				//Prima però faccio un'ulteriore verifica:
				//Verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu' grandi o viceversa: cio' causa
				//l'inversione del segno del confronto. 
				if (AIWallsArray[i][2] >= AIWallsArray[i][0])
				{
					//Se il valore attuale della x della LightCycle è compreso tra il valore piu' piccolo del muro i e il valore 
					//piu' grande ho un'intersezione.
					if (((xAILightCycleCollision >= AIWallsArray[i][0]) && (xAILightCycleCollision <= AIWallsArray[i][2]))
						|| ((x_AI >= AIWallsArray[i][0]) && (x_AI <= AIWallsArray[i][2])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with AI's Wall.\n");
						return 1;
					}
				}
				else
				{
					//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((xAILightCycleCollision >= AIWallsArray[i][2]) && (xAILightCycleCollision <= AIWallsArray[i][0]))
						|| ((x_AI >= AIWallsArray[i][2]) && (x_AI <= AIWallsArray[i][0])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with AI's Wall.\n");
						return 1;
					}
				}
			}
		}
		//Se AIParity è pari ad 1 il muro è parallelo all'asse x (x variante, z fissa). 
		else
		{
			//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
			if (((xAILightCycleCollision >= AIWallsArray[i][2] - C) && (xAILightCycleCollision <= AIWallsArray[i][2] + C))
				|| ((x_AI >= AIWallsArray[i][2] - C) && (x_AI <= AIWallsArray[i][2] + C)))
			{
				//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
				//Prima però faccio un'ulteriore verifica:
				//Verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu' grandi o viceversa: cio' causa
				//l'inversione del segno del confronto. 
				if (AIWallsArray[i][3] >= AIWallsArray[i][1])
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zAILightCycleCollision >= AIWallsArray[i][1]) && (zAILightCycleCollision <= AIWallsArray[i][3]))
						|| ((z_AI >= AIWallsArray[i][1]) && (z_AI <= AIWallsArray[i][3])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with AI's Wall.\n");
						return 1;
					}
				}
				else
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zAILightCycleCollision >= AIWallsArray[i][3]) && (zAILightCycleCollision <= AIWallsArray[i][1]))
						|| ((z_AI >= AIWallsArray[i][3]) && (z_AI <= AIWallsArray[i][1])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with AI's Wall.\n");
						return 1;
					}
				}
			}
		}
	}

	//COLLISIONE DELLA IA CON I MURI CREATI DAL GIOCATORE.
	//Faccio un ciclo partendo da init sino ad arrivare al terzultimo muro (altrimenti viene rilevata
	//una collisione tra due muri se il nuovo muro è parallelo all'asse z).
	for (i = 0; i <= sizePlayersWallsArray; i++)
	{
		//Se AIParity è uguale a 0 allora il muro che sto disegnando è parallelo all'asse z (z variante, x fissa).
		if (AIParity == 0)
		{
			//Verifico se il valore della z finale della LightCycle è compreso tra quelli assunti dalla z (spessore) del segmento (muro) i.
			if (((zAILightCycleCollision >= playersWallsArray[i][3] - C) && (zAILightCycleCollision <= playersWallsArray[i][3] + C))
				|| ((z_AI >= playersWallsArray[i][3] - C) && (z_AI <= playersWallsArray[i][3] + C)))
			{
				//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
				//Prima però faccio un'ulteriore verifica:
				//Verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu' grandi o viceversa: cio' causa
				//l'inversione del segno del confronto. 
				if (playersWallsArray[i][2] >= playersWallsArray[i][0])
				{
					//Se il valore attuale della x della LightCycle è compreso tra il valore piu' piccolo del muro i e il valore 
					//piu' grande ho un'intersezione.
					if (((xAILightCycleCollision >= playersWallsArray[i][0]) && (xAILightCycleCollision <= playersWallsArray[i][2]))
						|| ((x_AI >= playersWallsArray[i][0]) && (x_AI <= playersWallsArray[i][2])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with Player's Wall.\n");
						return 1;
					}
				}
				else
				{
					//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((xAILightCycleCollision >= playersWallsArray[i][2]) && (xAILightCycleCollision <= playersWallsArray[i][0]))
						|| ((x_AI >= playersWallsArray[i][2]) && (x_AI <= playersWallsArray[i][0])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with Player's Wall.\n");
						return 1;
					}
				}
			}
		}
		//Se AIParity è pari ad 1 il muro è parallelo all'asse x (x variante, z fissa). 
		else
		{
			//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
			if (((xAILightCycleCollision >= playersWallsArray[i][2] - C) && (xAILightCycleCollision <= playersWallsArray[i][2] + C))
				|| ((x_AI >= playersWallsArray[i][2] - C) && (x_AI <= playersWallsArray[i][2] + C)))
			{
				//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
				//Prima però faccio un'ulteriore verifica:
				//Verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu' grandi o viceversa: cio' causa
				//l'inversione del segno del confronto. 
				if (playersWallsArray[i][3] >= playersWallsArray[i][1])
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zAILightCycleCollision >= playersWallsArray[i][1]) && (zAILightCycleCollision <= playersWallsArray[i][3]))
						|| ((z_AI >= playersWallsArray[i][1]) && (z_AI <= playersWallsArray[i][3])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with Player's Wall.\n");
						return 1;
					}
				}
				else
				{
					//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
					if (((zAILightCycleCollision >= playersWallsArray[i][3]) && (zAILightCycleCollision <= playersWallsArray[i][1]))
						|| ((z_AI >= playersWallsArray[i][3]) && (z_AI <= playersWallsArray[i][1])))
					{
						//INTERSEZIONE!
						printf("AI: Intersection with Player's Wall.\n");
						return 1;
					}
				}
			}
		}
	}

	//VERIFICA COLLISIONI CON MOTO GIOCATORE.
	//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
	if (((xAILightCycleCollision >= xLightCycleCollision - C) && (xAILightCycleCollision <= xLightCycleCollision + C))
		|| ((x_AI >= x_observer - C) && (x_AI <= x_observer + C)))
	{
		//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
		//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
		//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
		if (zAILightCycleCollision >= z_AI)
		{
			//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((zAILightCycleCollision >= zLightCycleCollision) && (zAILightCycleCollision <= z_observer))
				|| ((z_AI >= zLightCycleCollision) && (z_AI <= z_observer)))
			{
				//INTERSEZIONE!
				printf("AI: Intersection with Player's Lightcycle.\n");
				return 1;
			}
		}
		else
		{
			//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((zAILightCycleCollision >= z_observer) && (zAILightCycleCollision <= zLightCycleCollision))
				|| ((z_AI >= z_observer) && (z_AI <= zLightCycleCollision)))
			{
				//INTERSEZIONE!
				printf("AI: Intersection with Player's Lightcycle.\n");
				return 1;
			}
		}
	}
	//Verifico se il valore della z finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
	if (((zAILightCycleCollision >= zLightCycleCollision - C) && (zAILightCycleCollision <= zLightCycleCollision + C))
		|| ((z_AI >= z_observer - C) && (z_AI <= z_observer + C)))
	{
		//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
		//Prima però verifico se il muro i è stato tracciato dai valori di x piu' piccoli verso quelli piu'
		//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
		if (xAILightCycleCollision >= x_AI)
		{
			//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((xAILightCycleCollision >= xLightCycleCollision) && (xAILightCycleCollision <= x_observer))
				|| ((x_AI >= xLightCycleCollision) && (x_AI <= x_observer)))
			{
				//INTERSEZIONE!
				printf("AI: Intersection with Player's Lightcycle.\n");
				return 1;
			}
		}
		else
		{
			//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
			if (((xAILightCycleCollision >= x_observer) && (xAILightCycleCollision <= xLightCycleCollision))
				|| ((x_AI >= x_observer) && (x_AI <= xLightCycleCollision)))
			{
				//INTERSEZIONE!
				printf("AI: Intersection with Player's Lightcycle.\n");
				return 1;
			}
		}
	}

	//COLLISIONE CON MURO ESTERNO.
	//VERIFICO ANCHE CHE IL VALORE ASSUNTO DALLA Z E DALLA X SIA INFERIORE ALLA DIMENSIONE DEL MONDO.
	//Se supero la dimensione del mondo lungo l'asse z ho un'intersezione: il PC ha vinto.
	if ((zAILightCycleCollision >= WORLDSIZE) || (zAILightCycleCollision <= -WORLDSIZE))
	{
		printf("AI: Intersection with Edge's Wall.\n");
		return 1;
	}
	//Se supero la dimensione del mondo lungo l'asse x ho un'intersezione: il PC ha vinto.
	if ((xAILightCycleCollision >= WORLDSIZE) || (xAILightCycleCollision <= -WORLDSIZE))
	{
		printf("AI: Intersection with Edge's Wall.\n");
		return 1;
	}
	return 0;
}


/*Funzione di movimento automatico dell'IA in base alla posizione dell'IA stessa e del giocatore.*/
void moveAI()
{
	int count, i;
	//CASO IN CUI LA IA è VICINO AI LIMITI DELLO SCENARIO.
	//Incremento il contatore uno.
	counterForAIDecision1++;
	//Se il contatore uno ha raggiunto 6, controllo la posizione della moto dell'IA rispetto ai muri del gioco.
	if (counterForAIDecision1 >= 6)
	{
		//Se sono vicino ad uno dei bordi del gioco.
		if ((xAILightCycleCollision > BORDEROFFSET) || (xAILightCycleCollision < -BORDEROFFSET) || (zAILightCycleCollision > BORDEROFFSET) || (zAILightCycleCollision < -BORDEROFFSET))
		{
			//Se sono vicino al muro a destra del gioco.
			if (xAILightCycleCollision > BORDEROFFSET)
			{
				//Se la moto dell'IA si trova molto vicina all'angolo in basso a destra.
				if (zAILightCycleCollision > BORDEROFFSET)
				{
					//Se si sta muovendo parallelamente all'asse z la faccio ruotare a destra.
					if (AIParity == 0)
					{
						AITurnRight();
					}
					//Mentre se si sta muovendo parallelamente all'asse x la faccio ruotare a sinistra.
					else
					{
						AITurnLeft();
					}
				}
				//Se la moto dell'IA si trova molto vicina all'angolo in alto a destra.
				else if (zAILightCycleCollision < -BORDEROFFSET)
				{
					//Se si sta muovendo parallelamente all'asse z la faccio ruotare a sinistra.
					if (AIParity == 0)
					{
						AITurnLeft();
					}
					//Mentre se si sta muovendo parallelamente all'asse x la faccio ruotare a destra.
					else
					{
						AITurnRight();
					}
				}
				//Se sono vicino ad uno dei lati ma non vicino ad un angolo entro qui.
				else
				{
					//Impongo che la IA decida di ruotare con una percentuale del 80%. 
					chooseToTurnWithACertainPercentage(80, "AI: Edge Near.\n");
				}
			}
			//Se sono vicino al muro a sinistra del gioco.
			else if (xAILightCycleCollision < -BORDEROFFSET)
			{
				//Se la moto dell'IA si trova molto vicina all'angolo in basso a sinistra.
				if (zAILightCycleCollision > BORDEROFFSET)
				{
					//Se si sta muovendo parallelamente all'asse z la faccio ruotare a sinistra.
					if (AIParity == 0)
					{
						AITurnLeft();
					}
					//Mentre se si sta muovendo parallelamente all'asse x la faccio ruotare a destra.
					else
					{
						AITurnRight();
					}
				}
				//Se la moto dell'IA si trova molto vicina all'angolo in alto a sinistra.
				else if (zAILightCycleCollision < -BORDEROFFSET)
				{
					//Se si sta muovendo parallelamente all'asse z la faccio ruotare a destra.
					if (AIParity == 0)
					{
						AITurnRight();
					}
					//Mentre se si sta muovendo parallelamente all'asse x la faccio ruotare a sinistra.
					else
					{
						AITurnLeft();
					}
				}
				//Se sono vicino ad uno dei lati ma non vicino ad un angolo entro qui.
				else
				{
					//Impongo che la IA decida di ruotare con una percentuale del 80%. 
					chooseToTurnWithACertainPercentage(80, "AI: Edge Near.\n");
				}
			}
			//Se sono vicino al lato in alto o in basso entro qui.
			else
			{
				//Impongo che la IA decida di ruotare con una percentuale del 80%. 
				chooseToTurnWithACertainPercentage(80, "AI: Edge Near.\n");
			}
		}
		//Riazzero il contatore per le decisioni dell'IA.
		counterForAIDecision1 = 0;
	}
	//Incremento il contatore due.
	counterForAIDecision2++;
	//Se il contatore due ha raggiunto 6, controllo i muri creati dall'IA.
	if (counterForAIDecision2 >= 6)
	{
		//Implemento un numero random che con il 5% di possibilità fa svoltare la moto.
		if (rand() % 100 < 5)
		{
			printf("AI: Casual Turn.\n");
			//Rotazione casuale a destra o sinistra.
			RandomAIRotationLeftOrRight();
		}
		//Altrimenti ciclo per controllare muri IA e giocatore.
		else
		{
			//Uso una procedura molto simile a quella per rilevare le collisioni per per verificare la loro 
			//posizione dei muri dell'IA e per evitare con una certa probabilità di creare collisioni.
			for (i = 0; i <= sizeAIWallsArray; i++)
			{
				//Verifico se il valore della z finale della LightCycle è compreso tra quelli assunti dalla z del muro attuale
				//piu' un offset dato da CHG.
				if ((zAILightCycleCollision >= AIWallsArray[i][3] - CHG) && (zAILightCycleCollision <= AIWallsArray[i][3] + CHG))
				{
					//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
					//Prima però verifico se il muro i è stato tracciato dai valori di x piu' piccoli verso quelli piu'
					//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
					if (AIWallsArray[i][2] >= AIWallsArray[i][0])
					{
						//Se il valore attuale della x della LightCycle è compreso tra il valore piu' piccolo del muro i e il valore 
						//piu' grande ho un'intersezione.
						if ((xAILightCycleCollision >= AIWallsArray[i][0]) && (xAILightCycleCollision <= AIWallsArray[i][2]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: AI Wall.\n");
						}
					}
					else
					{
						//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
						if ((xAILightCycleCollision >= AIWallsArray[i][2]) && (xAILightCycleCollision <= AIWallsArray[i][0]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: AI Wall.\n");
						}
					}
				}
				//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
				//piu' un offset dato da CHG.
				if ((xAILightCycleCollision >= AIWallsArray[i][2] - CHG) && (xAILightCycleCollision <= AIWallsArray[i][2] + CHG))
				{
					//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
					//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
					//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
					if (AIWallsArray[i][3] >= AIWallsArray[i][1])
					{
						//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
						if ((zAILightCycleCollision >= AIWallsArray[i][1]) && (zAILightCycleCollision <= AIWallsArray[i][3]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: AI Wall.\n");
						}
					}
					else
					{
						//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
						if ((zAILightCycleCollision >= AIWallsArray[i][3]) && (zAILightCycleCollision <= AIWallsArray[i][1]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: AI Wall.\n");
						}
					}
				}
			}
			//Uso una procedura molto simile a quella per rilevare le collisioni per per verificare la loro 
			//posizione dei muri dell'IA e per evitare con una certa probabilità di creare collisioni.
			for (i = 0; i <= sizePlayersWallsArray; i++)
			{
				//Verifico se il valore della z finale della LightCycle è compreso tra quelli assunti dalla z del muro attuale
				//piu' un offset dato da CHG.
				if ((zAILightCycleCollision >= playersWallsArray[i][3] - CHG) && (zAILightCycleCollision <= playersWallsArray[i][3] + CHG))
				{
					//Se si, verifico se la x è compresa tra i valori minimo e massimo del segmento i.
					//Prima però verifico se il muro i è stato tracciato dai valori di x piu' piccoli verso quelli piu'
					//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
					if (playersWallsArray[i][2] >= playersWallsArray[i][0])
					{
						//Se il valore attuale della x della LightCycle è compreso tra il valore piu' piccolo del muro i e il valore 
						//piu' grande ho un'intersezione.
						if ((xAILightCycleCollision >= playersWallsArray[i][0]) && (xAILightCycleCollision <= playersWallsArray[i][2]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: Player Wall.\n");
						}
					}
					else
					{
						//Se il valore attuale di x è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
						if ((xAILightCycleCollision >= playersWallsArray[i][2]) && (xAILightCycleCollision <= playersWallsArray[i][0]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: Player Wall.\n");
						}
					}
				}
				//Verifico se il valore della x finale del segmento(muro) attuale è compreso tra quelli assunti dalla x (spessore) del segmento (muro) i.
				//piu' un offset dato da CHG.
				if ((xAILightCycleCollision >= playersWallsArray[i][2] - CHG) && (xAILightCycleCollision <= playersWallsArray[i][2] + CHG))
				{
					//Se si, verifico se la z è compresa tra i valori minimo e massimo del segmento i.
					//Prima però verifico se il muro i è stato tracciato dai valori di z piu' piccoli verso quelli piu'
					//grandi o viceversa: cio' causa l'inversione del segno del confronto. 
					if (playersWallsArray[i][3] >= playersWallsArray[i][1])
					{
						//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
						if ((zAILightCycleCollision >= playersWallsArray[i][1]) && (zAILightCycleCollision <= playersWallsArray[i][3]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: Player Wall.\n");
						}
					}
					else
					{
						//Se il valore attuale di z è compreso tra il valore piu' piccolo del muro i e il valore piu' grande ho un'intersezione.
						if ((zAILightCycleCollision >= playersWallsArray[i][3]) && (zAILightCycleCollision <= playersWallsArray[i][1]))
						{
							//Impongo che la IA decida di ruotare con una percentuale del 50%. 
							chooseToTurnWithACertainPercentage(50, "AI Turn: Player Wall.\n");
						}
					}
				}
			}
		}
		counterForAIDecision2 = 0;
	}
	//Parte di codice dedita al movimento dell'IA. In base alla sua attuale direzione di movimento si incrementa
	//(o decrementa) la coordinata libera.
	//Verifico la parità: se mi sto muovendo parallelamente all'asse Z entro qui.
	if (AIParity == 0)
	{
		//Se mi sto muovendo dalle Z positive verso quelle negative entro qui.
		if (AIWallsArray[sizeAIWallsArray][3] >= AIWallsArray[sizeAIWallsArray][1])
		{
			z_AI = z_AI + SPEED;
		}
		//Altrimenti se mi sto muovendo dalle Z negative verso quelle positive entro qui.
		else
		{
			z_AI = z_AI - SPEED;
		}
		//Aggiorno la posizione del muro alle spalle del giocatore (relativa solo a Z).
		AIWallsArray[sizeAIWallsArray][3] = z_AI;
	}//Mentre se mi sto muovendo parallelamente all'asse X entro qui.
	else
	{
		//Se mi sto muovendo dalle X positive verso quelle negative entro qui.
		if (AIWallsArray[sizeAIWallsArray][2] >= AIWallsArray[sizeAIWallsArray][0])
		{
			x_AI = x_AI + SPEED;
		}
		//Altrimenti se mi sto muovendo dalle X negative verso quelle positive entro qui.
		else
		{
			x_AI = x_AI - SPEED;
		}
		//Aggiorno la posizione del muro alle spalle del giocatore (relativa solo a X).
		AIWallsArray[sizeAIWallsArray][2] = x_AI;
	}
	return;
}