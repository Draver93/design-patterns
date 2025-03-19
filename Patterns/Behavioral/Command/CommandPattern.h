#pragma once

#include "../../Pattern.h"

class CommandPattern : public Pattern {
public:
	std::string get_info();
	int run();
};