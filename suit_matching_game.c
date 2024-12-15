#include "function.h"
#include "struct.h"
#include "show.h"
void SuitMatcGame(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
{
    THE_CARD *gamecard = NULL;
    GAME_BET_RESULT bet_results = {NULL, 0, 0, DEFAULT_RESULTS_MEMORY_SIZE, user[currentUserIndex].balance};
    while (1)
    {
        int select;
        ClearScreen();
        puts("\n[ SUIT MATCHING GAME ]");
        ShowGameMenu();
        scanf("%d", &select);

        switch (select)
        {
        case NEW_GAME:
            NewGameSuitMatc(&gamecard, &bet_results);
            break;
        case CONTINUE:
            if(gamecard == NULL)
            {
                printf("No saved game found to continue. \n");
                getch();
                break;
            }
            //ContinueSuitMatc(&gamecard, &bet_results);
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

void NewGameSuitMatc(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
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
            PlaySuitMatc(gamecard, &bet_results);
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

void ContinueSuitMatc(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
{
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
            PlaySuitMatc(gamecard, &bet_results);
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

void PlaySuitMatc(THE_CARD **gamecard, GAME_BET_RESULT **bet_results)
{
    AddGameResultsMemory(bet_results);   // 결과 저장 메모리 부족 시 확장
    GetFirstCard(*gamecard);             // 첫번째 카드 출력
    ChooseSuitMatc(*bet_results);         // 베팅 항목 출력 후 홀 짝 선택
    SetBetAmount(*bet_results);
    GetSecondCard(*gamecard);            // 두번째 카드 출력
    SuitMatcGameResult(*gamecard, *bet_results);
}

void ChooseSuitMatc(GAME_BET_RESULT *bet_results)
{
    int choice;
    while(1)
    {
        ShowSuitMatcBetItem();
        scanf("%d", &choice);
        // 스페이드=1, 하트=2, 다이아=3, 클럽=4
        if(choice < 0 || choice > 5)
        {
            printf("please enter it correctly.");
            getch();
            ClearCursorToEnd();
        }
        break;
    }
    bet_results->suit_matching_choice = choice;
}

void SuitMatcGameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results)
{
    if (gamecard->suits_second_card == bet_results->suit_matching_choice)
    {
        puts("    [ Succeed ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Succeed");
        bet_results ->user_balance += (bet_results->betAmount * SUIT_PAYOUT);
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