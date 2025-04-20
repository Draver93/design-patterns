#include "Singleton.h"

#include <queue>
#include <string>
#include <iostream>


namespace singleton_pattern {
	class LoggerSingleton {
	private:
		std::queue<std::string> m_messages;
		LoggerSingleton() {}
	public:
		void push_log(std::string log) {
			m_messages.push("Message " + std::to_string(m_messages.size()) + ": " + log);
		}
		std::string pop_log() {
			if (m_messages.empty()) return "";
			std::string result = m_messages.front();
			m_messages.pop();
			return result;
		}
		int length() {
			return (int)m_messages.size();
		}

	public:
		static LoggerSingleton* getInstance() {
			static LoggerSingleton instance;
			return &instance;
		}

	};
}


std::string SingletonPattern::get_info() {
	return "Name: Singleton.\nType: Creational.\nDescription: The Singleton ensures that only one instance of an object exists and provides global access to it.";
}

int SingletonPattern::run() {

	using namespace singleton_pattern;

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