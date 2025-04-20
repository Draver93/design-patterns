#include "Strategy.h"

#include <vector>


namespace strategy_pattern {

	class AttackType {
	public:
		virtual void execute() = 0;
	};

	class SwordAttack : public AttackType {
	public:
		virtual void execute() {
			std::cout << "Sword strike" << "\n";
		};
	};

	class BowAttack : public AttackType {
	public:
		virtual void execute() {
			std::cout << "Bow shot" << "\n";
		};
	};

	class PunchAttack : public AttackType {
	public:
		virtual void execute() {
			std::cout << "Fist strike" << "\n";
		};
	};

	
	class Unit {
	protected:
		std::shared_ptr<AttackType> m_attack_type;
		int m_id;
	public:
		Unit() = delete;
		Unit(int id, std::shared_ptr<AttackType> attack_type) : m_attack_type(attack_type), m_id(id){}
		void set_attack_type(std::shared_ptr<AttackType> attack_type) { m_attack_type = attack_type; }

		void attack() {
			std::cout << "Unit: " + std::to_string(m_id) + " executes attack: ";
			m_attack_type->execute();
		}
	};

	class Archer : public Unit {
	public:
		Archer(int id) : Unit(id, std::make_shared<BowAttack>()) {}
	};

	class Knight : public Unit {
	public:
		Knight(int id) : Unit(id, std::make_shared<SwordAttack>()) {}
	};

	class Peasant : public Unit {
	public:
		Peasant(int id) : Unit(id, std::make_shared<PunchAttack>()) {}
	};
}


std::string StrategyPattern::get_info() {
	return "Name: Strategy Pattern.\nType: Behavioral.\nDescription: The Strategy pattern allows dynamically switching an object's behavior by selecting from a family of related algorithms through a common interface.";
}

int StrategyPattern::run() {

	using namespace strategy_pattern;
	
	std::srand((unsigned int)std::time(nullptr));
	std::vector<std::shared_ptr<Unit>> units;
	units.reserve(17);
	
	for (int i = 0; i < 2; i++) units.push_back(std::make_shared<Knight>(units.size()));
	for (int i = 0; i < 5; i++) units.push_back(std::make_shared<Archer>(units.size()));
	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Unit> peasant = std::make_shared<Peasant>(units.size());

		// Let's give some Peasants Bows, let's say 20%
		if ((rand() % 101) < 20) peasant->set_attack_type(std::make_shared<BowAttack>());

		units.push_back(peasant);
	}

	std::cout << "\n" << "Army Attack: " << "\n";
	for (auto& unit : units) unit->attack();

	return 0;
}