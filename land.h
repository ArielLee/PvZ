#ifndef LAND_H
#define LAND_H

#include <iostream>
#include <vector>

#include "plant.h"
#include "zombie.h"

class Land {
public:
	Land(size_t id) : id_(id) {

	}

	~Land() {
		if (plant_ != nullptr) {
			Clear();
		}
	}

	bool HasPlant() const {
		return plant_ != nullptr;
	}

	void Grow(Plant *plant) {
		plant_ = plant;
		plant_->SetPosition(id_);
	}

	Plant *GetPlant() const {
		return plant_;
	}

	void Clear() {
		delete plant_;
		plant_ = nullptr;
	}

	void Print(std::ostream& os, bool player_in, const std::vector<Zombie>& zombies) {
		os << '{' << (player_in ? '*' : ' ');

		for (size_t i = 0; i < zombies.size(); ++i) {
			if (zombies[i].Alive()) {
				if (id_ == zombies[i].Position()) {
					os << zombies[i].Id();
				} else {
					os << ' ';
				}
			}
		}

		os << "} ";

		if (plant_ == nullptr) {
			os << "Empty";
		} else {
			os << plant_;
		}
	}

private:
	size_t id_;
	Plant *plant_ = nullptr;
};

#endif