#pragma once
#include <string>
#include "pokemon.h"

struct Trainer {
    std::string name;
    Pokemon pokemon;
};

Trainer selectTrainer(int town);