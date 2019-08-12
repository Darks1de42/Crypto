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


void User_Interface::verschluesseln() {
    std::fstream klartextIn, verschluesseltOut;
    std::vector<uint8_t> klartext, verschluesselt;
    klartextIn.open("../datei.txt", std::fstream::in);
    verschluesseltOut.open("../verschluesselt.txt", std::fstream::out);
    if (klartextIn.is_open()) {
        while (klartextIn.peek() != EOF) {
            klartext.push_back(klartextIn.get());
        }
    }

    std::vector<uint8_t> key = getKey();
    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-256"));
    cipher->set_key(key);
    verschluesselt.resize(klartext.size());
    cipher->encrypt_n(klartext.data(), verschluesselt.data(), berechne(cipher->block_size(), klartext.size()));
    if (verschluesseltOut.is_open()) {
        for (auto buchstabe : verschluesselt) {
            verschluesseltOut << buchstabe;
        }
    }
    klartextIn.close();
    verschluesseltOut.close();
}

void User_Interface::blockEntschluesselung() {
    std::fstream klartextOut, verschluesseltIn;
    std::vector<uint8_t> key;

    klartextOut.open("../entschluesselt.txt", std::fstream::out);
    verschluesseltIn.open("../verschluesselt.txt", std::fstream::in);
    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-256"));
    cipher->set_key(key);
    std::vector<uint8_t> klartext;
    std::vector<uint8_t> verschluesselt;
    std::cout << "{" << key.data() << "}" << std::endl;


    if (verschluesseltIn.is_open() && klartextOut.is_open()) {

        while (true) {
            for (size_t i = 0; i < cipher->block_size(); ++i) {
                if (verschluesseltIn.peek() == EOF) { break; }

                verschluesselt.push_back(verschluesseltIn.get());

            }
            klartext.resize(verschluesselt.size());
            cipher->decrypt(verschluesselt.data(), klartext.data());
            klartextOut << klartext.data();
            std::flush(klartextOut);
            if (verschluesseltIn.peek() == EOF) { break; }
            klartext.clear();
            verschluesselt.clear();
        }
        klartextOut.close();
        verschluesseltIn.close();
    }

}


void User_Interface::entschluesseln() {
    std::fstream klartextOut, verschluesseltIn;
    std::vector<uint8_t> klartext, verschluesselt;
    klartextOut.open("../entschluesselt.txt", std::fstream::out);
    verschluesseltIn.open("../verschluesselt.txt", std::fstream::in);
    if (verschluesseltIn.is_open()) {
        while (verschluesseltIn.peek() != EOF) {
            verschluesselt.push_back(verschluesseltIn.get());
        }
    }

    std::vector<uint8_t> key = Botan::hex_decode("102030407655060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F");
    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-256"));
    cipher->set_key(key);
    klartext.resize(verschluesselt.size());
    cipher->decrypt_n(verschluesselt.data(), klartext.data(), berechne(cipher->block_size(), verschluesselt.size()));
    if (klartextOut.is_open()) {
        for (auto buchstabe : klartext) {
            klartextOut << buchstabe;
            std::cout << buchstabe;
        }
    }
    cipher.release();
}

size_t User_Interface::berechne(size_t blocksize, size_t dataLength) {
    size_t ergebnis = dataLength / blocksize;
    if (dataLength % blocksize > 0) {
        ++ergebnis;
    }
    return ergebnis;
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

std::vector<uint8_t> User_Interface::getKey() {

    return std::vector<uint8_t>() = Botan::hex_decode(
            "102030407655060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F");
}

