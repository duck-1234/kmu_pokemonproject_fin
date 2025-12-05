#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "title.h"
#include "nickname.h"
#include "starter.h"
#include "map.h"
#include "pokemon.h"
#include "trainer.h"
#include "battle.h"

using namespace std;
int main() {
    srand((unsigned)time(NULL));

    string y = title();
    if (y != "y" && y != "Y") {
        cout << "게임을 종료합니다." << endl;
        return 0;
    }

    cout << "게임을 시작합니다!" << endl;

    string name = nickname();
    cout << "자, " << name << "! 포켓몬 세계로 출발!" << endl;

    string myPokemonName = starter();
    Pokemon myPoke = createPokemon(myPokemonName);

#ifdef _WIN32
    system("pause");
    system("cls");
#else
    cout << "계속하려면 엔터를 누르세요...";
    cin.ignore();
    cin.get();
#endif

    while (true) {
        int townChoice;
        cout << "\n도시를 선택하세요.\n1. 꽃향기마을\n2. 잔모래마을\n3. 무쇠시티\n4. 운하시티\n5. 게임종료\n> ";
        cin >> townChoice;

        if (townChoice == 5) {
            cout << "게임을 종료합니다." << endl;
            break;
        }

        Trainer enemyTrainer = selectTrainer(townChoice);

        cout << "\n트레이너 " << enemyTrainer.name << "이(가) " << enemyTrainer.pokemon.name << "을(를) 내보냈다!" << endl;

#ifdef _WIN32
        system("pause");
#else
        cout << "계속하려면 엔터를 누르세요...";
        cin.ignore();
        cin.get();
#endif

        battle(myPoke, enemyTrainer.pokemon);

        if (myPoke.hp <= 0) {
            cout << myPoke.name << "이 쓰러졌습니다. 게임 종료." << endl;
            break;
        }
        else {
            cout << myPoke.name << "의 남은 HP: " << myPoke.hp << endl;
            myPoke.hp = myPoke.maxHp;
        }
    }

    return 0;
}
