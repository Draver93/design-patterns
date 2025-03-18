#pragma once

#include "../../Pattern.h"

class PrototypePattern : public Pattern {
public:
	std::string get_info();
	int run();
};