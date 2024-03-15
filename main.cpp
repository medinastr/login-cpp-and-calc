#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct login_{
    string email;
    string pass;
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

Login* newLogin(Login *login) {
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
    return new_login;
}

bool loginExists(Login *begin) {
    string check_email;
    string check_password;
    cout << "Email: ";
    cin >> check_email;
    cout << "Password: ";
    cin >> check_password;
    
    while(begin != nullptr) {
        if(begin->email == check_email && begin->pass == check_password) {
            return true;
        }
        begin = begin->next;
    }
    return false;
}


Login *readFile(fstream &file) {
    Login *begin = nullptr; // Ponteiro para o início da lista
    Login *end = nullptr; // Ponteiro para o final da lista

    string email, password;
    while (file >> email >> password) { // Loop até que não haja mais entrada
        Login *new_login = new Login(); // Criar um novo nó para cada entrada
        new_login->email = email; // Atribuir o email
        new_login->pass = password; // Atribuir a senha
        new_login->next = nullptr; // O próximo nó é inicializado como nulo

        if (begin == nullptr) { // Se a lista estiver vazia
            begin = new_login; // Define o novo nó como o início
            end = new_login; // E também como o fim
        } else {
            end->next = new_login; // Liga o último nó ao novo nó
            end = new_login; // Atualiza o ponteiro de fim para o novo nó
        }
    }

    return begin; // Retorna o início da lista
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
    showLogins(begin);


    return 0;
}