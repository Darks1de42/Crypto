#include <iostream>
#include "Header/CryptoClass.h"
#include <thread>


int main() {


    CryptoClass ui;
    ui.newPassword();
    ui.login();
    ui.encrypt("Geheimes Passwort");
    ui.decrypt("Geheimes Passwort");


    return 0;
}