#include <iostream>
#include "Header/CryptoClass.h"
#include <thread>


int main() {


    CryptoClass ui;
    ui.newPassword("Was geht?");
    ui.login("Was geht");
    ui.encrypt("Geheimes Passwort");
    ui.decrypt("Geheimes Passwort");


    return 0;
}