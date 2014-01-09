#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

#include "map.h"
#include "plant.h"
#include "player.h"
#include "zombie.h"
#include "bombplant.h"
#include "coinplant.h"
#include "healplant.h"
#include "shootplant.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::string;
using std::vector;

enum class TGameStatus { PLAYING, WIN, LOSE };

size_t default_num_lands = 8;
size_t default_num_zombies = 3;
size_t default_min_size = 1;
size_t default_max_size = 10;

int getNumber(int lb, int ub, int default_val) {
	char buf[256];

	cin.getline(buf, 256);

	int n = atoi(buf);

	return isdigit(buf[0]) ? (n >= lb && n <= ub ? n : default_val) : default_val;
}

int move(int lb, int ub, int curr_pos, int max_dist) {
	//curr_pos += (rand()%2 ? 1 : -1) * (rand() % max_dist + 1);
	curr_pos = (curr_pos + (rand() % max_dist)) % ub;

	return curr_pos; //(curr_pos < lb ? lb : (curr_pos > ub ? ub : curr_pos));
}

void ShowInformation(ostream& os, const Map& map, const Player& player, const vector<Zombie>& zombies) {
	map.Print(os, player, zombies);

	os << "------------------------------------------------" << endl;

	os << "Zombie information:" << endl;
	for (size_t i = 0; i < zombies.size(); ++i) {
		os << zombies[i] << endl;
	}

	os << "================================================" << endl;
}

int main() {
	system("cls");
	cout << " ---------------------------- " << endl
		 << "|     Plants vs. Zombies     |" << endl
		 << " ---------------------------- " << endl;

	cout << "Number of lands on the map (" << default_min_size << '-' << default_max_size << ", default: " << default_num_lands << ")...> ";
	size_t num_lands = getNumber(default_min_size, default_max_size, default_num_lands);
	cout << "Number of zombies on the map (" << default_min_size << '-' << default_max_size << ", default: " << default_num_zombies << ")...>";
	size_t num_zombies = getNumber(default_min_size, default_max_size, default_num_zombies);

	ifstream fin("plants.txt");

	vector<Plant *> plant_factory;

	if (fin.is_open()) {
		char type, junk;
		int cost, life, tmp[2];
		string name;

		while (fin >> type >> name >> junk >> cost >> life) {
			switch (type) {
			case 'C': // CoinPlant
				fin >> tmp[0] >> tmp[1];

				plant_factory.push_back(new CoinPlant('C', name, cost, life, tmp[0], tmp[1]));
				break;
			case 'S': // ShootPlant
				fin >> tmp[0];

				plant_factory.push_back(new ShootPlant('S', name, cost, life, tmp[0]));
				break;
			case 'B': // BombPlant
				plant_factory.push_back(new BombPlant('B', name, cost, life));
				break;
			case 'H': // HealPlant
				fin >> tmp[0];

				plant_factory.push_back(new HealPlant('H', name, cost, life, tmp[0]));
				break;
			}
		}
	} else {
		cout << "'plants.txt' cannot be opened!";

		return 0;
	}

	cout << "=============================================================================" << endl
		 << "Plants vs. Zombies Rule:" << endl << endl
		 << "How to win:" << endl
		 << "  (1) All zombies are dead." << endl
		 << "  (2) At least one plant is live." << endl
		 << "  (3) The number of dead bomb plants cannot exceed the number of zombies." << endl << endl
		 << "How to lose:" << endl
		 << "  All plants are dead." << endl
		 << "=============================================================================" << endl;
	system("pause");

	Map map(num_lands);
	Player player(rand() % num_lands);
	vector<Zombie> zombies;
	vector<Plant *> plants;

	for (size_t i = 0; i < num_zombies; ++i) {
		zombies.push_back(Zombie(i, rand() % num_lands));
	}

	TGameStatus status = TGameStatus::PLAYING;
	srand(time(NULL));

	size_t last_choice = plant_factory.size(); // default to give up
	size_t turn = 0; // 0 for player, other for zombies
	int typeB_cnt = 0;
	int alive_zombies_cnt = zombies.size();

	do {
		system("cls");

		if (turn == 0) { // player
			player.UpdatePos(move(0, num_lands, player.Position(), player.MaxMoveDist()));

			ShowInformation(cout, map, player, zombies);

			if (map[player.Position()].HasPlant()) {
				Plant *plant = map[player.Position()].GetPlant();

				string msg = plant->ActWith(player, plants);

				if (msg != "Nothing to do.") {
					cout << msg << endl;
				}
			} else {
				if (player.Money() > 0) {
					for (size_t i = 0; i < plant_factory.size(); ++i) {
						cout << '[' << i << "] ";

						plant_factory[i]->ShowDetailsAndEffects(cout);

						cout << endl;
					}

					cout << endl << "Player $" << player.Money() << ":    Enter you choice (" << plant_factory.size() << " to give up, default: " << last_choice << ")...> ";
					last_choice = getNumber(0, plant_factory.size(), last_choice);

					if (last_choice == plant_factory.size()) { // give up
						cout << "You give up!" << endl;
					} else {
						Plant *new_plant = plant_factory[last_choice]->Clone();

						plants.push_back(new_plant);
						map[player.Position()].Grow(new_plant);
						player.Spend(new_plant->Cost());
						cout << "You have planted " << new_plant->Name() << " at land " << player.Position() << '!' << endl;
					}
				} else {
					cout << "You do not have enough money to plant anything!" << endl;
				}
			}
		}
		else
        {
			Zombie& zombie = zombies[turn - 1];

			if (zombie.Alive()) {
				zombie.UpdatePos(move(0, num_lands, zombie.Position(), zombie.MaxMoveDist()));

				ShowInformation(cout, map, player, zombies);

				cout << "Zombie [" << zombie.Id() << "] moves to land " << zombie.Position() << '.' << endl;

				if (map[zombie.Position()].HasPlant()) {
					Plant *plant = map[zombie.Position()].GetPlant();

					string msg = plant->ActWith(zombie);

					if (msg != "Nothing to do.") {
						cout << msg << endl;
					}

					plant->Injured(zombie.Damage());
					cout << "Zombie eats plant " << plant->Name() << " and causes damage " << zombie.Damage() << '.' << endl;

					if (!zombie.Alive()) {
                        cout << "Zombie is killed!" << endl;
                        zombies.erase(zombies.begin() + (turn - 1));

						alive_zombies_cnt -= 1;
					}

					if (!plant->Alive()) {
						cout << "Plant " << plant->Name() << " is dead!" << endl;

						if (plant->Type() == 'B') {
							typeB_cnt += 1;
						}

						plants.erase(std::remove(plants.begin(), plants.end(), plant), plants.end());
						map[plant->Position()].Clear();
					}
				}
			}
			else
            {
                turn = (turn + 1) % (zombies.size() + 1);
                continue;
            }
		}

		turn = (turn + 1) % (zombies.size() + 1);

		if (alive_zombies_cnt == 0) {
			if (typeB_cnt < num_zombies && plants.size() > 0) {
				status = TGameStatus::WIN;

				cout << endl << "Congratulations! You have killed all zombies!" << endl;
			} else {
				status = TGameStatus::LOSE;

				cout << endl << "You lose the game since you cannot use that many bomb plants!" << endl;
			}
		} else if (plants.size() == 0) {
			status = TGameStatus::LOSE;

			cout << endl << "Oh no... You have no plant on the map ...." << endl;;
		}

		system("pause");
	} while (status == TGameStatus::PLAYING);

	for(int i = 0, j = plant_factory.size(); i < j; i ++)
    {
        Plant *p = plant_factory.at(i);
        delete p;
    }
    plant_factory.clear();

	return 0;
}
