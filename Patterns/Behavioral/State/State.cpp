#include "State.h"

class Npc;

class NpcState {
public:
	virtual void update(Npc* npc) = 0;
};

class Npc {
private:
	int _health;
	int _energy, _max_energy;
	int _power;
	int _level = 0;

	std::shared_ptr<NpcState> current_state;
public:
	void update() { current_state->update(this); }
	void set_state(std::shared_ptr<NpcState> next) { current_state = next; }
	bool use_energy(int amount) {
		_energy -= amount;
		bool enough = _energy >= 0;
		_energy = _energy > 0 ? _energy : 0;
		return enough;
	}
	bool gain_energy(int amount) {
		_energy += amount;
		if (_energy > _max_energy) _energy = _max_energy;
		return _energy == _max_energy;
	}
public:
	Npc() = delete;
	Npc(int hp, int energy, int power, std::shared_ptr<NpcState> init_state) : 
		_health(hp), _energy(energy), _power(power), current_state(init_state) {
		_max_energy = _energy;
	}
};


class LumberjackChoppState;
class LumberjackRestState;
class LumberjackStoreState;
class LumberjackInitState;

class LumberjackRestState : public NpcState {
public:
	void update(Npc* npc) {
		if (!npc->gain_energy(30)) { std::cout << "Lumberjack: Regain 30 energy" << std::endl; }
		else {
			std::cout << "Lumberjack: Energy fully restored" << std::endl;
			npc->set_state(std::static_pointer_cast<NpcState>(std::make_shared<LumberjackChoppState>()));
		}
	};
};

class LumberjackStoreState : public NpcState {
public:
	void update(Npc* npc) {
		if (npc->use_energy(5)) {
			std::cout << "Lumberjack: Stored wood" << std::endl;
			npc->set_state(std::static_pointer_cast<NpcState>(std::make_shared<LumberjackChoppState>()));
		}
		else {
			std::cout << "Lumberjack: Failed to store wood" << std::endl;
			npc->set_state(std::static_pointer_cast<NpcState>(std::make_shared<LumberjackRestState>()));
		}
	};
};

class LumberjackChoppState : public NpcState {
public:
	void update(Npc* npc) {
		if (npc->use_energy(7)) {
			std::cout << "Lumberjack: Chopped wood" << std::endl;
			npc->set_state(std::static_pointer_cast<NpcState>(std::make_shared<LumberjackStoreState>()));
		}
		else {
			std::cout << "Lumberjack: Failed to chop wood" << std::endl;
			npc->set_state(std::static_pointer_cast<NpcState>(std::make_shared<LumberjackRestState>()));
		}
	};
};

class LumberjackInitState : public NpcState {
public:
	void update(Npc* npc) {
		std::cout << "Lumberjack: Start his Journey" << std::endl;
		npc->set_state(std::static_pointer_cast<NpcState>(std::make_shared<LumberjackChoppState>()));
	};
};


class Lumberjack : public Npc {
public:
	Lumberjack() : Npc(100, 50, 5, std::make_shared<LumberjackInitState>()) {}
};


std::string StatePattern::get_info() {
	return "Name: State Pattern.\nType: Behavioral.\nDescription: The State pattern defines an object's behavior based on a state machine, where each state is represented by an independent class.";
}

int StatePattern::run() {

	std::shared_ptr<Npc> lumberjack = std::make_shared<Lumberjack>();

	std::cout << "\n" << "Display 20 steps of lumberjack" << std::endl;
	for (int i = 0; i < 20; i++) lumberjack->update();

	return 0;
}