/*
 weather_symbol

 Copyright (C) 2014 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: post@met.no

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301, USA
 */

#include "WeatherSymbol.h"
#include <boost/assign/list_of.hpp>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <stdexcept>


namespace weather_symbol
{


WeatherSymbol::WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm)
{
	setBaseCode_(hours, cloud_cover_in_percent, precipitation_in_mm);
}

WeatherSymbol::WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon)
{
	setBaseCode_(hours, cloud_cover_in_percent, precipitation_in_mm);
	setDetailedCode_(temperature_in_celsius, thunder, fog_in_percent, sun_below_horizon);
}

WeatherSymbol::~WeatherSymbol()
{
}

Code WeatherSymbol::code() const
{
	Code ret = Error;
	switch( cloudCover_ )
	{
	case 0:
		ret = Sun; break;
	case 1:
		ret = LightCloud; break;
	case 2:
		ret = PartlyCloud; break;
	case 3:
		ret = Cloud; break;
	default:
		throw std::runtime_error("internal error: clouds");
	}
	if ( ret == Cloud )
		switch ( precipitationDroplets_ )
		{
		case 0:
			break;
		case 1:
			ret = Drizzle; break;
		case 2:
			ret = LightRain; break;
		case 3:
			ret = Rain; break;
		default:
			throw std::runtime_error("internal error: precipitation");
		}
	else
		switch ( precipitationDroplets_ )
		{
		case 0:
			break;
		case 1:
			ret = DrizzleSun; break;
		case 2:
			ret = LightRainSun; break;
		case 3:
			ret = RainSun; break;
		default:
			throw std::runtime_error("internal error: precipitation");
		}

	return ret;
}

std::string WeatherSymbol::name() const
{
	typedef std::map<Code, std::string> NameMap;
	static const NameMap names = boost::assign::map_list_of
			(Error, "Error")
			(Sun, "Sun")
			(LightCloud, "LightCloud")
			(PartlyCloud, "PartlyCloud")
			(Cloud, "Cloud")
			(LightRainSun, "LightRainSun")
			(LightRainThunderSun, "LightRainThunderSun")
			(SleetSun, "SleetSun")
			(SnowSun, "SnowSun")
			(LightRain, "LightRain")
			(Rain, "Rain")
			(RainThunder, "RainThunder")
			(Sleet, "Sleet")
			(Snow, "Snow")
			(SnowThunder, "SnowThunder")
			(Fog, "Fog")
			(SleetSunThunder, "SleetSunThunder")
			(SnowSunThunder, "SnowSunThunder")
			(LightRainThunder, "LightRainThunder")
			(SleetThunder, "SleetThunder")
			(DrizzleThunderSun, "DrizzleThunderSun")
			(RainThunderSun, "RainThunderSun")
			(LightSleetThunderSun, "LightSleetThunderSun")
			(HeavySleetThunderSun, "HeavySleetThunderSun")
			(LightSnowThunderSun, "LightSnowThunderSun")
			(HeavySnowThunderSun, "HeavySnowThunderSun")
			(DrizzleThunder, "DrizzleThunder")
			(LightSleetThunder, "LightSleetThunder")
			(HeavySleetThunder, "HeavySleetThunder")
			(LightSnowThunder, "LightSnowThunder")
			(HeavySnowThunder, "HeavySnowThunder")
			(DrizzleSun, "DrizzleSun")
			(RainSun, "RainSun")
			(LightSleetSun, "LightSleetSun")
			(HeavySleetSun, "HeavySleetSun")
			(LightSnowSun, "LightSnowSun")
			(HeavySnowSun, "HeavySnowSun")
			(Drizzle, "Drizzle")
			(LightSleet, "LightSleet")
			(HeavySleet, "HeavySleet")
			(LightSnow, "LightSnow")
			(HeavySnow, "HeavySnow")
			(Dark_Sun, "Sun")
			(Dark_LightCloud, "Dark_LightCloud")
			(Dark_PartlyCloud, "PartlyCloud")
			(Dark_LightRainSun, "LightRainSun")
			(Dark_LightRainThunderSun, "LightRainThunderSun")
			(Dark_SleetSun, "SleetSun")
			(Dark_SnowSun, "SnowSun")
			(Dark_LightRain, "LightRain")
			(Dark_SleetSunThunder, "SleetSunThunder")
			(Dark_SnowSunThunder, "SnowSunThunder")
			(Dark_LightRainThunder, "LightRainThunder")
			(Dark_DrizzleThunderSun, "DrizzleThunderSun")
			(Dark_RainThunderSun, "RainThunderSun")
			(Dark_LightSleetThunderSun, "LightSleetThunderSun")
			(Dark_HeavySleetThunderSun, "HeavySleetThunderSun")
			(Dark_LightSnowThunderSun, "LightSnowThunderSun")
			(Dark_HeavySnowThunderSun, "HeavySnowThunderSun")
			(Dark_DrizzleSun, "DrizzleSun")
			(Dark_RainSun, "RainSun")
			(Dark_LightSleetSun, "LightSleetSun")
			(Dark_HeavySleetSun, "HeavySleetSun")
			(Dark_LightSnowSun, "LightSnowSun")
			(Dark_HeavySnowSun, "HeavySnowSun")
	;

	NameMap::const_iterator find = names.find(code());
	if ( find == names.end() )
		return "Unknown";
	return find->second;
}

bool WeatherSymbol::hasPrecipitation() const
{
	return precipitationDroplets_ > 0;
}


void WeatherSymbol::setBaseCode_(int hours, double cloud_cover_in_percent, double precipitation_in_mm)
{
	setCloudiness_(cloud_cover_in_percent);
	setPrecipitation_(hours, precipitation_in_mm);
}

void WeatherSymbol::setDetailedCode_(double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon)
{
	// TODO
}

void WeatherSymbol::setCloudiness_(double cloud_cover_in_percent)
{
	if ( cloud_cover_in_percent < 0 or cloud_cover_in_percent > 100 )
	{
		std::ostringstream errorMessage;
		errorMessage << "Invalid value for cloud cover: " << cloud_cover_in_percent;
		throw std::runtime_error(errorMessage.str());
	}

	if ( cloud_cover_in_percent <= 18.75 )
		cloudCover_ = 0;
	else if ( cloud_cover_in_percent <= 43.75 )
		cloudCover_ = 1;
	else if ( cloud_cover_in_percent <= 81.25 )
		cloudCover_ = 2;
	else
		cloudCover_ = 3;
}

namespace
{
std::vector<double> precipitation_limits(unsigned hours)
{
	if ( hours <= 0 or hours > 6 )
		throw std::runtime_error("Symbol time range must be between 1 and 6 hours");

	double limits_1h[3] = {0.1, 0.25, 0.95};
	double limits_6h[3] = {0.5, 0.95, 4.95};

	std::vector<double> ret;
	ret.push_back(0);
	for ( int i = 0; i < 3; ++ i )
	{
		double low =  limits_1h[i];
		double high = limits_6h[i];
		double step = (high - low) / 5;
		double value = (step * (hours-1)) + low;
		ret.push_back(value);
	}
	return ret;
}
}

void WeatherSymbol::setPrecipitation_(int hours, double precipitation_in_mm)
{
	if ( precipitation_in_mm < 0 )
		throw std::runtime_error("Precipitation cannot be below 0");

	std::vector<double> limits = precipitation_limits(hours);
	int droplets;
	for ( droplets = 3; droplets >= 0; -- droplets )
		if ( precipitation_in_mm >= limits[droplets] )
			break;

	precipitationDroplets_ = droplets;
}

}
