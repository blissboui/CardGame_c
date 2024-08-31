#ifndef FUNCTION_h
#define FUNCTION_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
void ShowListGames(void);   // 게임 메뉴 출력
void ShowOddEvenGame(void); // 홀/짝 게임 메뉴 출력
THE_CARD * ResetCard(void); // 카드를 기본값으로 설정
int GetRandomNumber(int max, int min);  // 랜덤값 1개 반환 함수
#endif