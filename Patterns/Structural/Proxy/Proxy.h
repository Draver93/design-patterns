#pragma once

#include "../../Pattern.h"

class ProxyPattern : public Pattern {
public:
	std::string get_info();
	int run();
};