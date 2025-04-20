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
		bool m_demuxer = false, m_decoder = false, m_processor = false, m_encoder = false, m_muxer = false;
	public:
		MediaWorkflowBuilder* demuxer() {
			m_demuxer = true;
			return this;
		}
		MediaWorkflowBuilder* decoder() {
			m_decoder = true;
			return this;
		}
		MediaWorkflowBuilder* processor() {
			m_processor = true;
			return this;
		}
		MediaWorkflowBuilder* encoder() {
			m_encoder = true;
			return this;
		}
		MediaWorkflowBuilder* muxer() {
			m_muxer = true;
			return this;
		}
		std::shared_ptr<MediaWorkflow> build() {
			return std::make_shared<MediaWorkflow>(m_demuxer, m_decoder, m_processor, m_encoder, m_muxer);
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
		MediaWorkflowBuilder mw_builder = MediaWorkflowBuilder();
		std::shared_ptr<MediaWorkflow> mw = mw_builder.demuxer()
			->decoder()
			->processor()
			->encoder()
			->muxer()->build();
	}
	// Or transcoding only
	{
		MediaWorkflowBuilder mw_builder = MediaWorkflowBuilder();
		std::shared_ptr<MediaWorkflow> mw = mw_builder.demuxer()
			->decoder()
			->encoder()
			->muxer()->build();
	}
	// Or just remuxing
	{
		MediaWorkflowBuilder mw_builder = MediaWorkflowBuilder();
		std::shared_ptr<MediaWorkflow> mw = mw_builder.demuxer()
			->muxer()->build();
	}
	// Or decoding to a raw
	{
		MediaWorkflowBuilder mw_builder = MediaWorkflowBuilder();
		std::shared_ptr<MediaWorkflow> mw = mw_builder.demuxer()
			->decoder()->build();
	}

	//BUT at the same time we can use DIRECTOR
	std::cout << "\n" << "With DIRECTOR" << "\n";

	MediaWorkflowDirector mw_director = MediaWorkflowDirector();
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director.build_media_processor(mw_builder);
		mw_builder->build();
	}
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director.build_media_transcoder(mw_builder);
		mw_builder->build();
	}
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director.build_media_remuxer(mw_builder);
		mw_builder->build();
	}
	{
		std::shared_ptr<MediaWorkflowBuilder> mw_builder = std::make_shared<MediaWorkflowBuilder>();
		mw_director.build_raw_media_extractor(mw_builder);
		mw_builder->build();
	}

	return 0;
}

