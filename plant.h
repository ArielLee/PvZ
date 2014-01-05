#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#include "zombie.h"

class Plant {
public:
	Plant(char type, std::string name, int cost, int life) : type_(type), name_(name), cost_(cost), life_(life) {
        static_life_ = life_;
	}

	virtual ~Plant() = default;

	char Type() const {
		return type_;
	}

	std::string Name() const {
		return name_;
	}

	int Cost() const {
		return cost_;
	}

	int Life() const {
		return life_;
	}

	bool Alive() const {
		return life_ > 0;
	}

	void Injured(int damage) {
		life_ -= damage;
	}

	void Recover(int heal_points) {
		life_ += heal_points;

		if(life_ > static_life_)
        {
            life_ = static_life_;
        }
	}

	void SetPosition(size_t pos) {
		position_ = pos;
	}

	size_t Position() const {
		return position_;
	}

	virtual Plant *Clone() const = 0;
	virtual void ShowDetailsAndEffects(std::ostream& os) const = 0;
	virtual void Print(std::ostream& os) const = 0;

	virtual std::string ActWith(Player& player, std::vector<Plant *> plants) {
		return "Nothing to do.";
	}

	virtual std::string ActWith(Zombie& zombie) {
		return "Nothing to do.";
	}

	friend std::ostream& operator<< (std::ostream& os, const Plant *plant) {
		plant->Print(os);

		return os;
	}

private:
	char type_;
	std::string name_;
	int cost_;
	int life_;
	int static_life_;
	size_t position_;
};

#endif
