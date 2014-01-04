#ifndef COINPLANT_H
#define COINPLANT_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "plant.h"
#include "player.h"

class CoinPlant : public Plant {
public:
	CoinPlant(char type, std::string name, int cost, int life, int visit, int reward) : Plant(type, name, cost, life), need_visit_(visit), reward_(reward) {
		left_visit_ = need_visit_;
	}

	Plant *Clone() const override {
		return new CoinPlant(Type(), Name(), Cost(), Life(), need_visit_, reward_);
	}

	void ShowDetailsAndEffects(std::ostream& os) const override {
		os << Name() << " $" << Cost() << " HP: " << Life()
		   << " - gives $" << reward_ << " every " << need_visit_ << " rounds";
	}

	void Print(std::ostream& os) const override {
		os << Name() << " HP: " << Life() << " (" << left_visit_ << " more visit" << (left_visit_ == 1 ? ' ' : 's') << ")";
	}

	std::string ActWith(Player& player, std::vector<Plant *> plants) override {
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

private:
	int need_visit_;
	int left_visit_;
	int reward_;
};

#endif