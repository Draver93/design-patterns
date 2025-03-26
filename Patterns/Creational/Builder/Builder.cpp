#include "Builder.h"

#include <iostream>


namespace builder_pattern {

	class MediaWorkflow {
	public:
		MediaWorkflow(bool demuxer, bool decoder, bool processor, bool encoder, bool muxer) {
			std::string result_pipeline = "[IN] -> ";
			if (demuxer) result_pipeline += "[demuxer] -> ";
			if (decoder) result_pipeline += "[decoder] -> ";
			if (processor) result_pipeline += "[processor] -> ";
			if (encoder) result_pipeline += "[encoder] -> ";
			if (muxer) result_pipeline += "[muxer] -> ";
			result_pipeline += "[OUT]";

			std::cout << result_pipeline << "\n";
		}
	};

	class MediaWorkflowBuilder {
	private:
		bool use_demuxer = false, use_decoder = false, use_processor = false, use_encoder = false, use_muxer = false;
	public:
		MediaWorkflowBuilder* demuxer() {
			use_demuxer = true;
			return this;
		}
		MediaWorkflowBuilder* decoder() {
			use_decoder = true;
			return this;
		}
		MediaWorkflowBuilder* processor() {
			use_processor = true;
			return this;
		}
		MediaWorkflowBuilder* encoder() {
			use_encoder = true;
			return this;
		}
		MediaWorkflowBuilder* muxer() {
			use_muxer = true;
			return this;
		}
		std::shared_ptr<MediaWorkflow> build() {
			return std::make_shared<MediaWorkflow>(use_demuxer, use_decoder, use_processor, use_encoder, use_muxer);
		}
	};

	class MediaWorkflowDirector {
	public:
		void build_raw_media_extractor(std::shared_ptr<MediaWorkflowBuilder> builder) {
			builder->demuxer()->decoder();
		}
		void build_media_transcoder(std::shared_ptr<MediaWorkflowBuilder> builder) {
			builder->demuxer()
				->decoder()
				->encoder()
				->muxer();
		}
		void build_media_remuxer(std::shared_ptr<MediaWorkflowBuilder> builder) {
			builder->demuxer()->muxer();
		}
		void build_media_processor(std::shared_ptr<MediaWorkflowBuilder> builder) {
			builder->demuxer()
				->decoder()
				->processor()
				->encoder()
				->muxer();
		}
	};
}


std::string BuilderPattern::get_info() {
	return "Name: Builder.\nType: Creational.\nDescription: With this pattern, we separate the construction of an object from its representation. It allows for better handling of complex and flexible object creation without sacrificing readability.";
}

int BuilderPattern::run() {
	
	using namespace builder_pattern;

	// Transcode pipeline class can be describe as class MediaEngine(demuxer, decoder, processor, encoder, muxer)
	// But not all field are needed at all time. 

	std::cout << "\n" << "Here is an example of a flexible mediapipeline creation" << "\n";
	// We can still create any type of workflows like:
	// Full media processing
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		std::shared_ptr<MediaWorkflow> mw = mw_builder->demuxer()
			->decoder()
			->processor()
			->encoder()
			->muxer()->build();
	}
	// Or transcoding only
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		std::shared_ptr<MediaWorkflow> mw = mw_builder->demuxer()
			->decoder()
			->encoder()
			->muxer()->build();
	}
	// Or just remuxing
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		std::shared_ptr<MediaWorkflow> mw = mw_builder->demuxer()
			->muxer()->build();
	}
	// Or decoding to a raw
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		std::shared_ptr<MediaWorkflow> mw = mw_builder->demuxer()
			->decoder()->build();
	}

	//BUT at the same time we can use DIRECTOR
	std::cout << "\n" << "With DIRECTOR" << "\n";

	std::shared_ptr<MediaWorkflowDirector> mw_director = std::make_shared<MediaWorkflowDirector>();
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director->build_media_processor(mw_builder);
		mw_builder->build();
	}
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director->build_media_transcoder(mw_builder);
		mw_builder->build();
	}
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director->build_media_remuxer(mw_builder);
		mw_builder->build();
	}
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director->build_raw_media_extractor(mw_builder);
		mw_builder->build();
	}

	return 0;
}

