//
// Created by dragonfire on 20.07.19.
//

#ifndef BOTANPROJEKT_USER_INTERFACE_H
#define BOTANPROJEKT_USER_INTERFACE_H

#include <iostream>
#include <botan/argon2.h>
#include <botan/system_rng.h>
#include <botan/cryptobox.h>
#include <fstream>
#include <botan/block_cipher.h>
#include <botan/hex.h>


class User_Interface {
public:
    bool login();

    void newPassword();

    static void test();

    void verschluesseln();

    void entschluesseln();


    static void blockEntschluesselung();

private:
    std::string passwort;
    char test1[250];
    char test2[250];

    static size_t berechne(size_t blocksize, size_t dataLength);

    static std::vector<uint8_t> getKey();
};


#endif //BOTANPROJEKT_USER_INTERFACE_H
