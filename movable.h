#ifndef MOVABLE_H
#define MOVABLE_H

class Movable {
public:
	Movable(size_t pos, size_t max_dist) : position_(pos), max_move_dist_(max_dist) {

	}

	size_t Position() const {
		return position_;
	}

	void UpdatePos(size_t pos) {
		position_ = pos;
	}

	size_t MaxMoveDist() const {
		return max_move_dist_;
	}

protected:
	size_t position_;
	size_t max_move_dist_;
};

#endif