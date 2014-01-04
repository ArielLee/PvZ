#ifndef BOMBPLANT_H
#define BOMBPLANT_H

#include <sstream>
#include <string>

#include "plant.h"

class BombPlant : public Plant {
public:
	BombPlant(char type, std::string name, int cost, int life) : Plant(type, name, cost, life), damage_(life) {

	}

	Plant *Clone() const override {
		return new BombPlant(Type(), Name(), Cost(), Life());
	}

	void ShowDetailsAndEffects(std::ostream& os) const override {
		os << Name() << " $" << Cost() << " HP: " << Life()
		   << " - gives " << damage_ << " damage points";
	}

	void Print(std::ostream& os) const override {
		os << Name() << " HP: " << Life();
	}

	std::string ActWith(Zombie& zombie) override {
		zombie.Injured(Life());

		Injured(Life());

		std::stringstream ss;
		ss << Name() << " gives " << Life() << " damage to the zombie!";
		return ss.str();
	}

private:
	int damage_;
};

#endif