#ifndef LAND_H
#define LAND_H

#include "plant.h"

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

	void Print(std::ostream& os, bool player_in, const std::vector<Zombie>& zombies);

private:
	size_t id_;
	Plant *plant_ = nullptr;
};

#endif
