//
// Created by dragonfire on 20.07.19.
//

#include <iostream>
#include <botan/argon2.h>
#include <botan/system_rng.h>

#include "../Header/User_Interface.h"

bool User_Interface::login() {
    char password[250];
    std::cout << "Hello please give me your password: ";
    std::cin.getline(reinterpret_cast<char *>(password), 250, '\n');


    if (Botan::argon2_check_pwhash(reinterpret_cast<const char *>(password), sizeof(password), passwort)) {
        std::cout << "Herzlichen Glückwunsch Login erfolgreich" << std::endl;
    } else {
        std::cout << "Falsches Passwort eingegeben" << std::endl;
    }


}

void User_Interface::newPassword() {
    Botan::System_RNG rng2;

    std::cout << "Bitte neues Passwort eingeben: ";
    std::cout.flush();
    std::cin.getline(passwort, 250, '\n');


    std::string t = Botan::argon2_generate_pwhash(passwort, sizeof(passwort), rng2, 1, 4000, 1);


}
