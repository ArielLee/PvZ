#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "land.h"
#include "player.h"
#include "zombie.h"

class Map {
public:
	Map(size_t num_lands) : num_lands_(num_lands) {
		lands_ = new Land *[num_lands_];

		for (size_t i = 0; i < num_lands_; ++i) {
			lands_[i] = new Land(i);
		}
	}

	~Map() {
		for (size_t i = 0; i < num_lands_; ++i) {
			delete lands_[i];
		}

		delete [] lands_;
	}

	void Print(std::ostream& os, const Player& player, const std::vector<Zombie>& zombies) const {
		for (size_t i = 0; i < num_lands_; ++i) {
			os << '[' << i << ']';

			lands_[i]->Print(os, (i == player.Position()), zombies);

			os << std::endl;
		}
	}

	Land& operator[] (size_t index) const {
		return *lands_[index];
	}
private:
	size_t num_lands_;
	Land **lands_;
};

#endif
