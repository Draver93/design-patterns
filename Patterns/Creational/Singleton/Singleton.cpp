#include "Singleton.h"

#include <queue>
#include <string>
#include <iostream>


class LoggerSingleton {
private:
	std::queue<std::string> messages;
	LoggerSingleton() {}
public:
	void push_log(std::string log) {
		messages.push("Message " + std::to_string(messages.size()) + ": " + log);
	}
	std::string pop_log() {
		if (messages.empty()) return "";
		std::string result = messages.front();
		messages.pop();
		return result;
	}
	int length() {
		return messages.size();
	}

private:
	static LoggerSingleton* instance;
public:
	static LoggerSingleton* getInstance() {
		if (!instance) instance = new LoggerSingleton();
		return instance;
	}

};
LoggerSingleton* LoggerSingleton::instance = nullptr;


std::string SingletonPattern::get_info() {
	return "Name: Singleton.\nType: Creational.\nDescription: The Singleton ensures that only one instance of an object exists and provides global access to it.";
}

int SingletonPattern::run() {

	// First scope
	{
		LoggerSingleton* logger = LoggerSingleton::getInstance();
		logger->push_log("loggin from the first scope.");
		logger->push_log("loggin from the first scope again.");
	}

	// Second scope
	{
		LoggerSingleton* logger = LoggerSingleton::getInstance();
		logger->push_log("loggin from the second scope.");
		logger->push_log("loggin from the second scope again.");
	}

	// Third scope
	{
		LoggerSingleton* logger = LoggerSingleton::getInstance();
		while (logger->length()) std::cout << logger->pop_log() << "\n";
	}

	return 0;
}