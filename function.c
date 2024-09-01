#include "function.h"
#include "card.h"

int GetRandomNumber(int min, int max) // 랜덤값 반환 함수
{
    return rand() % (max - min + 1) + min;
    // min~max에서 랜덤값 1개 반환
}
THE_CARD *ResetCard(void) // 새 게임 시 카드 기본값 초기화 함수
{
    THE_CARD *gamecard = (THE_CARD *)malloc(sizeof(THE_CARD));
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
char *GetSuits(int suits_num) // 카드 문양 전달 함수
{
    char *suits=(char*)malloc(4*sizeof(char));
    // UTF-8로 인코딩된 문자로 \0 포함 4바이트 필요
    switch (suits_num)
    {
    case 1:
        strcpy(suits, "\xE2\x99\xA0"); // 스페이드
        break;
    case 2:
        strcpy(suits, "\xE2\x99\xA5"); // 하트
        break;
    case 3:
        strcpy(suits, "\xE2\x99\xA6"); // 다이아
        break;
    case 4:
        strcpy(suits, "\xE2\x99\xA3"); // 클로버
        break;
    }
    return suits;
}
bool CheckCardDuplication(int card) // 카드 중복 확인 함수 (한번 나왔던 카드는 안 나오게)
{
    return card == 0 ? true : false;
    // 나왔던 카드라면 true 반환
    // 한번 나온 카드는 0으로 초기화 되었기 때문
}
void GetCard(THE_CARD *gamecard, int *sequence) // 카드 출력 함수
{
    int random_number;
    int random_suits;
    char *suits=NULL;   // 카드문양 저장
    char *first_or_second = *sequence == FIRST ? "First Card" : "Second Card";
    // sequence 값이 0이면 첫번째 or 1이면 두번째
    do
    {
        random_number = GetRandomNumber(0, 9); // 랜덤 숫자
        random_suits = GetRandomNumber(0, 3);  // 랜덤 문양
        // CheckCardDuplication()가 false를 반환 할때 까지 반복
    } while (CheckCardDuplication(gamecard->card[random_suits][random_number]));

    if (*sequence == FIRST) // *sequence 값이 첫번째 일 때
        gamecard->first_card = gamecard->card[random_suits][random_number];
    else // *sequence 값이 두번째 일 때
        gamecard->second_card = gamecard->card[random_suits][random_number];
    *sequence = !(*sequence); // 첫번째 or 두번째 변경

    ClearScreen(); // 화면 지우기
    suits=GetSuits(random_suits);
    printf("%s [ %s%d ] \n", first_or_second, suits, gamecard->card[random_suits][random_number]);
    free(suits);    // 문양 출력이 끝나면 메모리 해제
    gamecard->card[random_suits][random_number] = 0; // 한번 나온 카드값을 0으로 초기화
    // 한번 나온 카드는 다시 나오지 않음
}
bool OddEvenResult(THE_CARD *gamecard) // 홀수 짝수 결과 반환 함수
{
    bool result = (gamecard->first_card + gamecard->second_card) % 2 == 0 ? true : false;
    // 첫번째 카드와 두번째 카드를 더한 값이 짝수=true 홀수=false
    return result;
}
void GameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results)
{
    ResultAllocateMemory(bet_results);
    // 홀수 짝수를 맞췄을 때
    if (OddEvenResult(gamecard) == bet_results->odd_even_choice)
    {
        puts("[ Succeed ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Succeed");
        bet_results->num_results += 1;
    }

    // 틀렸을 때
    else
    {
        puts("[ Fail ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Fail");
        bet_results->num_results += 1;
    }
}
void ChooseOddEven(GAME_BET_RESULT *bet_results)
{
    int choice;
    ShowOddEvenBetItem(); // 홀 짝 베팅 항목 출력
    scanf("%d", &choice);
    // 홀수 선택 시:false 짝수 선택 시:true
    bet_results->odd_even_choice = choice == 1 ? false : true;
}
void ResultAllocateMemory(GAME_BET_RESULT *bet_results) // 게임 결과 저장 메모리 할당, 추가
{
    if (bet_results->num_results + 1 == bet_results->size_memory_results)
    {
        // 결과 저장 멤버의 메모리가 부족할 시 5 증가
        bet_results->game_results = (char(*)[RESULT_SIZE])
            realloc(bet_results->game_results, sizeof(bet_results->game_results) * (bet_results->size_memory_results + 5));
        bet_results->size_memory_results += 5; // 늘린 메모리크기 저장
    }
}