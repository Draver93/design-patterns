#include <iostream>
#include <vector>

#include "Creational/Singleton/Singleton.h"


int main() {
	int ret = 0;

	std::vector<std::shared_ptr<Pattern>> patterns;
	patterns.push_back(std::make_shared<SingletonPattern>());

	for (auto& pattern : patterns) 
	{
		std::cout << pattern->get_info() << std::endl;
		ret = pattern->run();
		if (ret != 0) break;
	}

	patterns.clear();
	return ret;
}