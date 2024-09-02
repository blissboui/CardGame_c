#ifndef CARD_H
#define CARD_H
#include <stdbool.h>

#define NUMBERS 10     // 카드 숫자
#define SUITS 4        // 카드 문양
#define RESULT_SIZE 10 // 결과 문자 크기
// 총 40장

// 카드 덱 구조체
typedef struct
{
    int card[SUITS][NUMBERS]; // 4개 문양 1~10까지 총 40장
    int num_first_card;           // 첫번째 카드 숫자
    int suits_first_card;     // 첫번재 카드 문양
    int num_second_card;          // 두번째 카드 숫자
} THE_CARD;

typedef struct
{
    char (*game_results)[RESULT_SIZE]; // 게임 결과 저장
    int num_results;    // 저장된 결과의 수
    int size_memory_results; // 결과 저장 메모리 크기
    bool odd_even_choice;    // 짝수=true, 홀수=false
    int betting_amount;      // 베팅 금액
} GAME_BET_RESULT;

#endif