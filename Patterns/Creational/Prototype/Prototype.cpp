#include "Prototype.h"
#include <vector>


namespace prototype_pattern {

	class IncCatridge {
	private:
		float capacity;
	public:
		IncCatridge() : capacity(100) { }
		bool use(int cap_perc) {
			capacity -= cap_perc;
			capacity = capacity < 0 ? 0 : capacity;
			return capacity;
		}
		std::string status() {
			return "Current capacity is: " + std::to_string(capacity);
		}
	};

	class Printer {
	protected:
		std::shared_ptr<IncCatridge> catridge;
	public:
		void add_catridge(std::shared_ptr<IncCatridge> c) {
			catridge = c;
		}
		std::string get_catridge_status() {
			if (catridge) return catridge->status();
			else return "Catridge not found";
		}
		void print(std::string text) {
			if (catridge->use((int)text.length())) std::cout << text << "\n";
			else std::cout << "Error: Insufficient inc" << "\n";
		}
	public:
		virtual std::shared_ptr<Printer> clone() = 0;
	};


	class PrinterCannon : public Printer {

	private:
		int _id;

	public:
		PrinterCannon(int id) : _id(id) { }
		PrinterCannon(const PrinterCannon& other) {
			catridge = std::make_shared<IncCatridge>(*other.catridge);
		}
		std::shared_ptr<Printer> clone() {
			//deep clone
			std::shared_ptr<Printer> printer = std::make_shared<PrinterCannon>(*this);
			return printer;
		};
	};

	class PrinterHP : public Printer {
	private:
		std::string guid;
	public:
		PrinterHP(std::string id) : guid(id) {}
		PrinterHP(const PrinterHP& other) = default;

		std::shared_ptr<Printer> clone() {
			//shallow clone
			std::shared_ptr<Printer> printer = std::make_shared<PrinterHP>(*this);
			return printer;
		};
	};
}


std::string PrototypePattern::get_info() {
	return "Name: Prototype.\nType: Creational.\nDescription: The pattern provides a way to handle cloning instances of a class by delegating the cloning functionality to the class itself.";
}

int PrototypePattern::run() {

	using namespace prototype_pattern;

	std::cout << "\n" << "PrinterCannon with deep copy:" << "\n";

	// Create Cannon printer and add catridge to it
	std::shared_ptr<Printer> cannon_printer = std::make_shared<PrinterCannon>(std::rand());
	cannon_printer->add_catridge(std::make_shared<IncCatridge>());

	// Print and display catridge state after
	cannon_printer->print("Printed text by PrinterCannon");
	std::cout << "Original printer state: " << cannon_printer->get_catridge_status() << "\n";
	
	// Deep clone Cannon printer
	std::shared_ptr<Printer> cannon_printer_clone = cannon_printer->clone();
	std::cout << "Clone printer created!" << "\n";

	// Print usung original printer and display catridge state after
	cannon_printer->print("Printed text by PrinterCannon again");
	std::cout << "Original printer state: " << cannon_printer->get_catridge_status() << "\n";

	// Check status of cloned object
	std::cout << "Clone printer state: " << cannon_printer_clone->get_catridge_status() << "\n";

	////////////////////////////
	std::cout << "\n" << "PrinterHP with shalow copy: " << "\n";

	// Create PrinterHP printer and add catridge to it
	std::shared_ptr<Printer> hp_printer = std::make_shared<PrinterHP>(std::to_string(std::rand()));
	hp_printer->add_catridge(std::make_shared<IncCatridge>());

	// Print and display catridge state after
	hp_printer->print("Printed text by PrinterHP");
	std::cout << "Original printer state: " << hp_printer->get_catridge_status() << "\n";

	// Shalow clone PrinterHP printer
	std::shared_ptr<Printer> hp_printer_clone = hp_printer->clone();
	std::cout << "Clone printer created!" << "\n";

	// Print usung original printer and display catridge state after
	hp_printer->print("Printed text by PrinterHP");
	std::cout << "Original printer state: " << hp_printer->get_catridge_status() << "\n";

	// Check status of cloned object
	std::cout << "Clone printer state: " << hp_printer->get_catridge_status() << "\n";

	return 0;
}