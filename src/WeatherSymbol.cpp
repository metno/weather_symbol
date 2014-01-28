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
#include <sstream>
#include <stdexcept>


namespace weather_symbol
{


WeatherSymbol::WeatherSymbol(Code code) :
		code_(code)
{
}

WeatherSymbol::WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm)
{
	code_ = getBaseCode_(hours, cloud_cover_in_percent, precipitation_in_mm);
}

WeatherSymbol::WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon)
{
	Code base = getBaseCode_(hours, cloud_cover_in_percent, precipitation_in_mm);
	getDetailedCode_(base, temperature_in_celsius, thunder, fog_in_percent, sun_below_horizon);
}

WeatherSymbol::WeatherSymbol(Code baseCode, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon)
{
	getDetailedCode_(baseCode, temperature_in_celsius, thunder, fog_in_percent, sun_below_horizon);
}


WeatherSymbol::~WeatherSymbol()
{
}

Code WeatherSymbol::code() const
{
	return code_;
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
			(Sun_Dark, "Sun_Dark")
			(LightCloud_Dark, "LightCloud_Dark")
			(LightRainSun_Dark, "LightRainSun_Dark")
			(SleetSunThunder, "SleetSunThunder")
			(SnowSunThunder, "SnowSunThunder")
			(LightRainThunder, "LightRainThunder")
			(SleetThunder, "SleetThunder")
			(Drizzle, "Drizzle")
			(LightSnow, "LightSnow");


	NameMap::const_iterator find = names.find(code_);
	if ( find == names.end() )
		return "ERROR";
	return find->second;
}

Code WeatherSymbol::getBaseCode_(int hours, double cloud_cover_in_percent, double precipitation_in_mm)
{
	Code clouds = getCloudiness_(cloud_cover_in_percent);
	Code rain = getPrecipitation_(clouds, hours, precipitation_in_mm);
	return rain;
}

Code WeatherSymbol::getDetailedCode_(Code base, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon)
{
	return base;
}

Code WeatherSymbol::getCloudiness_(double cloud_cover_in_percent)
{
	if ( cloud_cover_in_percent < 0 or cloud_cover_in_percent > 100 )
	{
		std::ostringstream errorMessage;
		errorMessage << "Invalid value for cloud cover: " << cloud_cover_in_percent;
		throw std::runtime_error(errorMessage.str());
	}

	if ( cloud_cover_in_percent <= 18.75 )
		return Sun;
	else if ( cloud_cover_in_percent <= 43.75 )
		return LightCloud;
	else if ( cloud_cover_in_percent <= 81.25 )
		return PartlyCloud;
	else
		return Cloud;

	// should never happen:
	return Error;
}

Code WeatherSymbol::getPrecipitation_(Code cloudiness, int hours, double precipitation_in_mm)
{
	if ( hours == 6 )
	{
		if ( precipitation_in_mm < 0 or precipitation_in_mm > 500 )
		{
			std::ostringstream errorMessage;
			errorMessage << "Invalid value for precipitation: " << precipitation_in_mm << " mm";
			throw std::runtime_error(errorMessage.str());
		}

		switch ( cloudiness )
		{
		case PartlyCloud:
			if ( precipitation_in_mm >= 5 )
				return Rain;
			if ( precipitation_in_mm >= 0.8 )
				return LightRain;
			// fallthrough here!
		case LightCloud:
		case Sun:
			if ( precipitation_in_mm >= 0.4 )
				return LightRainSun;
			break;

		case Cloud:
			if ( precipitation_in_mm >= 5 )
				return Rain;
			if ( precipitation_in_mm >= 0.4 )
				return LightRain;
			break;
		}

		return cloudiness;
	}
	else
	{
		throw std::runtime_error("Invalid period for symbol: Only 6 hours is currently supported");
	}
}

}
