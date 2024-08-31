#include "card.h"
#include "function.h"
int main(void)
{
    srand(time(NULL));
    int game_select;
    THE_CARD * gamecard;
    while(1)
    {
        ShowListGames();
        printf("Select The Game:");
        scanf("%d",game_select);
        switch(game_select)
        {
            case 1:
                int select; // 메뉴 선택
                gamecard=ResetCard();
                while(1)
                {
                    ShowOddEvenGame();
                    printf("Select The Menu:");
                    scanf("%d",select);
                    switch(select)
                    {
                        case 1:
                    }

                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                break;
            default:
                puts("Please Enter It Correctly.");
                getch();  // 아무 키나 누르면 다음으로 진행
        }

    }
}