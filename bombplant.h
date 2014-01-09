#ifndef BOMBPLANT_H
#define BOMBPLANT_H


class BombPlant : public Plant {
public:
	BombPlant(char type, std::string name, int cost, int life) : Plant(type, name, cost, life), damage_(life) {

	}

	virtual Plant *Clone() const override {
		return new BombPlant(Type(), Name(), Cost(), Life());
	}

	virtual void ShowDetailsAndEffects(std::ostream& os) const override;
	virtual void Print(std::ostream& os) const override;
	virtual std::string ActWith(Zombie& zombie) override;

private:
	int damage_;
};

#endif
