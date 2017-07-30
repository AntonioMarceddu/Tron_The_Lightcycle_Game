# Tron The Lightcycle Game

## Link at the video presentation: https://www.youtube.com/watch?v=4oe2F32DFtM
Description available in english and italian below.

## English

### Introduction
TRON - The LightCycle Game is a game made for the examination of Graphics Engineering of Politecnico di Torino by Antonio Marceddu. The programming part and a fraction of the graphic part has been realized in OpenGL with the addition of GLUT, Assimp and Devil libraries, while the remaining fraction (realization of lightcycles) has been realized with Blender. This guide has the objective to explicate and motivate implementation choices of the project for educational purposes without talking too much of the code, as it is all commented in Italian language.

### Description of the game
The game is a reprocessing of the famous race between lightcycles of TRON film; citing wikipedia, the lightcycle are motorcycles used in such mortal races "motolabyrinth" that take place within a so-called "game grid". The races are lethal because when the lightcycle moves they release behind an energy wall against which you can crash, in a similar way as it happens in the game Snake, who became famous for the presence in many mobile phones. To win the game, you need to crash your opponent through these walls or against the walls that surround the game grid.

### Flowchart of the map of the game
The map of the game, both as regards the storage of the walls created by the player and by the IA that the mode of operation of the AI and the collisions, is schematically represented in two dimensions; it means that are considered only the X coordinate and the Z coordinate and is totally neglected the Y coordinate, which is used only in the design phase to achieve the three-dimensional environment.

### Management of the game walls
The walls of the game are managed as segments that are drawn from a coordinate (X1, Z1) to a coordinate (X2, Z2). The first coordinate is fixed (starting point of the wall) and the second (ending point of the wall) varies with the position of the player. With each rotation of the player and AI, the pivot point becomes the ending point of the previous segment (wall) and the start point of the new segment (wall) that is instantiated, having towards different than the previous one. In the design phase, the segments are presented with an offset (positive and negative) that represents the wall thickness.

### Reshaping
The reshape is fully dynamic: the game and all the menus are adapted to changes in the resolution, with the obvious consequence that many menus' and written, based on the selected resolution, could not be more legible. The gaming experience is optimized for playability in 16:9 (the initial resolution is 1280 x 720).

### Stabilization of the frame rate
For the stabilization of the frame rate, has been created an idle function that calls the redraw function of the screen every 33 ms approximately, in way to have an average number of frames per second (fps) equal to about 30. This leads to having a running speed of the game independent from the machine in which it run.

### Audio
For the audio part is used a function present in windows.h, PlaySound; if you import the list into a Linux machine, comment the above function and windows.h includes, where present, in order to allow the start of the program.

### Blender files import and textures
The files created with Blender (and then saved in OBJ) are imported by the library objectImporter.c, that is the sample library of use of Assimp extended by me to allow the import of a larger number of .obj files. Instead, the texture import function is contained in textureLoader.c library, and accepts in input only 24-bit Bitmap images (.bmp).

### Parity
The player can move in four directions (two directions), each obtained by successive rotations of 90 degrees; this implies that the player at any time will always move parallel to the X axis (and therefore perpendicular to the Z axis) or parallel to the Z axis (and therefore perpendicular to the X axis). Each rotation causes switch between these two conditions, which can be summarized with a mechanism of parity, or binary; for this reason, both to the player and to the AI ​​ is assigned a variable of unique parity. It was chosen by default to set the parity to 0 when the AI ​​and the player moves parallel to the Z axis and 1 when they move parallel to the X axis of the game. At the starting of the game both the player and the AI moves parallel to Z and parity is set to 0; at each rotation of one of the two the corresponding parity variable is modified by making vary from 0 to 1 or vice versa.

### Fixed and variable coordinate
Let's talk about two key concepts to understand the collisions: fixed coordinate and variable coordinate. Summarizing what has been said previously we have two cases for the player's movement and IA: direction parallel to the X axis or parallel to the Z axis. This implies, as a consequence, that if the player is moving parallel to X, the X coordinate is call fixed as it remains constant, while the Z coordinate is said variable as it changes continuously. Conversely, as regards the movement in a direction parallel to Z; This result, albeit simple, it helps to understand the operation of the collision detection system, which we will discuss now.

### Collision detection
The collision detection algorithm works in this way:
1) For each exterior wall that defines the game and every wall created by the player and AI, we check if the end point (momentary, as both the player and the AI moves constantly) of the actual wall (which is creating by the player or the AI, the mechanism is the same) has the coordinate variable in the range which, as mentioned in the "MANAGEMENT OF THE GAME WALLS", is shown graphically as the wall thickness; if it is not in this range we'll repeat step 1 with the next wall of the list, otherwise we'll proceed with step 2.
2) We check if the wall that is being built is also between the extremes of the wall currently under analysis (also checking if it was built in ascending order, from smaller variable coordinates to larger, or in descending order); if these two conditions are both true you have a collision and is returned by the function 1 if the player has won (the IA has collided with a wall) or 2 (the player has collided with a wall).

### Mode of operation of AI
The mode of operation of the opponent AI works basically in the same way as the collision detection, in which is added a verification walls offset greater than the thickness of the wall; it will decide whether or not to turn in the presence of a wall or his opponent on the basis of the choice of random variables. In addition to that, the AI can turn randomly alone and has fixed rules relating to the bounding walls of the game.

### Relevant variables
* The walls of the player and AI are stored in separate dynamic matrix of NX4 dimension, with N incrementing in base on the number of walls created by the one or the other.
* The parity mechanism of the player and AI is achieved with two integer variables variants between 0 and 1 which are updated with the creation of a new wall.
* A static variable called NUMOBJ was created in order to contain the number of different .obj files imported within the game (2).
* For the creation of the Player walls, the AI walls and the elements of the playing field are used many static variables, contained mainly in WorldProperties.h file.
* The variables that control the camera are all dynamics; the VUP (View Up Vector) in particular is used to get the five different cameras of the game. 



## Italiano

### Introduzione
TRON - The LightCycle Game è un gioco realizzato per l'esame di Ingegneria Grafica del Politecnico di Torino da Antonio Marceddu. La parte di programmazione e una frazione della parte grafica è stata realizzata in OpenGL con l'aggiunta delle librerie GLUT, Assimp e DevIL, mentre la frazione rimanente (realizzazione delle lightcycle) è stata realizzata con Blender. Questa guida ha come obbiettivo quello di esplicare e motivare le scelte realizzative del progetto per scopo didattico senza addentrarsi troppo nel codice dello stesso, in quanto è interamente commentato in italiano.

### Descrizione del gioco
Il gioco è una riproposizione della celebre gara tra lightcycle del film TRON; citando wikipedia, le lightcycle sono delle motociclette usate in gare mortali dette “motolabirinti” che si svolgono all'interno di una cosiddetta “griglia di gioco”. Le gare sono letali perchè le lightcycle, al loro passaggio, rilasciano dietro di sé un muro di energia contro il quale è possibile schiantarsi, in maniera simile a quando accade nel gioco Snake, divenuto celebre per la presenza in moltissimi telefoni cellulari. Per vincere il gioco, occorre far schiantare l'avversario contro queste pareti o contro i muri che delimitano la griglia di gioco.

### Schematizzazione della mappa del gioco
La mappa del gioco, per quanto riguarda sia la memorizzazione dei muri creati dal giocatore e dalla IA che il funzionamento dell'IA avversaria e delle collisioni, viene schematizzata in due dimensioni; vengono cioè considerate solamente la coordinata X e la coordinata Z. Viene totalmente trascurata la coordinata Y, che viene utilizzata solo nella fase di disegno per realizzare l'ambiente tridimensionale.

### Gestione dei muri del gioco
I muri del gioco vengono gestiti come segmenti che vengono disegnati da una coordinata (X1,Z1) ad una coordinata (X2,Z2). La prima coordinata è fissa (punto di partenza del muro) mentre la seconda (punto finale del muro) varia al variare della posizione del giocatore. Ad ogni rotazione del giocatore e dell'IA il punto di rotazione diventa il punto finale del segmento (muro) precedente e il punto iniziale del nuovo segmento (muro) che viene istanziato, avente verso differente rispetto a quello precedente. Nella fase di disegno, i segmenti vengono rappresentati con
 un offset (positivo e negativo) che rappresenta lo spessore del muro.

### Reshaping
Il reshape è totalmente dinamico: il gioco e tutti i menù vengono adattati alle variazioni di risoluzione, con la ovvia conseguenza che molti menu' e scritte, in base alla risoluzione impostata, potrebbero non essere più perfettamente leggibili. L'esperienza di gioco è ottimizzata per una giocabilità in 16:9 (la risoluzione iniziale è di 1280 x 720).

### Stabilizzazione del frame rate
Per la stabilizzazione del frame rate, è stata creata una funzione di idle che richiama la funzione di ridisegno dello schermo ogni 33 ms circa, in modo tale da avere un numero medio di fotogrammi per secondo (fps) pari a circa 30. Ciò porta ad avere una velocità di esecuzione del gioco indipendente dalla macchina in cui viene eseguito. 

### Audio
Per l'audio viene usata una funzione di presente in windows.h, PlaySound; se si importa il listato in una macchina Linux, commentare la funzione predetta e gli include di windows.h, dove presenti, in modo da permettere l'avvio del programma.

### Importazione dei file di Blender e delle texture
L'importazione dei file realizzati con Blender (e poi salvati in .obj) viene realizzata dalla libreria objectImporter.c, libreria di esempio d'uso di Assimp da me estesa per l'importazione di un numero maggiore di file .obj. Invece, la funzione di importazione delle texture è contenuta nella libreria textureLoader.c, ed accetta in ingresso solo immagini di tipo Bitmap (.bmp) a 24 bit.

### Parità
Il giocatore si può muovere in quattro versi (due direzioni), ognuno ottenibile tramite rotazioni successive di 90 gradi; ciò implica che il giocatore in ogni momento si muoverà sempre parallelo all'asse X (e quindi perpendicolare all'asse Z) o parallelo all'asse Z (e quindi perpendicolare all'asse X). Ogni rotazione fa alternare queste due condizioni, che si possono schematizzare con un meccanismo a parità, o binario; per questo motivo, sia al giocatore che all'IA viene assegnata una variabile di parità univoca. E' stato scelto per default di impostare a 0 la parità quando l'IA e il giocatore si muovono parallelamente all'asse Z e ad 1 quando si muovono parallelamente rispetto all'asse X. All'inizio del gioco, sia il giocatore che l'IA si muovono parallelamente a Z e la parità viene impostata a 0; ad ogni rotazione di uno dei due viene modificata la corrispettiva variabile di parità facendola variare da 0 ad 1 o viceversa. 

### Coordinata fissa e coordinata variabile
Parliamo ora di due concetti chiave per comprendere le collisioni: quello di coordinata fissa e di coordinata variabile. Riassumendo quanto detto in precedenza abbiamo due casi per il movimento di giocatore e IA: direzione parallela all'asse X o parallela all'asse Z. Ciò implica, come conseguenza, che se il giocatore si sta muovendo parallelamente ad X, la coordinata X viene chiamata fissa in quanto rimane costante, mentre la coordinata Z viene detta variabile in quanto cambia continuamente. Viceversa per quanto riguarda il movimento in direzione parallela a Z; questa conseguenza, seppur semplice, aiuta a capire il funzionamento del sistema di rilevazione delle collisioni, di cui discuteremo ora.

### Collisioni
L'algoritmo di rilevazione delle collisioni funziona in questo modo:
1) Per ogni muro esterno che delimita il gioco e per ogni muro creato dal giocatore e dall'IA, si verifica se il punto finale (momentaneo, in quanto sia il giocatore e l'IA si muovono costantemente) del muro attuale (che sta creando o il giocatore o l'IA, il meccanismo è lo stesso) ha la coordinata variabile compresa nel range che, come detto nella sezione “GESTIONE DEI MURI DEL GIOCO”, viene rappresentato graficamente come lo spessore del muro; se non è compreso in questo range si ripete il passo 1 con il muro successivo della lista, altrimenti si procede con il passo 2.
2) Si verifica se il muro che si sta costruendo è inoltre compreso tra gli estremi del muro attualmente in analisi (verificando anche se è stato costruito in modo ascendente, cioè da valori della coordinata variabile più piccoli a valori più grandi, o viceversa discendente); se queste due condizioni sono entrambe vere si ha una collisione e viene restituito dalla funzione 1 se ha vinto il giocatore (la IA ha colliso con un muro) o 2 (il giocatore ha colliso con un muro).

### IA avversaria
Il funzionamento dell'IA avversaria è fondamentalmente lo stesso di quello della rilevazione delle collisioni, a cui viene aggiunto un offset di verifica muri maggiore rispetto a quello dello spessore del muro; essa deciderà o meno di girare in presenza di un muro suo o dell'avversario in base a delle variabili di scelta randomiche. Oltre a ciò, la IA può svoltare randomicamente da sola e ha delle regole fisse di verifica riguardo ai muri di delimitazione del gioco.

### Variabili rilevanti
* I muri del giocatore e dell'IA vengono memorizzati in matrici dinamiche separate di dimensione Nx4, con N incrementante in base al numero di muri creati dall'uno o dall'altro.
* Il meccanismo di parità del giocatore e dell'IA viene realizzato con due variabili intere varianti tra 0 ed 1 che vengono aggiornate alla creazione di un nuovo muro.
* E' stata creata una variabile statica NUMOBJ contenente il numero di file .obj diversi importati all'interno del gioco (2). 
* Per la creazione dei muri del giocatore, dell'IA e degli elementi del campo di gioco si usano molte variabili statiche, contenute soprattutto nel file WorldProperties.h
* Le variabili che controllano la telecamera sono tutte dinamiche; il VUP (View Up Vector) in particolare viene usato per ottenere le cinque diverse telecamere del gioco.
