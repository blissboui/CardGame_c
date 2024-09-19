#include "function.h"
#include "struct.h"
#include "show.h"

void HighLowGame(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
{
    THE_CARD *gamecard = NULL;
    GAME_BET_RESULT bet_results = {NULL, 0, 0, DEFAULT_RESULTS_MEMORY_SIZE, user[currentUserIndex].balance};
    while (1)
    {
        int select;
        ClearScreen();
        puts("\n[ HIGH-LOW GAME ]");
        ShowGameMenu();
        scanf("%d", &select);

        switch (select)
        {
        case NEW_GAME:
            NewGameHighLow(&gamecard, &bet_results);
            break;
        case CONTINUE:
            if(gamecard == NULL)
            {
                printf("No saved game found to continue. \n");
                getch();
                break;
            }
            ContinueHighLow(&gamecard, &bet_results);
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

void NewGameHighLow(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
{
    int state = 0;
    while (1)
    {
        int select;
        ShowGamePlay(bet_results);
        scanf("%d", &select);
        switch (select)
        {
        case START_GAME:
            if(bet_results->user_balance <= 0)
            {   
                printf("Insufficient funds \n");
                getch();
                 break;
            }
            if (state == 0)
            {
                NewGameSetUp(&gamecard, &bet_results);
                state = 1;
            }
            ResetDecksAfterGames(&gamecard, &bet_results);
            PlayHighLowGame(gamecard, &bet_results);
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
void ContinueHighLow(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
{
    int state = 0;
    while (1)
    {
        int select;
        ShowGamePlay(bet_results);
        scanf("%d", &select);
        switch (select)
        {
        case START_GAME:
            if(bet_results->user_balance <= 0)
            {   
                printf("Insufficient funds \n");
                getch();
                 break;
            }
            ResetDecksAfterGames(&gamecard, &bet_results);
            PlayHighLowGame(gamecard, &bet_results);
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


void PlayHighLowGame(THE_CARD **gamecard, GAME_BET_RESULT **bet_results) // 하이로우 게임 플레이 함수
{
    AddGameResultsMemory(bet_results);   // 결과 저장 메모리 부족 시 확장
    GetFirstCard(*gamecard);             // 첫번째 카드 출력
    ChooseHighLow(*bet_results);       
    SetBetAmount(*bet_results);
    GetSecondCard(*gamecard);            // 두번째 카드 출력
    HighLowGameResult(*gamecard, *bet_results);
}

void ChooseHighLow(GAME_BET_RESULT *bet_results)
{
    int choice;
    ShowHighLowBetItem();
    scanf("%d", &choice);
    // 하이 선택 시:true 로우 선택 시:false
    bet_results->high_low_choice = choice == 1 ? true : false;
}

void HighLowGameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results) 
{
    if (HighLowResult(gamecard) == bet_results->high_low_choice)
    {
        puts("    [ Succeed ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Succeed");
        bet_results ->user_balance += (bet_results->betAmount * BET_PAYOUT);
    }
    else
    {
        puts("      [ Fail ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Fail");
    }
    bet_results->num_results += 1;  // 저장된 결과 개수 증가
    bet_results->num_of_games += 1; // 진행된 게임 수 증가
    getch();
}

bool HighLowResult(THE_CARD *gamecard)
{
    bool result = gamecard->num_second_card <= 5 ? false : true;
    // 첫번째 카드와 두번째 카드를 더한 값이 짝수=true 홀수=false
    return result;
}