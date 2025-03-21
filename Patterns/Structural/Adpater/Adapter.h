#pragma once

#include "../../Pattern.h"

class AdapterPattern : public Pattern {
public:
	std::string get_info();
	int run();
};