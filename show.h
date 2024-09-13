#ifndef __SHOW_H__
#define __SHOW_H__
void ClearScreen();             // 콘솔 화면을 지우는 함수
void PauseScreen();             // 계속하려면 아무 키나 누르십시오 출력
void ShowLoginMenu(void);       // 로그인 메뉴 출력 함수
void ShowMainMenu(void);
void ShowListGames(void);       // 게임 메뉴 출력
void ShowProfile(ACCOUNT_INFO *user, int currentUserIndex);
void ShowOddEvenGameMenu(void); // 홀/짝 게임 메뉴 출력
void ShowOddEvenGamePlay(GAME_BET_RESULT *bet_results); // 홀 짝 게임 플레이 메뉴 출력
void ShowOddEvenBetItem(void);  // 홀 짝 베팅 항목 출력
#endif