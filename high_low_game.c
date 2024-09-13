// #include "function.h"
// #include "struct.h"
// #include "show.h"

// void HighLowGame(ACCOUNT_INFO *user, int currentUserIndex, int user_num)
// {
//     THE_CARD *gamecard = NULL;
//     GAME_BET_RESULT bet_results = {NULL, 0, 0, DEFAULT_RESULTS_MEMORY_SIZE, user[currentUserIndex].balance};
//     while (1)
//     {
//         int select;
//         ClearScreen();
//         puts("\n[ HIGH-LOW GAME ]");
//         ShowGameMenu();
//         scanf("%d", &select);

//         switch (select)
//         {
//         case NEW_GAME:
//             NewGameOddEven(&gamecard, &bet_results);
//             break;
//         case CONTINUE:
//             ContinueOddEven(&gamecard, &bet_results);
//             break;
//         case RESULTS:
//             ShowGameResults(&bet_results);
//             break;
//         case BACK:
//             user[currentUserIndex].balance = bet_results.user_balance;
//             StoreData(user,user_num);
//             free(gamecard);
//             free(bet_results.game_results);
//             return;
//         }
//     }
// }

// void NewGameOddEven(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
// {
//     int state = 0;
//     while (1)
//     {
//         int select;
//         ShowGamePlay(bet_results);
//         scanf("%d", &select);
//         switch (select)
//         {
//         case START_GAME:
//             if (state == 0)
//             {
//                 NewGameSetUp(&gamecard, &bet_results);
//                 state = 1;
//             }
//             ResetDecksAfterGames(&gamecard, &bet_results);
//             PlayOddEvenGame(gamecard, &bet_results);
//             break;
//         case END_GAME:
//             return;
//         default:
//             puts("Please enter it correctly.");
//             getch();
//             break;
//         }
//     }
// }

// void PlayHighLowGame(THE_CARD **gamecard, GAME_BET_RESULT **bet_results) // 하이로우 게임 플레이 함수
// {
//     AddGameResultsMemory(bet_results);   // 결과 저장 메모리 부족 시 확장
//     GetFirstCard(*gamecard);             // 첫번째 카드 출력
//     ChooseOddEven(*bet_results);         // 베팅 항목 출력 후 홀 짝 선택
//     SetBetAmount(*bet_results);
//     GetSecondCard(*gamecard);            // 두번째 카드 출력
//     GameResult(*gamecard, *bet_results); // 홀 짝 게임 결과 출력 후 저장
// }