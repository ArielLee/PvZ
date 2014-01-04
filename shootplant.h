#ifndef SHOOTPLANT_H
#define SHOOTPLANT_H

#include <iostream>
#include <sstream>
#include <string>

#include "plant.h"
#include "zombie.h"

class ShootPlant : public Plant {
public:
	ShootPlant(char type, std::string name, int cost, int life, int damage) : Plant(type, name, cost, life), damage_(damage) {

	}

	Plant *Clone() const override {
		return new ShootPlant(Type(), Name(), Cost(), Life(), damage_);
	}

	void ShowDetailsAndEffects(std::ostream& os) const override {
		os << Name() << " $" << Cost() << " HP: " << Life()
		   << " - gives " << damage_ << " damage points";
	}

	void Print(std::ostream& os) const override {
		os << Name() << " HP: " << Life();
	}

	std::string ActWith(Zombie& zombie) override {
		zombie.Injured(damage_);

		std::stringstream ss;
		ss << Name() << " gives " << damage_ << " damage to the zombie!";
		return ss.str();
	}

private:
	int damage_;
};

#endif