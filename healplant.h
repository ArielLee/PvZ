#ifndef HEALPLANT_H
#define HEALPLANT_H


class HealPlant : public Plant {
public:
	HealPlant(char type, std::string name, int cost, int life, int heal) : Plant(type, name, cost, life), heal_points_(heal) {

	}

	virtual Plant *Clone() const override {
		return new HealPlant(Type(), Name(), Cost(), Life(), heal_points_);
	}

	virtual void ShowDetailsAndEffects(std::ostream& os) const override;
	virtual void Print(std::ostream& os) const override;
	virtual std::string ActWith(Player& player, std::vector<Plant *> plants) override;

private:
	int heal_points_;
};

#endif
