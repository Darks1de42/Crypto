#include <iostream>
#include "Header/User_Interface.h"
#include <thread>


int main() {


    User_Interface ui;
    ui.newPassword();
    ui.login();
    ui.verschluesseln("Geheimes Passwort");
    ui.entschluesseln("Geheimes Passwort");


    return 0;
}