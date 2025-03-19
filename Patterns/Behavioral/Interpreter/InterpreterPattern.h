#pragma once

#include "../../Pattern.h"

class InterpreterPattern : public Pattern {
public:
	std::string get_info();
	int run();
};