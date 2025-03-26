#include "Proxy.h"

#include <regex>


namespace proxy_pattern {

	class Storage {
	public:
		virtual void send_data(std::string) = 0;
	};

	class StorageProvider : public Storage {
	public:
		void send_data(std::string data) {
			std::cout << "POST: " << data << std::endl;
		};
	};

	class SanitizedStorageProvider : public Storage {
	private:
		std::shared_ptr<Storage> real_storage;
	public:
		SanitizedStorageProvider() {
			real_storage = std::make_shared<StorageProvider>();
		}

		void send_data(std::string data) {
			real_storage->send_data(std::regex_replace(data, std::regex("bad_data"), "good_data"));
		};
	};
}


std::string ProxyPattern::get_info() {
	return "Name: Proxy.\nType: Structural.\nDescription: The Proxy pattern creates an intermediary layer over an existing class, adding validation or access control while preserving the open-closed principle.";
}

int ProxyPattern::run() {

	using namespace proxy_pattern;

	// Example without Proxy
	{
		std::shared_ptr<Storage> storage = std::make_shared<StorageProvider>();

		std::cout << "\n" << "Example without sanitization" << std::endl;
		storage->send_data("good_data|good_data|bad_data|good_data|good_data");
	}

	// Example with Proxy
	// Same business logic for the client but with additional layer of validation.
	{
		std::shared_ptr<Storage> storage = std::make_shared<SanitizedStorageProvider>();

		std::cout << "\n" << "Example with sanitization through Proxy class" << std::endl;
		storage->send_data("good_data|good_data|bad_data|good_data|good_data");
	}

	return 0;
}