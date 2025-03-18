#pragma once

#include "../../Pattern.h"

class FactoryMethod : public Pattern {
public:
	std::string get_info();
	int run();
};