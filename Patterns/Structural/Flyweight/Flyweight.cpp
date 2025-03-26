#include "Flyweight.h"

#include <vector>


namespace flyweight_pattern {

	class BottleLable {
	private:
		std::string image_path;
		std::string description;
		std::string product_composition;
	public:
		BottleLable() = delete;
		BottleLable(std::string path, std::string desc, std::string compose) : image_path(path), description(desc), product_composition(compose) {};
		const std::string& get_description() { return description; }
	};

	class Bottle {
	private:
		int _uid;
		std::shared_ptr<BottleLable> _label;
	protected:
		Bottle(int uid, std::shared_ptr<BottleLable> label) : _uid(uid), _label(label) {}
	public:
		const std::string& get_desc() { return _label->get_description(); }
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
		std::shared_ptr<BottleLable> pepsi_label;
		int bottle_cnt = 0;
	public:
		std::shared_ptr<Bottle> create_bottle() {
			if (!pepsi_label) pepsi_label = std::make_shared<BottleLable>("path/to/the/image", "delicious pepsi without sugar", "sugar,water,other");
			bottle_cnt++;
			return std::make_shared<PepsiBottle>(bottle_cnt, pepsi_label);
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