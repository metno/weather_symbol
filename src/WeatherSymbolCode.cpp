/*
    libweather_symbol

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

#include "WeatherSymbolCode.h"
#include <boost/assign/list_of.hpp>
#include <map>
#include <set>

namespace weather_symbol
{

std::string name(Code c)
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

	NameMap::const_iterator find = names.find(c);
	if ( find == names.end() )
		return "Unknown";
	return find->second;
}

bool hasPrecipitation(Code c)
{
	typedef std::set<Code> CodeSet;
	static const CodeSet precipitationFreeCodes = boost::assign::list_of
			(Error)
			(Sun)
			(LightCloud)
			(PartlyCloud)
			(Cloud)
			(Fog)
			(Dark_Sun)
			(Dark_LightCloud)
			(Dark_PartlyCloud)
	;
	return precipitationFreeCodes.find(c) == precipitationFreeCodes.end();
}

}
