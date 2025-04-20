#include "FactoryMethod.h"

#include <vector>


namespace factory_method {

	class Entity {
	public:
		int m_id;
		int m_health;
		int m_damage;
		Entity(int id, int health, int damage) 
			: m_id(id), m_health(health), m_damage(damage) {}
	};

	class Spider : public Entity {
	public:
		Spider(int id) 
			: Entity(id, 5, 2) {}
	};

	class Sheep : public Entity {
	public:
		Sheep(int id)
			: Entity(id, 10, 0) {}
	};

	class Warior : public Entity {
	public:
		Warior(int id) : 
			Entity(id, 100, 10) {}
	};


	class Spawner {
	private:
	protected:
		virtual std::shared_ptr<Entity> spawn(int id) = 0;

	public:
		std::shared_ptr<Entity> create(int id) {
			return spawn(id);
		}
	};

	class SpiderSpawner : public Spawner {
	public:
		std::shared_ptr<Entity> spawn(int id) {
			return std::make_shared<Spider>(id);
		};
	};

	class SheepSpawner : public Spawner {
	public:
		std::shared_ptr<Entity> spawn(int id) {
			return std::make_shared<Sheep>(id);
		};
	};

	class WariorSpawner : public Spawner {
	public:
		std::shared_ptr<Entity> spawn(int id) {
			return std::make_shared<Warior>(id);
		};
	};
}


std::string FactoryMethodPattern::get_info() {
	return "Name: Factory Method.\nType: Creational.\nDescription: Define interface for object creation. Delegate concrete product creation to method of the subclasses.";
}

int FactoryMethodPattern::run() {

	using namespace factory_method;

	// We have business logic for working with entities. The pool of entities can be extended without violating SOLID principles.
	std::vector<std::shared_ptr<Spawner>> world_spawners;
	world_spawners.push_back(std::make_shared<SpiderSpawner>());
	world_spawners.push_back(std::make_shared<SpiderSpawner>());
	world_spawners.push_back(std::make_shared<SheepSpawner>());
	world_spawners.push_back(std::make_shared<WariorSpawner>());
	// world_spawners.push_back(std::make_shared<...>());
	// world_spawners.push_back(std::make_shared<...>());
	// world_spawners.push_back(std::make_shared<...>());
	// world_spawners.push_back(std::make_shared<...>());

	//Now our business logic will work only with Spawner and Entities
	std::vector<std::shared_ptr<Entity>> world_entities;
	int entity_id = 0;
	for (auto& spawner : world_spawners) {
		world_entities.push_back(spawner->create(entity_id));
		entity_id++;
	}

	for (auto& spawner : world_spawners) {
		world_entities.push_back(spawner->create(entity_id));
		entity_id++;
	}

	for (auto& entity : world_entities) {
		std::cout << "\n" << "Entity:\n"
		<< "  id: " + std::to_string(entity->m_id) << "\n"
		<< "  damage: " + std::to_string(entity->m_damage) << "\n"
		<< "  health: " + std::to_string(entity->m_health) << "\n";
	}

	return 0;
}

