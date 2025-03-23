#pragma once

#include "../../Pattern.h"

class CompositePattern : public Pattern {
public:
	std::string get_info();
	int run();
};