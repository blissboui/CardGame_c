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
char * GetSuits(int suits_num)   // 카드 문양 전달 함수
{
    char * suits;
    switch(suits_num)
    {
        case 1:
            strcpy(suits,"\xE2\x99\xA0"); // 스페이드
            break;
        case 2:
            strcpy(suits,"\xE2\x99\xA5"); // 하트
            break;
        case 3:
            strcpy(suits,"\xE2\x99\xA6"); // 다이아
            break;
        case 4:
            strcpy(suits,"\xE2\x99\xA3"); // 클로버
            break;
    }
    return suits;
}
bool CheckCardDuplication(int card) // 카드 중복 확인 함수 (한번 나왔던 카드는 안 나오게)
{
    return card == 0 ? false : true;
}
void FirstCard(THE_CARD * gamecard)
{
    int random_number;
    int random_suits;
    do
    {
    random_number=GetRandomNumber(0,9); // 랜덤 숫자
    random_suits=GetRandomNumber(0,3);  // 랜덤 문양
    } while(CheckCardDuplication(gamecard->card[random_suits][random_number]));
    printf("첫번째 카드 [ %s%d ] \n",GetSuits(random_suits),gamecard->card[random_suits][random_number]);
    gamecard->card[random_suits][random_number] = 0;    // 한번 나온 카드값을 0으로 초기화
    // 한번 나온 카드는 다시 나오지 않음
}
void SecondCard(THE_CARD * gamecard)
{
    int 
}