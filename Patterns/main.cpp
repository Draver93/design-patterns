#include <iostream>
#include <vector>

#include "Creational/Singleton/Singleton.h"
#include "Creational/Prototype/Prototype.h"
#include "Creational/FactoryMethod/FactoryMethod.h"
#include "Creational/AbstractFactory/AbstractFactory.h"
#include "Creational/Builder/Builder.h"

#include "Behavioral/ChainOfResponsibility/ChainOfResponsibility.h"
#include "Behavioral/Command/Command.h"
#include "Behavioral/Interpreter/Interpreter.h"
#include "Behavioral/Observer/Observer.h"
#include "Behavioral/State/State.h"

#include "Structural/Proxy/Proxy.h"
#include "Structural/Adpater/Adapter.h"
#include "Structural/Bridge/Bridge.h"
#include "Structural/Composite/Composite.h"
#include "Structural/Decorator/Decorator.h"
#include "Structural/Facade/Facade.h"
#include "Structural/Flyweight/Flyweight.h"

int main() {
	int ret = 0;

	std::vector<std::shared_ptr<Pattern>> patterns;
	patterns.push_back(std::make_shared<SingletonPattern>());
	patterns.push_back(std::make_shared<PrototypePattern>());
	patterns.push_back(std::make_shared<FactoryMethodPattern>());
	patterns.push_back(std::make_shared<BuilderPattern>());
	patterns.push_back(std::make_shared<AbstractFactoryPattern>());

	patterns.push_back(std::make_shared<ChainOfResponsibilityPattern>());
	patterns.push_back(std::make_shared<CommandPattern>());
	patterns.push_back(std::make_shared<InterpreterPattern>());
	patterns.push_back(std::make_shared<ObserverPattern>());
	patterns.push_back(std::make_shared<StatePattern>());

	patterns.push_back(std::make_shared<ProxyPattern>());
	patterns.push_back(std::make_shared<AdapterPattern>());
	patterns.push_back(std::make_shared<BridgePattern>());
	patterns.push_back(std::make_shared<CompositePattern>());
	patterns.push_back(std::make_shared<DecoratorPattern>());
	patterns.push_back(std::make_shared<FacadePattern>());
	patterns.push_back(std::make_shared<FlyweightPattern>());

	for (auto& pattern : patterns) 
	{
		std::cout << "\n" << pattern->get_info() << std::endl;
		ret = pattern->run();
		if (ret != 0) break;
	}

	patterns.clear();
	return ret;
}