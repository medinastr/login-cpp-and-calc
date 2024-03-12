#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

typedef struct login_{
    char email[40];
    char pass[15];
    struct login_ *next;
}Login;

bool checkPassword(string password) {
    bool characters = false;
    bool numbers = false;
    int size = 0;

    for (char c : password) {
        if (isalpha(c)) {
            characters = true;
        } else if (isdigit(c)) {
            numbers = true;
        }
        size++;
    }
    if(size < 8) {
        return false;
    }

    return characters && numbers;
}

void newLogin(Login login) {
    printf("Your email: ");
    scanf(" %s", login.email);
    bool check_password = false;
    while(check_password == false) {
        printf("\n(The password need 8 characters, number and letters)\n");
        printf("Password: ");
        scanf(" %s", login.pass);
        check_password = checkPassword(login.pass);
        if(check_password == false) {
            printf("\nInvalid password, enter again.\n\n");
        }
    }
}

bool loginExists(Login login) {
    string check_email;
    string check_password;
    printf("Email: ");
    scanf(" %s", check_email);
    printf("Password: ");
    scanf(" %s", check_password);
    
}

Login *readFile(fstream file) {
    Login *begin = nullptr;
    string email, password;
    file >> email;
    while(email != "END") {
        begin->email = email;
        file >> password;
        begin->pass = password;
    }
}

int main() {
    fstream file("login.ods");
    if(!file.is_open()) {
        printf("The file of login doesn't exist.\n");
    }


    return 0;
}