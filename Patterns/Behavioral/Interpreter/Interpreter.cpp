#include "Interpreter.h"

#include <map>
#include <vector>
#include <regex>


namespace interpreter_pattern {

	class Context {
	public:
		//Example data for evaluation
		bool debug = false;
		std::string name = "";
		std::string city = "";
		int age = 0;

		std::string input_data;
		Context(std::string data) : input_data(data) {}
		void evaluate(const std::map<std::string, std::string>& map) {
			if (map.find("age") != map.end()) age = std::stoi(map.at("age"));;
			if (map.find("name") != map.end()) name = map.at("name");
			if (map.find("city") != map.end()) city = map.at("city");
			if (map.find("debug") != map.end()) debug = map.at("debug") == "true";
		}
	};


	class Expression {
	public:
		virtual void interpret(std::shared_ptr<Context> ctx) = 0;
	};

	class DoubleDashExpression : public Expression {
	public:
		void interpret(std::shared_ptr<Context> ctx) {

			std::regex word_regex(R"--(--(\w+)\s+([\w\d]+))--");
			auto words_begin = std::sregex_iterator(ctx->input_data.begin(), ctx->input_data.end(), word_regex);
			auto words_end = std::sregex_iterator();

			std::map<std::string, std::string> data_map;
			for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			{
				std::smatch match = *i;
				data_map[match[1]] = match[2];
			}
			ctx->evaluate(data_map);
		};
	};

	class SingleDashExpression : public Expression {
	public:
		void interpret(std::shared_ptr<Context> ctx) {

			std::regex word_regex(R"(-(\w+)=(\w+))");
			auto words_begin = std::sregex_iterator(ctx->input_data.begin(), ctx->input_data.end(), word_regex);
			auto words_end = std::sregex_iterator();

			std::map<std::string, std::string> data_map;
			for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			{
				std::smatch match = *i;
				data_map[match[1]] = match[2];
			}
			ctx->evaluate(data_map);
		};
	};


	class ArgInterpreter {
		std::shared_ptr<Context> ctx;
		std::vector<std::shared_ptr<Expression>> expressions;
	public:
		ArgInterpreter(std::string data) : ctx(std::make_shared<Context>(data)) { }

		void add_expression(std::shared_ptr<Expression> exp) {
			expressions.push_back(exp);
		}

		std::shared_ptr<Context> interpret() {
			for (auto& expr : expressions) expr->interpret(ctx);
			return ctx;
		};
	};
}


std::string InterpreterPattern::get_info() {
	return "Name: Interpreter Pattern.\nType: Behavioral.\nDescription: The Interpreter pattern allows parsing and evaluating any kind of data into the desired representation.";
}

int InterpreterPattern::run() {

	using namespace interpreter_pattern;

	std::string arg_string = "--name John --age 30 -city=NewYork -debug=true";
	std::shared_ptr<ArgInterpreter> arg_interpreter = std::make_shared<ArgInterpreter>(arg_string);
	arg_interpreter->add_expression(std::make_shared<SingleDashExpression>());
	arg_interpreter->add_expression(std::make_shared<DoubleDashExpression>());

	std::shared_ptr<Context> ctx = arg_interpreter->interpret();

	//Now we can work with arguments directly by using evaluated data
	if(ctx->debug) {
		std::cout << "\n" << 
			"Name: " << ctx->name << "\n" <<
			"City: " << ctx->city << "\n" <<
			"Age: " << ctx->age << "\n";
	}

	return 0;
}