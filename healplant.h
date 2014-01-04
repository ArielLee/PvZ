#ifndef HEALPLANT_H
#define HEALPLANT_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "plant.h"
#include "player.h"

class HealPlant : public Plant {
public:
	HealPlant(char type, std::string name, int cost, int life, int heal) : Plant(type, name, cost, life), heal_points_(heal) {

	}

	Plant *Clone() const override {
		return new HealPlant(Type(), Name(), Cost(), Life(), heal_points_);
	}

	void ShowDetailsAndEffects(std::ostream& os) const override {
		os << Name() << " $" << Cost() << " HP: " << Life()
		   << " - gives all your plants " << heal_points_ << " HP back.";
	}

	void Print(std::ostream& os) const override {
		os << Name() << " HP: " << Life();
	}

	std::string ActWith(Player& player, std::vector<Plant *> plants) override {
		for (auto plant : plants) {
			plant->Recover(heal_points_);
		}

		std::stringstream ss;
		ss << "All your plants have recovered " << heal_points_ << " HP!";
		return ss.str();
	}

private:
	int heal_points_;
};

#endif