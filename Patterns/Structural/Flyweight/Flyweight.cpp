#include "Flyweight.h"

#include <vector>


namespace flyweight_pattern {

	class BottleLable {
	private:
		std::string m_image_path;
		std::string m_description;
		std::string m_product_composition;
	public:
		BottleLable() = delete;
		BottleLable(std::string image_path, std::string description, std::string product_composition)
			: m_image_path(image_path), m_description(description), m_product_composition(product_composition) {};
		const std::string& get_description() { return m_description; }
	};

	class Bottle {
	private:
		int m_uid;
		std::shared_ptr<BottleLable> m_label;
	protected:
		Bottle(int uid, std::shared_ptr<BottleLable> label) : m_uid(uid), m_label(label) {}
	public:
		const std::string& get_desc() { return m_label->get_description(); }
	};

	class PepsiBottle : public Bottle {
	public:
		PepsiBottle() = delete;
		PepsiBottle(int uid, std::shared_ptr<BottleLable> label) : Bottle(uid, label) {};
	};


	class Factory {
	public:
		virtual std::shared_ptr<Bottle> create_bottle() = 0;
	};

	class PepsiFactory : public Factory {
	private:
		std::shared_ptr<BottleLable> m_label;
		int m_bottle_cnt = 0;
	public:
		std::shared_ptr<Bottle> create_bottle() {
			if (!m_label) m_label = std::make_shared<BottleLable>("path/to/the/image", "delicious pepsi without sugar", "sugar,water,other");
			m_bottle_cnt++;
			return std::make_shared<PepsiBottle>(m_bottle_cnt, m_label);
		};
	};
}


std::string FlyweightPattern::get_info() {
	return "Name: Flyweight.\nType: Structural.\nDescription: The Flyweight pattern is a memory optimization technique that reduces redundancy by sharing common structures among a large number of similar objects.";
}

int FlyweightPattern::run() {

	using namespace flyweight_pattern;

	std::shared_ptr<Factory> pepsi_factory = std::make_shared<PepsiFactory>();

	std::cout << "\n" << "Creating bottles with unique ID and the same label pattern." << std::endl;
	std::vector<std::shared_ptr<Bottle>> bottles;
	for (int i = 0; i < 1000; i++) bottles.push_back(pepsi_factory->create_bottle());
	std::cout << "Probe in beginning: \n	" << "Description: " << bottles.at(0)->get_desc() << std::endl;
	std::cout << "Probe in middle: \n	" << "Description: " << bottles.at(bottles.size() / 2)->get_desc() << std::endl;
	std::cout << "Probe in end: \n	" << "Description: " << bottles.at(bottles.size() - 1)->get_desc() << std::endl;
	std::cout <<  bottles.size() << " bottles created with same label pattern." << std::endl;

	return 0;
}