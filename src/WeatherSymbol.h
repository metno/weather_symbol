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
//#include <cstdint>

namespace weather_symbol
{

struct WeatherData {
	float totalCloudCover; ///The total cloud cover in percent.
	float lowCloudCover; ///Cloud cover of lower heights clouds in percent.
	float mediumCloudCover;///Cloud cover of medium heights clouds in percent.
	float highCloudCover;///Cloud cover of high heights clouds in percent.
	float precipitation; ///Precipitation in mm.
	float maxPrecipitation; ///Maximum expected precipitation in mm.
	float minPrecipitation; ///Minimum expected precipitation in mm.
	bool thunder;           ///There is a probability for thunder storm.
	bool fog;           	///There is a probability for fog.
	float temperature;        ///Temperature in celsius degree.
	float wetBulbTemperature; ///Wet bulb temperature in celsius degree.
	WeatherData();
};



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
	 * Simple instantiation.
	 *
	 * @param hours of accumulated precipitation, in hours. May not be above 6.
	 * @param cloud_cover_in_percent Amount of clouds in the sky, in range 0-100
	 * @param precipitation_in_mm Accumulated rainfall for the given number of hours, in millimeters
	 *
	 * @throws std::runtime_error if any parameters are out of bonds.
	 */
	WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm);

	/**
	 * Complex instantiation.
	 *
	 * @param hours of accumulated precipitation, in hours. May not be above 6.
	 * @param cloud_cover_in_percent Amount of clouds in the sky, in range 0-100
	 * @param precipitation_in_mm Accumulated rainfall for the given number of hours, in millimeters
	 * @param temperature_in_celsius Air temperature, for deciding precipitation phase (rain/sleet/snow)
	 * @param thunder Is there a chance of thunder?
	 * @param fog_in_percent Amount of fog, in range 0-100.
	 *
	 * @throws std::runtime_error if any parameters are out of bonds.
	 */
	WeatherSymbol( int hours,
			       double cloud_cover_in_percent, double precipitation_in_mm, double temperature_in_celsius,
			       bool thunder, bool fog );

	/**
	 * Instantiation from a base code symbol.
	 *
	 * A  base code is a symbol that is constructed from cloud cover and precipitation only,
	 * ie from the constructor WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm).
	 *
	 * @param hours of accumulated precipitation, in hours. May not be above 6.
	 * @param base_code generated from cloud cover and precipitation only.
	 * @param weather_data a struct containing all weather data, precipitation, cloud cover etc.
	 * @param sun_below_horizon Is the sun below the horizon? In some cases this will affect the weather symbol
	 *
	 * @throws std::runtime_error if any parameters are out of bonds.
	 * @see WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm).
	 */
	WeatherSymbol(int hours, Code base_code, const WeatherData &weather_data );

	/**
	 * Complex instatiation.
	 *
	 * @param hours of accumulated precipitation, in hours. May not be above 6.
	 * @param weather_data a struct containing all weather data, precipitation, cloud cover etc.
	 * @param sun_below_horizon Is the sun below the horizon? In some cases this will affect the weather symbol
	 *
	 * @throws std::runtime_error if any parameters are out of bonds.
	 */
	WeatherSymbol(int hours, const WeatherData &weather_data );


	~WeatherSymbol();

	/**
	 * The init function initialize internal global variables.
	 * Use it when the program has multiple threads. It must be
	 * called before any threads use the WeatherSymbol library.
	 */
	static void init();

	/**
	 * Get the numeric code for this object
	 */
	Code code() const;

	/**
	 * Does the given symbol mean rain or snow in any way?
	 */
	bool hasPrecipitation() const;

	/**
	 * Does the given symbol indicate fog?
	 */
	bool hasFog() const;

	/**
	 * Does the given symbol indicate thunder?
	 */
	bool hasThunder() const;


	bool operator < (const WeatherSymbol & other) const;

private:
	void setBaseCode_(int hours, double cloud_cover_in_percent, double precipitation_in_mm);
	void setBaseCodeFromCode_( weather_symbol::Code base_code );
	void setDetailedCode_( int hours,  const WeatherData &weatherData );
	void setCloudiness_(double cloud_cover_in_percent);
	void setPrecipitation_(int hours, double precipitation_in_mm);

//	std::int8_t cloudCover_; ///< 0-Sun, 1-LightCloud, 2-PartlyCloud, 3-Cloud
//	std::int8_t precipitationDroplets_; ///< 0-No rain, 1-Drizzle, 2-LightRain, 3-Rain
//	std::int8_t precipitationPhase_; ///< 0-rain, 1-sleet, 2-snow
	char cloudCover_; ///< 0-Sun, 1-LightCloud, 2-PartlyCloud, 3-Cloud
	char precipitationDroplets_; ///< 0-No rain, 1-Drizzle, 2-LightRain, 3-Rain
	char precipitationPhase_; ///< 0-rain, 1-sleet, 2-snow
	bool thunder_;    ///< If true there is a probability for thunder.
	bool fog_;        ///< If true there is a probability for fog.
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
