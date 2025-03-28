#include "Mediator.h"

#include <queue>
#include <map>


namespace mediator_pattern {

	class Mediator {
	protected:
		std::map<std::string, std::queue<std::string>> data_queue;
	public:
		virtual ~Mediator() = default;  // Virtual destructor

		virtual std::string receive_data(std::string type) = 0;
		virtual void send_data(std::string type, std::string data) = 0;
	};

	class PipelineMediator : public Mediator {
	public:
		std::string receive_data(std::string type) {
			std::string request_data = "";
			if (!data_queue[type].empty()) {
				request_data = data_queue[type].front();
				data_queue[type].pop();
			}
			return request_data;
		};
		void send_data(std::string type, std::string data) {
			data_queue[type].push(data);
		};
	};


	class PipelineNode {
	protected:
		std::shared_ptr<Mediator> _mediator;
	public:
		PipelineNode() = delete;
		PipelineNode(std::shared_ptr<Mediator> mediator) : _mediator(mediator) {}

		virtual ~PipelineNode() = default;  // Virtual destructor
		virtual void update() = 0;
	};

	class Encoder : public PipelineNode {
	public:
		Encoder(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {
		}
	public:
		void update() {
			std::string data = _mediator->receive_data("Encoder");
			if (data.empty()) return;

			data = "Encoded[" + data + "]";

			_mediator->send_data("Writer", data);
		}
	};

	class Decoder : public PipelineNode {
	public:
		Decoder(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {
		}

		void update() {
			std::string data = _mediator->receive_data("Decoder");
			if (data.empty()) return;

			data = "Decoded[" + data + "]";

			_mediator->send_data("Encoder", data);
		}
	};

	class Reader : public PipelineNode {
	public:
		Reader(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {
		}
		void update() {
			_mediator->send_data("Decoder", "Data");
		}
	};

	class Writer : public PipelineNode {
	private:
		int packet_id = 0;
	public:
		Writer(std::shared_ptr<Mediator> mediator) : PipelineNode(mediator) {
		}
		void update() {
			std::string data = _mediator->receive_data("Writer");
			if (data.empty()) return;

			std::cout << "Packet: " + data + "[" + std::to_string(packet_id) + "] has been written" << std::endl;
			packet_id++;
		}
	};
}


std::string MediatorPattern::get_info() {
	return "Name: Mediator Pattern.\nType: Behavioral.\nDescription: The Mediator pattern defines a centralized communication mechanism between objects, ensuring they interact independently without direct dependencies.";
}

int MediatorPattern::run() {

	using namespace mediator_pattern;

	std::shared_ptr<Mediator> mediator = std::make_shared<PipelineMediator>();

	std::shared_ptr<PipelineNode> reader = std::make_shared<Reader>(mediator);
	std::shared_ptr<PipelineNode> decoder = std::make_shared<Decoder>(mediator);
	std::shared_ptr<PipelineNode> encoder = std::make_shared<Encoder>(mediator);
	std::shared_ptr<PipelineNode> writer = std::make_shared<Writer>(mediator);

	std::cout << "\n" << "Example of multiple pipeline nodes working together through the mediator: " << std::endl;

	const int FRAME_CNT = 20;
	for (int i = 0; i < FRAME_CNT; i++) reader->update();
	for (int i = 0; i < FRAME_CNT; i++) decoder->update();
	for (int i = 0; i < FRAME_CNT; i++) encoder->update();
	for (int i = 0; i < FRAME_CNT; i++) writer->update();

	return 0;
}