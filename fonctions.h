/**
 * @file fonctions.h
 * @brief Header file containing function declarations for game logic.
 */

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 10   // size of the board
#define NB_BOAT 5 // number of boats

// il y a ici toutes les header de fonctions et les structures qui sont utilisées dans le main pour la bataille navale

/**
 * @enum CaseType
 * @brief Represents the type of a case.
 */
typedef enum
{
    WATER,
    WATER_SHOT,
    BOAT,
    WRECK,
} CaseType;

/**
 * @enum Orientation
 * @brief Represents the orientation of a boat.
 */
typedef enum
{
    HORIZONTAL,
    VERTICAL
} Orientation;

/**
 * @struct Boat
 * @brief Represents a boat.
 */
typedef struct
{
    int size;                /**< Size of the boat. */
    int x;                   /**< X position of the boat. */
    int y;                   /**< Y position of the boat. */
    Orientation orientation; /**< Orientation of the boat (HORIZONTAL or VERTICAL). */
    int hits;                /**< Number of hits the boat has taken. */
} Boat;

/**
 * @struct Board
 * @brief Represents the game board.
 */
typedef struct
{
    CaseType **matrix; /**< 2D matrix representing the board. */
    int size;          /**< Size of the board. */
} Board;

/**
 * @struct Game
 * @brief Represents the game.
 */
typedef struct
{
    Board *playerBoard;   /**< The player's board. */
    Board *computerBoard; /**< The computer's board. */
    Boat **playerBoats;   /**< The player's boats. */
    Boat **computerBoats; /**< The computer's boats. */
} Game;

/**
 * @brief Creates a board.
 * @param size The size of the board.
 * @return A pointer to the board.
 */
Board *createBoard(int size);

/**
 * @brief Creates a boat.
 * @param size The size of the boat.
 * @param x The x position of the boat.
 * @param y The y position of the boat.
 * @param orientation The orientation of the boat.
 * @return A pointer to the boat.
 */
Boat *createBoat(int size, int x, int y, Orientation orientation);

/**
 * @brief Checks if a boat can be placed on the board.
 * @param board The board.
 * @param boat The boat.
 * @return 1 if the boat can be placed, 0 otherwise.
 */
int canPlaceBoat(Board *board, Boat *boat);

/**
 * @brief Places a boat on the board.
 * @param board The board.
 * @param boat The boat.
 */
void placeBoat(Board *board, Boat *boat);

/**
 * @brief Initializes the boats on the board.
 * @param board The board.
 * @param boats The boats.
 * @param nbBoats The number of boats.
 */
void initializeBoats(Board *board, Boat **boats, int nbBoats);

/**
 * @brief Creates a game.
 * @param size The size of the board.
 * @param nbBoat The number of boats.
 * @return A pointer to the game.
 */
Game *createGame(int size, int nbBoat);

/**
 * @brief Clears the buffer.
 */
void cleanBuffer();

/**
 * @brief Displays the board.
 * @param board The board.
 * @param isPlayer 1 if the board is the player's, 0 otherwise.
 */
void displayBoard(Board *board, int isPlayer);

/**
 * @brief Displays the board with the boats.
 * @param board The board.
 * @param isPlayer 1 if the board is the player's, 0 otherwise.
 */
int isBoatWrecked(Boat *boat);

/**
 * @brief Displays the board with the boats.
 * @param board The board.
 * @param isPlayer 1 if the board is the player's, 0 otherwise.
 */
void fireShot(Board *board, int x, int y, Boat **boats);

/**
 * @brief Displays the board with the boats.
 * @param board The board.
 * @param isPlayer 1 if the board is the player's, 0 otherwise.
 */
void playerTurn(Game *game);

/**
 * @brief Displays the board with the boats.
 * @param board The board.
 * @param isPlayer 1 if the board is the player's, 0 otherwise.
 */
void computerTurn(Game *game);

/**
 * @brief Checks if the game is over.
 * @param game The game.
 * @return 1 if the game is over, 0 otherwise.
 */
int isGameOver(Game *game);

/**
 * @brief Frees the memory allocated for the board.
 * @param board The board.
 */
void freeGame(Game *game);

/**
 * @brief Frees the memory allocated for the board.
 * @param board The board.
 */
int playerBoatsWrecked(Game *game);

#endif // FONCTIONS_H
