#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int Blackjack();
int game();
int rules();

int Blackjack(int hideCard, int *aceCount)
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
    printf("[p]開始遊戲  [q]離開遊戲  [r]遊戲規則\n");
    return 0;
}
int game() // 主菜單
{
    int playerpoints = 0, dealerpoints = 0;
    int playerAceCount = 0, dealerAceCount = 0;
    char command = 0;
    int n = 0;
    while (!command)
    {
        command = getchar();
        switch (command)
        {
        case 'p':
            for (int i = 0; i < 2; i++)
            {
                srand(time(NULL) + i);
                playerpoints += Blackjack(0, &playerAceCount);
            }
            printf("Player points: %d\n", playerpoints);
            for (int i = 2; i < 4; i++)
            {
                srand(time(NULL) - i);
                dealerpoints += Blackjack(i != 3, &dealerAceCount);
            }
            printf("Dealer points: %d\n", dealerpoints);
            char command = getchar();
            if (command == 'q')
            {
                break;
            }
            else if (command == 'h')
            {
                do
                {

                    srand(time(NULL) + n);
                    n++;

                    playerpoints += Blackjack(0, &playerAceCount);
                    printf("Player points: %d\n", playerpoints);

                    command = getchar();

                } while (command == 'h');
            }
        case 'q':
            break;
        case 'r': // 遊戲規則頁
            rules();
            command = getchar();
            game();
            break;
        default:
            printf("指令錯誤，請重新輸入\n輸入指令：");
            command = 0;
            while (getchar() != '\n')
            {
                continue;
            }
        }
    }
    return 0;
}

int main()
{
    printf("**************************************************\n\t\t    21點\n");
    printf("**************************************************\n\n");
    printf("[p]開始遊戲  [q]離開遊戲  [r]遊戲規則\n");
    game();
    return 0;
}