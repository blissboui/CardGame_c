#include "card.h"
#include "function.h"
int main(void)
{
    srand(time(NULL));
    int select_game;
    int card_sequence = 0; // 카드를 가져올때 첫번째 or 두번째 카드
    THE_CARD *gamecard;    // 카드 덱

    while (1)
    {
        ShowListGames();
        printf("Select The Game:");
        scanf("%d", &select_game);

        switch (select_game)
        {
        case ODD_EVEN_GAME:          // 홀/짝 게임
            while (select_game != 4) // 4누를 시 종료
            {
                ShowOddEvenGameMenu(); // 메뉴 출력
                printf("Select The Menu:");
                scanf("%d", &select_game);
                switch (select_game)
                {
                case New_game: // 1.새 게임
                    int odd_even_select;
                    gamecard = ResetCard();      // 새로운 카드덱 생성
                    
                    while (odd_even_select != 2) // 2누를시 종료
                    {
                        ShowOddEvenGamePlay(); // 플레이 메뉴 출력
                        printf("Select:");
                        scanf("%d", &odd_even_select);

                        switch (odd_even_select)
                        {
                        case START_GAME: // 1. 게임 시작
                            GetCard(gamecard, &card_sequence);
                            break;
                        case END_GAME: // 2. 게임 종료
                            getch();   // 아무 키나 누르면 다음으로 진행
                            break;
                        default:
                            puts("Please Enter It Correctly.");
                            getch(); // 아무 키나 누르면 다음으로 진행
                            break;
                        }
                    }
                    break;

                case Continue: // 2.이어하기
                    break;
                case Result: // 3.결과 확인
                    break;
                case Exit: // 4.나가기
                    break;
                }
            }
            break;
        case HIGH_LOW_GAME: // 하이로우 게임
            break;
        case SUITS_GUESSING_GAME: // 카드 문양 맞추기 게임
            break;
        case CARD_SIZE_MATCH_GAME: // 카드값 크기 대결 게임
            break;
        case PROGRAM_END: // 프로그램 종료
            return 0;
        default:
            puts("Please Enter It Correctly.");
            getch(); // 아무 키나 누르면 다음으로 진행
            break;
        }
    }
}