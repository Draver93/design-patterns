#include "AbstractFactory.h"

#include <vector>


namespace abstract_factory_pattern {

	class Entity {
	public:
		int id;
		int health;
		int damage;
		int mana;
	};

	class OrcWarior : public Entity {
	public:
		OrcWarior(int id) {
			this->health = 100;
			this->mana = 0;
			this->damage = 10;
			this->id = id;
		}
	};

	class OrcMage : public Entity {
	public:
		OrcMage(int id) {
			this->health = 20;
			this->mana = 80;
			this->damage = 50;
			this->id = id;
		}
	};

	class OrcPet : public Entity {
	public:
		OrcPet(int id) {
			this->health = 200;
			this->mana = 0;
			this->damage = 5;
			this->id = id;
		}
	};

	class ElfWarior : public Entity {
	public:
		ElfWarior(int id) {
			this->health = 80;
			this->mana = 20;
			this->damage = 15;
			this->id = id;
		}
	};

	class ElfMage : public Entity {
	public:
		ElfMage(int id) {
			this->health = 90;
			this->mana = 150;
			this->damage = 70;
			this->id = id;
		}
	};

	class ElfPet : public Entity {
	public:
		ElfPet(int id) {
			this->health = 150;
			this->mana = 10;
			this->damage = 15;
			this->id = id;
		}
	};

	class HumanWarior : public Entity {
	public:
		HumanWarior(int id) {
			this->health = 90;
			this->mana = 0;
			this->damage = 20;
			this->id = id;
		}
	};

	class HumanMage : public Entity {
	public:
		HumanMage(int id) {
			this->health = 40;
			this->mana = 120;
			this->damage = 30;
			this->id = id;
		}
	};

	class HumanPet : public Entity {
	public:
		HumanPet(int id) {
			this->health = 170;
			this->mana = 5;
			this->damage = 10;
			this->id = id;
		}
	};


	class Vilage {
	public:
		virtual std::shared_ptr<Entity> spawn_warior(int id) = 0;
		virtual std::shared_ptr<Entity> spawn_mage(int id) = 0;
		virtual std::shared_ptr<Entity> spawn_pet(int id) = 0;
	};

	class OrcVilage : public Vilage {
	public:
		std::shared_ptr<Entity> spawn_warior(int id) {
			return std::make_shared<OrcWarior>(id);
		}
		std::shared_ptr<Entity> spawn_mage(int id) {
			return std::make_shared<OrcMage>(id);
		}
		std::shared_ptr<Entity> spawn_pet(int id) {
			return std::make_shared<OrcPet>(id);
		}
	};

	class ElfVilage : public Vilage {
	public:
		std::shared_ptr<Entity> spawn_warior(int id) {
			return std::make_shared<ElfWarior>(id);
		}
		std::shared_ptr<Entity> spawn_mage(int id) {
			return std::make_shared<ElfMage>(id);
		}
		std::shared_ptr<Entity> spawn_pet(int id) {
			return std::make_shared<ElfPet>(id);
		}
	};

	class HumanVilage : public Vilage {
	public:
		std::shared_ptr<Entity> spawn_warior(int id) {
			return std::make_shared<HumanWarior>(id);
		}
		std::shared_ptr<Entity> spawn_mage(int id) {
			return std::make_shared<HumanMage>(id);
		}
		std::shared_ptr<Entity> spawn_pet(int id) {
			return std::make_shared<HumanPet>(id);
		}
	};
}


std::string AbstractFactoryPattern::get_info() {
	return "Name: Abstract Factory.\nType: Creational.\nDescription: The Abstract Factory pattern is an extension of the Factory Method pattern. It is useful when working with families of related objects.";
}

int AbstractFactoryPattern::run() {

	using namespace abstract_factory_pattern;

	// With the Factory Method pattern, you can extend a single family of classes. However, when introducing a second dimension,  
	// the Factory Method must be modified to handle the additional dimension, which violates SOLID principles.  
	//  
	// This is where the Abstract Factory pattern helps maintain SOLID principles by introducing factories for families of objects.

	std::vector<std::shared_ptr<Vilage>> vilages;
	vilages.push_back(std::make_shared<HumanVilage>());
	vilages.push_back(std::make_shared<ElfVilage>());
	vilages.push_back(std::make_shared<OrcVilage>());
	// vilages.push_back(std::make_shared<...>());
	// vilages.push_back(std::make_shared<...>());
	// vilages.push_back(std::make_shared<...>());
	// vilages.push_back(std::make_shared<...>());

	// Now our business logic will work only with Vilages and Entities
	std::vector<std::shared_ptr<Entity>> world_entities;
	int entity_id = 0;
	for (auto& vilage : vilages) {
		world_entities.push_back(vilage->spawn_mage(entity_id));
		entity_id++;
	}

	for (auto& vilage : vilages) {
		world_entities.push_back(vilage->spawn_warior(entity_id));
		entity_id++;
	}

	for (auto& vilage : vilages) {
		world_entities.push_back(vilage->spawn_pet(entity_id));
		entity_id++;
	}

	for (auto& entity : world_entities) {
		std::cout << "\n" << "Entity:\n"
			<< "  id: " + std::to_string(entity->id) << "\n"
			<< "  damage: " + std::to_string(entity->damage) << "\n"
			<< "  health: " + std::to_string(entity->health) << "\n";
	}

	return 0;
}