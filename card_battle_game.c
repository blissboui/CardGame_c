#include "function.h"
#include "struct.h"
#include "show.h"
void BattleGame(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
{ 
    THE_CARD *gamecard = NULL;
    GAME_BET_RESULT bet_results = {NULL, 0, 0, DEFAULT_RESULTS_MEMORY_SIZE, user[currentUserIndex].balance};
    while (1)
    {
        int select;
        ClearScreen();
        puts("\n[ CARD BATTLE GAME ]");
        ShowGameMenu();
        scanf("%d", &select);

        switch (select)
        {
        case NEW_GAME:
            NewGameCardBattle(&gamecard, &bet_results);
            break;
        case CONTINUE:
            if(gamecard == NULL)
            {
                printf("No saved game found to continue. \n");
                getch();
                break;
            }
            ContinueCardBattle(&gamecard, &bet_results);
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

void BattleGameGetCard(THE_CARD *gamecard, CARD *card)
{
    int random_deck;
    int random_suits;
    int random_number;
    do
    {
        random_deck = GetRandomNumber(0, DECK - 1);      // 랜덤 덱
        random_suits = GetRandomNumber(0, SUITS - 1);    // 랜덤 문양
        random_number = GetRandomNumber(0, NUMBERS - 1); // 랜덤 숫자
        // CheckCardDuplication()가 false를 반환 할때 까지 반복
        // 해당 카드가 이전에 나왔었는지 검사
    } while (CheckCardDuplication(gamecard->card[random_deck][random_suits][random_number]));
    card->num_card = random_number + 1;
    card->suit_card = random_suits;
    gamecard->card[random_deck][random_suits][random_number] = 0;
    // 한번 나온 카드값을 0으로 초기화 (다시 나오지 않음)
}

void PlayBattleGame(THE_CARD **gamecard, GAME_BET_RESULT **bet_results)
{
    CARD cardStore;
    CARD *card = &cardStore;
    FIRST_AND_SECOND_CARD computerCard;
    FIRST_AND_SECOND_CARD userCard;
    int comSum, userSum;
    float odds;

    AddGameResultsMemory(bet_results);   // 결과 저장 메모리 부족 시 확장

    // 컴퓨터의 첫번째 카드
    BattleGameGetCard(*gamecard, card);
    computerCard.first_card = *card;
    // user의 첫번째 카드
    BattleGameGetCard(*gamecard, card);
    userCard.first_card = *card;

    odds = ReturnOdds(userCard.first_card.num_card, computerCard.first_card.num_card);

    ClearScreen();
    // 첫번째 카드들 출력
    printf("\n[ Computer's Card ]    |     [ User's Card ]\t    **Odds [ x%0.2f ]**\n"
           "                       | ", odds);
    printf("\n First Card [ ");
    PrintSuits(computerCard.first_card.suit_card);
    printf("%-2d]     |", computerCard.first_card.num_card);

    printf("    First Card [ ");
    PrintSuits(userCard.first_card.suit_card);
    printf("%-2d]\n", userCard.first_card.num_card);

    printf("\t\t       | \n"
           "\t\t       | \n");

    // 베팅
    SetBetAmount(*bet_results);

    printf("\033[7;1H");
    printf("\033[0J");
    getch();

    // computer의 두번째 카드
    BattleGameGetCard(*gamecard, card);
    computerCard.second_card = *card;
    // user의 두번째 카드
    BattleGameGetCard(*gamecard, card);
    userCard.second_card = *card;

    // 컴퓨터 두번째 카드 출력
    printf("\033[5;1H");
    printf("Second Card [ ");
    PrintSuits(computerCard.second_card.suit_card);
    printf("%-2d]", computerCard.second_card.num_card);
    
    getch();
    CountDisplay();

    // user 두번째 카드 출력
    printf(" Second Card [ ");
    PrintSuits(userCard.second_card.suit_card);
    printf("%-2d]\n", userCard.second_card.num_card);

    comSum = computerCard.first_card.num_card + computerCard.second_card.num_card;
    userSum = userCard.first_card.num_card + userCard.second_card.num_card;

    getch();
    // 결과 출력 후 저장
    BattleGameResult(comSum, userSum, *bet_results, odds);
}

void CountDisplay(void)     // 3초 카운트 출력 함수
{
    printf("\033[27G");
    printf("\t   3");
    Sleep(1000);
    printf("\033[27G");
    printf("\033[K");
    
    printf("\t   2");
    Sleep(1000);
    printf("\033[27G");
    printf("\033[K");

    printf("\t   1");
    Sleep(1000);
    printf("\033[27G");
    printf("\033[K");
}

void BattleGameResult(int comSum, int userSum, GAME_BET_RESULT *bet_results, float odds)
{
    if(comSum < userSum)    // user win
    {
        puts("\t\t       |\t[ Win ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Succeed");
        bet_results ->user_balance += (bet_results->betAmount * odds);
    }

    else if(comSum == userSum)
    {
        puts("      [ Draw ]\t\t\t[ Draw ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Draw");
        bet_results ->user_balance += bet_results->betAmount;
    }

    else    // computer win
    {
        puts("       [ Win ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Fail");
    }
    bet_results->num_results += 1;  // 저장된 결과 개수 증가
    bet_results->num_of_games += 1; // 진행된 게임 수 증가
    getch();
}

float ReturnOdds(int userCard, int computerCard)    // 배당률 반환
{
    int num = computerCard - userCard;

    if(num == 9)
        return BATTLE_4;

    else if(num == 8)
        return BATTLE_3;
    
    else if(num == 7)
        return BATTLE_2;
    
    else    
        return BATTLE_1;
}

void PrintSuits(int suits_num)
{
    switch (suits_num)
    {
    case 0:
        printf("%s", SPADES);
        break;
        
    case 1:
        printf("%s", HEARTS);
        break;

    case 2:
        printf("%s", DIAMONDS);
        break;

    case 3:
        printf("%s", CLUBS);
        break;
    }
}

void NewGameCardBattle(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
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
            PlayBattleGame(gamecard, &bet_results);
            break;
        case END_GAME:
            return;
        default:
            puts("Please enter it correctly.");
            getch();
            ClearInputBuffer();
            break;
        }
    }
}

void ContinueCardBattle(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
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
            PlayBattleGame(gamecard, &bet_results);
            break;
        case END_GAME:
            return;
        default:
            puts("Please enter it correctly.");
            getch();
            ClearInputBuffer();
            break;
        }
    }
}

