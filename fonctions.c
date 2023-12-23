#include "fonctions.h"

/*!
 * \brief function to create a board
 * \param size the size of the board
 * \return the board
 */
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

/*!
 * \brief function to create a boat
 * \param size the size of the boat
 * \param x the x position of the boat
 * \param y the y position of the boat
 * \param orientation the orientation of the boat
 * \return the boat
 */
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
    boat->hits = 0;

    return boat;
}

/*!
 * \brief function for check if a boat can be placed
 * \param board the board
 * \param boat the boat
 * \return 1 if the boat can be placed, 0 otherwise
 */
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

/*!
 * \brief function to place a boat
 * \param board the board
 * \param boat the boat
 */
void placeBoat(Board *board, Boat *boat)
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

/*!
 * \brief function to initialize the boats
 * \param board the board
 * \param boats the array of boats
 * \param nbBoats the number of boats
 */
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

/*!
 * \brief function to create a game
 * \param size the size of the board
 * \param nbBoat the number of boats
 * \return the game
 */
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

/*!
 * \brief function to clean the buffer
 */
void cleanBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/*!
 * \brief function to display the board
 * \param board the board
 * \param isPlayer 1 if it's the player's board, 0 otherwise
 */
void displayBoard(Board *board, int isPlayer)
{
    // check if the board is correct
    if (board == NULL)
    {
        printf("Error: the board is not correct\n");
        exit(1);
    }
    // check if the isPlayer is correct
    if (isPlayer != 0 && isPlayer != 1)
    {
        printf("Error: the isPlayer is not correct\n");
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

/*!
 * \brief function to check if a boat is wrecked
 * \param boat the boat
 * \return 1 if the boat is wrecked, 0 otherwise
 */
int isBoatWrecked(Boat *boat)
{
    // check if the boat is correct
    if (boat == NULL)
    {
        printf("Error: the boat not correct\n");
        exit(1);
    }
    // check if the boat is wrecked
    if (boat->hits == boat->size)
    {
        return 1;
    }
    return 0;
}

/*!
 * \brief function to fire a shot
 * \param board the board
 * \param x the x position of the shot
 * \param y the y position of the shot
 * \param boats the array of boats
 */
void fireShot(Board *board, int x, int y, Boat **boats)
{
    // check if the board is correct
    if (board == NULL)
    {
        printf("Error: the board is not correct\n");
        exit(1);
    }
    // check if the position is correct
    if (x < 0 || x >= board->size || y < 0 || y >= board->size)
    {
        printf("Error: the position is not correct\n");
        exit(1);
    }
    // check if the array of boats is correct
    if (boats == NULL)
    {
        printf("Error: the array of boats is not correct\n");
        exit(1);
    }
    // Check if the shot hit a boat
    if (board->matrix[x][y] == BOAT)
    {
        // Find the boat that was hit
        Boat *hitBoat = NULL;
        for (int i = 0; i < NB_BOAT; i++)
        {
            for (int j = 0; j < boats[i]->size; j++)
            {
                int boatX = boats[i]->x;
                int boatY = boats[i]->y;
                if (boats[i]->orientation == HORIZONTAL)
                {
                    boatX += j;
                }
                else if (boats[i]->orientation == VERTICAL)
                {
                    boatY += j;
                }
                if (boatX == x && boatY == y)
                {
                    hitBoat = boats[i];
                    break;
                }
            }
            if (hitBoat != NULL)
            {
                break;
            }
        }
        // Mark the shot as a hit
        board->matrix[x][y] = WRECK;
        printf("Touché\n");

        // Increment the hits counter
        hitBoat->hits++;

        // Check if the boat is wrecked after marking the shot as a hit
        if (isBoatWrecked(hitBoat))
        {
            printf("Coulé\n");
        }
    }
    else if (board->matrix[x][y] == WRECK || board->matrix[x][y] == WATER_SHOT)
    {
        printf("Tu as déjà tiré ici\n");
    }
    else
    {
        // The shot missed
        board->matrix[x][y] = WATER_SHOT;
        printf("A l'eau\n");
    }
}

/*!
 * \brief function to play a turn for the player
 * \param game the game
 */
void playerTurn(Game *game)
{
    // check if the game is correct
    if (game == NULL)
    {
        printf("Error: the game is not correct\n");
        exit(1);
    }
    // ask the player to enter a position
    int x, y, retour = 0;
    printf("Entrez la position x :");
    while (retour != 1)
    {
        retour = scanf("%d", &x);
        cleanBuffer();
    }
    retour = 0;
    printf("Entrez la position y :");
    while (retour != 1)
    {
        retour = scanf("%d", &y);
        cleanBuffer();
    }
    printf("\n");
    // check if the position is correct
    if (x < 0 || x >= game->playerBoard->size || y < 0 || y >= game->playerBoard->size)
    {
        printf("la position est en dehors du plateau de jeu\n");
        exit(1);
    }
    // fire at the position
    fireShot(game->computerBoard, x, y, game->computerBoats);
    // display the board
    displayBoard(game->computerBoard, 0);
}

/*!
 * \brief function to play a turn for the computer
 * \param game the game
 */
void computerTurn(Game *game)
{
    // check if the game is correct
    if (game == NULL)
    {
        printf("Error: the game is not correct\n");
        exit(1);
    }
    // Generate random coordinates for the shot
    int x, y;
    do
    {
        x = rand() % game->playerBoard->size;
        y = rand() % game->playerBoard->size;
    } while (game->playerBoard->matrix[x][y] == WATER_SHOT || game->playerBoard->matrix[x][y] == WRECK);

    // Fire shot
    fireShot(game->playerBoard, x, y, game->playerBoats);

    // Display the board
    displayBoard(game->playerBoard, 1);
}

/*!
 * \brief function to check if all player's boats are wrecked
 * \param game the game
 * \return 1 if all player's boats are wrecked, 0 otherwise
 */
int playerBoatsWrecked(Game *game)
{
    // check if the game is correct
    if (game == NULL)
    {
        printf("Error: the game is not correct\n");
        exit(1);
    }
    for (int i = 0; i < NB_BOAT; i++)
    {
        if (!isBoatWrecked(game->playerBoats[i]))
        {
            return 0; // Un bateau du joueur n'est pas coulé
        }
    }
    return 1; // Tous les bateaux du joueur sont coulés
}

/*!
 * \brief function to check if the game is over
 * \param game the game
 * \return 1 if the game is over, 0 otherwise
 */
int isGameOver(Game *game)
{
    // check if the game is correct
    if (game == NULL)
    {
        printf("Error: the game is not correct\n");
        exit(1);
    }
    int playerBoatsWrecked = 1;
    int computerBoatsWrecked = 1;

    // check if all player's boats are wrecked
    for (int i = 0; i < NB_BOAT; i++)
    {
        if (isBoatWrecked(game->playerBoats[i]) == 0)
        {
            playerBoatsWrecked = 0;
            break;
        }
    }

    // check if all computer's boats are wrecked
    for (int i = 0; i < NB_BOAT; i++)
    {
        if (isBoatWrecked(game->computerBoats[i]) == 0)
        {
            computerBoatsWrecked = 0;
            break;
        }
    }

    return playerBoatsWrecked || computerBoatsWrecked;
}

/*!
 * \brief function to free the memory
 * \param game the game
 */
void freeGame(Game *game)
{
    // check if the game is correct
    if (game == NULL)
    {
        printf("Error: the game is not correct\n");
        exit(1);
    }
    // free the memory
    for (int i = 0; i < game->playerBoard->size; i++)
    {
        free(game->playerBoard->matrix[i]);
    }
    free(game->playerBoard->matrix);
    free(game->playerBoard);

    for (int i = 0; i < game->computerBoard->size; i++)
    {
        free(game->computerBoard->matrix[i]);
    }
    free(game->computerBoard->matrix);
    free(game->computerBoard);

    for (int i = 0; i < NB_BOAT; i++)
    {
        free(game->playerBoats[i]);
    }
    free(game->playerBoats);

    for (int i = 0; i < NB_BOAT; i++)
    {
        free(game->computerBoats[i]);
    }
    free(game->computerBoats);

    free(game);
}