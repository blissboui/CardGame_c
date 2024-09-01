#include <stdio.h>
#include <stdlib.h>

void ClearScreen() // 콘솔 화면 지우는 함수
{
    system("cls"); // windows에서 콘솔 화면을 지우는 명령어
}
void ShowListGames(void) // 게임 목록 출력 함수
{
    ClearScreen();
    printf("\n---List Of Games--- \n"
           "1. ODD-EVEN GAME \n"
           "2. LOW-HIGH GAME \n"
           "3. SUITS GUESSING GAME \n"
           "4. CARD SIZE MATCH GAME \n"
           "5. EXIT \n\n"

           "Select The Game: ");
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
           "2. EVEN \n\n"

           "What Is Your Choice: ");
}