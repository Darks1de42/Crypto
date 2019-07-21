//
// Created by dragonfire on 20.07.19.
//

#include <iostream>
#include <botan/argon2.h>
#include <botan/system_rng.h>

#include "../Header/User_Interface.h"

bool User_Interface::login() {
    char password[250];
    size_t i = 0;
    std::cout << "Hello please give me your password: ";
    std::cout.flush();


    for (; i < 250 && std::cin.peek() != '\n'; ++i) {
        password[i] = std::cin.get();
    }

    if (Botan::argon2_check_pwhash(password, i, passwort)) {
        std::cout << "Herzlichen Glückwunsch Login erfolgreich" << std::endl;
    } else {
        std::cout << "Falsches Passwort eingegeben" << std::endl;
    }


}

void User_Interface::newPassword() {
    Botan::System_RNG rng2; //Zufallszahlengenerator

    std::cout << "Bitte neues Passwort eingeben: ";
    std::cout.flush();
    char t[250];
    size_t i = 0;

    for (; i < 250 && std::cin.peek() != '\n'; ++i) {
        t[i] = std::cin.get();
    }
    passwort = Botan::argon2_generate_pwhash(t, i, rng2, 1, 4000, 1);


}

void User_Interface::test() {
    Botan::System_RNG rng2;
    std::string passwort = "Geheim";
    std::string t = Botan::argon2_generate_pwhash(passwort.data(), passwort.size(), rng2, 1, 4000, 1);

    if (Botan::argon2_check_pwhash(passwort.data(), passwort.size(), t)) {
        std::cout << "Herzlichen Glückwunsch Login erfolgreich" << std::endl;
    } else {
        std::cout << "Falsches Passwort eingegeben" << std::endl;
    }

}
