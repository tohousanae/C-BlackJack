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
    printf("正在退出遊戲...\n");
    // 執行一些清理操作...
}

/* 抽取一張卡並轉換成點數 */
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
    printf("1. 遊戲目標是獲得或接近21點而不超過21點。\n");
    printf("2. 卡牌點數：2-10的牌以其面值計算；J、Q、K算作10點；A算作11點，但多個A則算作1點。\n");
    printf("3. 遊戲開始時，玩家和莊家各發兩張牌。\n");
    printf("4. 玩家可以看到自己的兩張牌，但只能看到莊家的一張牌。\n");
    printf("5. 玩家可以選擇再抽一張牌（要牌）或停止抽牌（不要牌）。\n");
    printf("6. 若玩家的總點數超過21，則玩家爆牌，遊戲結束，莊家勝利。\n");
    printf("7. 若玩家選擇停止抽牌，輪到莊家進行操作。\n");
    printf("8. 莊家按照固定規則決定是否抽牌。莊家必須抽牌直到達到17點或以上。若莊家抽取五張牌而未爆牌，莊家勝利。\n");
    printf("9. 若莊家的總點數超過21，莊家爆牌，玩家勝利。\n");
    printf("10. 若莊家選擇停止抽牌，則比較玩家和莊家的點數，點數較接近21點的一方獲勝。\n");
    printf("11. 若玩家和莊家的點數相同，則為平局。\n\n");
    printf("請重新輸入指令：\n");
    return 0;
}

/* 主菜單 */
int game()
{
    printf("[p]開始遊戲  [q]退出遊戲  [r]遊戲規則\n");
    int playerpoints = 0, dealerpoints = 0;
    int playerAceCount = 0, dealerAceCount = 0;
    char command;
    int n = 0; // 初始化
    command = getchar();
    while (getchar() != '\n')
    {
    } // 清除輸入緩衝區中的任何剩餘字符
    if (command == 'p')
    {
        printf("玩家目前的牌:\n");
        for (int i = 0; i < 2; i++) // 顯示初始玩家牌
        {
            srand(time(NULL) + 3 * i - 2 * i);
            playerpoints += Blackjack(0, &playerAceCount);
        }
        printf("玩家點數: %d\n", playerpoints);
        printf("莊家目前的牌:\n");
        for (int i = 2; i < 4; i++) // 顯示初始莊家牌
        {
            srand(time(NULL) - 3 * i + 2 * i);
            dealerpoints += Blackjack(i != 3, &dealerAceCount);
        }
        printf("\n");
        printf("是否要再抽一張牌？\n[h]要牌 [f]停止抽牌\n");
        command = getchar();
        while (getchar() != '\n')
        {
        } // 清除輸入緩衝區中的任何剩餘字符
        if (command == 'f') // 玩家停止抽牌，輪到莊家進行操作
        {
            printf("莊家抽牌中:\n");
            while (dealerpoints < 17) // 莊家必須抽牌直到達到17點或以上
            {
                srand(time(NULL) + 3 * n - 2 * n);
                n++;

                dealerpoints += Blackjack(0, &dealerAceCount);

                if (dealerpoints > 21)
                {
                    printf("\n玩家點數: %d\n", playerpoints);
                    printf("莊家點數: %d\n", dealerpoints);
                    printf("莊家爆牌！你贏了\n");
                    break;
                }
            }
            printf("\n");
            if (dealerpoints <= 21)
            {
                printf("玩家點數: %d\n", playerpoints);
                printf("莊家點數: %d\n", dealerpoints);

                if (playerpoints > dealerpoints)
                {
                    printf("玩家勝利\n");
                }
                else if (playerpoints < dealerpoints)
                {
                    printf("莊家勝利\n");
                }
                else
                {
                    printf("平局\n");
                }
            }
        }

        /* 玩家輸入'h'來再抽一張牌 */
        else if (command == 'h')
        {
            do
            {
                srand(time(NULL) - 2 * n + 3 * n);
                n++;

                playerpoints += Blackjack(0, &playerAceCount);
                printf("玩家點數: %d\n", playerpoints);

                if (playerpoints > 21)
                {
                    printf("爆牌！你輸了\n");
                    break;
                }
                printf("是否要再抽一張牌？\n[h]要牌 [f]停止抽牌\n");
                command = getchar();
                while (getchar() != '\n')
                {
                } // 清除輸入緩衝區中的任何剩餘字符
                if (command == 'f') // 玩家停止抽牌，輪到莊家進行操作
                {
                    printf("莊家抽牌中:\n");
                    while (dealerpoints < 17)
                    {
                        srand(time(NULL) + n);
                        n++;

                        dealerpoints += Blackjack(0, &dealerAceCount);

                        if (dealerpoints > 21)
                        {
                            printf("\n玩家點數: %d\n", playerpoints);
                            printf("莊家點數: %d\n", dealerpoints);
                            printf("莊家爆牌！你贏了\n");
                            break;
                        }
                    }
                    printf("\n");
                    if (dealerpoints <= 21)
                    {
                        printf("玩家點數: %d\n", playerpoints);
                        printf("莊家點數: %d\n", dealerpoints);

                        if (playerpoints > dealerpoints)
                        {
                            printf("玩家勝利\n");
                        }
                        else if (playerpoints < dealerpoints)
                        {
                            printf("莊家勝利\n");
                        }
                        else
                        {
                            printf("平局\n");
                        }
                    }
                }

            } while (command == 'h');
        }
        else
        {
            printf("無效指令。正在終止程式。\n");
            atexit(cleanup);

            // 一些程式邏輯...

            // 終止程式並返回退出代碼0
            exit(0);
        }
    }
    else if (command == 'r') // 遊戲規則頁面
    {
        rules();
        game();
    }
    else if (command == 'q') // 退出程式
    {
        atexit(cleanup);

        // 一些程式邏輯...

        // 終止程式並返回退出代碼0
        exit(0);
    }
    else
    {
        printf("無效指令。請重新輸入。\n輸入指令:");
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
        printf("再玩一次？ [y]再玩一次 [n]退出遊戲\n");
        command = getchar();
        while (getchar() != '\n')
        {
        } // 清除輸入緩衝區中的任何剩餘字符
        if (command == 'n')
        {
            atexit(cleanup);

            // 一些程式邏輯...

            // 終止程式並返回退出代碼0
            exit(0);
        }

    } while (command == 'y');
    return 0;
}



