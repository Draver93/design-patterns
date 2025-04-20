#include "Bridge.h"

#include <vector>


namespace bridge_pattern {

	class Stats {
	public:
		int m_health = 100,
			m_mana = 0,
			m_strength = 0,
			m_stamina = 0;
		Stats(int health, int mana, int strength, int stamina) :
				m_health(health), m_mana(mana), m_strength(strength), m_stamina(stamina) {}
	};


	class Profession {
	public:
		std::string m_attack_type;
		virtual std::string attack(std::shared_ptr<Stats> stats) = 0;
	};

	class Mage : public Profession {
	public:
		Mage() {
			m_attack_type = "Fireball";
		}
		std::string attack(std::shared_ptr<Stats> stats) {
			if (stats->m_mana > 140) return m_attack_type + ": Strong";
			else if (stats->m_mana > 50) return m_attack_type + ": Normal";
			return m_attack_type + ": Weak";
		};
	};

	class Warrior : public Profession {
	public:
		Warrior() {
			m_attack_type = "Sword Slash";
		}
		std::string attack(std::shared_ptr<Stats> stats) {
			if (stats->m_strength > 90) return m_attack_type + ": Strong";
			else if (stats->m_strength > 70) return m_attack_type + ": Normal";
			return m_attack_type + ": Weak";
		};
	};

	class Archer : public Profession {
	public:
		Archer() {
			m_attack_type = "Rain of Arrows";
		}
		std::string attack(std::shared_ptr<Stats> stats) {
			if (stats->m_stamina > 90) return m_attack_type + ": Strong";
			else if (stats->m_stamina > 60) return m_attack_type + ": Normal";
			return m_attack_type + ": Weak";
		};
	};


	class Entity {
	protected:
		std::shared_ptr<Stats> m_stats;
		std::shared_ptr<Profession> m_profession;
	public:
		virtual std::string attack() = 0;
	};

	class Orc : public Entity {
	public:
		Orc(std::shared_ptr<Profession> profession) {
			m_profession = profession;
			m_stats = std::make_shared<Stats>(150, 5, 100, 50);
		}
		std::string attack() {
			return m_profession->attack(m_stats);
		};
	};

	class Elf : public Entity {
	public:
		Elf(std::shared_ptr<Profession> profession) {
			m_profession = profession;
			m_stats = std::make_shared<Stats>(70, 150, 50, 100);
		}
		std::string attack() {
			return m_profession->attack(m_stats);
		};
	};

	class Human : public Entity {
	public:
		Human(std::shared_ptr<Profession> profession) {
			m_profession = profession;
			m_stats = std::make_shared<Stats>(100, 75, 80, 70);
		}
		std::string attack() {
			return m_profession->attack(m_stats);
		};
	};

}


std::string BridgePattern::get_info() {
	return "Name: Bridge.\nType: Structural.\nDescription: The Bridge pattern enables multi-dimensional class extension without requiring every possible class combination.";
}

int BridgePattern::run() {

	using namespace bridge_pattern;

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