#include "ObserverPattern.h"

#include <vector>
#include <queue>


class Processor {
public:
	virtual std::string update(std::string frame) = 0;
};

class FrameResize : public Processor {
public:
	std::string update(std::string frame) {
		return "Resized{" + frame + "}";
	};
};

class FrameRotate : public Processor {
public:
	std::string update(std::string frame) {
		return "Rotated{" + frame + "}";
	};
};


class Transcoder {
private:
	std::vector<std::shared_ptr<Processor>> prcessors;
	std::queue<std::string> input_data;
public:
	Transcoder(std::queue<std::string> data) : input_data(data) { }

	void add_processor(std::shared_ptr<Processor> proc) { prcessors.push_back(proc); }
	std::vector<std::string> run() {
		std::vector<std::string> output_data;

		while (!input_data.empty()) {
			//read and decode frame
			std::string frame = input_data.front();
			input_data.pop();

			//process frame
			for (auto& processor : prcessors) frame = processor->update(frame);

			//write frame
			output_data.push_back(frame);
		}

		return output_data;
	}
};


std::string ObserverPattern::get_info() {
	return "Name: Observer Pattern.\nType: Behavioral.\nDescription: The Observer pattern defines a one-to-many relationship between objects, ensuring that when the observable object changes, all its dependents are notified.";
}

int ObserverPattern::run() {

	std::queue<std::string> input_stream;
	input_stream.push("frame_1");
	input_stream.push("frame_2");
	input_stream.push("frame_3");

	std::shared_ptr<Transcoder> transcoder = std::make_shared<Transcoder>(input_stream);
	transcoder->add_processor(std::make_shared<FrameResize>());
	transcoder->add_processor(std::make_shared<FrameRotate>());

	std::vector<std::string> output_stream = transcoder->run();

	std::cout << "\n" << "Result of processing input stream using two subscrived processors: " << std::endl;
	for (auto& frame : output_stream) {
		std::cout << "Processed frame: " << frame << "\n";
	}

	return 0;
}