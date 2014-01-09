#include <iostream>
#include <vector>

#include "plant.h"
#include "zombie.h"
#include "land.h"

void Land::Print(std::ostream& os, bool player_in, const std::vector<Zombie>& zombies) {
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
