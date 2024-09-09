#include "card.h"
#include "function.h"

int main(void)
{
    srand(time(NULL));
    ACCOUNT_INFO *user = CheckMemoryAllocation(malloc(DEFAULT_USER_NUM * sizeof(ACCOUNT_INFO)));
    int user_num = 0;
    while(1)
    {
        while (1)   // 로그인, 회원가입
        {
            int select, login_success = 0, signUp_success = 0;
            ShowLoginMenu();
            scanf("%d", &select);

            switch (select)
            {
            case LOGIN:
                login_success = LoginUser(user, user_num);

                if (login_success == 1)
                    puts("--- Login Successful ---");
                else
                    puts("--- Login Failed ---");
                getch();
                break;

            case SIGN_UP:
                signUp_success = SignUpUser(user, user_num);

                if(signUp_success == 1)
                    puts("--- Sign up Successful ---");
                else
                    puts("--- Sign up Failed ---");
                user_num++;
                getch();
                break;
            case EXIT_GAME:
                return 0;
            default:
                puts("please enter it correctly.");
                getch();
                break;
            }

            if (login_success == 1)
                break;
        }
        while(1)    // 메인메뉴
        {
            int select;
            ShowMainMenu();
            scanf("%d",&select);

            switch(select)
            {
                case GAME_LIST:
                    GameList();
                    break;
                case PROFILE:
                    break;
                case LOG_OUT:
                    break;
                default:
                    puts("please enter it correctly.");
                    getch();
                    break;
            }
            if(select == LOG_OUT)
                break;
        }
    }
}
void GameList(void)
{
    while(1)
    {
        int select;
        ShowListGames();
        scanf("%d",&select);

        switch (select)
        {
        case ODD_EVEN_GAME:
            OddEvenGame(); 
            break;
        case HIGH_LOW_GAME:
            break;
        case EXIT_LIST:
            break;
        default:
            puts("please enter it correctly.");
            getch();
            break;
        }

        if(select == EXIT_LIST)
            break;
    }
}
void OddEvenGame(void)
{
    THE_CARD *gamecard = NULL;
    GAME_BET_RESULT bet_results = {NULL, 0, 0, DEFAULT_RESULTS_MEMORY_SIZE};
    while(1)
    {
        int select;
        ShowOddEvenGameMenu();
        scanf("%d",&select);

        switch(select)
        {
            case NEW_GAME:
                NewGameOddEven(&gamecard,&bet_results);
            case CONTINUE:
                break;
            case RESULTS:
                break;
            case BACK:
                break;
        }

        if(select == BACK)
            break;
    }
}
void NewGameOddEven(THE_CARD **gamecard, GAME_BET_RESULT *bet_results)
{
    while(1)
    {
        int select, state=0;
        ShowOddEvenGamePlay();
        scanf("%d",&select);
        switch(select)
        {
            case START_GAME:
                if(state == 0)
                {
                    NewGameSetUp(&gamecard, &bet_results);
                    state = 1;
                }
                ResetDecksAfterGames(&gamecard, &bet_results);
                PlayOddEvenGame(gamecard, &bet_results);
                break;
            case END_GAME:
                break;
            default:
                puts("Please enter it correctly.");
                getch();
                break;
        }
        if(select == END_GAME)
            break;
    }
}
