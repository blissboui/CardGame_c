#include "function.h"
#include "card.h"
#include "show.h"

int main(void)
{
    srand(time(NULL));
    ACCOUNT_INFO *user = CheckMemoryAllocation(malloc(DEFAULT_USER_NUM * sizeof(ACCOUNT_INFO)));
    int user_num = 0, currentUserIndex;

    LoadData(user, &user_num);
    while (1)
    {
        while (1) // 로그인, 회원가입
        {
            int select, login_success = 0, signUp_success = 0;
            ShowLoginMenu();
            scanf("%d", &select);

            switch (select)
            {
            case LOGIN:
                login_success = LoginUser(user, user_num, &currentUserIndex);

                if (login_success == 1)
                    puts("--- Login Successful ---");
                else
                    puts("--- Login Failed ---");
                getch();
                break;

            case SIGN_UP:
                signUp_success = SignUpUser(user, &user_num);

                if (signUp_success == 1)
                    puts("--- Sign up Successful ---");

                else
                    puts("--- Sign up Failed ---");
                getch();
                break;
            case EXIT:
                StoreData(user, user_num);
                free(user);
                return 0;
            default:
                puts("please enter it correctly.");
                getch();
                break;
            }

            if (login_success == 1)
                break;
        }
        while (1) // 메인메뉴
        {
            int select;
            ShowMainMenu();
            scanf("%d", &select);

            switch (select)
            {
            case GAME_LIST:
                GameList();
                break;
            case PROFILE:
                Profile(user, currentUserIndex);
                break;
            case LOG_OUT:
                break;
            default:
                puts("please enter it correctly.");
                getch();
                break;
            }
            if (select == LOG_OUT)
                break;
        }
    }
}

