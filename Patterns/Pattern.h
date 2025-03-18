#pragma once

#include <string>

class Pattern {
public:
	virtual std::string get_info() = 0;
	virtual int run() = 0;
};