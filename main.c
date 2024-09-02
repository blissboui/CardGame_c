#include "card.h"
#include "function.h"
int main(void)
{
    srand(time(NULL));
    int select_game;
    THE_CARD *gamecard = NULL;                  // 카드 덱
    GAME_BET_RESULT bet_results = {NULL, 0, 5}; // 베팅 항목, 결과 (결과, 결과 개수, 메모리크기)

    while (1)
    {
        ShowListGames();
        scanf("%d", &select_game);

        switch (select_game)
        {
        case ODD_EVEN_GAME:          // 홀/짝 게임
            while (select_game != 4) // 4누를 시 종료
            {
                ShowOddEvenGameMenu(); // 메뉴 출력
                scanf("%d", &select_game);
                switch (select_game)
                {
                case New_game: // 1.새 게임
                    int odd_even_select;
                    gamecard = ResetCard();             // 새로운 카드덱 생성
                    ResultAllocateMemory(&bet_results); // 게임 결과 저장 메모리 할당
                    do
                    {
                        ShowOddEvenGamePlay(); // 플레이 메뉴 출력
                        scanf("%d", &odd_even_select);

                        switch (odd_even_select)
                        {
                        case START_GAME:                        // 1. 게임 시작
                            GetFirstCard(gamecard);             // 첫번째 카드 출력
                            ChooseOddEven(&bet_results);        // 베팅 항목 출력 후 홀 짝 선택
                            GetSecondCard(gamecard);            // 두번째 카드 출력
                            GameResult(gamecard, &bet_results); // 홀 짝 게임 결과 출력 후 저장
                            break;
                        case END_GAME: // 2. 게임 종료
                            break;
                        default:
                            puts("Please Enter It Correctly.");
                            getch(); // 아무 키나 누르면 다음으로 진행
                            break;
                        }
                    } while (odd_even_select != 2); // 2누를시 종료
                    break;
                case Continue: // 2.이어하기
                    break;
                case Result: // 3.결과 확인
                    ShowGameResults(&bet_results);
                    break;
                case Exit:                          // 4.나가기
                    free(bet_results.game_results); // 결과 저장 메모리 해제
                    free(gamecard);                 // 카드덱 메모리 해제
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