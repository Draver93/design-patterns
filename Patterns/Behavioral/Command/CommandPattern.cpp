#include "CommandPattern.h"

#include <stack>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

class VerticalMovementReciver {
protected:
	float z = 0;
public:
	virtual void rise(int altitude) {
		z += altitude;
	};
};

class HorizontalMovementReciver {
protected:
	float x = 0, y = 0;
	float angle = 0;
public:
	virtual void move(float distance) {
		float rad = angle* (PI / 180.0f);
		x += distance * std::cos(rad);
		y += distance * std::sin(rad);
	};
	virtual void rotate(float degree) {
		angle += degree;
	};
};

class RCDrone : public HorizontalMovementReciver, public VerticalMovementReciver {
public:
	std::string get_status() {
		return "pos: x[" + std::to_string(x) + "], y[" + std::to_string(x) + "], z[" + std::to_string(z) + "]; angle: " + std::to_string(angle);
	}
};

class RCCar : public HorizontalMovementReciver {
public:
	std::string get_status() {
		return "pos: x[" + std::to_string(x) + "], y[" + std::to_string(x) + "]; angle: " + std::to_string(angle);
	}
};


class Signal {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class MoveSignal : public Signal {
private:
	float dst;
	std::shared_ptr<HorizontalMovementReciver> rcvr;
public:
	MoveSignal(float distance, std::shared_ptr<HorizontalMovementReciver> reciver) : dst(distance), rcvr(reciver){ }
	void execute() override {
		rcvr->move(dst);
	};
	void undo() override {
		rcvr->move(-dst);
	};
};

class RotateSignal : public Signal {
private:
	float degree;
	std::shared_ptr<HorizontalMovementReciver> rcvr;
public:
	RotateSignal(float angle, std::shared_ptr<HorizontalMovementReciver> reciver) : degree(angle), rcvr(reciver) { }
	void execute() override {
		rcvr->rotate(degree);
	};
	void undo() override {
		rcvr->rotate(-degree);
	};
};

class AltitudeSignal : public Signal {
private:
	float alt;
	std::shared_ptr<VerticalMovementReciver> rcvr;
public:
	AltitudeSignal(float altitude, std::shared_ptr<VerticalMovementReciver> reciver) : alt(altitude), rcvr(reciver) { }
	void execute() {
		rcvr->rise(alt);
	};
	void undo() {
		rcvr->rise(-alt);
	};
};


class RadioController {
private:
	std::shared_ptr<HorizontalMovementReciver> horizontal_movement_reciver;
	std::shared_ptr<VerticalMovementReciver> verical_movement_reciver;
	std::stack<std::shared_ptr<Signal>> signals;
public:
	RadioController() { }
	void connect_vertical_reciver(std::shared_ptr<VerticalMovementReciver> reciver) {
		verical_movement_reciver = reciver;
	}
	void connect_horizontal_reciver(std::shared_ptr<HorizontalMovementReciver> reciver) {
		horizontal_movement_reciver = reciver;
	}
	void move(float distance) {
		if (!horizontal_movement_reciver) { std::cout << "\n" << "Command `move` failed to execute" << "\n"; return; }
		if (distance != 0) {
			std::shared_ptr<Signal> signal = std::make_shared<MoveSignal>(distance, horizontal_movement_reciver);
			signal->execute();
			signals.push(signal);
		}
	}
	void rotate(float angle) {
		if (!horizontal_movement_reciver) { std::cout << "\n" << "Command `rotate` failed to execute" << "\n"; return; }
		if (angle != 0) {
			std::shared_ptr<Signal> signal = std::make_shared<RotateSignal>(angle, horizontal_movement_reciver);
			signal->execute();
			signals.push(signal);
		}
	}
	void rise(float alt) {
		if (!verical_movement_reciver) { std::cout << "\n" << "Command `rise` failed to execute" << "\n"; return; }
		if (alt != 0) {
			std::shared_ptr<Signal> signal = std::make_shared<AltitudeSignal>(alt, verical_movement_reciver);
			signal->execute();
			signals.push(signal);
		}
	}
	void home() {
		while (!signals.empty()) {
			signals.top()->undo();
			signals.pop();
		}
	}
};


std::string CommandPattern::get_info() {
	return "Name: Command Pattern.\nType: Behavioral.\nDescription: Instead of establishing direct communication between the sender and receiver, we provide a list of commands for the receiver to execute. \
	By encapsulating each command, we gain flexibility in controlling command execution.";
}

int CommandPattern::run() {

	std::cout << "\n" << "Drone command execution example:" << std::endl;
	{
		std::shared_ptr<RCDrone> drone = std::make_shared<RCDrone>();
		std::shared_ptr<RadioController> controller = std::make_shared<RadioController>();
		controller->connect_horizontal_reciver(drone);
		controller->connect_vertical_reciver(drone);
		controller->move(98);
		std::cout << "\n" << "[Drone] " << drone->get_status() << "\n";
		controller->rotate(14);
		controller->home();
		std::cout << "\n" << "[Drone] " << drone->get_status() << "\n";
		controller->move(250);
		controller->rise(11);
		std::cout << "\n" << "[Drone] " << drone->get_status() << "\n";
	}

	std::cout << "\n" << "Car command execution example:" << std::endl;
	{
		std::shared_ptr<RCCar> car = std::make_shared<RCCar>();
		std::shared_ptr<RadioController> controller = std::make_shared<RadioController>();
		controller->connect_horizontal_reciver(car);
		controller->move(124);
		std::cout << "\n" << "[Car] " << car->get_status() << "\n";
		controller->rotate(52);
		controller->move(23);
		std::cout << "\n" << "[Car] " << car->get_status() << "\n";
		controller->rise(80);
		controller->home();
		std::cout << "\n" << "[Car] " << car->get_status() << "\n";
	}


	return 0;
}