#include <stdio.h>
void ShowListGames(void)    // 게임 목록 출력 함수
{
    puts("\n---List Of Games--- \n" 
         "1. ODD-EVEN GAME \n"
         "2. LOW-HIGH GAME \n"
         "3. SUITS GUESSING GAME \n"
         "4. CARD SIZE MATCH GAME \n"
         "5. EXIT");
}
void ShowOddEvenGameMenu(void)  // 홀/짝 게임 메뉴 출력 함수
{
    puts("\n[ODD-EVEN GAME]\n"
         "1. New Game \n"
         "2. Continue \n"
         "3. Result \n"
         "4. EXIT \n");
}
void ShowOddEvenGamePlay(void)  // 홀 짝 게임 플레이 메뉴 출력 함수
{
    puts("\n[GAME PLAY]\n"
         "1. Game Start \n"
         "2. End \n");
}