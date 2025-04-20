#include "Command.h"

#include <stack>
#include <cmath>


namespace command_pattern {

	constexpr float PI = 3.1415926f;

	class VerticalMovementReciver {
	protected:
		float m_altitude = 0;
	public:
		virtual void rise(float altitude) {
			m_altitude += altitude;
		};
	};

	class HorizontalMovementReciver {
	protected:
		float m_pos_x = 0, m_pos_y = 0;
		float m_angle = 0;
	public:
		virtual void move(float distance) {
			float rad = m_angle * (PI / 180.0f);
			m_pos_x += distance * std::cos(rad);
			m_pos_y += distance * std::sin(rad);
		};
		virtual void rotate(float degree) {
			m_angle += degree;
		};
	};

	class RCDrone : public HorizontalMovementReciver, public VerticalMovementReciver {
	public:
		std::string get_status() {
			return "pos: x[" + std::to_string(m_pos_x) + "], y[" + std::to_string(m_pos_x) + "], z[" + std::to_string(m_altitude) + "]; angle: " + std::to_string(m_angle);
		}
	};

	class RCCar : public HorizontalMovementReciver {
	public:
		std::string get_status() {
			return "pos: x[" + std::to_string(m_pos_x) + "], y[" + std::to_string(m_pos_x) + "]; angle: " + std::to_string(m_angle);
		}
	};


	class Signal {
	public:
		virtual void execute() = 0;
		virtual void undo() = 0;
	};

	class MoveSignal : public Signal {
	private:
		float m_dst;
		std::shared_ptr<HorizontalMovementReciver> m_rcvr;
	public:
		MoveSignal(float distance, std::shared_ptr<HorizontalMovementReciver> reciver) : m_dst(distance), m_rcvr(reciver) { }
		void execute() override {
			m_rcvr->move(m_dst);
		};
		void undo() override {
			m_rcvr->move(-m_dst);
		};
	};

	class RotateSignal : public Signal {
	private:
		float m_angle;
		std::shared_ptr<HorizontalMovementReciver> m_rcvr;
	public:
		RotateSignal(float angle, std::shared_ptr<HorizontalMovementReciver> reciver) : m_angle(angle), m_rcvr(reciver) { }
		void execute() override {
			m_rcvr->rotate(m_angle);
		};
		void undo() override {
			m_rcvr->rotate(-m_angle);
		};
	};

	class AltitudeSignal : public Signal {
	private:
		float m_altitude;
		std::shared_ptr<VerticalMovementReciver> m_rcvr;
	public:
		AltitudeSignal(float altitude, std::shared_ptr<VerticalMovementReciver> reciver) : m_altitude(altitude), m_rcvr(reciver) { }
		void execute() {
			m_rcvr->rise(m_altitude);
		};
		void undo() {
			m_rcvr->rise(-m_altitude);
		};
	};


	class RadioController {
	private:
		std::shared_ptr<HorizontalMovementReciver> m_movement_reciver_hor;
		std::shared_ptr<VerticalMovementReciver> m_movement_reciver_vert;
		std::stack<std::shared_ptr<Signal>> m_signals;
	public:
		RadioController() { }
		void connect_vertical_reciver(std::shared_ptr<VerticalMovementReciver> reciver) {
			m_movement_reciver_vert = reciver;
		}
		void connect_horizontal_reciver(std::shared_ptr<HorizontalMovementReciver> reciver) {
			m_movement_reciver_hor = reciver;
		}
		void move(float distance) {
			if (!m_movement_reciver_hor) { std::cout << "\n" << "Command `move` failed to execute" << "\n"; return; }
			if (distance != 0) {
				std::shared_ptr<Signal> signal = std::make_shared<MoveSignal>(distance, m_movement_reciver_hor);
				signal->execute();
				m_signals.push(signal);
			}
		}
		void rotate(float angle) {
			if (!m_movement_reciver_hor) { std::cout << "\n" << "Command `rotate` failed to execute" << "\n"; return; }
			if (angle != 0) {
				std::shared_ptr<Signal> signal = std::make_shared<RotateSignal>(angle, m_movement_reciver_hor);
				signal->execute();
				m_signals.push(signal);
			}
		}
		void rise(float alt) {
			if (!m_movement_reciver_vert) { std::cout << "\n" << "Command `rise` failed to execute" << "\n"; return; }
			if (alt != 0) {
				std::shared_ptr<Signal> signal = std::make_shared<AltitudeSignal>(alt, m_movement_reciver_vert);
				signal->execute();
				m_signals.push(signal);
			}
		}
		void home() {
			while (!m_signals.empty()) {
				m_signals.top()->undo();
				m_signals.pop();
			}
		}
	};
}


std::string CommandPattern::get_info() {
	return "Name: Command Pattern.\nType: Behavioral.\nDescription: Instead of establishing direct communication between the sender and receiver, we provide a list of commands for the receiver to execute. \
	By encapsulating each command, we gain flexibility in controlling command execution.";
}

int CommandPattern::run() {

	using namespace command_pattern;

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