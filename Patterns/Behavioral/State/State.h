#pragma once

#include "../../Pattern.h"

class StatePattern : public Pattern {
public:
	std::string get_info();
	int run();
};