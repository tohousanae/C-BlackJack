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
    printf("離開遊戲...\n");
    // 执行一些清理操作...
}
int Blackjack(int hideCard, int *aceCount) // 抽牌並轉換成點數
{
    char *cardfaces[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char *cardsuits[] = {"♠", "\033[31m♥\033[m", "\033[31m♦\033[m", "♣"};
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
    printf("1.遊戲的目標是接近或達到21點，但不能超過21點。\n");
    printf("2.牌面點數：2-10的牌按照其點數計算；J、Q、K按照10點計算；A 牌當作 11 點(本程式中以‘1’當作‘A’)，但是第二個 A 牌以後皆為 1 點\n");
    printf("3.遊戲開始時，玩家和莊家會分別發兩張牌。\n");
    printf("4.玩家可以看到自己的兩張牌，但只能看到莊家的一張牌。\n");
    printf("5.玩家可以選擇繼續抽牌（Hit）或停止抽牌（Stand）。\n");
    printf("6.如果玩家的牌面點數超過21點，玩家爆牌，遊戲結束，莊家獲勝。\n");
    printf("7.如果玩家選擇停止抽牌，輪到莊家進行操作。\n");
    printf("8.莊家會根據固定的規則來決定是否抽牌。莊家在取得17點之前必須要牌，莊家如果拿牌五張而沒有爆牌則視為莊家勝利。\n");
    printf("9.如果莊家的牌面點數超過21點，莊家爆牌，玩家獲勝。\n");
    printf("10.如果莊家選擇停止抽牌，比較玩家和莊家的牌面點數。點數更接近21點的一方獲勝。\n");
    printf("11.如果玩家和莊家的點數相同，則平局。\n\n");
    printf("請再次輸入指令：\n");
    return 0;
}
int game() // 主菜單
{
    printf("[p]開始遊戲  [q]離開遊戲  [r]遊戲規則\n");
    int playerpoints = 0, dealerpoints = 0;
    int playerAceCount = 0, dealerAceCount = 0;
    char command;
    int n = 0; // 初始化
    command = getchar();
    while (getchar() != '\n')
    {
    } // 清空输入缓冲区中的剩余字符
    if (command == 'p')
    {
        printf("玩家目前有的牌：\n");
        for (int i = 0; i < 2; i++) // 玩家顯示初始牌
        {
            srand(time(NULL) + i);
            playerpoints += Blackjack(0, &playerAceCount);
        }
        printf("玩家點數： %d\n", playerpoints);
        printf("莊家目前有的牌：\n");
        for (int i = 2; i < 4; i++) // 莊家顯示初始牌
        {
            srand(time(NULL) - i);
            dealerpoints += Blackjack(i != 3, &dealerAceCount);
        }
        printf("\n");
        printf("是否要牌：\n[h]要牌 [f]翻牌\n");
        command = getchar();
        while (getchar() != '\n')
        {
        }                   // 清空输入缓冲区中的剩余字符
        if (command == 'f') // 玩家停止要牌後莊家要牌
        {
            printf("莊家的要牌：\n");
            while (dealerpoints < 17) // 莊家在17點前必須要牌
            {
                srand(time(NULL) + n);
                n++;

                dealerpoints += Blackjack(0, &dealerAceCount);

                if (dealerpoints > 21)
                {
                    printf("\n玩家點數： %d\n", playerpoints);
                    printf("莊家點數： %d\n", dealerpoints);
                    printf("莊家BURST! 你贏了\n");
                    break;
                }
            }
            printf("\n");
            if (dealerpoints <= 21)
            {
                printf("玩家點數： %d\n", playerpoints);
                printf("莊家點數： %d\n", dealerpoints);

                if (playerpoints > dealerpoints)
                {
                    printf("玩家贏了\n");
                }
                else if (playerpoints < dealerpoints)
                {
                    printf("莊家贏了\n");
                }
                else
                {
                    printf("平局\n");
                }
            }
        }
        /*玩家輸入h要牌*/
        else if (command == 'h')
        {
            do
            {
                srand(time(NULL) + n);
                n++;

                playerpoints += Blackjack(0, &playerAceCount);
                printf("玩家點數： %d\n", playerpoints);

                if (playerpoints > 21)
                {
                    printf("BURST! 你輸了\n");
                    break;
                }
                printf("是否要牌：\n[h]要牌 [f]翻牌\n");
                command = getchar();
                while (getchar() != '\n')
                {
                }                   // 清空输入缓冲区中的剩余字符
                if (command == 'f') // 玩家停止要牌後由莊家要牌
                {
                    printf("莊家的要牌：\n");
                    while (dealerpoints < 17)
                    {
                        srand(time(NULL) + n);
                        n++;

                        dealerpoints += Blackjack(0, &dealerAceCount);

                        if (dealerpoints > 21)
                        {
                            printf("\n玩家點數： %d\n", playerpoints);
                            printf("莊家點數： %d\n", dealerpoints);
                            printf("莊家BURST! 你贏了\n");
                            break;
                        }
                    }
                    printf("\n");
                    if (dealerpoints <= 21)
                    {
                        printf("玩家點數： %d\n", playerpoints);
                        printf("莊家點數： %d\n", dealerpoints);

                        if (playerpoints > dealerpoints)
                        {
                            printf("玩家贏了\n");
                        }
                        else if (playerpoints < dealerpoints)
                        {
                            printf("莊家贏了\n");
                        }
                        else
                        {
                            printf("平局\n");
                        }
                    }
                }
            } while (command == 'h');
        }
    }

    else if (command == 'r') // 遊戲規則頁
    {
        rules();
        game();
    }
    else if (command == 'q') // 退出程序
    {
        atexit(cleanup);

        // 一些程序逻辑...

        // 终止程序并返回退出码0
        exit(0);
    }
    else
    {
        printf("指令錯誤，請重新輸入\n輸入指令：");
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
        printf("再來一局嗎？[y]再來一局 [n]離開遊戲\n");
        command = getchar();
        while (getchar() != '\n')
        {
        } // 清空输入缓冲区中的剩余字符
    } while (command == 'y');
    system("pause");
    return 0;
}