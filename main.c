#include "card.h"
#include "function.h"
int main(void)
{
    srand(time(NULL));
    int select_game;
    int odd_even_select;
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
                    int state = 0;  // 새 게임 시 설정 함수를 1회만 동작하기 위함
                    do
                    {
                        ShowOddEvenGamePlay(); // 플레이 메뉴 출력
                        scanf("%d", &odd_even_select);

                        switch (odd_even_select)
                        {
                        case START_GAME: // 1. 게임 시작
                            if (state == 0) // 새로운 게임 시작시 1회만 실행
                            {   
                                free(gamecard);
                                gamecard = ResetCard();
                                NewGameSetUp(gamecard, &bet_results); // 게임 시작 전 설정 함수
                            }
                            PlayOddEvenGame(gamecard, &bet_results); // 홀짝 게임 플레이 함수
                            break;
                        case END_GAME: // 2. 게임 종료
                            break;
                        default:
                            puts("Please Enter It Correctly.");
                            getch(); // 아무 키나 누르면 다음으로 진행
                            break;
                        }
                    } while (odd_even_select != END_GAME);
                    break;
                case Continue: // 2.이어하기
                    do
                    {
                        ShowOddEvenGamePlay(); // 플레이 메뉴 출력
                        scanf("%d", &odd_even_select);

                        switch (odd_even_select)
                        {
                        case START_GAME:                             // 1. 게임 시작
                            PlayOddEvenGame(gamecard, &bet_results); // 홀짝 게임 플레이 함수
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