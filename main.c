#include "card.h"
#include "function.h"

int LoginUser(ACCOUNT_INFO *user, int user_num)
{
    char id[MAX_ID_LEN];
    char password[MAX_PW_LEN];
    ClearInputBuffer();
    ClearScreen();
    puts("[ Login ]");

    printf("ID: \n");
    printf("PW: ");

    printf("\033[A"); // 커서를 위로 이동
    fgets(id, MAX_ID_LEN, stdin);
    RemoveNewline(id);

    printf("PW: ");
    fgets(password, MAX_PW_LEN, stdin);
    RemoveNewline(password);
    for (int idx = 0; idx < user_num; idx++)
    {
        if (strcmp(id, user[idx].userID) == 0 && strcmp(password, user[idx].userPW) == 0) // 같을 때
            return 1;
    }
    return 0;
}
void ClearInputBuffer(void)
{
    while (getchar() != '\n');
}
void RemoveNewline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}
int SignUpUser(ACCOUNT_INFO *user, int user_num)
{
    char confirm_password[MAX_PW_LEN];
    ClearInputBuffer();
    ClearScreen();
    puts("[ Sign up ]");
    printf("ID: \n");
    printf("PW: ");

    printf("\033[A");
    fgets(user[user_num].userID, MAX_ID_LEN, stdin);
    RemoveNewline(user[user_num].userID);

    printf("PW: ");
    fgets(user[user_num].userPW, MAX_PW_LEN, stdin);
    RemoveNewline(user[user_num].userPW);
ClearInputBuffer();
    printf("Confirm PW: ");
    fgets(confirm_password, MAX_PW_LEN, stdin);
    RemoveNewline(confirm_password);

    if(strcmp(user[user_num].userPW, confirm_password) == 0)
        return 1;

    return 0;
}
int main(void)
{
    srand(time(NULL));
    ACCOUNT_INFO *user = malloc(DEFAULT_USER_NUM * sizeof(ACCOUNT_INFO));
    int user_num = 0;
    while (1)
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
        default:
        }

        if (login_success == 1)
            break;
    }
}
