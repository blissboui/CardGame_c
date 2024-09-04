#include "function.h"

int GetRandomNumber(int min, int max) /*** 랜덤값 반환 함수 ***/
{
    return rand() % (max - min + 1) + min;
    // min~max에서 랜덤값 1개 반환
}

THE_CARD *ResetCard(void) /*** 새 게임 시 카드 기본값 초기화 함수 ***/
{
    THE_CARD *gamecard = (THE_CARD *)CheckMemoryAllocation(malloc(sizeof(THE_CARD)));
    // 카드 기본값 동적 할당
    if (gamecard == NULL)
    {
        puts("Program Error \n");
        return NULL;
    }
    for (int suits = 0; suits < 4; suits++)
    {
        for (int number = 0; number < 10; number++)
        {
            gamecard->card[suits][number] = number + 1;
        }
    }
    return gamecard; // 동적 할당된 메모리 주소 반환
}

char *GetSuits(int suits_num) /***  카드 문양 전달 함수 ***/
{
    char *suits = (char *)CheckMemoryAllocation(malloc(4 * sizeof(char)));
    // UTF-8로 인코딩된 문자로 \0 포함 4바이트 필요
    switch (suits_num)
    {
    case 0:
        strcpy(suits, "\xE2\x99\xA0"); // 스페이드
        break;
    case 1:
        strcpy(suits, "\xE2\x99\xA5"); // 하트
        break;
    case 2:
        strcpy(suits, "\xE2\x99\xA6"); // 다이아
        break;
    case 3:
        strcpy(suits, "\xE2\x99\xA3"); // 클로버
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
    int random_number;
    int random_suits;
    char *suits = NULL; // 카드문양 저장
    do
    {
        random_number = GetRandomNumber(0, 9); // 랜덤 숫자
        random_suits = GetRandomNumber(0, 3);  // 랜덤 문양
        // CheckCardDuplication()가 false를 반환 할때 까지 반복
        // 해당 카드가 이전에 나왔었는지 검사
    } while (CheckCardDuplication(gamecard->card[random_suits][random_number]));

    gamecard->num_first_card = random_number + 1; // 첫번째 카드 숫자 저장
    gamecard->suits_first_card = random_suits;    // 첫번째 카드 문양 저장

    ClearScreen(); // 화면 지우기
    suits = GetSuits(random_suits);
    printf("\nFirst  Card [ %s%d ] \n\n", suits, gamecard->card[random_suits][random_number]);
    free(suits); // 문양 출력이 끝나면 메모리 해제
    gamecard->card[random_suits][random_number] = 0;
    // 한번 나온 카드값을 0으로 초기화 (다시 나오지 않음)
}

void GetSecondCard(THE_CARD *gamecard) /*** 두번째 카드 출력후 저장 ***/
{
    int random_number;
    int random_suits;
    char *suits = NULL; // 카드문양 저장
    do
    {
        random_number = GetRandomNumber(0, 9); // 랜덤 숫자
        random_suits = GetRandomNumber(0, 3);  // 랜덤 문양
        // CheckCardDuplication()가 false를 반환 할때 까지 반복
        // 해당 카드가 이전에 나왔었는지 검사
    } while (CheckCardDuplication(gamecard->card[random_suits][random_number]));

    gamecard->num_second_card = gamecard->card[random_suits][random_number]; // 두번째 카드 숫자저장

    ClearScreen(); // 화면 지우기
    suits = GetSuits(gamecard->suits_first_card);
    printf("\nFirst  Card [ %s%d ] \n", suits, gamecard->num_first_card);
    free(suits); // 첫번째 카드 문양 출력 후 메모리 해제
    //Sleep(3000); // 2초 동안 대기
    suits = GetSuits(random_suits);
    printf("Second Card [ %s%d ] \n", suits, gamecard->card[random_suits][random_number]);
    free(suits); // 두번째 카드 문양 출력이 끝나면 메모리 해제
    gamecard->card[random_suits][random_number] = 0;
    //Sleep(3000); // 1초 동안 대기
    // 한번 나온 카드값을 0으로 초기화 (다시 나오지 않음)
}

void AllocateGameResultsMemory(GAME_BET_RESULT **bet_results) /***  게임 결과 저장 메모리 최초 할당 ***/
{
    (*bet_results)->game_results = (char(*)[RESULT_SIZE])CheckMemoryAllocation(malloc(INIT_RESULTS_STORAGE_MEMORY * sizeof((*bet_results)->game_results)));
}
void AddGameResultsMemory(GAME_BET_RESULT **bet_results) /*** 게임 결과 저장 메모리 추가 할당 ***/
{
    if ((*bet_results)->num_results == (*bet_results)->size_results_memory)
    {
        (*bet_results)->size_results_memory += 5;
        (*bet_results)->game_results = CheckMemoryAllocation(realloc((*bet_results)->game_results, (*bet_results)->size_results_memory * sizeof((*bet_results)->game_results)));
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
    for (int result = 0; result < bet_results->num_results; result++)
    {
        printf("%2d. %s \n", result + 1, bet_results->game_results[result]);
    }
    getch();
}
void NewGameSetUp(THE_CARD **gamecard, GAME_BET_RESULT *bet_results) /*** 게임 시작 전 설정 함수 (게임 시작 전 설정에 필요한 함수들의 집합) ***/
{
    free(*gamecard);
    *gamecard = ResetCard();                    // 새로운 카드덱 생성
    free(bet_results->game_results);            // 새 게임 시작시 결과 저장 메모리 해제
    AllocateGameResultsMemory(&bet_results); // 게임 결과 저장 메모리 할당
    bet_results->num_results = 0;               // 저장된 결과 개수 초기화
}
