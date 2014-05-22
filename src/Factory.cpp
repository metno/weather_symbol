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

#include "Factory.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <float.h>


namespace weather_symbol
{

Factory::Factory(unsigned hours) :
		hours_(hours),
		interpretor_(new Interpretor)
{
	if (hours <= 0 or hours > 6)
		throw std::runtime_error(
				"Symbol time range must be between 1 and 6 hours");
	initCodeTable_();
}

void Factory::initCodeTable_()
{
	using namespace weather_symbol;

	codeTable_[Fog][0][false] = Fog;
	codeTable_[Fog][1][false] = Fog;
	codeTable_[Fog][2][false] = Fog;
	codeTable_[Fog][0][true] = Fog;
	codeTable_[Fog][1][true] = Fog;
	codeTable_[Fog][2][true] = Fog;

	codeTable_[Sun][0][false] = Sun;
	codeTable_[Sun][1][false] = Sun;
	codeTable_[Sun][2][false] = Sun;
	codeTable_[Sun][0][true] = Sun;
	codeTable_[Sun][1][true] = Sun;
	codeTable_[Sun][2][true] = Sun;

	codeTable_[LightCloud][0][false] = LightCloud;
	codeTable_[LightCloud][1][false] = LightCloud;
	codeTable_[LightCloud][2][false] = LightCloud;
	codeTable_[LightCloud][0][true] = LightCloud;
	codeTable_[LightCloud][1][true] = LightCloud;
	codeTable_[LightCloud][2][true] = LightCloud;

	codeTable_[PartlyCloud][0][false] = PartlyCloud;
	codeTable_[PartlyCloud][1][false] = PartlyCloud;
	codeTable_[PartlyCloud][2][false] = PartlyCloud;
	codeTable_[PartlyCloud][0][true] = PartlyCloud;
	codeTable_[PartlyCloud][1][true] = PartlyCloud;
	codeTable_[PartlyCloud][2][true] = PartlyCloud;

	codeTable_[Cloud][0][false] = Cloud;
	codeTable_[Cloud][1][false] = Cloud;
	codeTable_[Cloud][2][false] = Cloud;
	codeTable_[Cloud][0][true] = Cloud;
	codeTable_[Cloud][1][true] = Cloud;
	codeTable_[Cloud][2][true] = Cloud;

	codeTable_[Drizzle][0][false] = Drizzle;
	codeTable_[Drizzle][1][false] = LightSleet;
	codeTable_[Drizzle][2][false] = LightSnow;
	codeTable_[Drizzle][0][true] = DrizzleThunder;
	codeTable_[Drizzle][1][true] = LightSleetThunder;
	codeTable_[Drizzle][2][true] = LightSnowThunder;

	codeTable_[LightRain][0][false] = LightRain;
	codeTable_[LightRain][1][false] = Sleet;
	codeTable_[LightRain][2][false] = Snow;
	codeTable_[LightRain][0][true] = LightRainThunder;
	codeTable_[LightRain][1][true] = SleetThunder;
	codeTable_[LightRain][2][true] = SnowThunder;

	codeTable_[Rain][0][false] = Rain;
	codeTable_[Rain][1][false] = HeavySleet;
	codeTable_[Rain][2][false] = HeavySnow;
	codeTable_[Rain][0][true] = RainThunder;
	codeTable_[Rain][1][true] = HeavySleetThunder;
	codeTable_[Rain][2][true] = HeavySnowThunder;

	codeTable_[DrizzleSun][0][false] = DrizzleSun;
	codeTable_[DrizzleSun][1][false] = LightSleetSun;
	codeTable_[DrizzleSun][2][false] = LightSnowSun;
	codeTable_[DrizzleSun][0][true] = DrizzleThunderSun;
	codeTable_[DrizzleSun][1][true] = LightSleetThunderSun;
	codeTable_[DrizzleSun][2][true] = LightSnowThunderSun;

	codeTable_[LightRainSun][0][false] = LightRainSun;
	codeTable_[LightRainSun][1][false] = SleetSun;
	codeTable_[LightRainSun][2][false] = SnowSun;
	codeTable_[LightRainSun][0][true] = LightRainThunderSun;
	codeTable_[LightRainSun][1][true] = SleetSunThunder;
	codeTable_[LightRainSun][2][true] = SnowSunThunder;

	codeTable_[RainSun][0][false] = RainSun;
	codeTable_[RainSun][1][false] = HeavySleetSun;
	codeTable_[RainSun][2][false] = HeavySnowSun;
	codeTable_[RainSun][0][true] = RainThunderSun;
	codeTable_[RainSun][1][true] = HeavySleetThunderSun;
	codeTable_[RainSun][2][true] = HeavySnowThunderSun;
}

Factory::~Factory()
{
}

Code Factory::getSymbol(double cloud_cover_in_percent,
		double precipitation_in_mm) const
{
	int clouds = getCloudiness_(cloud_cover_in_percent);
	int precipitation = getPrecipitation_(precipitation_in_mm);
	return getCode_(clouds, precipitation);
}

Code Factory::getSymbol(double cloud_cover_in_percent,
		double precipitation_in_mm, double temperature_in_celsius, bool thunder,
		bool fog) const
{
	int clouds = getCloudiness_(cloud_cover_in_percent);
	int precipitationDroplets = getPrecipitation_(precipitation_in_mm);
	int phase = 0;
	if ( precipitationDroplets > 0 )
		phase = getPrecipitationPhase_(temperature_in_celsius);
	bool isThunder = thunder and precipitationDroplets > 0;
	bool isFog = fog and precipitationDroplets == 0;

	return getCode_(clouds, precipitationDroplets, phase, isThunder, isFog);
}

Code Factory::getSymbol(Code base_code, const WeatherData & weather_data) const
{
	int cloudCover = 0;
	int precipitationDroplets = 0;
	switch( base_code )
	{
	case Sun: cloudCover = 0; break;
	case LightCloud: cloudCover = 1; break;
	case PartlyCloud: cloudCover = 2; break;
	case Cloud: cloudCover = 3; break;
	case Drizzle: cloudCover = 3; precipitationDroplets = 1; break;
	case LightRain: cloudCover = 3; precipitationDroplets = 2; break;
	case Rain: cloudCover = 3; precipitationDroplets = 3; break;
	case DrizzleSun: cloudCover = 2; precipitationDroplets = 1; break;
	case LightRainSun: cloudCover = 2; precipitationDroplets = 2; break;
	case RainSun: cloudCover = 2; precipitationDroplets = 3; break;
	default:
		throw std::range_error(interpretor_->name(base_code) + " - not a valid base code.");
	}

	return getCode_(weather_data, cloudCover, precipitationDroplets);
}

Code Factory::getSymbol(const WeatherData & weather_data) const
{
	int cloudCover = getCloudiness_(weather_data.totalCloudCover);
	int precipitationDroplets = getPrecipitation_(weather_data.precipitation);

	//Test if cloud cover is dominated by high clouds. If so: max clouds is reduced
	try
	{
		if( cloudCover == 3 and precipitationDroplets == 0 and
			not weather_data.fog and
			getCloudiness_(weather_data.lowCloudCover) == 0 and
			getCloudiness_(weather_data.mediumCloudCover) == 0
		  )
			cloudCover = 2;
	}
	catch ( std::exception & )
	{
		// ignored: This will happen if data were missing for low or medium cloud cover
	}
	//If there is a chance for precipitation, set the cloud cover to at least partly cloud.
	if( weather_data.maxPrecipitation != WeatherData::undefined() && weather_data.maxPrecipitation > 0.1 && cloudCover < 2 )
		cloudCover = 2;

	return getCode_(weather_data, cloudCover, precipitationDroplets);
}

namespace
{
template<typename T, typename Key, typename Entry>
const T & lookup(Key what, const Entry & where)
{
	typename Entry::const_iterator find = where.find(what);
	if ( find == where.end() )
		throw std::runtime_error("Error when looking converting symbol");
	return find->second;
}
}

Code Factory::getCode_(int cloudCover, int precipitationDroplets, int precipitationPhase, int thunder, bool fog) const
{
	Code ret = Error;

	if ( fog )
		return Fog;

	switch ( cloudCover )
	{
	case 0:
		ret = Sun;
		break;
	case 1:
		ret = LightCloud;
		break;
	case 2:
		ret = PartlyCloud;
		break;
	case 3:
		ret = Cloud;
		break;
	default:
		throw std::runtime_error("internal error: clouds");
	}

	if (ret == Cloud)
		switch ( precipitationDroplets )
		{
		case 0:
			break;
		case 1:
			ret = Drizzle;
			break;
		case 2:
			ret = LightRain;
			break;
		case 3:
			ret = Rain;
			break;
		default:
			throw std::runtime_error("internal error: precipitation");
		}
	else
		switch ( precipitationDroplets )
		{
		case 0:
			break;
		case 1:
			ret = DrizzleSun;
			break;
		case 2:
			ret = LightRainSun;
			break;
		case 3:
			ret = RainSun;
			break;
		default:
			throw std::runtime_error("internal error: precipitation");
		}

	const PhaseLookup & p = lookup<PhaseLookup>(ret, codeTable_);
	const ThunderLookup & t = lookup<ThunderLookup>(precipitationPhase, p);
	ret = lookup<weather_symbol::Code>(thunder, t);

	if (ret == Error)
		throw std::runtime_error(
				"internal error: Add precipitation phase and thunder.");

	return ret;
}

Code Factory::getCode_(const WeatherData & weather_data, int cloudCover, int precipitationDroplets) const
{
	int precipitationPhase = 0;
	if ( precipitationDroplets > 0 )
	{
		if ( weather_data.wetBulbTemperature != WeatherData::undefined() )
			precipitationPhase = getPrecipitationPhaseFromWetBulb_(weather_data.wetBulbTemperature);
		else
			precipitationPhase = getPrecipitationPhase_(weather_data.temperature);
	}
	bool thunder = weather_data.thunder and precipitationDroplets > 0;
	bool fog =  weather_data.fog and precipitationDroplets == 0;

	return getCode_(cloudCover, precipitationDroplets, precipitationPhase, thunder, fog);
}

int Factory::getCloudiness_(double cloud_cover_in_percent) const
{
	if (cloud_cover_in_percent < 0 or cloud_cover_in_percent > 100)
	{
		std::ostringstream errorMessage;
		errorMessage << "Invalid value for cloud cover: "
				<< cloud_cover_in_percent;
		throw std::runtime_error(errorMessage.str());
	}

	if (cloud_cover_in_percent <= 13)
		return 0;
	else if (cloud_cover_in_percent <= 38)
		return 1;
	else if (cloud_cover_in_percent <= 86)
		return 2;
	else
		return 3;
}

namespace
{
std::vector<double> precipitation_limits(unsigned hours)
{
	double limits_1h[3] =
	{ 0.1, 0.25, 0.95 };
	double limits_6h[3] =
	{ 0.5, 0.95, 4.95 };

	std::vector<double> ret;
	ret.reserve( 4 );
	ret.push_back(0);
	for (int i = 0; i < 3; ++i)
	{
		double low = limits_1h[i];
		double high = limits_6h[i];
		double step = (high - low) / 5;
		double value = (step * (hours - 1)) + low;
		ret.push_back(value);
	}
	return ret;
}
}

int Factory::getPrecipitation_(double precipitation_in_mm) const
{
	if (precipitation_in_mm < 0)
		throw std::runtime_error("Precipitation cannot be below 0");

	std::vector<double> limits = precipitation_limits(hours_);
	int droplets;
	for (droplets = 3; droplets >= 0; --droplets)
		if (precipitation_in_mm >= limits[droplets])
			break;

	return droplets;
}

int Factory::getPrecipitationPhase_(double temperature_in_celsius) const
{
	if( temperature_in_celsius <= 0.5 )
		return 2;
	else if( temperature_in_celsius <= 1.5 )
		return 1;

	return 0;
}

int Factory::getPrecipitationPhaseFromWetBulb_(double wet_bulb_temperature_in_celsius) const
{
	if( wet_bulb_temperature_in_celsius <= 0.5 )
		return 2;
	else if( wet_bulb_temperature_in_celsius <= 1.0 )
		return 1;

	return 0;
}

}
