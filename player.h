#ifndef PLAYER_H
#define PLAYER_H

#include "movable.h"

class Player : public Movable {
public:
	static const int DEFAULT_MONEY = 100;
	static const int DEFAULT_MAX_MOVE = 6;

	Player(size_t pos) : Movable(pos, DEFAULT_MAX_MOVE) {
		money_ = DEFAULT_MONEY;
	}

	void Earn(int money) {
		money_ += money;
	}

	int Money() const {
		return money_;
	}

	void Spend(int cost) {
		money_ -= cost;
	}

private:
	int money_;
};

#endif
