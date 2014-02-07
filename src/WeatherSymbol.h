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

/**
 * A symbol, describing a weather situation. This object may in essence be instantiated in two ways:
 *
 * - Simple, using only cloud cover and precipitation amount.
 * - Complex, using several variables.
 */
struct WeatherSymbol
{
public:
	/**
	 * Simple instatiation.
	 *
	 * @param hours of accumulated precipitation, in hours. May not be above 6.
	 * @param cloud_cover_in_percent Amount of clouds in the sky, in range 0-100
	 * @param precipitation_in_mm Accumulated rainfall for the given number of hours, in millimeters
	 *
	 * @throws std::runtime_error if any parameters are out of bonds.
	 */
	WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm);

	/**
	 * Complex instatiation.
	 *
	 * @param hours of accumulated precipitation, in hours. May not be above 6.
	 * @param cloud_cover_in_percent Amount of clouds in the sky, in range 0-100
	 * @param precipitation_in_mm Accumulated rainfall for the given number of hours, in millimeters
	 * @param temperature_in_celsius Air temperature, for deciding precipitation phase (rain/sleet/snow)
	 * @param thunder Is there a chance of thunder?
	 * @param fog_in_percent Amount of fog, in range 0-100.
	 * @param sun_below_horizon Is the sun below the horizon? In some cases this will affect the weather symbol
	 *
	 * @throws std::runtime_error if any parameters are out of bonds.
	 */
	WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm, double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon);

	~WeatherSymbol();

	/**
	 * Get the numeric code for this object
	 */
	Code code() const;

	/**
	 * Get a name for this symbol
	 */
	std::string name() const;

	/**
	 * Does the given symbol mean rain or snow in any way?
	 */
	bool hasPrecipitation() const;


private:
	void setBaseCode_(int hours, double cloud_cover_in_percent, double precipitation_in_mm);
	void setDetailedCode_(double temperature_in_celsius, bool thunder, double fog_in_percent, bool sun_below_horizon);

	void setCloudiness_(double cloud_cover_in_percent);
	void setPrecipitation_(int hours, double precipitation_in_mm);

	short cloudCover_;
	short precipitationDroplets_;
};

inline bool operator == (const WeatherSymbol & s, Code code)
{
	return s.code() == code;
}

inline bool operator == (Code code, const WeatherSymbol & s)
{
	return s.code() == code;
}


}

#endif /* WEATHERSYMBOL_H_ */
