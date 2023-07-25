#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int Blackjack(int hideCard, int *aceCount);
int game();
int rules();
void cleanup();

void cleanup()
{
    printf("Exiting the game...\n");
    // Perform some cleanup operations...
}

/*Draw a card and convert it into points*/
int Blackjack(int hideCard, int *aceCount)
{
    char *cardfaces[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char *cardsuits[] = {"♠", "♥", "♣", "♦"};
    int totalPoints = 0;
    int randomIndex = rand() % (sizeof(cardfaces) / sizeof(cardfaces[0]));
    char *randomNumber = cardfaces[randomIndex];
    char *randomSuit = cardsuits[rand() % (sizeof(cardsuits) / sizeof(cardsuits[0]))];
    int points;

    if (randomNumber[0] == 'J' || randomNumber[0] == 'Q' || randomNumber[0] == 'K')
    {
        points = 10;
    }
    else if (randomNumber[0] == 'A' && *aceCount == 0)
    {
        points = 11;
        (*aceCount)++;
    }
    else if (randomNumber[0] == 'A' && *aceCount >= 1)
    {
        points = 1;
        (*aceCount)++;
    }
    else
    {
        points = atoi(randomNumber);
    }

    if (hideCard)
    {
        printf("[? ?]\t");
    }
    else
    {
        printf("[%s %s]\t", randomSuit, randomNumber);
    }

    return points;
}

int rules()
{
    printf("1. The goal of the game is to get as close to or reach 21 points without exceeding 21.\n");
    printf("2. Card values: Cards 2-10 count as their face value; J, Q, K count as 10 points; A counts as 11 points (represented as '1' in this program), but subsequent A's count as 1 point.\n");
    printf("3. At the beginning of the game, the player and the dealer are dealt two cards each.\n");
    printf("4. The player can see both of their cards, but can only see one of the dealer's cards.\n");
    printf("5. The player can choose to draw another card (Hit) or stop drawing cards (Stand).\n");
    printf("6. If the player's total points exceed 21, the player busts, and the game ends with the dealer winning.\n");
    printf("7. If the player chooses to stand, it's the dealer's turn to play.\n");
    printf("8. The dealer follows fixed rules to decide whether to draw cards. The dealer must draw cards until they have 17 points or more. If the dealer draws a total of five cards without busting, the dealer wins.\n");
    printf("9. If the dealer's total points exceed 21, the dealer busts, and the player wins.\n");
    printf("10. If the dealer chooses to stand, the points of the player and the dealer are compared, and the one closer to 21 points wins.\n");
    printf("11. If the player and the dealer have the same number of points, it's a tie.\n\n");
    printf("Please input the command again:\n");
    return 0;
}

/*Main menu*/
int game()
{
    printf("[p]Start Game  [q]Exit Game  [r]Game Rules\n");
    int playerpoints = 0, dealerpoints = 0;
    int playerAceCount = 0, dealerAceCount = 0;
    char command;
    int n = 0; // Initialize
    command = getchar();
    while (getchar() != '\n')
    {
    } // Clear any remaining characters in the input buffer
    if (command == 'p')
    {
        printf("Player's current cards:\n");
        for (int i = 0; i < 2; i++) // Display initial player cards
        {
            srand(time(NULL) + 3 * i - 2 * i);
            playerpoints += Blackjack(0, &playerAceCount);
        }
        printf("Player points: %d\n", playerpoints);
        printf("Dealer's current cards:\n");
        for (int i = 2; i < 4; i++) // Display initial dealer cards
        {
            srand(time(NULL) - 3 * i + 2 * i);
            dealerpoints += Blackjack(i != 3, &dealerAceCount);
        }
        printf("\n");
        printf("Do you want to draw another card?\n[h]Hit [f]Flip the cards\n");
        command = getchar();
        while (getchar() != '\n')
        {
        } // Clear any remaining characters in the input buffer
        if (command == 'f') // Player stops drawing cards, and it's the dealer's turn to play
        {
            printf("Dealer's turn to draw cards:\n");
            while (dealerpoints < 17) // The dealer must draw cards until they have 17 points or more
            {
                srand(time(NULL) + 3 * n - 2 * n);
                n++;

                dealerpoints += Blackjack(0, &dealerAceCount);

                if (dealerpoints > 21)
                {
                    printf("\nPlayer points: %d\n", playerpoints);
                    printf("Dealer points: %d\n", dealerpoints);
                    printf("Dealer BUSTED! You win\n");
                    break;
                }
            }
            printf("\n");
            if (dealerpoints <= 21)
            {
                printf("Player points: %d\n", playerpoints);
                printf("Dealer points: %d\n", dealerpoints);

                if (playerpoints > dealerpoints)
                {
                    printf("Player wins\n");
                }
                else if (playerpoints < dealerpoints)
                {
                    printf("Dealer wins\n");
                }
                else
                {
                    printf("Tie\n");
                }
            }
        }

        /*Player enters 'h' to draw another card*/
        else if (command == 'h')
        {
            do
            {
                srand(time(NULL) - 2 * n + 3 * n);
                n++;

                playerpoints += Blackjack(0, &playerAceCount);
                printf("Player points: %d\n", playerpoints);

                if (playerpoints > 21)
                {
                    printf("BUSTED! You lose\n");
                    break;
                }
                printf("Do you want to draw another card?\n[h]Hit [f]Flip the cards\n");
                command = getchar();
                while (getchar() != '\n')
                {
                } // Clear any remaining characters in the input buffer
                if (command == 'f') // Player stops drawing cards, and it's the dealer's turn to play
                {
                    printf("Dealer's turn to draw cards:\n");
                    while (dealerpoints < 17)
                    {
                        srand(time(NULL) + n);
                        n++;

                        dealerpoints += Blackjack(0, &dealerAceCount);

                        if (dealerpoints > 21)
                        {
                            printf("\nPlayer points: %d\n", playerpoints);
                            printf("Dealer points: %d\n", dealerpoints);
                            printf("Dealer BUSTED! You win\n");
                            break;
                        }
                    }
                    printf("\n");
                    if (dealerpoints <= 21)
                    {
                        printf("Player points: %d\n", playerpoints);
                        printf("Dealer points: %d\n", dealerpoints);

                        if (playerpoints > dealerpoints)
                        {
                            printf("Player wins\n");
                        }
                        else if (playerpoints < dealerpoints)
                        {
                            printf("Dealer wins\n");
                        }
                        else
                        {
                            printf("Tie\n");
                        }
                    }
                }

            } while (command == 'h');
        }
        else
        {
            printf("Invalid command. Terminating the program.\n");
            atexit(cleanup);

            // Some program logic...

            // Terminate the program and return exit code 0
            exit(0);
        }
    }
    else if (command == 'r') // Game rules page
    {
        rules();
        game();
    }
    else if (command == 'q') // Exit the program
    {
        atexit(cleanup);

        // Some program logic...

        // Terminate the program and return exit code 0
        exit(0);
    }
    else
    {
        printf("Invalid command. Please input again.\nInput command:");
        game();
    }

    return 0;
}

int main()
{
    char command;
    do
    {
        game();
        printf("Play again? [y]Play again [n]Exit the game\n");
        command = getchar();
        while (getchar() != '\n')
        {
        } // Clear any remaining characters in the input buffer
        if (command == 'n')
        {
            atexit(cleanup);

            // Some program logic...

            // Terminate the program and return exit code 0
            exit(0);
        }

    } while (command == 'y');
    return 0;
}