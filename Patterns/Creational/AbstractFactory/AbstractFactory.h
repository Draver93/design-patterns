#pragma once

#include "../../Pattern.h"

class AbstractFactoryPattern : public Pattern {
public:
	std::string get_info();
	int run();
};