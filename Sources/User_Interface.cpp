//
// Created by dragonfire on 20.07.19.
//



#include "../Header/User_Interface.h"


bool User_Interface::login() {
    char password[250] = {""};
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
    std::cin.clear();
    std::cin.ignore();
    passwort = Botan::argon2_generate_pwhash(t, i, rng2, 1, 4000, 1);


}


void User_Interface::verschluesseln(std::string &&password) {
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
    std::cout << "Schlüsellänge von: "
              <<
              cipher->minimum_keylength() << "-" <<
              cipher->maximum_keylength() << std::endl;
    verschluesselt.resize(klartext.size());
    cipher->encrypt_n(klartext.data(), verschluesselt.data(),
                      calculateBlockSize(cipher->block_size(), klartext.size()));
    if (verschluesseltOut.is_open()) {
        for (auto buchstabe : verschluesselt) {
            verschluesseltOut << buchstabe;
        }
    }
    klartextIn.close();
    verschluesseltOut.close();
}


void User_Interface::entschluesseln(std::string &&password) {
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
                      calculateBlockSize(cipher->block_size(), verschluesselt.size()));
    if (klartextOut.is_open()) {
        for (auto buchstabe : klartext) {
            klartextOut << buchstabe;
            std::cout << buchstabe;
        }
    }
    cipher.release();
}

size_t User_Interface::calculateBlockSize(size_t blocksize, size_t dataLength) {
    size_t ergebnis = dataLength / blocksize;
    if (dataLength % blocksize > 0) {
        ++ergebnis;
    }
    return ergebnis;
}


std::vector<uint8_t> User_Interface::getHash(std::string password) {

    password = makeHash(password);
    std::vector<uint8_t> ergebnis;
    for (size_t i = 0; i < 32; ++i) {
        ergebnis.push_back(password[i]);
    }
    return ergebnis;
}


std::string User_Interface::makeHash(std::string password) {
    std::unique_ptr<Botan::HashFunction> hash1(Botan::HashFunction::create("SHA-256"));
    hash1->update(password);
    return Botan::hex_encode(hash1->final());
}