#ifndef __STRUCT_H__
#define __STRUCT_H__
#include <stdbool.h>

#define DECK 3                                           // 카드 덱 수
#define SUITS 4                                          // 카드 문양
#define NUMBERS 10                                       // 카드 숫자
#define RESULT_SIZE 10                                   // 결과 문자 크기
#define DEFAULT_RESULTS_MEMORY_SIZE 10                   // 결과 저장 메모리 기본크기
#define MAX_NUMBER_OF_GAMES (DECK * SUITS * NUMBERS / 4) // 새 게임 시 최대 가능 게임 횟수
#define BET_PAYOUT 1.98

#define USER_DATA "user_data.txt"
#define MAX_ID_LEN 10
#define MAX_PW_LEN 20
#define DEFAULT_USER_NUM 10
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
    int user_balance;
    int betAmount;
    bool odd_even_choice; // 짝수=true, 홀수=false
    bool high_low_choice; // 하이=true, 로우=false
} GAME_BET_RESULT;

typedef struct
{
    char userID[MAX_ID_LEN];
    char userPW[MAX_PW_LEN];
    int balance;
} ACCOUNT_INFO;

#endif