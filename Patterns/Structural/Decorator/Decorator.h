#pragma once

#include "../../Pattern.h"

class DecoratorPattern : public Pattern {
public:
	std::string get_info();
	int run();
};