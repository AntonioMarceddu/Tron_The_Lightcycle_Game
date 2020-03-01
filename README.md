# Tron The Lightcycle Game

## Link at the video presentation: https://www.youtube.com/watch?v=4oe2F32DFtM
Description available in english and italian below.

## English

### Introduction
TRON - The LightCycle Game is a game created for the Graphic Computer Science exam of the Polytechnic of Turin by Antonio Marceddu. The programming part and a fraction of the graphic part was made in OpenGL with the addition of the GLUT, Assimp and DevIL libraries, while the remaining part (realization of the lightcycle) was made with Blender. This guide aims to explain and motivate, for educational purposes, the realization choices of the project, without going too far into the code itself as it is entirely commented in Italian.

### Game description
The game is a re-presentation of the famous lightcycle race of the film TRON; citing the respective wikipedia page, the light bikes are motorbikes used in deadly races called "motor mazes" which take place inside a so-called "game grid". The races are lethal because the lightcycle, as they pass, release behind them a wall of energy against which it is possible to crash, in a similar way to when it happens in the Snake game, which has become famous for the presence in many mobile phones. To win the game, you must crash your opponent against these walls or against the walls that delimit the game grid.

### Schematization of the game map
The game map, as regards both the memorization of the walls created by the player and the AI and the functioning of the opposing AI and of the collisions, is schematized in two dimensions; that is, only the X and Z coordinates are considered. The Y coordinate is totally neglected, which is used only in the drawing phase to create the three-dimensional environment.

### Management of the walls of the game
The walls of the game are managed as segments that are drawn from a coordinate (X1, Z1) to a coordinate (X2, Z2). The first coordinate is fixed (starting point of the wall), while the second (ending point of the wall) varies according to the position of the player. With each rotation of the player and the AI, the rotation point becomes the endpoint of the previous segment (wall) and the starting point of the new segment (wall) which is instantiated, having a different sense than the previous one. In the drawing phase, the segments are represented with an offset (positive and negative) that represents the thickness of the wall.

### Reshaping
The reshape is totally dynamic: the game and all menus are adapted to changes in resolution, with the obvious consequence that many menus and writings, depending on the set resolution, may no longer be perfectly legible. The gaming experience is optimized for 16: 9 gameplay (initial resolution is 1280 x 720).

### Stabilization of the frame rate
For the stabilization of the frame rate, an idle function that calls the screen redesign function every 33 ms approximately has been created, so that the average number of frames per second (fps) is approximately 30. This leads to having an execution speed of the game independent of the machine in which it runs.

### Audio
As for audio, a function present in windows.h, PlaySound is used; if you import the listing into a Linux machine, you must therefore comment on both the aforementioned function and the includes windows.h, where present, in order to allow the program to start.

### Import of Blender files and textures
The import of the files created with Blender (and then saved in .obj) is carried out by the objectImporter.c library, an example of Assimp's use library extended by me to allow the import of a greater number of .obj files. The texture import function is instead contained in the textureLoader.c library and accepts only 24-bit bitmap (.bmp) images as input.

### Parity
The player can move in four directions (two senses), each obtainable through successive rotations of 90 degrees; this implies that the player will always move at any time parallel to the X-axis (and therefore perpendicular to the Z-axis) or parallel to the Z-axis (and therefore perpendicular to the X-axis). Each rotation alternates between these two conditions, which can be schematized with an equal or binary mechanism; for this reason, both the player and the AI are assigned a unique parity variable. By default, it was chosen to set parity to 0 when the AI and the player move parallel to the Z-axis and to 1 when they move parallel to the X-axis. At the start of the game, both the player and the AI move parallel to Z and the parity is set to 0; the rotation of one of the two changes the respective parity variable, making it vary from 0 to 1 or vice versa.

### Fixed coordinate and variable coordinate
Now let's talk about two key concepts to understand collisions: fixed coordinate and variable coordinate. Summarizing what has been said above, we have two cases for player movement and AI: direction parallel to the X-axis or parallel to the Z-axis. This implies, as a consequence, that if the player is moving parallel to X, the X coordinate is called fixed because it remains constant, while the Z coordinate is called variable because it changes continuously. Vice versa, as regards movement in the direction parallel to Z; this consequence, albeit simple, helps to understand the operation of the collision detection system, which we will discuss now.

### Collisions
The collision detection algorithm works like this:
1) For each external wall that delimits the game and for each wall created by the player and the AI, it is checked whether the endpoint (momentary, as both the player and the AI move constantly) of the current wall (which is creating either the player or the AI, the mechanism is the same) has the variable coordinate included in the range which, as mentioned in the section "MANAGEMENT OF THE WALLS OF THE GAME", is graphically represented as the thickness of the wall; if it is not included in this range, repeat step 1 with the next wall of the list, otherwise proceed with step 2.
2) It occurs if the wall being built is also included between the ends of the wall currently being analyzed (also checking if it was built in an ascending way, i.e. from smaller variable coordinate values to larger values, or vice versa descending); if these two conditions are both true there is a collision and an integer equal to 1 is returned from the function if the player has won (the AI has collided with a wall) or 2 if the player has lost (the player has collided with a wall).

### AI opponent
The opposing AI is rather spartan and far from being competitive, as it was not the focus of the project and the respective exam. The respective algorithm is basically similar to that of collision detection, to which is added a wall verification offset greater than that of the wall thickness; it will decide whether or not to turn in the presence of a wall of his or his opponent based on random choice variables. In addition, the AI can turn on its own and has fixed rules of verification regarding the boundary walls of the game.

### Relevant variables
* The player and AI walls are stored in separate dynamic arrays of size Nx4, with N increased based on the number of walls created by one or the other.
* The player and AI parity mechanism is accomplished with two integer variables, updated on the creation of a new wall.
* A static variable NUMOBJ has been created, containing the number of different .obj files imported into the game (2).
* Many static variables are used to create the walls of the player, the AI and the elements of the playing field, contained above all in the file WorldProperties.h
* The variables that control the camera are completely dynamic; in particular, the VUP (View Up Vector) is used to obtain the five different cameras of the game.



## Italiano

### Introduzione
TRON - The LightCycle Game è un gioco realizzato per l'esame di Informatica Grafica del Politecnico di Torino da Antonio Marceddu. La parte di programmazione e una frazione della parte grafica è stata realizzata in OpenGL con l'aggiunta delle librerie GLUT, Assimp e DevIL, mentre la frazione rimanente (realizzazione delle lightcycle) è stata realizzata con Blender. Questa guida ha come obbiettivo quello di esplicare e motivare, per scopi didattici, le scelte realizzative del progetto, senza addentrarsi troppo nel codice stesso in quanto è interamente commentato in italiano.

### Descrizione del gioco
Il gioco è una riproposizione della celebre gara tra lightcycle del film TRON; citando la rispettiva pagina wikipedia, le lightcycle sono delle motociclette usate in gare mortali dette “motolabirinti” che si svolgono all'interno di una cosiddetta “griglia di gioco”. Le gare sono letali perché le lightcycle, al loro passaggio, rilasciano dietro di esse un muro di energia contro il quale è possibile schiantarsi, in maniera simile a quando accade nel gioco Snake, divenuto celebre per la presenza in moltissimi telefoni cellulari. Per vincere il gioco, occorre far schiantare l'avversario contro queste pareti o contro i muri che delimitano la griglia di gioco.

### Schematizzazione della mappa del gioco
La mappa del gioco, per quanto riguarda sia la memorizzazione dei muri creati dal giocatore e dall'IA che il funzionamento dell'IA avversaria e delle collisioni, viene schematizzata in due dimensioni; vengono cioè considerate solamente le coordinate X e Z. Viene totalmente trascurata la coordinata Y, che viene utilizzata solo nella fase di disegno per realizzare l'ambiente tridimensionale.

### Gestione dei muri del gioco
I muri del gioco vengono gestiti come segmenti che vengono disegnati da una coordinata (X1, Z1) ad una coordinata (X2, Z2). La prima coordinata è fissa (punto di partenza del muro), mentre la seconda (punto finale del muro) varia al variare della posizione del giocatore. Ad ogni rotazione del giocatore e dell'IA, il punto di rotazione diventa il punto finale del segmento (muro) precedente e il punto iniziale del nuovo segmento (muro) che viene istanziato, avente un verso differente rispetto a quello precedente. Nella fase di disegno, i segmenti vengono rappresentati con un offset (positivo e negativo) che rappresenta lo spessore del muro.

### Reshaping
Il reshape è totalmente dinamico: il gioco e tutti i menù vengono adattati alle variazioni di risoluzione, con la ovvia conseguenza che molti menù e scritte, in base alla risoluzione impostata, potrebbero non essere più perfettamente leggibili. L'esperienza di gioco è ottimizzata per una giocabilità in 16:9 (la risoluzione iniziale è di 1280 x 720).

### Stabilizzazione del frame rate
Per la stabilizzazione del frame rate, è stata creata una funzione di idle che richiama la funzione di ridisegno dello schermo ogni 33 ms circa, in modo tale che il numero medio di fotogrammi per secondo (fps) sia circa 30. Ciò porta ad avere una velocità di esecuzione del gioco indipendente dalla macchina in cui viene eseguito. 

### Audio
Per quanto riguarda l'audio, viene usata una funzione presente in windows.h, PlaySound; se si importa il listato in una macchina Linux, occorre quindi commentare sia la funzione predetta che gli include di windows.h, dove presenti, in modo da permettere l'avvio del programma.

### Importazione dei file di Blender e delle texture
L'importazione dei file realizzati con Blender (e poi salvati in .obj) viene realizzata dalla libreria objectImporter.c, libreria di esempio d'uso di Assimp da me estesa per consentire l'importazione di un numero maggiore di file .obj. La funzione di importazione delle texture è invece contenuta nella libreria textureLoader.c ed accetta in ingresso solo immagini di tipo bitmap (.bmp) a 24 bit.

### Parità
Il giocatore si può muovere in quattro versi (due direzioni), ognuno ottenibile tramite rotazioni successive di 90 gradi; ciò implica che il giocatore si muoverà in ogni momento sempre parallelo all'asse X (e quindi perpendicolare all'asse Z) o parallelo all'asse Z (e quindi perpendicolare all'asse X). Ogni rotazione fa alternare queste due condizioni, che si possono schematizzare con un meccanismo a parità, o binario; per questo motivo, sia al giocatore che all'IA viene assegnata una variabile di parità univoca. Come default, è stato scelto di impostare a 0 la parità quando l'IA e il giocatore si muovono parallelamente all'asse Z e ad 1 quando si muovono parallelamente rispetto all'asse X. All'inizio del gioco, sia il giocatore che l'IA si muovono parallelamente a Z e la parità viene impostata a 0; alla rotazione di uno dei due viene modificata la rispettiva variabile di parità, facendola variare da 0 ad 1 o viceversa. 

### Coordinata fissa e coordinata variabile
Parliamo ora di due concetti chiave per comprendere le collisioni: coordinata fissa e coordinata variabile. Riassumendo quanto detto in precedenza, abbiamo due casi per il movimento di giocatore e IA: direzione parallela all'asse X o parallela all'asse Z. Ciò implica, come conseguenza, che se il giocatore si sta muovendo parallelamente a X, la coordinata X viene chiamata fissa in quanto rimane costante, mentre la coordinata Z viene detta variabile in quanto cambia continuamente. Viceversa, per quanto riguarda il movimento in direzione parallela a Z; questa conseguenza, seppur semplice, aiuta a capire il funzionamento del sistema di rilevazione delle collisioni, di cui discuteremo ora.

### Collisioni
L'algoritmo di rilevazione delle collisioni funziona in questo modo:
1) Per ogni muro esterno che delimita il gioco e per ogni muro creato dal giocatore e dall'IA, si verifica se il punto finale (momentaneo, in quanto sia il giocatore e l'IA si muovono costantemente) del muro attuale (che sta creando o il giocatore o l'IA, il meccanismo è lo stesso) ha la coordinata variabile compresa nel range che, come detto nella sezione “GESTIONE DEI MURI DEL GIOCO”, viene rappresentato graficamente come lo spessore del muro; se non è compreso in questo range si ripete il passo 1 con il muro successivo della lista, altrimenti si procede con il passo 2.
2) Si verifica se il muro che si sta costruendo è inoltre compreso tra gli estremi del muro attualmente in analisi (verificando anche se è stato costruito in modo ascendente, cioè da valori della coordinata variabile più piccoli a valori più grandi, o viceversa discendente); se queste due condizioni sono entrambe vere si ha una collisione e viene restituito dalla funzione un intero pari a 1 se il giocatore ha vinto (la IA ha colliso con un muro) o 2 se il giocatore ha perso (il giocatore ha colliso con un muro).

### IA avversaria
L’IA avversaria è piuttosto spartana e lungi dall’essere competitiva, in quanto non era il focus del progetto e del rispettivo esame. Il rispettivo algoritmo è fondamentalmente simile a quello di rilevazione delle collisioni, a cui viene aggiunto un offset di verifica muri maggiore rispetto a quello dello spessore del muro; essa deciderà o meno di girare in presenza di un muro suo o dell'avversario in base a delle variabili di scelta randomiche. Oltre a ciò, la IA può svoltare da sola e ha delle regole fisse di verifica riguardo ai muri di delimitazione del gioco.

### Variabili rilevanti
* I muri del giocatore e dell'IA sono memorizzati in matrici dinamiche separate di dimensione Nx4, con N incrementato in base al numero di muri creati dall'uno o dall'altro.
* Il meccanismo di parità del giocatore e dell'IA viene realizzato con due variabili intere, aggiornate alla creazione di un nuovo muro.
* È stata creata una variabile statica NUMOBJ, contenente il numero di file .obj diversi importati all'interno del gioco (2). 
* Per la creazione dei muri del giocatore, dell'IA e degli elementi del campo di gioco si usano molte variabili statiche, contenute soprattutto nel file WorldProperties.h
* Le variabili che controllano la telecamera sono del tutto dinamiche; in particolare, il VUP (View Up Vector) viene usato per ottenere le cinque diverse telecamere del gioco.
