#pragma once
#include <string>

struct Pokemon {
    std::string name;
    int level;
    int hp;      // 현재 HP
    int maxHp;   // 최대 HP
    int attack;
    int defense;
    int speed;
    std::string skill1;
    std::string skill2;
    std::string skill3;
    std::string skill4;
};

Pokemon createPokemon(const std::string& name);

Pokemon createPokemon(
    const std::string& name,
    int level,
    int hp,
    int attack,
    int defense,
    int speed,
    const std::string& skill1,
    const std::string& skill2,
    const std::string& skill3,
    const std::string& skill4
);