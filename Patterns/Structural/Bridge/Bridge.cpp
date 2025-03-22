#include "Bridge.h"

#include <vector>

class Stats {
public:
	int health = 100,
		mana = 0,
		strength = 0,
		stamina = 0;
	Stats(int health, int mana, int strength, int stamina) {
		this->health = health,
		this->mana = mana,
		this->strength = strength,
		this->stamina = stamina;
	}
};


class Profession {
public:
	std::string attack_type;
	virtual std::string attack(std::shared_ptr<Stats> stats) = 0;
};

class Mage : public Profession {
public:
	Mage() {
		attack_type = "Fireball";
	}
	std::string attack(std::shared_ptr<Stats> stats) {
		if (stats->mana > 140) return attack_type + ": Strong";
		else if (stats->mana > 50) return attack_type + ": Normal";
		return attack_type + ": Weak";
	};
};

class Warrior : public Profession {
public:
	Warrior() {
		attack_type = "Sword Slash";
	}
	std::string attack(std::shared_ptr<Stats> stats) {
		if (stats->strength > 90) return attack_type + ": Strong";
		else if (stats->strength > 70) return attack_type + ": Normal";
		return attack_type + ": Weak";
	};
};

class Archer : public Profession {
public:
	Archer() {
		attack_type = "Rain of Arrows";
	}
	std::string attack(std::shared_ptr<Stats> stats) {
		if (stats->stamina > 90) return attack_type + ": Strong";
		else if(stats->stamina > 60) return attack_type + ": Normal";
		return attack_type + ": Weak";
	};
};


class Entity {
protected:
	std::shared_ptr<Stats> stats;
	std::shared_ptr<Profession> prof;
public:
	virtual std::string attack() = 0;
};

class Orc : public Entity {
public:
	Orc(std::shared_ptr<Profession> profession) {
		prof = profession;
		stats = std::make_shared<Stats>(150, 5, 100, 50);
	}
	std::string attack() {
		return prof->attack(stats);
	};
};

class Elf : public Entity {
public:
	Elf(std::shared_ptr<Profession> profession) {
		prof = profession;
		stats = std::make_shared<Stats>(70, 150, 50, 100);
	}
	std::string attack() {
		return prof->attack(stats);
	};
};

class Human : public Entity {
public:
	Human(std::shared_ptr<Profession> profession) {
		prof = profession;
		stats = std::make_shared<Stats>(100, 75, 80, 70);
	}
	std::string attack() {
		return prof->attack(stats);
	};
};


std::string BridgePattern::get_info() {
	return "Name: Bridge.\nType: Structural.\nDescription: The Bridge pattern enables multi-dimensional class extension without requiring every possible class combination.";
}

int BridgePattern::run() {

	// The Bridge pattern allows us to easily extend one dimension without needing to extend other dimensions.

	// Team Humans 
	{
		std::vector<std::shared_ptr<Entity>> entities;
		entities.push_back(std::make_shared<Human>(std::make_shared<Mage>()));
		entities.push_back(std::make_shared<Human>(std::make_shared<Warrior>()));
		entities.push_back(std::make_shared<Human>(std::make_shared<Archer>()));

		std::cout << "\n Team Human Attacks:\n";
		for (auto& it : entities) std::cout << it->attack() << "\n";
	}

	// Team Meta
	{
		std::vector<std::shared_ptr<Entity>> entities;
		entities.push_back(std::make_shared<Elf>(std::make_shared<Mage>()));
		entities.push_back(std::make_shared<Orc>(std::make_shared<Warrior>()));
		entities.push_back(std::make_shared<Elf>(std::make_shared<Archer>()));

		std::cout << "\n Team Meta Attacks:\n";
		for (auto& it : entities) std::cout << it->attack() << "\n";
	}

	// Team Worst
	{
		std::vector<std::shared_ptr<Entity>> entities;
		entities.push_back(std::make_shared<Orc>(std::make_shared<Mage>()));
		entities.push_back(std::make_shared<Elf>(std::make_shared<Warrior>()));
		entities.push_back(std::make_shared<Orc>(std::make_shared<Archer>()));

		std::cout << "\n Team Worst Attacks:\n";
		for (auto& it : entities) std::cout << it->attack() << "\n";
	}

	return 0;
}