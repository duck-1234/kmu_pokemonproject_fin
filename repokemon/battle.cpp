// battle.cpp
#include "battle.h"
#include "pokemon.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

// 타입 열거형 (간단한 주요 타입만 포함)
enum class Type {
    NONE,
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    ICE,
    ROCK,
    GROUND,
    FIGHTING,
    BUG,
    POISON,
    PSYCHIC,
    STEEL,
    DRAGON,
    GHOST,
    DARK,
    FAIRY,
    FLYING
};

struct Move {
    std::string name;
    int power;
    Type type;
};

// 현재 사용되는 포켓몬 이름 기반 타입 매핑
Type getPokemonType(const std::string& pname) {
    if (pname == "이상해꽃" || pname == "이상해씨") return Type::GRASS;
    if (pname == "리자몽") return Type::FIRE;
    if (pname == "거북왕") return Type::WATER;
    if (pname == "윈디") return Type::FIRE;
    if (pname == "헬가") return Type::FIRE;
    if (pname == "갸라도스") return Type::WATER;
    if (pname == "스라크") return Type::BUG;
    if (pname == "별가사리") return Type::WATER;
    if (pname == "리오르") return Type::FIGHTING;
    if (pname == "아쿠스타") return Type::WATER;
    if (pname == "아리아도스") return Type::BUG;
    if (pname == "코코파스") return Type::ROCK;
    if (pname == "루카리오") return Type::FIGHTING;
    if (pname == "기기기어르") return Type::STEEL;
    if (pname == "대왕끼리동") return Type::GROUND;
    if (pname == "플로젤") return Type::WATER;
    if (pname == "렌트라") return Type::ELECTRIC;
    if (pname == "킹드라") return Type::WATER;
    if (pname == "밀로틱") return Type::WATER;
    if (pname == "메타그로스") return Type::STEEL;
    // 기본값
    return Type::NONE;
}

// 타입 상성 (움직임 타입 vs 방어 타입) -> multiplier
double typeEffectiveness(Type moveType, Type targetType) {
    if (moveType == Type::NONE || targetType == Type::NONE) return 1.0;

    // 매우 기본적인 상성 매핑 (필요하면 확장)
    if (moveType == Type::FIRE) {
        if (targetType == Type::GRASS || targetType == Type::ICE) return 2.0;
        if (targetType == Type::WATER || targetType == Type::ROCK) return 0.5;
    }
    if (moveType == Type::WATER) {
        if (targetType == Type::FIRE || targetType == Type::ROCK) return 2.0;
        if (targetType == Type::GRASS || targetType == Type::WATER) return 0.5;
    }
    if (moveType == Type::GRASS) {
        if (targetType == Type::WATER || targetType == Type::GROUND) return 2.0;
        if (targetType == Type::FIRE || targetType == Type::POISON) return 0.5;
    }
    if (moveType == Type::ELECTRIC) {
        if (targetType == Type::WATER) return 2.0;
        if (targetType == Type::GROUND) return 0.0; // 면역
    }
    if (moveType == Type::ICE) {
        if (targetType == Type::GRASS || targetType == Type::DRAGON) return 2.0;
    }
    if (moveType == Type::FIGHTING) {
        if (targetType == Type::DARK || targetType == Type::ROCK) return 2.0;
        if (targetType == Type::FLYING) return 0.5; // 만약 존재하면
    }
    if (moveType == Type::ROCK) {
        if (targetType == Type::FIRE || targetType == Type::BUG) return 2.0;
    }
    if (moveType == Type::BUG) {
        if (targetType == Type::GRASS || targetType == Type::PSYCHIC) return 2.0;
    }
    if (moveType == Type::PSYCHIC) {
        if (targetType == Type::FIGHTING || targetType == Type::POISON) return 2.0;
    }
    if (moveType == Type::STEEL) {
        if (targetType == Type::ICE || targetType == Type::ROCK) return 2.0;
    }
    if (moveType == Type::DRAGON) {
        if (targetType == Type::DRAGON) return 2.0;
    }
    // 기본: 1배
    return 1.0;
}

// 기술 이름 → Move (power, type) 맵
Move getMove(const std::string& name) {
    // 예시: 주요 기술 타입을 대체로 넣음 (필요하면 확장/수정)
    if (name == "몸통박치기")     return { name, 30, Type::NORMAL };
    if (name == "씨뿌리기")       return { name, 20, Type::GRASS };
    if (name == "덩굴채찍")       return { name, 45, Type::GRASS };
    if (name == "회오리")         return { name, 40, Type::NORMAL };
    if (name == "불꽃세례")       return { name, 40, Type::FIRE };
    if (name == "할퀴기")         return { name, 35, Type::NORMAL };
    if (name == "화염방사")       return { name, 90, Type::FIRE };
    if (name == "물대포")         return { name, 40, Type::WATER };
    if (name == "거품")           return { name, 20, Type::WATER };
    if (name == "하이드로펌프")   return { name, 80, Type::WATER };
    if (name == "신속")           return { name, 60, Type::NORMAL };
    if (name == "번개엄니")       return { name, 65, Type::ELECTRIC };
    if (name == "기습")           return { name, 50, Type::DARK };
    if (name == "악의파동")       return { name, 85, Type::DARK };
    if (name == "불꽃엄니")       return { name, 75, Type::FIRE };
    if (name == "물의파동")       return { name, 80, Type::WATER };
    if (name == "물기")           return { name, 60, Type::WATER };
    if (name == "깨물어부수기")   return { name, 80, Type::DARK };
    if (name == "연속자르기")     return { name, 35, Type::NORMAL };
    if (name == "풀베기")         return { name, 55, Type::GRASS };
    if (name == "벌레먹음")       return { name, 60, Type::BUG };
    if (name == "깜짝베기")       return { name, 40, Type::DARK };
    if (name == "사이코키네시스") return { name, 90, Type::PSYCHIC };
    if (name == "카운터")         return { name, 70, Type::FIGHTING };
    if (name == "아이언해드")     return { name, 80, Type::STEEL };
    if (name == "번개")           return { name, 70, Type::ELECTRIC };
    if (name == "냉동빔")         return { name, 90, Type::ICE };
    if (name == "독침")           return { name, 40, Type::POISON };
    if (name == "독찌르기")       return { name, 70, Type::POISON };
    if (name == "돌던지기")       return { name, 50, Type::ROCK };
    if (name == "스톤에지")       return { name, 70, Type::ROCK };
    if (name == "바위깨기")       return { name, 50, Type::ROCK };
    if (name == "파동탄")         return { name, 80, Type::FIGHTING };
    if (name == "본러쉬")         return { name, 75, Type::FIGHTING };
    if (name == "점프킥")         return { name, 85, Type::FIGHTING };
    if (name == "차지빔")         return { name, 60, Type::ELECTRIC };
    if (name == "기어소서")       return { name, 80, Type::STEEL };
    if (name == "트라이어택")     return { name, 90, Type::NORMAL };
    if (name == "지진")           return { name, 80, Type::GROUND };
    if (name == "들이받기")       return { name, 85, Type::NORMAL };
    if (name == "아쿠아테일")     return { name, 90, Type::WATER };
    if (name == "파도타기")       return { name, 90, Type::WATER };
    if (name == "괴력")           return { name, 80, Type::FIGHTING };
    if (name == "스파크")         return { name, 65, Type::ELECTRIC };
    if (name == "와일드볼트")     return { name, 90, Type::ELECTRIC };
    if (name == "하이드로캐논")   return { name, 90, Type::WATER };
    if (name == "용의분노")       return { name, 85, Type::DRAGON };
    if (name == "용의파동")       return { name, 85, Type::DRAGON };
    if (name == "폭포오르기")     return { name, 80, Type::WATER };
    if (name == "열탕")           return { name, 80, Type::FIRE };
    if (name == "풀묶기")         return { name, 60, Type::GRASS };
    if (name == "불릿펀치")       return { name, 40, Type::STEEL };
    if (name == "코멧펀치")       return { name, 90, Type::FIGHTING };
    if (name == "사념의박치기")   return { name, 80, Type::PSYCHIC };

    // 기본 기술: 물리 50, 노말 타입
    return { name, 50, Type::NORMAL };
}

// 현재 시간 문자열 (HH:MM:SS)
std::string nowTimeStr() {
    std::time_t t = std::time(nullptr);
    std::tm local_tm;
#if defined(_WIN32)
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << local_tm.tm_hour << ":"
        << std::setfill('0') << std::setw(2) << local_tm.tm_min << ":"
        << std::setfill('0') << std::setw(2) << local_tm.tm_sec;
    return ss.str();
}

// 크리티컬 판정 (간단한 버전: 스피드 기반 확률, 최대 15%)
bool isCritical(const Pokemon& p) {
    int chance = std::min(15, p.speed / 10); // speed 150 -> 15% cap
    return (rand() % 100) < chance;
}

// 데미지 계산: 본가 스타일 기반 + STAB + 타입 상성 + 랜덤 + 크리티컬
int calcDamage(const Pokemon& attacker, const Pokemon& defender, const std::string& moveName) {
    Move move = getMove(moveName);

    int level = std::max(1, attacker.level);

    // (((2 * L / 5 + 2) * A * Power / D) / 50) + 2
    double A = static_cast<double>(attacker.attack);
    double D = std::max(1.0, static_cast<double>(defender.defense)); // 0 나누기 방지
    double power = static_cast<double>(move.power);

    double base = (((2.0 * level / 5.0 + 2.0) * A * power / D) / 50.0) + 2.0;

    //자속보정
    Type atkType = getPokemonType(attacker.name);
    double stab = (move.type != Type::NONE && move.type == atkType) ? 1.5 : 1.0;

    // 타입 상성
    Type defType = getPokemonType(defender.name);
    double typeMul = typeEffectiveness(move.type, defType);

    // 랜덤 요인 (0.85 ~ 1.00)
    double randFactor = (85 + (rand() % 16)) / 100.0;

    double damage = base * stab * typeMul * randFactor;

    // 크리티컬(대략 1.5배)
    if (isCritical(attacker)) {
        damage *= 1.5;
    }

    // 최소 데미지 보장
    int idamage = static_cast<int>(std::round(damage));
    if (idamage < 1) idamage = 1;
    return idamage;
}

// 전투 로그 출력 보조
void logAttack(const std::string& timeStr, const std::string& attackerName, const std::string& moveName, int dmg, double effectiveness, bool critical) {
    cout << "[" << timeStr << "] " << attackerName << "의 " << moveName;
    if (critical) cout << " (크리티컬!)";
    cout << " -> " << dmg << " 데미지";
    if (effectiveness >= 2.0) cout << " (초효과!)";
    else if (effectiveness == 0.0) cout << " (효과 없음)";
    else if (effectiveness < 1.0) cout << " (약효)";
    cout << endl;
}

// 실제 배틀 함수
void battle(Pokemon& myPoke, Pokemon& enemy) {
    // 전투 시작 시 HP를 최대치로 초기화 (원하면 변경 가능)
    myPoke.hp = myPoke.maxHp;
    enemy.hp = enemy.maxHp;

    cout << "\n=============================\n";
    cout << myPoke.name << " VS " << enemy.name << "!" << endl;
    cout << "=============================\n";

    // 전투 루프
    while (myPoke.hp > 0 && enemy.hp > 0) {
        cout << "\n[" << myPoke.name << " HP: " << myPoke.hp << " / " << enemy.name << " HP: " << enemy.hp << "]\n";

        cout << "\n사용할 기술을 선택하세요:\n";
        cout << "1. " << myPoke.skill1 << "\n2. " << myPoke.skill2 << "\n3. " << myPoke.skill3 << "\n4. " << myPoke.skill4 << "\n> ";

        int choice;
        cin >> choice;
        string myMove;
        switch (choice) {
        case 1: myMove = myPoke.skill1; break;
        case 2: myMove = myPoke.skill2; break;
        case 3: myMove = myPoke.skill3; break;
        case 4: myMove = myPoke.skill4; break;
        default: myMove = myPoke.skill1; break;
        }

        string enemyMovesRaw[4] = { enemy.skill1, enemy.skill2, enemy.skill3, enemy.skill4 };
        // 유효한 기술만 모아서 선택 (빈 문자열이나 "없음" 방지)
        string enemyMove = enemyMovesRaw[rand() % 4];
        int tries = 0;
        while ((enemyMove == "" || enemyMove == "없음") && tries < 10) {
            enemyMove = enemyMovesRaw[rand() % 4];
            tries++;
        }
        if (enemyMove == "" || enemyMove == "없음") enemyMove = enemy.skill1; // fallback

        // 선공 결정: 속도 우선 (동일하면 플레이어 우선)
        bool playerFirst = (myPoke.speed >= enemy.speed);

        // 공격자와 방어자 역할을 일반화해서 처리
        auto doAttack = [&](Pokemon& attacker, Pokemon& defender, const string& moveName) {
            std::string tstr = nowTimeStr();
            Move mv = getMove(moveName);
            double eff = typeEffectiveness(mv.type, getPokemonType(defender.name));
            bool crit = isCritical(attacker);
            int dmg = calcDamage(attacker, defender, moveName);

            // 메시지 출력
            logAttack(tstr, attacker.name, moveName, dmg, eff, crit);

            // HP 차감 (효과 0이면 데미지 0)
            if (eff == 0.0) {
                // 면역
            }
            else {
                defender.hp -= dmg;
                if (defender.hp < 0) defender.hp = 0;
            }
            cout << defender.name << "의 남은 HP: " << defender.hp << endl;
            };

        // 한 턴의 처리
        if (playerFirst) {
            doAttack(myPoke, enemy, myMove);
            if (enemy.hp > 0) {
                doAttack(enemy, myPoke, enemyMove);
            }
        }
        else {
            doAttack(enemy, myPoke, enemyMove);
            if (myPoke.hp > 0) {
                doAttack(myPoke, enemy, myMove);
            }
        }

        // 전투 종료 체크
        if (myPoke.hp <= 0 || enemy.hp <= 0) break;
    }

    cout << "\n=============================\n";
    if (myPoke.hp > 0)
        cout << myPoke.name << "의 승리!\n";
    else
        cout << enemy.name << "의 승리...\n";
    cout << "=============================\n";
}
