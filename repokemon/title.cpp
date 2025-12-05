#include "title.h"
#include <iostream>
using namespace std;

string title() {
    string y;
    cout << "               __                                  ___.              .___" << endl;
    cout << "______   ____ |  | __ ____   _____   ____   ____   \\_ |__   ______ __| _/" << endl;
    cout << "\\____ \\ /  _ \\|  |/ // __ \\ /     \\ /  _ \\ /    \\   | __ \\ /  ___// __ | " << endl;
    cout << "|  |_> >  <_> )    <\\  ___/|  Y Y  (  <_> )   |  \\  | \\_\\ \\\\___ \\/ /_/ | " << endl;
    cout << "|   __/ \\____/|__|_ \\\\___  >__|_|  /\\____/|___|  /  |___  /____  >____ | " << endl;
    cout << "|__|               \\/    \\/      \\/            \\/       \\/     \\/     \\/ " << endl;
    cout << endl;
    cout << "게임을 시작하려면 y 를 입력하세요: ";
    cin >> y;
    return y;
}
