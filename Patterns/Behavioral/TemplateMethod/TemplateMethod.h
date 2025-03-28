#pragma once

#include "../../Pattern.h"

class TemplateMethodPattern : public Pattern {
public:
	std::string get_info();
	int run();
};