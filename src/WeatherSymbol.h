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

#ifndef WEATHERSYMBOL_H_
#define WEATHERSYMBOL_H_

#include "WeatherSymbolCode.h"
#include <string>

namespace weather_symbol
{

struct WeatherSymbol
{
public:
	WeatherSymbol(Code code);
	WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm);
	WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon);
	WeatherSymbol(Code baseCode, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon);

	~WeatherSymbol();

	Code code() const;
	std::string name() const;

private:
	static Code getBaseCode_(int hours, double cloud_cover_in_percent, double precipitation_in_mm);
	static Code getDetailedCode_(Code base, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon);

	static Code getCloudiness_(double cloud_cover_in_percent);
	static Code getPrecipitation_(Code cloudiness, int hours, double precipitation_in_mm);

	Code code_;
};

inline bool operator == (WeatherSymbol s, Code code)
{
	return s.code() == code;
}

inline bool operator == (Code code, WeatherSymbol s)
{
	return s.code() == code;
}


}

#endif /* WEATHERSYMBOL_H_ */
