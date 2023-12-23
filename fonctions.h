#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 10   // size of the board
#define NB_BOAT 5 // number of boats

// il y a ici toutes les header de fonctions et les structures qui sont utilisées dans le main pour la bataille navale

// enumeration for the type of the case
typedef enum
{
    WATER,
    WATER_SHOT,
    BOAT,
    WRECK,
} CaseType;

// enumeration for the orientation of the boats
typedef enum
{
    HORIZONTAL,
    VERTICAL
} Orientation;

// structure for the boats
typedef struct
{
    int size;
    int x;
    int y;
    Orientation orientation;
    int hits;
} Boat;

// structure for the board
typedef struct
{
    CaseType **matrix;
    int size;
} Board;

// structure for "game"
typedef struct
{
    Board *playerBoard;
    Board *computerBoard;
    Boat **playerBoats;
    Boat **computerBoats;
} Game;

// function to create a board
Board *createBoard(int size);

// function to create a boat
Boat *createBoat(int size, int x, int y, Orientation orientation);

// function for check if a boat can be placed
int canPlaceBoat(Board *board, Boat *boat);

// function to place a boat
void placeBoat(Board *board, Boat *boat);

// function to initialize the boats
void initializeBoats(Board *board, Boat **boats, int nbBoats);

// function to create a game
Game *createGame(int size, int nbBoat);

// function to clean the buffer
void cleanBuffer();

// function to display the board
void displayBoard(Board *board, int isPlayer);

// function to check if the boat is wrecked
int isBoatWrecked(Boat *boat);

// function to fire a shot
void fireShot(Board *board, int x, int y, Boat **boats);

// function for the player turn
void playerTurn(Game *game);

// function to play a turn for the computer
void computerTurn(Game *game);

// function to check if the game is over
int isGameOver(Game *game);

// function to free the memory
void freeGame(Game *game);

// function to check if the player boats are wrecked
int playerBoatsWrecked(Game *game);

#endif // FONCTIONS_H
