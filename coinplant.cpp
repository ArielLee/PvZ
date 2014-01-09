#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "plant.h"
#include "player.h"
#include "coinplant.h"

void CoinPlant::ShowDetailsAndEffects(std::ostream& os) const {
    os << Name() << " $" << Cost() << " HP: " << Life()
       << " - gives $" << reward_ << " every " << need_visit_ << " rounds";
}

void CoinPlant::Print(std::ostream& os) const {
    os << Name() << " HP: " << Life() << " (" << left_visit_ << " more visit" << (left_visit_ == 1 ? ' ' : 's') << ")";
}

std::string CoinPlant::ActWith(Player& player, std::vector<Plant *> plants) {
    left_visit_ -= 1;

    std::stringstream ss;

    if (left_visit_ == 0) {
        left_visit_ = need_visit_;
        player.Earn(reward_);

        ss << "You have earned $" << reward_ << "! Now you have $" << player.Money() << ".";
        return ss.str();
    } else {
        ss << "You still need " << left_visit_ << " visit(s) to earn $" << reward_ << ".";
        return ss.str();
    }
}
