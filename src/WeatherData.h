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

#ifndef WEATHERDATA_H_
#define WEATHERDATA_H_

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

	/**
	 * "Missing" value for data
	 */
	static float undefined();
};

}

#endif /* WEATHERDATA_H_ */
