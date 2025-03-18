#pragma once

#include "../../Pattern.h"

class BuilderPattern : public Pattern {
public:
	std::string get_info();
	int run();
};