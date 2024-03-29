
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// macros
#define MAX_PATHLENGTH 70
#define MIN_PATHLENGTH 10
#define MAXLIVES 10
#define MINLIVES 1
#define MULTIPLE 5
#define MAXMOVES 26
#define MINMOVES 3

// Structure to store player information
struct playerInfo
{
    int LIVES;
    char SYMBOL;
    int treasure_found;
    int history[MAX_PATHLENGTH];
};

// Structure to store game information
struct gameInfo
{

    int MOVES;
    int PATH_LENGTH;
    int BOMBS[MAX_PATHLENGTH];
    int treasure[MAX_PATHLENGTH];
};

int main(void)
{
    struct playerInfo player;
    struct gameInfo game;
    int x, y, i;
    int Lives_Reamining, Moves_Reamining, position = MAX_PATHLENGTH + 1;

    // Welcome message
    printf("================================"
           "\n         Treasure Hunt!"
           "\n================================");

    // Player configuration
    printf("\n\nPLAYER Configuration");
    printf("\n--------------------");
    printf("\nEnter a single character to represent the player: ");
    scanf(" %c", &player.SYMBOL);

    // Set the number of lives for the player
    do
    {
        printf("Set the number of lives: ");
        scanf("%d", &player.LIVES);

        if (player.LIVES < MINLIVES || player.LIVES > MAXLIVES)
        {
            printf("     Must be between 1 and 10!\n");
        }
    } while (player.LIVES < MINLIVES || player.LIVES > MAXLIVES);

    printf("Player configuration set-up is complete");

    // Game configuration
    printf("\n\nGAME Configuration");
    printf("\n------------------\n");

    // Set the path length
    do
    {

        printf("Set the path length (a multiple of 5 between 10-70): ");
        scanf("%d", &game.PATH_LENGTH);
        if (game.PATH_LENGTH < MIN_PATHLENGTH || game.PATH_LENGTH > MAX_PATHLENGTH || (game.PATH_LENGTH % MULTIPLE != 0))
        {

            printf("     Must be a multiple of 5 and between 10-70!!!\n");
        }

    } while (game.PATH_LENGTH < MIN_PATHLENGTH || game.PATH_LENGTH > MAX_PATHLENGTH || (game.PATH_LENGTH % MULTIPLE != 0));

    // Set the limit for number of moves allowed
    do
    {
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &game.MOVES);
        if (game.MOVES < player.LIVES || game.MOVES > (int)(0.75 * game.PATH_LENGTH))
        {

            printf("    Value must be between %d and %d\n", player.LIVES, (int)(0.75 * game.PATH_LENGTH));
        }
    } while (game.MOVES < player.LIVES || game.MOVES > (int)(0.75 * game.PATH_LENGTH));

    // Bomb placement
    printf("\nBOMB Placement"
           "\n--------------");
    printf("\nEnter the bomb positions in sets of 5 where a value"
           "\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input."
           "\n(Example: 1 0 0 1 1) NOTE: there are 20 to set!\n");

    // Input bomb positions
    for (i = 0; i < game.PATH_LENGTH; i += 5)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
        scanf("%d %d %d %d %d", &game.BOMBS[i], &game.BOMBS[i + 1], &game.BOMBS[i + 2], &game.BOMBS[i + 3], &game.BOMBS[i + 4]);
    }
    printf("BOMB placement set");

    // Treasure placement
    printf("\n\nTREASURE Placement"
           "\n------------------");
    printf("\nEnter the treasure placements in sets of 5 where a value"
           "\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input."
           "\n(Example: 1 0 0 1 1) NOTE: there are 20 to set!\n");

    // Input treasure positions
    for (i = 0; i < game.PATH_LENGTH; i += 5)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
        scanf("%d %d %d %d %d", &game.treasure[i], &game.treasure[i + 1], &game.treasure[i + 2], &game.treasure[i + 3], &game.treasure[i + 4]);
    }
    printf("TREASURE placement set");

    printf("\n\nGAME configuration set-up is complete...");

    printf("\n\n------------------------------------"
           "\nTREASURE HUNT Configuration Settings"
           "\n------------------------------------");
    printf("\nPlayer:");
    printf("\n   Symbol     : %c", player.SYMBOL);
    printf("\n   Lives      : %d", player.LIVES);
    printf("\n   Treasure   : [ready for gameplay]");
    printf("\n   History    : [ready for gameplay]");

    printf("\n\nGame:");
    printf("\n   Path Length: %d", game.PATH_LENGTH);
    printf("\n   Bombs      : ");

    // Print bomb positions
    for (x = 0; x < game.PATH_LENGTH; x++)
    {
        printf("%d", game.BOMBS[x]);
    }

    printf("\n   Treasure   : ");
    // Print treasure positions
    for (y = 0; y < game.PATH_LENGTH; y++)
    {
        printf("%d", game.treasure[y]);
    }

    printf("\n\n===================================="
           "\n~ Get ready to play TREASURE HUNT! ~"
           "\n====================================\n");

    Lives_Reamining = player.LIVES;
    Moves_Reamining = game.MOVES;
    player.treasure_found = 0;
    int count = 0;
    char recentPosition[MAX_PATHLENGTH];
    char positionItem[MAX_PATHLENGTH];

    // Initialize player's history and positionItem arrays
    for (x = 0; x < game.PATH_LENGTH; x++)
    {

        player.history[x] = 0;
    }
    for (y = 0; y < game.PATH_LENGTH; y++)
    {
        positionItem[y] = '-';
    }
    for (y = 0; y < game.PATH_LENGTH; y++)
    {
        recentPosition[y] = ' ';
    }

    // Game loop
    do
    {

        // Print recent position and position item
        for (y = 0; y < game.PATH_LENGTH; y++)
        {
            if (recentPosition[y] == 'V')
            {
                count++;
            }
        }
        if (count == 0)
        {
            printf("\n");
        }
        else
        {
            printf("  ");
            for (y = 0; y < game.PATH_LENGTH; y++)
            {
                if (recentPosition[y] == 'V')
                {
                    printf("%c\n", recentPosition[y]);
                    break;
                }
                else
                {
                    printf("%c", recentPosition[y]);
                }
            }
        }
        for (y = 0; y < game.PATH_LENGTH; y++)
        {
            recentPosition[y] = ' ';
        }

        printf("  ");
        for (y = 0; y < game.PATH_LENGTH; y++)
        {
            printf("%c", positionItem[y]);
        }
        printf("\n");

        printf("  ");
        for (i = 1; i <= game.PATH_LENGTH; i++)
        {
            if (i % 10 == 0)
            {
                printf("%d", (int)i / 10);
            }
            else
            {
                printf("|");
            }
        }
        printf("\n");

        printf("  ");
        for (i = 0; i < game.PATH_LENGTH; i += 10)
        {
            printf("1234567890");
        }

        printf("\n+---------------------------------------------------+");
        printf("\n  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d", Lives_Reamining, player.treasure_found, Moves_Reamining);
        printf("\n+---------------------------------------------------+\n");

        if (Lives_Reamining == 0)
        {
            break;
        }

        if (Moves_Reamining == 0)
        {
            break;
        }
        do
        {
            printf("Next Move [1-20]: ");
            scanf("%d", &position);

            if (position < 1 || position > game.PATH_LENGTH)
            {
                printf("  Out of Range!!!\n");
            }

        } while (position < 1 || position > game.PATH_LENGTH);
        printf("\n");

        if (player.history[position - 1] == 1)
        {
            printf("===============> Dope! You've been here before!\n\n");
            recentPosition[position - 1] = 'V';
            Moves_Reamining++;
        }
        else if (game.BOMBS[position - 1] == 1 && game.treasure[position - 1] == 1)
        {
            printf("===============> [&] !!! BOOOOOM !!! [&]\n");
            printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n\n");
            positionItem[position - 1] = '&';
            recentPosition[position - 1] = 'V';
            Lives_Reamining--;
            player.treasure_found++;
        }
        else if (game.BOMBS[position - 1] == 1)
        {
            printf("===============> [!] !!! BOOOOOM !!! [!]\n\n");
            positionItem[position - 1] = '!';
            recentPosition[position - 1] = 'V';
            Lives_Reamining--;
        }
        else if (game.treasure[position - 1] == 1)
        {
            printf("===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
            positionItem[position - 1] = '$';
            recentPosition[position - 1] = 'V';
            player.treasure_found++;
        }
        else
        {
            printf("===============> [.] ...Nothing found here... [.]\n\n");
            positionItem[position - 1] = '.';
            recentPosition[position - 1] = 'V';
        }

        player.history[position - 1] = 1;

        Moves_Reamining--;
        if (Lives_Reamining == 0)
        {
            printf("No more LIVES remaining!\n\n");
        }
        if (Moves_Reamining == 0)
        {
            printf("No more MOVES remaining!\n\n");
        }

    } while (Moves_Reamining >= 0 && Lives_Reamining >= 0);

    printf("\n");

    printf("##################\n");
    printf("#   Game over!   #\n");
    printf("##################\n");
    printf("\n");

    printf("You should play again and try to beat your score!\n");
    printf("\n");

    return 0;
}
