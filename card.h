#ifndef CARD_H
#define CARD_H
#include <stdbool.h>

#define DECK 3                                           // 카드 덱 수
#define SUITS 4                                          // 카드 문양
#define NUMBERS 10                                       // 카드 숫자
#define RESULT_SIZE 10                                   // 결과 문자 크기
#define DEFAULT_RESULTS_MEMORY_SIZE 10                   // 결과 저장 메모리 기본크기
#define MAX_NUMBER_OF_GAMES (DECK * SUITS * NUMBERS / 4) // 새 게임 시 최대 가능 게임 횟수
// 총 120장

// 카드 덱 구조체
typedef struct
{
    int card[DECK][SUITS][NUMBERS]; // 포커카드 1~10 3덱 총 120장
    int num_first_card;             // 첫번째 카드 숫자
    int suits_first_card;           // 첫번재 카드 문양
    int num_second_card;            // 두번째 카드 숫자
} THE_CARD;

typedef struct
{
    char (*game_results)[RESULT_SIZE]; // 게임 결과 저장
    int num_results;                   // 저장된 결과의 수
    int num_of_games;                  // 카드 리셋 후 진행된 게임 수
    int size_results_memory;           // 결과 저장 메모리 크기
    bool odd_even_choice;              // 짝수=true, 홀수=false
    int betting_amount;                // 베팅 금액
} GAME_BET_RESULT;

#endif