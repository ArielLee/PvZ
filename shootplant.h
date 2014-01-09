#ifndef SHOOTPLANT_H
#define SHOOTPLANT_H

class ShootPlant : public Plant {
public:
	ShootPlant(char type, std::string name, int cost, int life, int damage) : Plant(type, name, cost, life), damage_(damage) {

	}

	virtual Plant *Clone() const override {
		return new ShootPlant(Type(), Name(), Cost(), Life(), damage_);
	}

	virtual void ShowDetailsAndEffects(std::ostream& os) const override;
	virtual void Print(std::ostream& os) const override;
	virtual std::string ActWith(Zombie& zombie) override;

private:
	int damage_;
};

#endif
