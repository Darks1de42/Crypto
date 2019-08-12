#include <iostream>
#include "Header/User_Interface.h"
#include <thread>

int i = 0;

void test() {
    std::cout << "Test: " << ++i << std::endl;
}

int main() {
    User_Interface ui;
    ui.newPassword();
    ui.login();
    ui.verschluesseln();
    ui.entschluesseln();


    return 0;
}