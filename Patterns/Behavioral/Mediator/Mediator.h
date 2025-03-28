#pragma once

#include "../../Pattern.h"

class MediatorPattern : public Pattern {
public:
	std::string get_info();
	int run();
};