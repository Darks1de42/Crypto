//
// Created by dragonfire on 20.07.19.
//

#ifndef BOTANPROJEKT_USER_INTERFACE_H
#define BOTANPROJEKT_USER_INTERFACE_H


class User_Interface {
public:
    bool login();

    void newPassword();

private:
    char passwort[250] = {
            "$argon2id$v=19$m=4000,t=1,p=1$Ymce4AgWnMzMRdDixrpzZQ$d6aKoWoeIGBt+zHGrhS8Xxff2wwlXCV+T3RXCILv/7o"};

};


#endif //BOTANPROJEKT_USER_INTERFACE_H
