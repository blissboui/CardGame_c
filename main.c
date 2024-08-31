#include "card.h"
#include "function.h"
int main(void)
{
    srand(time(NULL));
    int select_game;
    THE_CARD *gamecard; // 카드 덱
    while (1)
    {
        ShowListGames();
        printf("Select The Game:");
        scanf("%d", select_game);
        switch (select_game)
        {
        case ODD_EVEN_GAME:     // 홀/짝 게임
            int select_Odd_Even;         // 메뉴 선택
            while (select_Odd_Even != 4) // 4누를 시 종료
            {
                ShowOddEvenGame(); // 메뉴 출력
                printf("Select The Menu:");
                scanf("%d", select_Odd_Even);
                switch (select_Odd_Even)
                {
                case New_game: // 1.새 게임
                    while (select_game != 4)    // 4누를시 종료
                    {
                        gamecard = ResetCard(); // 새로운 카드덱 생성
                    }
                    break;
                case Continue:  // 2.이어하기
                case Result:    // 3.결과 확인
                case Exit:      // 4.나가기
                    break;
                }
            }
            break;
        case HIGH_LOW_GAME:        // 하이로우 게임
        case SUITS_GUESSING_GAME:  // 카드 문양 맞추기 게임
        case CARD_SIZE_MATCH_GAME: // 카드값 크기 대결 게임
        case END:                  // 프로그램 종료
            break;
        default:
            puts("Please Enter It Correctly.");
            getch(); // 아무 키나 누르면 다음으로 진행
        }
    }
}