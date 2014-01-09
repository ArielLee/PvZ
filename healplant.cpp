#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "plant.h"
#include "player.h"
#include "healplant.h"

void HealPlant::ShowDetailsAndEffects(std::ostream& os) const {
    os << Name() << " $" << Cost() << " HP: " << Life()
       << " - gives all your plants " << heal_points_ << " HP back.";
}

void HealPlant::Print(std::ostream& os) const {
    os << Name() << " HP: " << Life();
}

std::string HealPlant::ActWith(Player& player, std::vector<Plant *> plants) {
    for (auto plant : plants) {
        plant->Recover(heal_points_);
    }

    std::stringstream ss;
    ss << "All your plants have recovered " << heal_points_ << " HP!";
    return ss.str();
}
