#include "Mediator.h"

#include <queue>
#include <map>


namespace mediator_pattern {

	class Mediator {
	protected:
		std::map<const char*, std::queue<std::string>> m_data_queue;
	public:
		virtual ~Mediator() = default;  // Virtual destructor

		virtual std::string receive_data(const char* type) = 0;
		virtual void send_data(const char* type, const std::string& data) = 0;
	};

	class PipelineMediator : public Mediator {
	public:
		std::string receive_data(const char* type) {
			std::string request_data = "";
			if (!m_data_queue[type].empty()) {
				request_data = m_data_queue[type].front();
				m_data_queue[type].pop();
			}
			return request_data;
		};
		void send_data(const char* type, const std::string& data) {
			m_data_queue[type].push(data);
		};
	};


	class PipelineNode {
	protected:
		std::shared_ptr<Mediator> m_mediator;
	public:
		PipelineNode() = delete;
		PipelineNode(std::shared_ptr<Mediator> mediator) : m_mediator(mediator) {}

		virtual ~PipelineNode() = default;  // Virtual destructor
		virtual void update() = 0;
	};

	class Encoder : public PipelineNode {
	public:
		Encoder(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {}

		void update() {
			std::string data = m_mediator->receive_data("Encoder");
			if (data.empty()) return;

			data = "Encoded[" + data + "]";

			m_mediator->send_data("Writer", data);
		}
	};

	class Decoder : public PipelineNode {
	public:
		Decoder(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {}

		void update() {
			std::string data = m_mediator->receive_data("Decoder");
			if (data.empty()) return;

			data = "Decoded[" + data + "]";

			m_mediator->send_data("Encoder", data);
		}
	};

	class Reader : public PipelineNode {
	public:
		Reader(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {}

		void update() {
			m_mediator->send_data("Decoder", "Data");
		}
	};

	class Writer : public PipelineNode {
	private:
		int m_packet_id = 0;

	public:
		Writer(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {}

		void update() {
			std::string data = m_mediator->receive_data("Writer");
			if (data.empty()) return;

			std::cout << "Packet: " + data + "[" + std::to_string(m_packet_id) + "] has been written" << std::endl;
			m_packet_id++;
		}
	};
}


std::string MediatorPattern::get_info() {
	return "Name: Mediator Pattern.\nType: Behavioral.\nDescription: The Mediator pattern defines a centralized communication mechanism between objects, ensuring they interact independently without direct dependencies.";
}

int MediatorPattern::run() {

	using namespace mediator_pattern;

	std::shared_ptr<Mediator> mediator = std::make_shared<PipelineMediator>();

	Reader reader(mediator);
	Decoder decoder(mediator);
	Encoder encoder(mediator);
	Writer writer(mediator);

	std::cout << "\n" << "Example of multiple pipeline nodes working together through the mediator: " << std::endl;

	const int FRAME_CNT = 20;
	for (int i = 0; i < FRAME_CNT; i++) reader.update();
	for (int i = 0; i < FRAME_CNT; i++) decoder.update();
	for (int i = 0; i < FRAME_CNT; i++) encoder.update();
	for (int i = 0; i < FRAME_CNT; i++) writer.update();

	return 0;
}