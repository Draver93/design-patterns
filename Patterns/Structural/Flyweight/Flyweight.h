#pragma once

#include "../../Pattern.h"

class FlyweightPattern : public Pattern {
public:
	std::string get_info();
	int run();
};