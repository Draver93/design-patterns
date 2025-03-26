#include "ChainOfResponsibility.h"


namespace cor_pattern {

	class Filter {
	protected:
		std::shared_ptr<Filter> next;
	public:
		std::shared_ptr<Filter> set_next(std::shared_ptr<Filter> next_filter) { next = next_filter; return next; }
		virtual std::string process(std::string data) {
			if (next) next->process(data);
			return data;
		}
	};

	class RotateFilter : public Filter {
	private:
		float rot_angle = 0;
	public:
		RotateFilter(float angle) : rot_angle(angle) { }
		std::string process(std::string data) override {

			std::string result = "rotated(" + std::to_string(rot_angle) + "){" + data + "}";
			if (next) return next->process(result);
			return result;
		}
	};

	class ScaleFilter : public Filter {
	private:
		float scale_factor = 0;
	public:
		ScaleFilter(float scale) : scale_factor(scale) { }
		std::string process(std::string data) override {

			std::string result = "scale(" + std::to_string(scale_factor) + "x){" + data + "}";
			if (next) return next->process(result);
			return result;
		}
	};

	class ResizeFilter : public Filter {
	private:
		int w = 0, h = 0;
	public:
		ResizeFilter(int width, int heigth) : w(width), h(heigth) { }
		std::string process(std::string data) override {

			std::string result = "resize(" + std::to_string(w) + "/" + std::to_string(h) + "x){" + data + "}";
			if (next) return next->process(result);
			else result;
		}
	};
}


std::string ChainOfResponsibilityPattern::get_info() {
	return "Name: Chain of Responsibility Pattern.\nType: Behavioral.\nDescription: Instead of handling multiple responsibilities in a single class, we create a chain of classes/handlers where each class handles only one responsibility.";
}

int ChainOfResponsibilityPattern::run() {

	using namespace cor_pattern;

	//Scale and rotate pipeline
	{
		std::shared_ptr<Filter> scale_filter = std::make_shared<ScaleFilter>(2.0f);
		std::shared_ptr<Filter> rotate_filter = std::make_shared<RotateFilter>(90.0f);

		std::shared_ptr<Filter> root_filter = rotate_filter;
		root_filter->set_next(scale_filter);
		std::cout << "\n" << "Rotate and scale pipeline: " << root_filter->process("Cat image") << std::endl;
	}

	//Scale resize and rotate pipeline
	{
		std::shared_ptr<Filter> scale_filter = std::make_shared<ScaleFilter>(2.0f);
		std::shared_ptr<Filter> resize_filter = std::make_shared<ResizeFilter>(1024, 768);
		std::shared_ptr<Filter> rotate_filter = std::make_shared<RotateFilter>(90.0f);

		std::shared_ptr<Filter> root_filter = scale_filter;
		root_filter->set_next(scale_filter)->set_next(resize_filter)->set_next(rotate_filter);
		std::cout << "\n" << "Scale resize and rotate pipeline: " << root_filter->process("Dog image") << std::endl;
	}

	return 0;
}