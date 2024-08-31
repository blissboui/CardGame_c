#ifndef FUNCTION_h
#define FUNCTION_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define ODD_EVEN_GAME 1
#define HIGH_LOW_GAME 2
#define SUITS_GUESSING_GAME 3
#define CARD_SIZE_MATCH_GAME 4
#define END 5
#define New_game 1
#define Continue 2
#define Result 3
#define Exit 4
void ShowListGames(void);   // 게임 메뉴 출력
void ShowOddEvenGame(void); // 홀/짝 게임 메뉴 출력
THE_CARD * ResetCard(void); // 카드를 기본값으로 설정
int GetRandomNumber(int max, int min);  // 랜덤값 1개 반환 함수
#endif