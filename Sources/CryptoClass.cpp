//
// Created by dragonfire on 20.07.19.
//



#include "../Header/CryptoClass.h"


bool CryptoClass::login(std::string password) {


    if (Botan::argon2_check_pwhash(password.c_str(), password.length(), loginPassword)) {
        return true;
    } else {
        static size_t wrongTries = 0;
        syslog(LOG_ALERT, "False password tries=%zu", ++wrongTries);
        return false;


    }


}

void CryptoClass::newPassword(std::string password) {
    Botan::System_RNG rng2; //Zufallszahlengenerator




    loginPassword = Botan::argon2_generate_pwhash(password.c_str(), password.length(), rng2, 1, 4000, 1);
    syslog(LOG_NOTICE, "User set new password");


}


void CryptoClass::encrypt(std::string &&password) {

    std::fstream klartextIn, verschluesseltOut;
    std::vector<uint8_t> klartext, verschluesselt;
    klartextIn.open("../datei.txt", std::fstream::in);
    verschluesseltOut.open("../verschluesselt.txt", std::fstream::out);
    if (klartextIn.is_open()) {
        while (klartextIn.peek() != EOF) {
            klartext.push_back(klartextIn.get());
        }
    }

    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-256"));
    cipher->set_key(getHash(password));

    verschluesselt.resize(klartext.size());
    cipher->encrypt_n(klartext.data(), verschluesselt.data(),
                      calculatesBlocks(cipher->block_size(), klartext.size()));
    if (verschluesseltOut.is_open()) {
        for (auto buchstabe : verschluesselt) {
            verschluesseltOut << buchstabe;
        }
    }
    klartextIn.close();
    verschluesseltOut.close();
}


void CryptoClass::decrypt(std::string &&password) {
    std::fstream klartextOut, verschluesseltIn;
    std::vector<uint8_t> klartext, verschluesselt;
    klartextOut.open("../entschluesselt.txt", std::fstream::out);
    verschluesseltIn.open("../verschluesselt.txt", std::fstream::in);
    if (verschluesseltIn.is_open()) {
        while (verschluesseltIn.peek() != EOF) {
            verschluesselt.push_back(verschluesseltIn.get());
        }
    }

    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-256"));
    cipher->set_key(getHash(password));
    klartext.resize(verschluesselt.size());
    cipher->decrypt_n(verschluesselt.data(), klartext.data(),
                      calculatesBlocks(cipher->block_size(), verschluesselt.size()));
    if (klartextOut.is_open()) {
        for (auto buchstabe : klartext) {
            klartextOut << buchstabe;
        }
    }
    cipher.release();
}

size_t CryptoClass::calculatesBlocks(size_t blocksize, size_t dataLength) {
    size_t ergebnis = dataLength / blocksize;
    if (dataLength % blocksize > 0) {
        ++ergebnis;
    }
    return ergebnis;
}


std::vector<uint8_t> CryptoClass::getHash(std::string password) {

    password = makeHash(password);
    std::vector<uint8_t> ergebnis;
    for (size_t i = 0; i < 32; ++i) {
        ergebnis.push_back(password[i]);
    }
    return ergebnis;
}


std::string CryptoClass::makeHash(std::string password) {
    std::unique_ptr<Botan::HashFunction> hash1(Botan::HashFunction::create("SHA-256"));
    hash1->update(password);
    return Botan::hex_encode(hash1->final());
}