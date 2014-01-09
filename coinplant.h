#ifndef COINPLANT_H
#define COINPLANT_H



class CoinPlant : public Plant {
public:
	CoinPlant(char type, std::string name, int cost, int life, int visit, int reward) : Plant(type, name, cost, life), need_visit_(visit), reward_(reward) {
		left_visit_ = need_visit_;
	}

	virtual Plant *Clone() const override {
		return new CoinPlant(Type(), Name(), Cost(), Life(), need_visit_, reward_);
	}

	virtual void ShowDetailsAndEffects(std::ostream& os) const override;
	virtual void Print(std::ostream& os) const override;
	virtual std::string ActWith(Player& player, std::vector<Plant *> plants) override;

private:
	int need_visit_;
	int left_visit_;
	int reward_;
};

#endif
