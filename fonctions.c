#include "fonctions.h"

// function to create a board
Board *createBoard(int size)
{
    // check if the size is correct
    if (size != SIZE)
    {
        printf("Error: the size of the board is not correct\n");
        exit(1);
    }
    // allocation of the board
    Board *board = malloc(sizeof(Board));
    if (board == NULL)
    {
        printf("Error: allocation failed for board\n");
        exit(1);
    }

    board->size = size;

    board->matrix = malloc(size * sizeof(int *));
    if (board->matrix == NULL)
    {
        printf("Error: allocation failed for matrix creation\n");
        free(board);
        exit(1);
    }
    // allocation of the matrix and set all the cases to WATER
    for (int i = 0; i < size; i++)
    {
        board->matrix[i] = malloc(size * sizeof(CaseType *));
        if (board->matrix[i] == NULL) // if the allocation failed we free all the memory allocated before and exit the program
        {
            printf("Error: allocation failed for matrix creation\n");
            for (int j = 0; j < i; j++)
            {
                free(board->matrix[j]);
            }
            free(board->matrix);
            free(board);
            exit(1);
        }
        for (int j = 0; j < size; j++)
        {
            board->matrix[i][j] = WATER;
        }
    }
    return board;
}

// function to create a boat
Boat *createBoat(int size, int x, int y, Orientation orientation)
{
    // check if the size is correct
    if (size < 2 || size > 5)
    {
        printf("Error: the size of the boat is not correct\n");
        exit(1);
    }
    // check if the position is correct
    if (x < 0 || y < 0)
    {
        printf("Error: the position of the boat is not correct\n");
        exit(1);
    }
    // check if the orientation is correct
    if (orientation != HORIZONTAL && orientation != VERTICAL)
    {
        printf("Error: the orientation of the boat is not correct\n");
        exit(1);
    }
    // allocation of the boat
    Boat *boat = malloc(sizeof(Boat));
    if (boat == NULL)
    {
        printf("Error: allocation failed for boat\n");
        exit(1);
    }

    boat->size = size;
    boat->x = x;
    boat->y = y;
    boat->orientation = orientation;

    return boat;
}

// function to check if the boat can be placed at a certain position
int canPlaceBoat(Board *board, Boat *boat)
{
    // check if the board is correct
    if (board == NULL)
    {
        printf("Error: the board is not correct\n");
        exit(1);
    }
    // check if the boat is correct
    if (boat == NULL)
    {
        printf("Error: the boat is not correct\n");
        exit(1);
    }
    // check if the boat is in the board
    if (boat->orientation == HORIZONTAL && boat->x + boat->size > board->size)
    {
        return 0;
    }
    if (boat->orientation == VERTICAL && boat->y + boat->size > board->size)
    {
        return 0;
    }

    // check if the boat is not on another boat
    for (int i = 0; i < boat->size; i++)
    {
        int x = boat->x + (boat->orientation == HORIZONTAL ? i : 0);
        int y = boat->y + (boat->orientation == VERTICAL ? i : 0);

        if (board->matrix[x][y] == BOAT)
        {
            return 0;
        }
    }

    return 1;
}

// function to place a boat on a board
void placeBoat(Board *board, Boat *boat)
{
    int retour = 0;
    // check if the boat can be placed
    retour = canPlaceBoat(board, boat);
    if (retour == 0)
    {
        printf("Error: the boat can't be placed\n");
        exit(1);
    }

    // place the boat
    for (int i = 0; i < boat->size; i++)
    {
        int x = boat->x + (boat->orientation == HORIZONTAL ? i : 0);
        int y = boat->y + (boat->orientation == VERTICAL ? i : 0);

        board->matrix[x][y] = BOAT;
    }
}

// function to initialize the boats
void initializeBoats(Board *board, Boat **boats, int nbBoats)
{
    // check all the parameters
    //  check if the board is correct
    if (board == NULL)
    {
        printf("Error: the board is not correct\n");
        exit(1);
    }
    // check if the array of boats is correct
    if (boats == NULL)
    {
        printf("Error: the array of boats is not correct\n");
        exit(1);
    }
    // check if the number of boats is correct
    if (nbBoats != NB_BOAT)
    {
        printf("Error: the number of boats is not correct\n");
        exit(1);
    }

    // Boat sizes for 5 boats
    int boatSizes[] = {5, 4, 3, 3, 2};

    // Initialize boats
    for (int i = 0; i < nbBoats; i++)
    {
        Boat *boat;
        do
        {
            // Get boat size
            int size = boatSizes[i];
            // Generate random position and orientation
            int x = rand() % board->size;
            int y = rand() % board->size;
            Orientation orientation = rand() % 2 == 0 ? HORIZONTAL : VERTICAL;
            // Create boat
            boat = createBoat(size, x, y, orientation);
        } while (!canPlaceBoat(board, boat));
        // Place boat on the board
        for (int j = 0; j < boat->size; j++)
        {
            int x = boat->x + (boat->orientation == HORIZONTAL ? j : 0);
            int y = boat->y + (boat->orientation == VERTICAL ? j : 0);
            board->matrix[x][y] = BOAT;
        }
        // Store boat in array
        boats[i] = boat;
    }
}

// function to create a game
Game *createGame(int size, int nbBoat)
{
    // check if the size is correct
    if (size != SIZE)
    {
        printf("Error: the size of the board is not correct\n");
        exit(1);
    }
    // check if the number of boats is correct
    if (nbBoat != NB_BOAT)
    {
        printf("Error: the number of boats is not correct\n");
        exit(1);
    }
    // allocation of the game
    Game *game = malloc(sizeof(Game));
    if (game == NULL)
    {
        printf("Error: allocation failed for game\n");
        exit(1);
    }

    game->playerBoard = createBoard(size);
    game->computerBoard = createBoard(size);

    game->playerBoats = malloc(nbBoat * sizeof(Boat *));
    if (game->playerBoats == NULL)
    {
        printf("Error: allocation failed for playerBoats\n");
        exit(1);
    }

    game->computerBoats = malloc(nbBoat * sizeof(Boat *));
    if (game->computerBoats == NULL)
    {
        printf("Error: allocation failed for computerBoats\n");
        exit(1);
    }

    initializeBoats(game->playerBoard, game->playerBoats, nbBoat);
    initializeBoats(game->computerBoard, game->computerBoats, nbBoat);

    return game;
}

// function to clear the buffer
void cleanBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

// function to display the board
void displayBoard(Board *board, int isPlayer)
{
    // check if the board is correct
    if (board == NULL)
    {
        printf("Error: the board is not correct\n");
        exit(1);
    }

    // display the board
    if (isPlayer == 1)
    {
        printf("Ton plateau:\n");
    }
    else
    {
        printf("Plateau de l'ordinateur:\n");
    }
    // print column number
    printf("  ");
    for (int i = 0; i < board->size; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < board->size; i++)
    {
        // print row number
        printf("%d ", i);
        for (int j = 0; j < board->size; j++)
        {
            // print the case
            if (board->matrix[i][j] == WATER)
            {
                printf("~ ");
            }
            else if (board->matrix[i][j] == WATER_SHOT)
            {
                printf("o ");
            }
            else if (board->matrix[i][j] == BOAT)
            {
                if (isPlayer == 1)
                {
                    printf("B ");
                }
                else
                {
                    printf("~ ");
                }
            }
            else if (board->matrix[i][j] == WRECK)
            {
                printf("X ");
            }
        }
        printf("\n");
    }
}

// function to play a turn for the player
void playerTurn(Game *game)
{
    // ask the player to enter a position
    int x, y, retour = 0;
    printf("Entrez la position x");
    while (retour != 1)
    {
        retour = scanf("%d", &x);
        cleanBuffer();
    }
    retour = 0;
    printf("Entrez la position y");
    while (retour != 1)
    {
        retour = scanf("%d", &y);
        cleanBuffer();
    }
    // check if the position is correct
    if (x < 0 || x >= game->playerBoard->size || y < 0 || y >= game->playerBoard->size)
    {
        printf("la position est en dehors du plateau de jeu\n");
        exit(1);
    }
    // fire at the position
    if (game->computerBoard->matrix[x][y] == BOAT)
    {
        game->computerBoard->matrix[x][y] = WRECK;
        printf("Touché\n");
    }
    else
    {
        game->computerBoard->matrix[x][y] = WATER_SHOT;
        printf("A l'eau\n");
    }
}