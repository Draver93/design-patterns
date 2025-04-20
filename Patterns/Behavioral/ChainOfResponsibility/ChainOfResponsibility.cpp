#include "ChainOfResponsibility.h"


namespace cor_pattern {

	class Filter {
	protected:
		std::shared_ptr<Filter> m_next;
	public:
		std::shared_ptr<Filter> set_next(std::shared_ptr<Filter> next_filter) { m_next = next_filter; return m_next; }
		virtual std::string process(std::string data) {
			if (m_next) m_next->process(data);
			return data;
		}
	};

	class RotateFilter : public Filter {
	private:
		float m_rot_angle = 0;
	public:
		RotateFilter(float angle) : m_rot_angle(angle) { }
		std::string process(std::string data) override {

			std::string result = "rotated(" + std::to_string(m_rot_angle) + "){" + data + "}";
			if (m_next) return m_next->process(result);
			return result;
		}
	};

	class ScaleFilter : public Filter {
	private:
		float m_scale_factor = 0;
	public:
		ScaleFilter(float scale) : m_scale_factor(scale) { }
		std::string process(std::string data) override {

			std::string result = "scale(" + std::to_string(m_scale_factor) + "x){" + data + "}";
			if (m_next) return m_next->process(result);
			return result;
		}
	};

	class ResizeFilter : public Filter {
	private:
		int m_width = 0, m_height = 0;
	public:
		ResizeFilter(int width, int heigth) : m_width(width), m_height(heigth) { }
		std::string process(std::string data) override {

			std::string result = "resize(" + std::to_string(m_width) + "/" + std::to_string(m_height) + "x){" + data + "}";
			if (m_next) return m_next->process(result);
			else return result;
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