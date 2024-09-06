#include "card.h"
#include "function.h"

#define MAX_ID_LEN 10
#define MAX_PW_LEN 4
#define DEFAULT_USER_NUM 10
typedef struct main2
{
    char userID[MAX_ID_LEN];
    char userPW[MAX_PW_LEN];
}ACCOUNT_INFO;


int LoginUser(ACCOUNT_INFO *user, int user_num)
{
    char id[MAX_ID_LEN];
    char password[MAX_PW_LEN];
    ClearInputBuffer();
    printf("ID: \n");
    printf("PW: ");

    printf("\033[A"); // 커서를 위로 이동
    fgets(id, MAX_ID_LEN, stdin);
    RemoveNewline(id);

    printf("PW: ");
    fgets(password, MAX_PW_LEN, stdin);
    RemoveNewline(password);
    for(int idx=0 ; idx < user_num ; idx++)
    {
        if(strcmp(id,user[idx].userID) == 0 && strcmp(password,user[idx].userPW) == 0)    // 같을 때
            return 1;
    }
    return 0;
}
void ClearInputBuffer(void)
{
    while(getcher()!='\n');
}
void RemoveNewline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}

int main(void)
{
    srand(time(NULL));
    ACCOUNT_INFO *user=malloc(DEFAULT_USER_NUM * sizeof(ACCOUNT_INFO));
    int user_num=0;
    while (1)
    {
        int select, login_success = 0;
        ShowLoginMenu();
        scanf("%d", &select);

        switch (select)
        {
        case LOGIN:
            while(LoginUser(user, user_num) == 0)
                puts("--- Login failed ---");
            puts("--- Login Successful ---");
            break;

        case SIGN_UP:
        default:
        }
        if (login_success == 1)
            break;
    }
}