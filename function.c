#include "function.h"
#include "card.h"

int GetRandomNumber(int max, int min)   // 랜덤값 반환 함수
{
    return rand()%(max-min+1)+min;
    // min~max에서 랜덤값 1개 반환
}
THE_CARD * ResetCard(void)    // 새 게임 시 카드 기본값 초기화 함수
{
    THE_CARD * gamecard=(THE_CARD*)malloc(sizeof(THE_CARD));
    // 카드 기본값 동적 할당
    for(int suits=0 ; suits<4 ; suits++)
    {
        for(int number=0 ; number<10 ; number++)
            gamecard->card[suits][number]=number+1;
    }
    return gamecard;    // 동적 할당된 메모리 반환
}
void Odd_Even_Game(void)    // 홀/짝 게임
{
    
}