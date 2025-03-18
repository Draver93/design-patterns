#include <iostream>
#include <vector>

#include "Creational/Singleton/Singleton.h"
#include "Creational/Prototype/Prototype.h"
#include "Creational/FactoryMethod/FactoryMethod.h"
#include "Creational/Builder/Builder.h"


int main() {
	int ret = 0;

	std::vector<std::shared_ptr<Pattern>> patterns;
	patterns.push_back(std::make_shared<SingletonPattern>());
	patterns.push_back(std::make_shared<PrototypePattern>());
	patterns.push_back(std::make_shared<FactoryMethodPattern>());
	patterns.push_back(std::make_shared<BuilderPattern>());

	for (auto& pattern : patterns) 
	{
		std::cout << "\n" << pattern->get_info() << std::endl;
		ret = pattern->run();
		if (ret != 0) break;
	}

	patterns.clear();
	return ret;
}