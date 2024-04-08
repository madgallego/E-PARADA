#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep() function

#define MAX 100

typedef struct { //struct of Admin
    char user[MAX];
    char passkey[MAX];

} Admin;

void clearTerminal() {
    system("clear || cls");
}

void space_up(int lines) {
    for (int i = 0; i < lines; i++)
        printf("\n");
}

void space_left(int spaces) {
    for (int i = 0; i < spaces; i++)
        printf(" ");
}

void loading(int seconds) {
    printf("Loading");
    for (int i = 0; i < 3; i++) {
        printf(". ");
        fflush(stdout);
        sleep(seconds); // Sleep for specified number of seconds
    }
    printf("\n");
}

void SignIn() {
    Admin admin[5] = {{"lex", "bbmharc"}, {"lester", "bblester"}, {"yno", "bbyno"}, {"joy", "bbxar"}, {"cs1b", "satuits"}};
    Admin enter;

    while (1) {

        clearTerminal();
        space_up(5);
        space_left(20);
        printf("-------------------------------\n");
        space_left(20);
        printf("        ADMIN LOGIN\n");
        space_left(20);
        printf("-------------------------------\n");
        space_up(2);
        space_left(25);
        printf("User: ");
        scanf("%s", enter.user);
        space_left(25);
        printf("Password: ");
        scanf("%s", enter.passkey);
        space_up(2);
        space_left(20);
        printf("-------------------------------\n");

        // Check if the input_passkey matches any of the predefined passkeys
        int i;
        int flag = 0;
        for (i = 0; i < 5; i++) {
            if ((strcmp(admin[i].user, enter.user) == 0) && (strcmp(admin[i].passkey, enter.passkey) == 0)) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            space_up(2);
            space_left(20);
            printf("Log in successful\n"); //successful
            space_up(2);
            space_left(20);
            loading(1);
            clearTerminal();
            break;
        } else {
            space_left(20);
            printf("Invalid passkey. Try again.\n"); //err
            space_up(2);
            space_left(20);
            loading(1);
        }
    }
}

int main() {
    SignIn();
    return 0;
}