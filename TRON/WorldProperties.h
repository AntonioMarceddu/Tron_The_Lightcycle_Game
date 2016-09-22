#pragma once

//Dimensione del mondo creato (pavimentazione, muri).
#define WORLDSIZE 100
#define WORLDSIZEBORDER 101
#define WORLDSIZEOFFSET 100.5
#define SKYBOXSIZE 300
//Altezza minima e massima dei muri di delimitazione del gioco.
#define MINHEIGHT -2
#define MAXHEIGHT 0
//Variabile contenente un numero statico; Tale numero viene usato per inizializzare i vettori contenenti
//il punto iniziale e finale dei muri del giocatore e dell'IA.
#define NUMCOL 4
//Variabile recante il mezzo spessore del muro. I muri vengono salvati come vettori recanti posizione iniziale e 
//finale; per tale motivo per creare lo spessore i muri vengono disegnati dando un'offset di +-C ai valori salvati.
#define C 0.25
//Altezza minima e massima dei muri disegnati dal giocatore e dall'IA.
#define WALLMINHEIGHT -1.98
#define WALLMAXHEIGHT 0.02
//Velocità del gioco.
#define SPEED 0.5