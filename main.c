#include "fonctions.h"

int main()
{
    srand(time(NULL));
    Game *game = createGame(SIZE, NB_BOAT);
    displayBoard(game->playerBoard, 1);
    displayBoard(game->computerBoard, 0);

    return 0;
}
