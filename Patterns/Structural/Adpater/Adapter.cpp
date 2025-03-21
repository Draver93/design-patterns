#include "Adapter.h"

#include <map>

class WeatherV1 {
public:
	virtual void set_region(std::string region) = 0;
	virtual std::string get_data() = 0;
};

class WeatherV2 {
public:
	virtual void set_region(int region_id) = 0;
	virtual std::string get_weather() = 0;
};


class RegionWeather : public WeatherV1 {
private:
	std::string _region;
	std::map<std::string, std::string> region_data;
public:
	RegionWeather() {
		region_data["eu_east"] = "Weather is Good)";
		region_data["eu_west"] = "Weather is Okey)";
		region_data["us_east"] = "Weather is Fine)";
		region_data["us_west"] = "Weather is Great)";
	}

	void set_region(std::string region) { _region = region; };
	std::string get_data() {
		if (region_data.find(_region) != region_data.end())
			return "Weather API version 1: " + region_data[_region];
		return "Weather API version 1: Region data missing";
	};
};

class RegionWeatherAdapter : public WeatherV2 {
private:
	std::shared_ptr<WeatherV1> _adaptee;
	std::map<int, std::string> region_id_to_name_map;
public:
	RegionWeatherAdapter(std::shared_ptr<WeatherV1> adaptee) : _adaptee(adaptee) {
		region_id_to_name_map[1] = "eu_east";
		region_id_to_name_map[2] = "eu_west";
		region_id_to_name_map[3] = "us_east";
		region_id_to_name_map[4] = "us_west";
	}
	void set_region(int region_id) { _adaptee->set_region(region_id_to_name_map[region_id]); };
	std::string get_weather() {
		return _adaptee->get_data();
	};

};

class RegionWeatherAdapterAdapter : public WeatherV1 {
private:
	std::shared_ptr<WeatherV2> _adaptee;
	std::map<std::string, int> region_name_to_id_map;
public:
	RegionWeatherAdapterAdapter(std::shared_ptr<WeatherV2> adaptee) : _adaptee(adaptee) {
		region_name_to_id_map["eu_east"] = 1;
		region_name_to_id_map["eu_west"] = 2;
		region_name_to_id_map["us_east"] = 3;
		region_name_to_id_map["us_west"] = 4;
	}
	void set_region(std::string region) { _adaptee->set_region(region_name_to_id_map[region]); };
	std::string get_data() {
		return _adaptee->get_weather();
	};

};


std::string AdapterPattern::get_info() {
	return "Name: Adapter.\nType: Structural.\nDescription: The Adapter pattern converts one interface into another, enabling compatibility without modifying existing business logic.";
}

int AdapterPattern::run() {

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