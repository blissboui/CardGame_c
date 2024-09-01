#ifndef CARD_H
#define CARD_H

#define NUMBERS 10 // 카드 숫자
#define SUITS 4    // 카드 문양
// 총 40장


// 카드 덱 구조체
typedef struct
{
    int card[SUITS][NUMBERS]; // 4개 문양 1~10까지 총 40장
    int first_card;           // 첫번째 카드
    int second_card;          // 두번째 카드
} THE_CARD;

typedef struct
{
    char (*game_result)[10]; // 게임 결과 저장
    bool odd_even_choice;    // 짝수=true, 홀수=false
    int betting_amount;      // 베팅 금액
} GAME_BET_RESULT;

#endif