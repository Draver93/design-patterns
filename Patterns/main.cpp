#include <iostream>
#include <array>

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
#include "Behavioral/Visitor/Visitor.h"
#include "Behavioral/Strategy/Strategy.h"
#include "Behavioral/TemplateMethod/TemplateMethod.h"
#include "Behavioral/Memento/Memento.h"
#include "Behavioral/Mediator/Mediator.h"
#include "Behavioral/Iterator/Iterator.h"

#include "Structural/Proxy/Proxy.h"
#include "Structural/Adpater/Adapter.h"
#include "Structural/Bridge/Bridge.h"
#include "Structural/Composite/Composite.h"
#include "Structural/Decorator/Decorator.h"
#include "Structural/Facade/Facade.h"
#include "Structural/Flyweight/Flyweight.h"

int main() {
	int ret = 0;

	std::array<std::shared_ptr<Pattern>, 23> patterns = {
		std::make_shared<SingletonPattern>(),
		std::make_shared<PrototypePattern>(),
		std::make_shared<FactoryMethodPattern>(),
		std::make_shared<BuilderPattern>(),
		std::make_shared<AbstractFactoryPattern>(),

		std::make_shared<ChainOfResponsibilityPattern>(),
		std::make_shared<CommandPattern>(),
		std::make_shared<InterpreterPattern>(),
		std::make_shared<ObserverPattern>(),
		std::make_shared<StatePattern>(),
		std::make_shared<VisitorPattern>(),
		std::make_shared<StrategyPattern>(),
		std::make_shared<TemplateMethodPattern>(),
		std::make_shared<MementoPattern>(),
		std::make_shared<MediatorPattern>(),
		std::make_shared<IteratorPattern>(),

		std::make_shared<ProxyPattern>(),
		std::make_shared<AdapterPattern>(),
		std::make_shared<BridgePattern>(),
		std::make_shared<CompositePattern>(),
		std::make_shared<DecoratorPattern>(),
		std::make_shared<FacadePattern>(),
		std::make_shared<FlyweightPattern>()
	};


	for (auto& pattern : patterns)
	{
		std::cout << "\n" << pattern->get_info() << "\n";
		ret = pattern->run();
		if (ret != 0) break;
	}

	return ret;
}