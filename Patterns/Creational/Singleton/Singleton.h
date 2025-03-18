#pragma once

#include "../../Pattern.h"


class SingletonPattern : public Pattern {
public:
	std::string get_info();
	int run();
};