#include "Decorator.h"

#include <vector>


class Telescope {
public:
	virtual float magnification() = 0;
};


class OmegonTelescope : public Telescope {
public:
	float magnification() {
		return 2.0f;
	};
};

class PrimeTelescope : public Telescope {
public:
	float magnification() {
		return 10.0f;
	};
};

class DeltaTelescope : public Telescope {
public:
	float magnification() {
		return 100.0f;
	};
};


class Lense2x : public Telescope {
private:
	std::shared_ptr<Telescope> telescope;
public:
	Lense2x(std::shared_ptr<Telescope> t) : telescope(t) {}
	float magnification() {
		return telescope->magnification() * 2.0f;
	};
};

class Lense5x : public Telescope {
private:
	std::shared_ptr<Telescope> telescope;
public:
	Lense5x(std::shared_ptr<Telescope> t) : telescope(t) {}
	float magnification() {
		return telescope->magnification() * 5.0f;
	};
};

class Lense0_5x : public Telescope {
private:
	std::shared_ptr<Telescope> telescope;
public:
	Lense0_5x(std::shared_ptr<Telescope> t) : telescope(t) {}
	float magnification() {
		return telescope->magnification() * 0.5f;
	};
};


std::string DecoratorPattern::get_info() {
	return "Name: Decorator.\nType: Structural.\nDescription: The Decorator pattern allows dynamically extending an object's responsibilities.";
}

int DecoratorPattern::run() {

	std::shared_ptr<Telescope> prime_telescope = std::make_shared<PrimeTelescope>();
	std::cout << "\n" << "Prime Telescope Magnification(without lenses): " << prime_telescope->magnification() << std::endl;
	prime_telescope = std::make_shared<Lense0_5x>(prime_telescope);
	prime_telescope = std::make_shared<Lense5x>(prime_telescope);
	std::cout << "Prime Telescope Magnification(with lenses): " << prime_telescope->magnification() << std::endl;

	std::shared_ptr<Telescope> delta_telescope = std::make_shared<DeltaTelescope>();
	std::cout << "\n" << "Delta Telescope Magnification(without lenses): " << delta_telescope->magnification() << std::endl;
	delta_telescope = std::make_shared<Lense5x>(delta_telescope);
	delta_telescope = std::make_shared<Lense5x>(delta_telescope);
	delta_telescope = std::make_shared<Lense5x>(delta_telescope);
	std::cout << "Delta Telescope Magnification(with lenses): " << delta_telescope->magnification() << std::endl;

	std::shared_ptr<Telescope> omegon_telescope = std::make_shared<OmegonTelescope>();
	std::cout << "\n" << "Omegon Telescope Magnification(without lenses): " << omegon_telescope->magnification() << std::endl;
	omegon_telescope = std::make_shared<Lense2x>(omegon_telescope);
	omegon_telescope = std::make_shared<Lense0_5x>(omegon_telescope);
	omegon_telescope = std::make_shared<Lense5x>(omegon_telescope);
	std::cout << "Omegon Telescope Magnification(with lenses): " << omegon_telescope->magnification() << std::endl;

	return 0;
}