#pragma once

#include "../../Pattern.h"

class FacadePattern : public Pattern {
public:
	std::string get_info();
	int run();
};