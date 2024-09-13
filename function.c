#include "function.h"
#include "show.h"
#include "struct.h"

FILE *CheckFileOpen(FILE *userData)
{
    if (userData == NULL)
    {
        puts("Failed to open file.");
        getch();
        return NULL;
    }
    return userData;
}
void StoreData(ACCOUNT_INFO *user, int user_num)
{
    FILE *fileclear = CheckFileOpen(fopen(USER_DATA, "w"));
    fclose(fileclear);
    FILE *userData = CheckFileOpen(fopen(USER_DATA, "a"));
    for (int idx = 0; idx < user_num; idx++)
        fprintf(userData, "%s %s %d\n", user[idx].userID, user[idx].userPW, user[idx].balance);

    fclose(userData);
}
void LoadData(ACCOUNT_INFO *user, int *user_num)
{
    FILE *userData = CheckFileOpen(fopen(USER_DATA, "r"));
    while (1)
    {
        fscanf(userData, "%s %s %d", user[*user_num].userID, user[*user_num].userPW, &user[*user_num].balance);
        if (feof(userData) != 0)
            break;
        (*user_num)++;
    }
    fclose(userData);
}
int LoginUser(ACCOUNT_INFO *user, int user_num, int *currentUserIndex)
{
    char id[MAX_ID_LEN];
    char password[MAX_PW_LEN];
    ClearInputBuffer();
    ClearScreen();
    puts("\n[ Login ]");

    printf("ID: \n");
    printf("PW: ");

    printf("\033[A"); // 커서를 위로 이동
    fgets(id, MAX_ID_LEN, stdin);
    RemoveNewline(id);

    printf("PW: ");
    fgets(password, MAX_PW_LEN, stdin);
    RemoveNewline(password);
    for (int idx = 0; idx < user_num; idx++)
    {
        if (strcmp(id, user[idx].userID) == 0 && strcmp(password, user[idx].userPW) == 0)
        { // 같을 때
            puts("--- Login Successful ---");
            *currentUserIndex = idx;
            return 1;
        }
    }
    puts("--- Login Failed ---");
    return 0;
}
void SignUpUser(ACCOUNT_INFO *user, int *user_num)
{
    char confirm_password[MAX_PW_LEN];
    ClearInputBuffer();
    ClearScreen();
    puts("\n[ Sign up ]");
    printf("ID: \n");
    printf("PW: ");

    printf("\033[A");
    fgets(user[*user_num].userID, MAX_ID_LEN, stdin);
    RemoveNewline(user[*user_num].userID);

    printf("PW: ");
    fgets(user[*user_num].userPW, MAX_PW_LEN, stdin);
    RemoveNewline(user[*user_num].userPW);

    printf("Confirm PW: ");
    fgets(confirm_password, MAX_PW_LEN, stdin);
    RemoveNewline(confirm_password);

    if (strcmp(user[*user_num].userPW, confirm_password) == 0)
    {
        puts("--- Sign up Successful ---");
        user[*user_num].balance = 0;
        (*user_num)++;
        StoreData(user, *user_num);
        return;
    }
    puts("--- Sign up Failed ---");
    return;
}
void GameList(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
{
    while (1)
    {
        int select;
        ShowListGames();
        scanf("%d", &select);

        switch (select)
        {
        case ODD_EVEN_GAME:
            OddEvenGame(user, currentUserIndex, user_num);
            break;
        case HIGH_LOW_GAME:
            break;
        case EXIT:
            return;
        default:
            puts("please enter it correctly.");
            getch();
            break;
        }
    }
}
void Profile(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
{
    while (1)
    {
        int select;
        ShowProfile(user, currentUserIndex);
        scanf("%d", &select);

        switch (select)
        {
        case DEPOSIT:
            Deposit(user, currentUserIndex);
            break;
        case WITHDRAW:
            Withdrawal(user, currentUserIndex);
            break;
        case EXIT:
            StoreData(user, user_num);
            return;
        default:
            puts("please enter it correctly.");
            getch();
            break;
        }
    }
}
void Deposit(ACCOUNT_INFO *user, int currentUserIndex)
{
    int depositAmount;
    ClearScreen();
    printf("\n[ Deposit ] \n"
           "Deposit Amount: ");
    scanf("%d", &depositAmount);

    user[currentUserIndex].balance += depositAmount;
}
void Withdrawal(ACCOUNT_INFO *user, int currentUserIndex)
{
    int whitdrawalAmount;
    ClearScreen();
    printf("\n[ Deposit ] \n"
           "Withdrawal Amount: ");
    scanf("%d", &whitdrawalAmount);

    user[currentUserIndex].balance -= whitdrawalAmount;
}
void ClearInputBuffer(void)
{
    while (getchar() != '\n')
        ;
}
void RemoveNewline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}
int GetRandomNumber(int min, int max) /*** 랜덤값 반환 함수 ***/
{
    return rand() % (max - min + 1) + min;
    // min~max에서 랜덤값 1개 반환
}

THE_CARD *ResetDecks(void) /*** 새 게임 시 카드 기본값 초기화 함수 ***/
{
    THE_CARD *gamecard = (THE_CARD *)CheckMemoryAllocation(malloc(sizeof(THE_CARD)));
    // 카드 기본값 동적 할당
    for (int deck = 0; deck < DECK; deck++)
    {
        for (int suits = 0; suits < SUITS; suits++)
        {
            for (int number = 0; number < NUMBERS; number++)
            {
                gamecard->card[deck][suits][number] = number + 1;
            }
        }
    }
    return gamecard; // 동적 할당된 메모리 주소 반환
}
void ResetDecksAfterGames(THE_CARD ***gamecard, GAME_BET_RESULT **bet_results) /*** 최대 게임 횟수 초과 시 카드덱 리셋 ***/
{
    // 카드 리셋 후 진행된 게임 수가 최대 게임 수 일때 카드덱 리셋
    if ((*bet_results)->num_of_games == MAX_NUMBER_OF_GAMES)
    {
        free(**gamecard);                 // 기존 카드덱 메모리 해제
        **gamecard = ResetDecks();        // 새로운 카드덱 초기화
        (*bet_results)->num_of_games = 1; // 기본값
    }
}

char *GetSuits(int suits_num) /***  카드 문양 전달 함수 ***/
{
    char *suits = (char *)CheckMemoryAllocation(malloc(4 * sizeof(char)));
    // UTF-8로 인코딩된 문자로 \0 포함 4바이트 필요
    switch (suits_num)
    {
    case 0:
        strcpy(suits, SPADES); // 스페이드
        break;
    case 1:
        strcpy(suits, HEARTS); // 하트
        break;
    case 2:
        strcpy(suits, DIAMONDS); // 다이아
        break;
    case 3:
        strcpy(suits, CLUBS); // 클로버
        break;
    }
    return suits;
}

bool CheckCardDuplication(int card) /*** 카드 중복 확인 함수 (한번 나왔던 카드는 안 나오게) ***/
{
    return card == 0 ? true : false;
    // 나왔던 카드라면 true 반환
    // 한번 나온 카드는 0으로 초기화 되었기 때문
}

void GetFirstCard(THE_CARD *gamecard) /*** 첫번째 카드 출력후 저장 ***/
{
    int random_deck;
    int random_suits;
    int random_number;
    char *suits = NULL; // 카드문양 저장
    do
    {
        random_deck = GetRandomNumber(0, DECK - 1);      // 랜덤 덱
        random_suits = GetRandomNumber(0, SUITS - 1);    // 랜덤 문양
        random_number = GetRandomNumber(0, NUMBERS - 1); // 랜덤 숫자
        // CheckCardDuplication()가 false를 반환 할때 까지 반복
        // 해당 카드가 이전에 나왔었는지 검사
    } while (CheckCardDuplication(gamecard->card[random_deck][random_suits][random_number]));

    gamecard->num_first_card = random_number + 1; // 첫번째 카드 숫자 저장
    gamecard->suits_first_card = random_suits;    // 첫번째 카드 문양 저장

    ClearScreen(); // 화면 지우기
    suits = GetSuits(random_suits);
    printf("\nFirst  Card [ %s%d ] \n\n", suits, random_number + 1);
    free(suits); // 문양 출력이 끝나면 메모리 해제
    gamecard->card[random_deck][random_suits][random_number] = 0;
    // 한번 나온 카드값을 0으로 초기화 (다시 나오지 않음)
}

void GetSecondCard(THE_CARD *gamecard) /*** 두번째 카드 출력후 저장 ***/
{
    int random_deck;
    int random_suits;
    int random_number;
    char *suits = NULL; // 카드문양 저장
    do
    {
        random_deck = GetRandomNumber(0, DECK - 1);      // 랜덤 덱
        random_suits = GetRandomNumber(0, SUITS - 1);    // 랜덤 문양
        random_number = GetRandomNumber(0, NUMBERS - 1); // 랜덤 숫자
        // CheckCardDuplication()가 false를 반환 할때 까지 반복
        // 해당 카드가 이전에 나왔었는지 검사
    } while (CheckCardDuplication(gamecard->card[random_deck][random_suits][random_number]));

    gamecard->num_second_card = random_number + 1; // 두번째 카드 숫자저장

    ClearScreen(); // 화면 지우기
    suits = GetSuits(gamecard->suits_first_card);
    printf("\nFirst  Card [ %s%d ] \n", suits, gamecard->num_first_card);
    free(suits); // 첫번째 카드 문양 출력 후 메모리 해제
    Sleep(3000); // 2초 동안 대기
    suits = GetSuits(random_suits);
    printf("Second Card [ %s%d ] \n", suits, random_number + 1);
    free(suits); // 두번째 카드 문양 출력이 끝나면 메모리 해제
    gamecard->card[random_deck][random_suits][random_number] = 0;
    Sleep(1000); // 1초 동안 대기
    //  한번 나온 카드값을 0으로 초기화 (다시 나오지 않음)
}

void AllocateGameResultsMemory(GAME_BET_RESULT **bet_results) /***  게임 결과 저장 메모리 최초 할당 ***/
{
    (*bet_results)->game_results = CheckMemoryAllocation(malloc(DEFAULT_RESULTS_MEMORY_SIZE * RESULT_SIZE));
}
void AddGameResultsMemory(GAME_BET_RESULT **bet_results) /*** 게임 결과 저장 메모리 확장 ***/
{
    if ((*bet_results)->num_results == (*bet_results)->size_results_memory)
    {
        (*bet_results)->size_results_memory += 5;
        (*bet_results)->game_results = CheckMemoryAllocation(realloc((*bet_results)->game_results, (*bet_results)->size_results_memory * RESULT_SIZE));
        // 메모리 추가가 필요할 시 5만큼 추가 할당
    }
}
void *CheckMemoryAllocation(void *memory) /*** 메모리 할당 검사 함수 ***/
{
    if (memory == NULL)
    {
        puts("Memory allocation failed!");
        exit(EXIT_FAILURE);
        //  메모리 할당 실패 시 프로그램 종료
    }
    return memory;
}
void ShowGameResults(GAME_BET_RESULT *bet_results) /*** 게임 결과 출력 함수***/
{
    ClearScreen();
    puts("\n[ Games Result ]\n");
    for (int result = 0; result < bet_results->num_results; result++)
    {
        printf("%2d. %s \n", result + 1, bet_results->game_results[result]);
    }
    getch();
}
void NewGameSetUp(THE_CARD ***gamecard, GAME_BET_RESULT **bet_results) /*** 게임 시작 전 설정 함수 (게임 시작 전 설정에 필요한 함수들의 집합) ***/
{
    free(**gamecard);
    **gamecard = ResetDecks();                  // 새로운 카드덱 생성
    free((*bet_results)->game_results);         // 새 게임 시작시 결과 저장 메모리 해제
    AllocateGameResultsMemory(&(*bet_results)); // 게임 결과 저장 메모리 할당
    (*bet_results)->num_results = 0;            // 저장된 결과 개수 초기화
}
void SetBetAmount(GAME_BET_RESULT *bet_results)
{
    printf("\nBalance [ %d ] \n",bet_results->user_balance);
    while(1)   // 배팅 금액이 현재 잔액보다 크면 반복
    {
        printf("Enter your bet amount: ");
        scanf("%d", &bet_results->betAmount);

        if(bet_results->betAmount <= bet_results->user_balance)
            break;
        printf("please enter it correctly");
        getch();
        ClearLine();
    }
    bet_results->user_balance -= bet_results->betAmount;
}
void ClearLine(void)
{
    printf("\033[0G");
    printf("\033[K");
    printf("\033[A");
    printf("\033[0G");
    printf("\033[K");
}