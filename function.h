#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
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
#define FIRST 0
#define SECOND 1

// 메뉴 출력 함수
void ClearScreen();             // 콘솔 화면을 지우는 함수
void PauseScreen();             // 계속하려면 아무 키나 누르십시오 출력
void ShowListGames(void);       // 게임 메뉴 출력
void ShowOddEvenGameMenu(void); // 홀/짝 게임 메뉴 출력
void ShowOddEvenGamePlay(void); // 홀 짝 게임 플레이 메뉴 출력
void ShowOddEvenBetItem(void);  // 홀 짝 베팅 항목 출력

// 기능 함수
THE_CARD *ResetCard(void);                                           // 카드를 기본값으로 설정
int GetRandomNumber(int max, int min);                               // 랜덤값 1개 반환 함수
void GetFirstCard(THE_CARD *gamecard);                               // 첫번째 카드 출력 후 저장
void GetSecondCard(THE_CARD *gamecard);                              // 두번째 카드 출력 후 저장
void ResultAllocateMemory(GAME_BET_RESULT *bet_results);             // 게임 결과 저장하는 메모리
void ShowGameResults(GAME_BET_RESULT *bet_results);                  // 게임 결과 출력 함수
void NewGameSetUp(THE_CARD *gamecard, GAME_BET_RESULT *bet_results); // 게임 시작 전 설정 함수 (게임 시작 전 설정에 필요한 함수들의 집합)

// 홀 짝 게임 함수
void PlayOddEvenGame(THE_CARD *gamecard, GAME_BET_RESULT *bet_results); // 홀짝 게임 플레이 함수 (홀짝게임에 필요한 함수들의 집합)
void ChooseOddEven(GAME_BET_RESULT *bet_results);                       // 홀 짝 베팅 항목 출력 후 선택하는 함수
void GameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results);      // 홀 짝 게임 결과 출력 후 저장 함수
#endif

// ♤◇♧♡