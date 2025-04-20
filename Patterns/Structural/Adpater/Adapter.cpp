#include "Adapter.h"

#include <map>


namespace adapter_pattern {

	class WeatherV1 {
	public:
		virtual void set_region(const char* region) = 0;
		virtual std::string get_data() = 0;
	};

	class WeatherV2 {
	public:
		virtual void set_region(int region_id) = 0;
		virtual std::string get_weather() = 0;
	};


	class RegionWeather : public WeatherV1 {
	private:
		std::string m_region;
		std::map<const char*, std::string> m_region_data;
	public:
		RegionWeather() {
			m_region_data["eu_east"] = "Weather is Good)";
			m_region_data["eu_west"] = "Weather is Okey)";
			m_region_data["us_east"] = "Weather is Fine)";
			m_region_data["us_west"] = "Weather is Great)";
		}

		void set_region(const char* region) { m_region = region; };
		std::string get_data() {
			if (m_region_data.find(m_region.c_str()) != m_region_data.end())
				return "Weather API version 1: " + m_region_data[m_region.c_str()];
			return "Weather API version 1: Region data missing";
		};
	};

	class RegionWeatherAdapter : public WeatherV2 {
	private:
		std::shared_ptr<WeatherV1> m_adaptee;
		std::map<int, const char*> m_id_to_name_map;
	public:
		RegionWeatherAdapter(std::shared_ptr<WeatherV1> adaptee) 
			: m_adaptee(adaptee) {
			m_id_to_name_map[1] = "eu_east";
			m_id_to_name_map[2] = "eu_west";
			m_id_to_name_map[3] = "us_east";
			m_id_to_name_map[4] = "us_west";
		}
		void set_region(int region_id) { m_adaptee->set_region(m_id_to_name_map[region_id]); };
		std::string get_weather() {
			return m_adaptee->get_data();
		};

	};

	class RegionWeatherAdapterAdapter : public WeatherV1 {
	private:
		std::shared_ptr<WeatherV2> m_adaptee;
		std::map<std::string, int> m_name_to_id_map;
	public:
		RegionWeatherAdapterAdapter(std::shared_ptr<WeatherV2> adaptee) 
			: m_adaptee(adaptee) {
			m_name_to_id_map["eu_east"] = 1;
			m_name_to_id_map["eu_west"] = 2;
			m_name_to_id_map["us_east"] = 3;
			m_name_to_id_map["us_west"] = 4;
		}
		void set_region(const char* region) { m_adaptee->set_region(m_name_to_id_map[region]); };
		std::string get_data() {
			return m_adaptee->get_weather();
		};
	};
}


std::string AdapterPattern::get_info() {
	return "Name: Adapter.\nType: Structural.\nDescription: The Adapter pattern converts one interface into another, enabling compatibility without modifying existing business logic.";
}

int AdapterPattern::run() {

	using namespace adapter_pattern;

	// Original client code related to weather gathering
	{
		std::shared_ptr<WeatherV1> weather = std::make_shared<RegionWeather>();
		weather->set_region("eu_east");
		std::cout << "\n" << "Old client logic and interface result: " << weather->get_data() << std::endl;
	}

	// Modified client code interface but data still received from old interface through Adapter Class
	{
		std::shared_ptr<WeatherV2> weather = std::make_shared<RegionWeatherAdapter>(std::make_shared<RegionWeather>());
		weather->set_region(1);
		std::cout << "\n" << "New client logic old interface result: " << weather->get_weather() << std::endl;
	}

	// Original client code related to weather gathering new weather interface
	{
		std::shared_ptr<WeatherV1> weather = std::make_shared<RegionWeatherAdapterAdapter>(std::make_shared<RegionWeatherAdapter>(std::make_shared<RegionWeather>()));
		weather->set_region("eu_east");
		std::cout << "\n" << "Old client logic new interface result: " << weather->get_data() << std::endl;
	}
	return 0;
}