#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>

#include "movable.h"

class Zombie : public Movable {
public:
	static const int DEFAULT_LIFE = 40;
	static const int DEFAULT_DAMAGE = 15;
	static const int DEFAULT_MAX_MOVE = 3;

	Zombie(size_t id, size_t pos) : Movable(pos, DEFAULT_MAX_MOVE), id_(id) {
		life_ = DEFAULT_LIFE;
		damage_ = DEFAULT_DAMAGE;
	}

	size_t Id() const {
		return id_;
	}

	bool Alive() const {
		return life_ > 0;
	}

	int Damage() const {
		return damage_;
	}

	void Injured(int damage) {
		life_ -= damage;
	}

	friend std::ostream& operator<< (std::ostream& os, const Zombie& zombie) {
		os << '[' << zombie.id_ << "] Damage: " << zombie.damage_ << " HP: ";

		for (int i = 0; i < zombie.life_; ++i) {
			os << '*';
		}

		return os;
	}

private:
	size_t id_;
	int life_;
	int damage_;
};

#endif
