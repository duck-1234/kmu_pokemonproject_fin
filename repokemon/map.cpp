#include "map.h"
#include <iostream>
using namespace std;

string map() {
    string direction;
    cout << "이제 여행을 떠날 시간입니다! 어느 방향으로 가시겠습니까? (동, 서, 남, 북): ";
    cin >> direction;

    if (direction == "북") {
        cout << "북쪽으로 이동합니다." << endl;
        cout << "꽃향기 마을에 도착했다!" << endl;
    }
    else if (direction == "남") {
        cout << "남쪽으로 이동합니다." << endl;
        cout << "잔모래마을에 도착했다!" << endl;
    }
    else if (direction == "동") {
        cout << "동쪽으로 이동합니다." << endl;
        cout << "무쇠시티에 도착했다!" << endl;
    }
    else if (direction == "서") {
        cout << "서쪽으로 이동합니다." << endl;
        cout << "운하시티에 도착했다!" << endl;
    }
    else {
        cout << "잘못된 방향입니다. 다시 시도하세요." << endl;
        return map();
    }
    return direction;
}