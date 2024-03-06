#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

typedef struct login_{
    char email[40];
    char pass[15];
    //struct login_ *next;
}Login;

bool checkPassword(string str) {
    bool characters = false;
    bool numbers = false;

    for (char c : str) {
        if (isalpha(c)) {
            characters = true;
        } else if (isdigit(c)) {
            numbers = true;
        }
    }

    return characters && numbers;
}

void newLogin(Login login) {
    printf("Your email: ");
    scanf(" %s", login.email);
    bool check_password = false;
    while(check_password == false) {
        printf("Password: ");
        scanf(" %s", login.pass);
        check_password = checkPassword(login.pass);
        if(check_password == false) {
            printf("\nInvalid password, enter again.\n\n");
        }
    }
}

int main() {
    //Login *begin = NULL;
    fstream file("login.ods");
    if(!file.is_open()) {
        printf("The file of login doesn't exist.\n");
    }
    Login login;
    newLogin(login);


    return 0;
}