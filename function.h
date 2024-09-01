#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "card.h"

#define ODD_EVEN_GAME 1
#define HIGH_LOW_GAME 2
#define SUITS_GUESSING_GAME 3
#define CARD_SIZE_MATCH_GAME 4
#define PROGRAM_END 5
#define New_game 1
#define Continue 2
#define Result 3
#define Exit 4
#define START_GAME 1
#define END_GAME 2
#define FIRST 1
#define SECOND 2

void ShowListGames(void);                        // 게임 메뉴 출력
void ShowOddEvenGameMenu(void);                  // 홀/짝 게임 메뉴 출력
void ShowOddEvenGamePlay(void);                  // 홀 짝 게임 플레이 메뉴 출력
THE_CARD *ResetCard(void);                       // 카드를 기본값으로 설정
int GetRandomNumber(int max, int min);           // 랜덤값 1개 반환 함수
void GetCard(THE_CARD *gamecard, int *sequence); // 랜덤 카드 출력하는 함수
#endif

// ♤◇♧♡