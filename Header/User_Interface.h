//
// Created by dragonfire on 20.07.19.
//

#ifndef BOTANPROJEKT_USER_INTERFACE_H
#define BOTANPROJEKT_USER_INTERFACE_H


class User_Interface {
public:
    bool login();

    void newPassword();

    void test();

private:
    std::string passwort;
    char test1[250];
    char test2[250];
};


#endif //BOTANPROJEKT_USER_INTERFACE_H
