#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include "card.h"

#define LOGIN 1
#define SIGN_UP 2
#define EXIT 3
#define GAME_LIST 1
#define PROFILE 2
#define LOG_OUT 3
#define ODD_EVEN_GAME 1
#define HIGH_LOW_GAME 2
#define NEW_GAME 1
#define CONTINUE 2
#define RESULTS 3
#define BACK 4
#define START_GAME 1
#define END_GAME 2
#define DEPOSIT 1
#define WITHDRAW 2
#define SPADES "\xE2\x99\xA0"
#define HEARTS "\xE2\x99\xA5"
#define DIAMONDS "\xE2\x99\xA6"
#define CLUBS "\xE2\x99\xA3"

// 기능 함수
THE_CARD *ResetDecks(void);                                            // 카드를 기본값으로 설정
void ResetDecksAfterGames(THE_CARD ***gamecard, GAME_BET_RESULT **bet_results); // 최대 게임 횟수 초과 시 카드덱 리셋
bool CheckCardDuplication(int card);                                  // 카드 중복 확인 함수
int GetRandomNumber(int max, int min);                                // 랜덤값 1개 반환 함수
void GetFirstCard(THE_CARD *gamecard);                                // 첫번째 카드 출력 후 저장
void GetSecondCard(THE_CARD *gamecard);                               // 두번째 카드 출력 후 저장
void AllocateGameResultsMemory(GAME_BET_RESULT **bet_results);        // 게임 결과 저장하는 메모리 최초 할당
void AddGameResultsMemory(GAME_BET_RESULT **bet_results);             // 결과 저장 메모리가 부족할 시 확장
void *CheckMemoryAllocation(void *memory);                            // 메모리 할당 검사 함수
void ShowGameResults(GAME_BET_RESULT *bet_results);                   // 게임 결과 출력 함수
void NewGameSetUp(THE_CARD ***gamecard, GAME_BET_RESULT **bet_results); // 게임 시작 전 설정 함수 (게임 시작 전 설정에 필요한 함수들의 집합)
void SetBetAmount(GAME_BET_RESULT *bet_results);
void ClearLine(void);   // 현재 줄과 이전 줄을 지우는 함수

// 홀 짝 게임 함수
void PlayOddEvenGame(THE_CARD **gamecard, GAME_BET_RESULT **bet_results); // 홀짝 게임 플레이 함수 (홀짝게임에 필요한 함수들의 집합)
void ChooseOddEven(GAME_BET_RESULT *bet_results);                       // 홀 짝 베팅 항목 출력 후 선택하는 함수
void GameResult(THE_CARD *gamecard, GAME_BET_RESULT *bet_results);      // 홀 짝 게임 결과 출력 후 저장 함수

int LoginUser(ACCOUNT_INFO *user, int user_num, int *currentUserIndex);
void SignUpUser(ACCOUNT_INFO *user, int *user_num);
void ClearInputBuffer(void);
void RemoveNewline(char str[]);
void GameList(ACCOUNT_INFO *user, int currentUserIndex, int user_num);
void OddEvenGame(ACCOUNT_INFO *user, int currentUserIndex, int user_num);
void NewGameOddEven(THE_CARD **gamecard, GAME_BET_RESULT *bet_results);
void ContinueOddEven(THE_CARD **gamecard, GAME_BET_RESULT *bet_results);
FILE *CheckFileOpen(FILE *userData);
void LoadData(ACCOUNT_INFO *user,int *user_num);
void StoreData(ACCOUNT_INFO *user, int user_num);
void Profile(ACCOUNT_INFO *user, int currentUserIndex, int user_num);
void Withdrawal(ACCOUNT_INFO *user, int currentUserIndex);
void Deposit(ACCOUNT_INFO *user, int currentUserIndex);
#endif

// ♤◇♧♡