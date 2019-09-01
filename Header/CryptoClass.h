//
// Created by dragonfire on 20.07.19.
//

#ifndef BOTANPROJEKT_CRYPTOCLASS_H
#define BOTANPROJEKT_CRYPTOCLASS_H

#include <iostream>
#include <botan/argon2.h>
#include <botan/system_rng.h>
#include <botan/cryptobox.h>
#include <fstream>
#include <botan/block_cipher.h>
#include <botan/hex.h>
#include <botan/hash.h>
#include <syslog.h>
/**
 * @brief Manages the login and the encryption and decryption of data
 * @author SySx-Dragonfire
 * @date 01.09.2019
 * @version 1.0
 *
 */
class CryptoClass {
public:
    CryptoClass(){
        openlog("CryptoClass", LOG_NDELAY | LOG_CONS, LOG_SYSLOG);
    }

    ~CryptoClass(){
        closelog();
    }

    /**
     * @brief Uses the argon2 password hash algorithm to test if the password is valid
     * @return TRUE if the password is valid
     */
    bool login();

    /**
     * @brief Writes a new password in the loginPassword parameter of the class
     */
    void newPassword();


    //File encryption and decryption with AES-256
    /**
     * @brief Encrypts file
     * @param [in] password the string that will be used as key for encryption
     */
    void encrypt(std::string &&password);

    /**
     * @brief Decrypts File @see entschluesselt.txt
     * @param[in] password the String that will be used for decryption
     */
    void decrypt(std::string &&password);


private:
    std::string loginPassword; ///< password for Login with argon2

    //Helper functions/////////////////////////////////////
    /**
     * @brief Calculates in how many blocks the data must be splitted for AES-256
     * @param [in] blocksize is the blocksize  of the algorithm
     * @param [in] dataLength the length of the data
     * @return [out]  Block number that is needed
     */
    static size_t calculatesBlocks(size_t blocksize, size_t dataLength);

    /**
     * @brief Gets the Hash in the right format that is needed for AES-256
     * @param [in] password gets the password for encryption/decryption
     * @return The passhash in a vector
     */
    static std::vector<uint8_t> getHash(std::string password);

    /**
     * @brief gets password and turns it in a hash
     * @param [in] password gets the password
     * @return The produced SHA-256 hash
     */
    static std::string makeHash(std::string password); //Hasht das Passwort mit SHA-256
};


#endif //BOTANPROJEKT_CRYPTOCLASS_H
