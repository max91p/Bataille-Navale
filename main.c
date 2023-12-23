#include "fonctions.h"

int main()
{
    srand(time(NULL));
    Game *game = createGame(SIZE, NB_BOAT);
    displayBoard(game->playerBoard, 1);
    displayBoard(game->computerBoard, 0);
    do
    {
        playerTurn(game);
        if (!isGameOver(game)) // Vérifier si le jeu est terminé après chaque tour de joueur
        {
            printf("--------------------\n");
            printf("Tour de l'ordinateur\n\n");
            sleep(1);
            computerTurn(game);
            printf("--------------------\n");
            printf("A ton tour\n");
        }
    } while (!isGameOver(game));

    // Afficher le message de fin de jeu
    if (playerBoatsWrecked(game))
        printf("L'ordinateur a gagné!\n");
    else
        printf("Félicitations! Tu as gagné!\n");

    // Libérer la mémoire
    freeGame(game);
    return 0;
}
