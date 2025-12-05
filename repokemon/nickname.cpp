#include "nickname.h"
#include <iostream>
#include <string>
using namespace std;

string nickname() {
    string name;
    cout << "트레이너의 닉네임을 쓰시오: ";
    cin >> name;
    cout << "포켓몬 세상에 온 것을 환영한다, " << name << "!" << endl;
    return name;

}
