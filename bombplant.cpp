#include <sstream>
#include <string>

#include "plant.h"
#include "bombplant.h"

void BombPlant::ShowDetailsAndEffects(std::ostream& os) const {
    os << Name() << " $" << Cost() << " HP: " << Life()
       << " - gives " << damage_ << " damage points";
}

void BombPlant::Print(std::ostream& os) const {
    os << Name() << " HP: " << Life();
}

std::string BombPlant::ActWith(Zombie& zombie) {
    damage_ = Life();

    zombie.Injured(damage_);

    Injured(damage_);

    std::stringstream ss;
    ss << Name() << " gives " << damage_ << " damage to the zombie!";

    return ss.str();
}
