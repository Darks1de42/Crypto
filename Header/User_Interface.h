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
#include <botan/hash.h>


class User_Interface {
public:

    ////Login with password hash algorithm argon2
    bool login();
    void newPassword();


    //File encryption and decryption with AES-256
    void verschluesseln(std::string &&password);

    void entschluesseln(std::string &&password);


private:
    std::string passwort;

    //Helper functions/////////////////////////////////////
    static size_t calculateBlockSize(size_t blocksize, size_t dataLength); //defines the Block size for AES-256
    static std::vector<uint8_t>
    getHash(std::string password);  //Liefert einen Vector für AES-256 mit dem gehasten Passwort zurück
    static std::string makeHash(std::string password); //Hasht das Passwort mit SHA-256
};


#endif //BOTANPROJEKT_USER_INTERFACE_H
