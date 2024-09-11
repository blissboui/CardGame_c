#include <stdio.h>
#include <stdlib.h>
#include "card.h"

void ClearScreen() // 콘솔 화면 지우는 함수
{
    system("cls"); // windows에서 콘솔 화면을 지우는 명령어
}
void PauseScreen()  // 계속하려면 아무 키나 누르십시오 출력
{
    system("pause");
}
void ShowLoginMenu(void)
{
    ClearScreen();
    printf("\n[ Card Games ] \n"
           "1. Login \n"
           "2. Sign Up \n"
           "3. Exit Game \n\n"
           "Select: ");
}
void ShowMainMenu(void)
{
    ClearScreen();
    printf("\n[ MENU ] \n"
           "1. Game List \n"
           "2. Profile \n"
           "3. Log Out \n\n"
           "Select: ");
}
void ShowListGames(void) // 게임 목록 출력 함수
{
    ClearScreen();
    printf("\n[ List Of Games ] \n"
           "1. ODD-EVEN GAME \n"
           "2. LOW-HIGH GAME \n"
           "3. EXIT \n\n"
           "Select The Game: ");
}
void ShowProfile(ACCOUNT_INFO *user, int currentUserIndex)
{
    ClearScreen();
    printf("\n[ Profile ] \n"
           "ID: %s \n"
           "Balance: %d \n\n"
           "1. Deposit \n"
           "2. Withdraw \n"
           "3. EXIT \n\n"
           "Select: ",user[currentUserIndex].userID, user[currentUserIndex].balance);
}
void ShowOddEvenGameMenu(void) // 홀/짝 게임 메뉴 출력 함수
{
    ClearScreen();
    printf("\n[ODD-EVEN GAME]\n"
           "1. New Game \n"
           "2. Continue \n"
           "3. Result \n"
           "4. EXIT \n\n"
           "Select The Menu: ");
}
void ShowOddEvenGamePlay(void) // 홀 짝 게임 플레이 메뉴 출력 함수
{
    ClearScreen();
    printf("\n[GAME PLAY]\n"
           "1. Game Start \n"
           "2. End \n\n"
           "Select: ");
}
void ShowOddEvenBetItem(void) // 홀수 짝수 베팅 항목 출력 함수
{
    printf("1. ODD \n"
           "2. EVEN \n"
           "What Is Your Choice: ");
}