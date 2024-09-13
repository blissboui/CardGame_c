#include "function.h"
#include "card.h"
#include "show.h"

void OddEvenGame(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
{
    THE_CARD *gamecard = NULL;
    GAME_BET_RESULT bet_results = {NULL, 0, 0, DEFAULT_RESULTS_MEMORY_SIZE, user[currentUserIndex].balance};
    while (1)
    {
        int select;
        ShowOddEvenGameMenu();
        scanf("%d", &select);

        switch (select)
        {
        case NEW_GAME:
            NewGameOddEven(&gamecard, &bet_results);
            break;
        case CONTINUE:
            ContinueOddEven(&gamecard, &bet_results);
            break;
        case RESULTS:
            ShowGameResults(&bet_results);
            break;
        case BACK:
            user[currentUserIndex].balance = bet_results.user_balance;
            StoreData(user,user_num);
            free(gamecard);
            free(bet_results.game_results);
            return;
        }
    }
}
void NewGameOddEven(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
{
    int state = 0;
    while (1)
    {
        int select;
        ShowOddEvenGamePlay(bet_results);
        scanf("%d", &select);
        switch (select)
        {
        case START_GAME:
            if (state == 0)
            {
                NewGameSetUp(&gamecard, &bet_results);
                state = 1;
            }
            ResetDecksAfterGames(&gamecard, &bet_results);
            PlayOddEvenGame(gamecard, &bet_results);
            break;
        case END_GAME:
            return;
        default:
            puts("Please enter it correctly.");
            getch();
            break;
        }
    }
}

void ContinueOddEven(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
{
    while (1)
    {
        int select;
        ShowOddEvenGamePlay(bet_results);
        scanf("%d", &select);
        switch (select)
        {
        case START_GAME:
            ResetDecksAfterGames(&gamecard, &bet_results);
            PlayOddEvenGame(gamecard, &bet_results);
            break;
        case END_GAME:
            return;
        default:
            puts("Please enter it correctly.");
            getch();
            break;
        }
    }
}
void PlayOddEvenGame(THE_CARD **gamecard, GAME_BET_RESULT **bet_results) // 홀짝 게임 플레이 함수 (홀짝게임에 필요한 함수들의 집합)
{
    AddGameResultsMemory(bet_results);   // 결과 저장 메모리 부족 시 확장
    GetFirstCard(*gamecard);             // 첫번째 카드 출력
    ChooseOddEven(*bet_results);         // 베팅 항목 출력 후 홀 짝 선택
    SetBetAmount(*bet_results);
    GetSecondCard(*gamecard);            // 두번째 카드 출력
    GameResult(*gamecard, *bet_results); // 홀 짝 게임 결과 출력 후 저장
}
bool OddEvenResult(THE_CARD *gamecard) // 홀수 짝수 결과 반환 함수
{
    bool result = (gamecard->num_first_card + gamecard->num_second_card) % 2 == 0 ? true : false;
    // 첫번째 카드와 두번째 카드를 더한 값이 짝수=true 홀수=false
    return result;
}
void GameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results) // 홀 짝 게임 결과 출력 후 저장 함수
{
    // 홀수 짝수를 맞췄을 때
    if (OddEvenResult(gamecard) == bet_results->odd_even_choice)
    {
        puts("    [ Succeed ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Succeed");
        bet_results ->user_balance += (bet_results->betAmount * BET_PAYOUT);
    }
    // 틀렸을 때
    else
    {
        puts("      [ Fail ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Fail");
    }
    bet_results->num_results += 1;  // 저장된 결과 개수 증가
    bet_results->num_of_games += 1; // 진행된 게임 수 증가
    getch();
}
void ChooseOddEven(GAME_BET_RESULT *bet_results) // 베팅 목록 출력 후 홀 짝 선택
{
    int choice;
    ShowOddEvenBetItem(); // 홀 짝 베팅 항목 출력
    scanf("%d", &choice);
    // 홀수 선택 시:false 짝수 선택 시:true
    bet_results->odd_even_choice = choice == 1 ? false : true;
}