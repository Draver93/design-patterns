#include "Facade.h"


namespace facade_pattern {

	class Engine {
	public:
		virtual int cranking() = 0;
		virtual int calc_spark_timing(int shaft_position) = 0;
		virtual int activate_coil(int coil_id) = 0;
	};

	class V10Engine : public Engine {
	public:
		int cranking() {
			return 0; // As initial angle of the shaft
		};
		int calc_spark_timing(int shaft_position) {
			switch (shaft_position) {
			case 0:   return 0;
			case 36:  return 5;
			case 72:  return 1;
			case 108: return 6;
			case 144: return 2;
			case 180: return 7;
			case 216: return 3;
			case 252: return 8;
			case 288: return 4;
			case 324: return 9;
			default: return 0;
			}
		};
		int activate_coil(int coil_id) {
			std::cout << "Ignition in: " << coil_id << " Cylinder" << std::endl;

			//Next shaft position
			switch (coil_id) {
			case 0: return 36;
			case 5: return 72;
			case 1: return 108;
			case 6: return 144;
			case 2: return 180;
			case 7: return 216;
			case 3: return 252;
			case 8: return 288;
			case 4: return 324;
			case 9: return 0;
			default: return 0;
			}
		}
	};

	class V6Engine : public Engine {
	public:
		int cranking() {
			return 0; // As initial angle of the shaft
		};
		int calc_spark_timing(int shaft_position) {
			switch (shaft_position) {
			case 0: return 0;
			case 60: return 3;
			case 120: return 1;
			case 180: return 4;
			case 240: return 2;
			case 300: return 5;
			default: return 0;
			}
		};
		int activate_coil(int coil_id) {
			std::cout << "Ignition in: " << coil_id << " Cylinder" << std::endl;

			//Next shaft position
			switch (coil_id) {
			case 0: return  60;
			case 3: return  120;
			case 1: return  180;
			case 4: return  240;
			case 2: return  300;
			case 5: return  0;
			default: return 0;
			}
		}
	};

	class Ignition {
	protected:
		std::shared_ptr<Engine> _engine;

	public:
		void connect_engine(std::shared_ptr<Engine> engine) { _engine = engine; }
		virtual void turn_on(int cycles) = 0;
	};

	class DISIgnition : public Ignition {
	public:
		void turn_on(int cycles) {
			int position = _engine->cranking();

			//Ignition specific calc

			while (cycles) {
				// Manual 
				int cylinder_id = _engine->calc_spark_timing(position);
				position = _engine->activate_coil(cylinder_id);
				cycles--;
			}
		}
	};

	class DirectIgnition : public Ignition { //Coil-on-plug
	public:
		void turn_on(int cycles) {
			int position = _engine->cranking();

			//Ignition specific calc

			while (cycles) {
				// Manual 
				int cylinder_id = _engine->calc_spark_timing(position);
				position = _engine->activate_coil(cylinder_id);
				cycles--;
			}
		}
	};


	class Car {
	private:
		std::shared_ptr<Engine> _engine;
		std::shared_ptr<Ignition> _ignition;
	public:
		std::shared_ptr<Ignition> get_ignition() { return _ignition; };
		std::shared_ptr<Engine> get_engine() { return _engine; };

	protected:
		Car() = delete;
		Car(std::shared_ptr<Engine> engine, std::shared_ptr<Ignition> ignition) : _engine(engine), _ignition(ignition) {
			_ignition->connect_engine(_engine);
		}
	};

	class DodgeViper : public Car {
	public:
		DodgeViper() :
			Car(std::make_shared<V10Engine>(),
				std::make_shared<DISIgnition>()) {
		}
	};

	class DodgeChallenger : public Car {
	public:
		DodgeChallenger() :
			Car(std::make_shared<V6Engine>(),
				std::make_shared<DirectIgnition>()) {
		}
	};
}


std::string FacadePattern::get_info() {
	return "Name: Facade.\nType: Structural.\nDescription: The Facade pattern abstracts complex underlying logic behind a simple, user-friendly interface.";
}

int FacadePattern::run() {

	using namespace facade_pattern;

	std::shared_ptr<Car> viper = std::make_shared<DodgeViper>();
	{	
		// We can use ignition Facade class that does all by himself
		std::cout << "\n" << "Calling ignition on: Viper" << "\n";
		viper->get_ignition()->turn_on(11);

		// Or we can manually run engine by ourself
		std::cout << "\n" << "Manually cranking the engine on: Viper" << "\n";
		int position = viper->get_engine()->cranking();
		int cycles = 0;
		while (cycles < 11) {
			int cylinder_id = viper->get_engine()->calc_spark_timing(position);
			position = viper->get_engine()->activate_coil(cylinder_id);
			cycles++;
		}
	}

	std::shared_ptr<Car> challenger = std::make_shared<DodgeChallenger>();
	{
		// Same thing for another car
		std::cout << "\n" << "Calling ignition on: Challenger" << "\n";
		challenger->get_ignition()->turn_on(7);

		// Manual 
		std::cout << "\n" << "Manually cranking the engine on: Challenger" << "\n";
		int position = challenger->get_engine()->cranking();
		int cycles = 0;
		while (cycles < 7) {
			int cylinder_id = challenger->get_engine()->calc_spark_timing(position);
			position = challenger->get_engine()->activate_coil(cylinder_id);
			cycles++;
		}
	}

	return 0;
}