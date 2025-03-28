#pragma once

#include "../../Pattern.h"

class MementoPattern : public Pattern {
public:
	std::string get_info();
	int run();
};