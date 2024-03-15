#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;


typedef struct login_{  // login NODE
    string email;
    string pass;
    struct login_ *next;
}Login;

// check if password that will be created doesn't have any problems
// The password needs 8 characters, numbers, and letters
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

// save the new login in linked list and in file
Login *newLogin(Login *begin) {

    Login *new_login = new Login();
    cout << "Your email: ";
    cin >> new_login->email;
    bool check_password = false;

    while(!check_password) {
        cout << "\n(The password needs 8 characters, numbers, and letters)\n";
        cout << "Password: ";
        cin >> new_login->pass;
        check_password = checkPassword(new_login->pass);
        if(!check_password) {
            cout << "\nInvalid password, enter again.\n\n";
        }
    }

    if (begin == nullptr) {
        begin = new_login;
    } else {
        Login *temp = begin;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_login;
    }

    // I think the error for save the new login is here
    ofstream file("login", ios::app);
    file << new_login->email << " " << new_login->pass << endl;
    file.close();

    return begin;
}

// it will check email and password for user who tries login
bool loginExists(Login *begin) {
    string check_email;
    string check_password;
    cout << "Email: ";
    cin >> check_email;
    cout << "Password: ";
    cin >> check_password;
    Login *aux = begin;
    
    while(aux != nullptr) {
        if(aux->email == check_email && aux->pass == check_password) {
            return true;
        }
        aux = aux->next;
    }
    return false;
}

// creating a linked list with login
Login *readFile(fstream &file) {
    Login *begin = nullptr;
    Login *end = nullptr;

    string email, password;
    while (file >> email >> password) { // loop until file NULL
        Login *new_login = new Login(); // creating nem node
        new_login->email = email;
        new_login->pass = password;
        new_login->next = nullptr;

        if (begin == nullptr) {  // if is an empty list
            begin = new_login; // new node will be the beginnig of the linked list
            end = new_login;
        } else {
            end->next = new_login;
            end = new_login;
        }
    }

    return begin;
}

void showLogins(Login *begin) {
    while(begin != NULL) {
        cout << begin->email << " " << begin->pass << endl;
        begin = begin->next;
    }
    printf("------------------------------------------\n");
}

int main() {
    fstream file("login");
    if(!file.is_open()) {
        printf("The file of login doesn't exist.\n");
    }

    Login *begin = readFile(file);
    // showLogins(begin);
    // if(loginExists(begin) == true) {
    //     cout << "OK" << endl;
    // }

    begin = newLogin(begin);
    showLogins(begin);


    return 0;
}