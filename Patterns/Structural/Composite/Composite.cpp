#include "Composite.h"

#include <vector>


namespace composite_pattern {

	class Component {
	public:
		virtual std::string	component_name() = 0;
	};

	// Battery Components
	class BatteryController : public Component {
	public:
		std::string	component_name() {
			return "Generic battery controller.";
		}
	};

	class LitiumCell : public Component {
	public:
		std::string	component_name() {
			return "Litium Cell Battery.";
		}
	};

	class NickelCell : public Component {
	public:
		std::string	component_name() {
			return "Nickel Cell Battery.";
		}
	};


	// Frame Components
	class Buttons : public Component {
	public:
		std::string	component_name() {
			return "Some Buttons.";
		}
	};

	class PlasicShell : public Component {
	public:
		std::string	component_name() {
			return "Plastic Shell.";
		}
	};

	class GlassShell : public Component {
	public:
		std::string	component_name() {
			return "Glass Shell.";
		}
	};


	// Screen components
	class Glass : public Component {
	public:
		std::string	component_name() {
			return "Glass Screen.";
		}
	};

	class Saphire : public Component {
	public:
		std::string	component_name() {
			return "Saphire Screen.";
		}
	};

	class ResistiveTouch : public Component {
	public:
		std::string	component_name() {
			return "Resistive Touch.";
		}
	};

	class CapacitiveTouch : public Component {
	public:
		std::string	component_name() {
			return "Capacitive Touch.";
		}
	};



	class FactoryProcess {
	private:
		std::vector<std::shared_ptr<FactoryProcess>> subprocesses;
		virtual std::shared_ptr<Component> build_component() {
			return nullptr;
		};
	public:
		std::vector<std::shared_ptr<Component>> run() {
			std::vector<std::shared_ptr<Component>> components;
			for (auto& proc : subprocesses) {
				std::vector<std::shared_ptr<Component>> sub_components = proc->run();
				if (!sub_components.empty()) components.insert(components.end(), sub_components.begin(), sub_components.end());
			}
			std::shared_ptr<Component> component = build_component();
			if (component) components.push_back(component);
			return components;
		};
		void add_subprocess(std::shared_ptr<FactoryProcess> process) { subprocesses.push_back(process); }
	};


	class BuildBatteryController : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<BatteryController>();
		}
	};

	class BuildNickelCell : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<NickelCell>();
		}
	};

	class BuildLitiumCell : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<LitiumCell>();
		}
	};


	class BuildGlassLayer : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<Glass>();
		}
	};

	class BuildSaphireLayer : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<Saphire>();
		}
	};


	class BuildResistiveTouch : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<ResistiveTouch>();
		}
	};

	class BuildCapacitiveTouch : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<CapacitiveTouch>();
		}
	};


	class BuildPlasticShell : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<PlasicShell>();
		}
	};

	class BuildGlassShell : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<GlassShell>();
		}
	};


	class BuildButtons : public FactoryProcess {
	private:
		std::shared_ptr<Component> build_component() override {
			return std::make_shared<Buttons>();
		}
	};
}


std::string CompositePattern::get_info() {
	return "Name: Composite.\nType: Structural.\nDescription: The Composite pattern allows logic to be stored in a tree-like structure while providing a unified interface for operations.";
}

int CompositePattern::run() {

	using namespace composite_pattern;

	// what if we need to compose some objects into groups. In addition object can be a group too.

	// Let's say we have a manufacturing process and need to build a complex product like a phone.  
	// This requires running multiple processes, but not all of them are necessary.  
	// How do we decide which processes are needed? We establish relationships.

	std::shared_ptr<FactoryProcess> build_cheap_battery = std::make_shared<FactoryProcess>();
	build_cheap_battery->add_subprocess(std::make_shared<BuildNickelCell>());
	build_cheap_battery->add_subprocess(std::make_shared<BuildBatteryController>());

	std::shared_ptr<FactoryProcess> build_good_battery = std::make_shared<FactoryProcess>();
	build_good_battery->add_subprocess(std::make_shared<BuildLitiumCell>());
	build_good_battery->add_subprocess(std::make_shared<BuildBatteryController>());

	std::shared_ptr<FactoryProcess> build_cheap_screen = std::make_shared<FactoryProcess>();	
	build_cheap_screen->add_subprocess(std::make_shared<BuildGlassLayer>());
	build_cheap_screen->add_subprocess(std::make_shared<BuildResistiveTouch>());

	std::shared_ptr<FactoryProcess> build_good_screen = std::make_shared<FactoryProcess>();
	build_good_screen->add_subprocess(std::make_shared<BuildGlassLayer>());
	build_good_screen->add_subprocess(std::make_shared<BuildCapacitiveTouch>());

	std::shared_ptr<FactoryProcess> build_great_screen = std::make_shared<FactoryProcess>();
	build_great_screen->add_subprocess(std::make_shared<BuildSaphireLayer>());
	build_great_screen->add_subprocess(std::make_shared<BuildCapacitiveTouch>());

	std::shared_ptr<FactoryProcess> build_cheap_frame = std::make_shared<FactoryProcess>();
	build_cheap_frame->add_subprocess(std::make_shared<BuildPlasticShell>());
	build_cheap_frame->add_subprocess(std::make_shared<BuildButtons>());

	std::shared_ptr<FactoryProcess> build_good_frame = std::make_shared<FactoryProcess>();
	build_good_frame->add_subprocess(std::make_shared<BuildGlassShell>());
	build_good_frame->add_subprocess(std::make_shared<BuildButtons>());

	// Cheap phone 
	{
		std::shared_ptr<FactoryProcess> build_cheap_phone = std::make_shared<FactoryProcess>();
		build_cheap_phone->add_subprocess(build_cheap_frame);
		build_cheap_phone->add_subprocess(build_cheap_screen);
		build_cheap_phone->add_subprocess(build_cheap_battery);

		std::vector<std::shared_ptr<Component>> phone_components = build_cheap_phone->run();
		std::cout << "\n" << "Cheap phone characteristics:" << "\n	";
		for (auto& component : phone_components)
			std::cout << component->component_name() << "\n	";
	}
	
	// Normal phone 
	{
		std::shared_ptr<FactoryProcess> build_normal_phone = std::make_shared<FactoryProcess>();
		build_normal_phone->add_subprocess(build_good_frame);
		build_normal_phone->add_subprocess(build_good_screen);
		build_normal_phone->add_subprocess(build_cheap_battery);

		std::vector<std::shared_ptr<Component>> phone_components = build_normal_phone->run();
		std::cout << "\n" << "Normal phone characteristics:" << "\n	";
		for (auto& component : phone_components)
			std::cout << component->component_name() << "\n	";
	}

	// Expensive phone 
	{
		std::shared_ptr<FactoryProcess> build_expensive_phone = std::make_shared<FactoryProcess>();
		build_expensive_phone->add_subprocess(build_good_frame);
		build_expensive_phone->add_subprocess(build_great_screen);
		build_expensive_phone->add_subprocess(build_good_battery);

		std::vector<std::shared_ptr<Component>> phone_components = build_expensive_phone->run();
		std::cout << "\n" << "Expensive phone characteristics:" << "\n	";
		for (auto& component : phone_components)
			std::cout << component->component_name() << "\n	";
	}
	return 0;
}