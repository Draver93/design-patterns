#include "TemplateMethod.h"

#include <vector>


namespace template_method_pattern {

	class WashingMachineProgramm {
	protected:
		enum class Step {
			IDLE,
			SPIN,
			HIGH_SPIN
		};
		static std::string get_step_name(Step step) {
			switch (step) {
			case Step::IDLE: return "idle";
			case Step::SPIN: return "spin";
			case Step::HIGH_SPIN: return "high speed";
			default: return "Unknown";
			}
		}

	private:
		virtual std::vector<Step> get_steps() = 0;
		virtual int get_step_temp(Step step) = 0;
		virtual int get_rpm(Step step) = 0;
		virtual bool need_water(Step step) = 0;

	public:
		void execute() {
			std::vector<Step> steps = get_steps();
			for (auto& step : steps) {
				int temp = get_step_temp(step);
				int rpm = get_rpm(step);
				std::cout << "Executing step: " << get_step_name(step)
					<< " with temp: " << temp
					<< " and speed: " << rpm << "rpm"
					<< (need_water(step) ? " (Water required)" : "") << "\n";
			}
		}
	};

	class PreWash : public WashingMachineProgramm {
	private:
		std::vector<Step> get_steps() {
			return std::vector<Step>({ Step::IDLE, Step::SPIN, Step::IDLE });
		};
		int get_step_temp(Step step) {
			switch (step) {
				case Step::IDLE: return 25;
				default: return 30;
			}
		};
		int get_rpm(Step step) {
			switch (step) {
				case Step::IDLE: return 300;
				case Step::SPIN: return 800;
				default: return 0;
			}
		};
		bool need_water(Step step) {
			switch (step) {
				case Step::IDLE: return true;
				case Step::SPIN: return false;
				default: return false;
			}
		};
	};

	class HighTempWash : public WashingMachineProgramm {
	private:
		std::vector<Step> get_steps() {
			return std::vector<Step>({ Step::IDLE, Step::SPIN, Step::SPIN, Step::IDLE, Step::SPIN, Step::IDLE });
		};
		int get_step_temp(Step step) {
			switch (step) {
				case Step::IDLE: return 60;
				default: return 90;
			}
		};
		int get_rpm(Step step) {
			switch (step) {
				case Step::IDLE: return 250;
				case Step::SPIN: return 600;
				default: return 0;
			}
		};
		bool need_water(Step step) {
			switch (step) {
				case Step::IDLE: return true;
				case Step::SPIN: return false;
				default: return false;
			}
		};
	};

	class ColourWash : public WashingMachineProgramm {
	private:
		std::vector<Step> get_steps() {
			return std::vector<Step>({ Step::IDLE, Step::SPIN, Step::HIGH_SPIN, Step::SPIN, Step::IDLE });
		};
		int get_step_temp(Step step) {
			switch (step) {
				case Step::IDLE: return 45;
				default: return 60;
			}
		};
		int get_rpm(Step step) {
			switch (step) {
				case Step::IDLE: return 100;
				case Step::SPIN: return 600;
				case Step::HIGH_SPIN: return 1200;
				default: return 0;
			}
		};
		bool need_water(Step step) {
			switch (step) {
				case Step::IDLE: return true;
				default: return false;
			}
		};
	};

	class SyntheticsWash : public WashingMachineProgramm {
	private:
		std::vector<Step> get_steps() {
			return std::vector<Step>({ Step::IDLE, Step::SPIN, Step::SPIN, Step::IDLE });
		};
		int get_step_temp(Step step) {
			switch (step) {
				case Step::IDLE: return 30;
				default: return 80;
			}
		};
		int get_rpm(Step step) {
			switch (step) {
				case Step::IDLE: return 100;
				case Step::SPIN: return 600;
				default: return 0;
			}
		};
		bool need_water(Step step) {
			switch (step) {
				case Step::IDLE: return true;
				default: return false;
			}
		};
	};
}


std::string TemplateMethodPattern::get_info() {
	return "Name: Template Method Pattern.\nType: Behavioral.\nDescription: The Template Method pattern defines a skeleton for an algorithm in a base class, allowing derived classes to provide specific implementations for certain steps.";
}

int TemplateMethodPattern::run() {

	using namespace template_method_pattern;

	std::shared_ptr<WashingMachineProgramm> programm;

	std::cout << "\n" << "Executing programm: SyntheticsWash" << std::endl;
	programm = std::make_shared<SyntheticsWash>();
	programm->execute(); 

	std::cout << "\n" << "Executing programm: ColourWash" << std::endl;
	programm = std::make_shared<ColourWash>();
	programm->execute();

	std::cout << "\n" << "Executing programm: HighTempWash" << std::endl;
	programm = std::make_shared<HighTempWash>();
	programm->execute();

	return 0;
}