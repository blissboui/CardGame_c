#include "function.h"

bool OddEvenResult(THE_CARD *gamecard) // 홀수 짝수 결과 반환 함수
{
    bool result = (gamecard->num_first_card + gamecard->num_second_card) % 2 == 0 ? true : false;
    // 첫번째 카드와 두번째 카드를 더한 값이 짝수=true 홀수=false
    return result;
}
void GameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results)   // 홀 짝 게임 결과 출력 후 저장 함수
{
    // 홀수 짝수를 맞췄을 때
    if (OddEvenResult(gamecard) == bet_results->odd_even_choice)
    {
        puts("[ Succeed ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Succeed");
    }
    // 틀렸을 때
    else
    {
        puts("[ Fail ]");
        strcpy(bet_results->game_results[bet_results->num_results], "Fail");
    }
    bet_results->num_results += 1;  // 저장된 결과 개수 증가
    Sleep(4000);
}
void ChooseOddEven(GAME_BET_RESULT *bet_results) // 베팅 목록 출력 후 홀 짝 선택
{
    int choice;
    ShowOddEvenBetItem(); // 홀 짝 베팅 항목 출력
    scanf("%d", &choice);
    // 홀수 선택 시:false 짝수 선택 시:true
    bet_results->odd_even_choice = choice == 1 ? false : true;
}