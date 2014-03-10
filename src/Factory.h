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

#ifndef WEATHERSYMBOLFACTORY_H_
#define WEATHERSYMBOLFACTORY_H_

#include "Code.h"
#include "Interpretor.h"
#include "WeatherData.h"
#include <boost/shared_ptr.hpp>
#include <map>

namespace weather_symbol
{


/**
 * Creates weather symbols from weather data. This factory may either be used
 * to create simple or complex symbols. Simple symbols only contain cloud
 * cover and precipitation droplets. Complex symbols also include
 * precipitation phase, fog and thunder.
 */
class Factory
{
public:
	/**
	 * Initialize factory, giving the time the symbol should be valid for, in
	 * hours. The hours value should be in range 1-6. An exception is thrown
	 * if the provided hours is out of range.
	 */
	explicit Factory(unsigned hours);

	~Factory();

	/**
	 * Get a simple symbol, with only cloud cover and precipitation droplets.
	 */
	Code getSymbol(double cloud_cover_in_percent, double precipitation_in_mm) const;

	/**
	 * Get a complex symbol, based on the input data.
	 */
	Code getSymbol(double cloud_cover_in_percent, double precipitation_in_mm, double temperature_in_celsius,
				       bool thunder, bool fog) const;

	/**
	 * Adapt a simple symbol, containing only clouds and precipitation
	 * droplets into a more complex symbol. If there is an inconsistency
	 * between the provided code, and the provided weather_data, the code takes
	 * precedence.
	 */
	Code getSymbol(Code base_code, const WeatherData &weather_data) const;

	/**
	 * Get a complex symbol, based on the input data.
	 */
	Code getSymbol(const WeatherData &weather_data) const;


	const boost::shared_ptr<Interpretor> interpretor() const
	{
		return interpretor_;
	}

private:
	unsigned hours_;
	boost::shared_ptr<Interpretor> interpretor_;

	typedef std::map<bool, weather_symbol::Code> ThunderLookup;
	typedef std::map<int, ThunderLookup> PhaseLookup;
	typedef std::map<Code, PhaseLookup> SimpleCodeLookup;
	SimpleCodeLookup codeTable_;



	/**
	 * Initialize code tables
	 */
	void initCodeTable_();

	/**
	 * Translate the various code elements to a Code
	 */
	Code getCode_(int cloudCover, int precipitationDroplets, int precipitationPhase = 0, int thunder = false, bool fog = false) const;

	/**
	 * Translate the various code elements to a Code, but let the given
	 * cloudCover and precipitationDroplets overrule the given weatherData.
	 */
	Code getCode_(const WeatherData & weatherData, int cloudCover, int precipitationDroplets ) const;

	/**
	 * Get degree of cloudiness, in range 0 (least) to 3 (most)
	 */
	int getCloudiness_(double cloud_cover_in_percent) const;

	/**
	 * Get precipitation droplets for symbol, 0 to 3.
	 */
	int getPrecipitation_(double precipitation_in_mm) const;

	/**
	 * Get phase of precipitation, 0 means rain, 1 means sleet, and 2 means snow
	 */
	int getPrecipitationPhase_(double temperature_in_celsius) const;

	/**
	 * Get phase of precipitation, 0 means rain, 1 means sleet, and 2 means
	 * snow. Note that input is _wet_bulb_ temperature.
	 */
	int getPrecipitationPhaseFromWetBulb_(double wet_bulb_temperature_in_celsius) const;
};

} /* namespace weather_symbol */
#endif /* WEATHERSYMBOLFACTORY_H_ */
