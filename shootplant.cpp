#include <iostream>
#include <sstream>
#include <string>

#include "plant.h"
#include "zombie.h"
#include "shootplant.h"

void ShootPlant::ShowDetailsAndEffects(std::ostream& os) const {
    os << Name() << " $" << Cost() << " HP: " << Life()
       << " - gives " << damage_ << " damage points";
}

void ShootPlant::Print(std::ostream& os) const {
    os << Name() << " HP: " << Life();
}

std::string ShootPlant::ActWith(Zombie& zombie) {
    zombie.Injured(damage_);

    std::stringstream ss;
    ss << Name() << " gives " << damage_ << " damage to the zombie!";
    return ss.str();
}
