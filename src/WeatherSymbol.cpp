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
#include <float.h>

using namespace std;

namespace {
typedef map<int, map<int, map< bool, weather_symbol::Code> > >  CodeTable;

CodeTable codeTable;

void initCodeTable() {
	using namespace weather_symbol;

	codeTable[Fog][0][false] = Fog;
	codeTable[Fog][1][false] = Fog;
	codeTable[Fog][2][false] = Fog;
	codeTable[Fog][0][true] = Fog;
	codeTable[Fog][1][true] = Fog;
	codeTable[Fog][2][true] = Fog;

	codeTable[Sun][0][false] = Sun;
	codeTable[Sun][1][false] = Sun;
	codeTable[Sun][2][false] = Sun;
	codeTable[Sun][0][true] = Sun;
	codeTable[Sun][1][true] = Sun;
	codeTable[Sun][2][true] = Sun;

	codeTable[LightCloud][0][false] = LightCloud;
	codeTable[LightCloud][1][false] = LightCloud;
	codeTable[LightCloud][2][false] = LightCloud;
	codeTable[LightCloud][0][true] = LightCloud;
	codeTable[LightCloud][1][true] = LightCloud;
	codeTable[LightCloud][2][true] = LightCloud;

	codeTable[PartlyCloud][0][false] = PartlyCloud;
	codeTable[PartlyCloud][1][false] = PartlyCloud;
	codeTable[PartlyCloud][2][false] = PartlyCloud;
	codeTable[PartlyCloud][0][true] = PartlyCloud;
	codeTable[PartlyCloud][1][true] = PartlyCloud;
	codeTable[PartlyCloud][2][true] = PartlyCloud;

	codeTable[Cloud][0][false] = Cloud;
	codeTable[Cloud][1][false] = Cloud;
	codeTable[Cloud][2][false] = Cloud;
	codeTable[Cloud][0][true] = Cloud;
	codeTable[Cloud][1][true] = Cloud;
	codeTable[Cloud][2][true] = Cloud;

	codeTable[Drizzle][0][false] = Drizzle;
	codeTable[Drizzle][1][false] = LightSleet;
	codeTable[Drizzle][2][false] = LightSnow;
	codeTable[Drizzle][0][true] = DrizzleThunder;
	codeTable[Drizzle][1][true] = LightSleetThunder;
	codeTable[Drizzle][2][true] = LightSnowThunder;

	codeTable[LightRain][0][false]= LightRain;
	codeTable[LightRain][1][false]= Sleet;
	codeTable[LightRain][2][false]= Snow;
	codeTable[LightRain][0][true]= LightRainThunder;
	codeTable[LightRain][1][true]= SleetThunder;
	codeTable[LightRain][2][true]= SnowThunder;

	codeTable[Rain][0][false] = Rain;
	codeTable[Rain][1][false] = HeavySleet;
	codeTable[Rain][2][false] = HeavySnow;
	codeTable[Rain][0][true] = RainThunder;
	codeTable[Rain][1][true] = HeavySleetThunder;
	codeTable[Rain][2][true] = HeavySnowThunder;

	codeTable[DrizzleSun][0][false] = DrizzleSun;
	codeTable[DrizzleSun][1][false] = LightSleetSun;
	codeTable[DrizzleSun][2][false] = LightSnowSun;
	codeTable[DrizzleSun][0][true] = DrizzleThunderSun;
	codeTable[DrizzleSun][1][true] = LightSleetThunderSun;
	codeTable[DrizzleSun][2][true] = LightSnowThunderSun;

	codeTable[LightRainSun][0][false] = LightRainSun;
	codeTable[LightRainSun][1][false] = SleetSun;
	codeTable[LightRainSun][2][false] = SnowSun;
	codeTable[LightRainSun][0][true] = LightRainThunderSun;
	codeTable[LightRainSun][1][true] = SleetSunThunder;
	codeTable[LightRainSun][2][true] = SnowSunThunder;

	codeTable[RainSun][0][false] = RainSun;
	codeTable[RainSun][1][false] = HeavySleetSun;
	codeTable[RainSun][2][false] = HeavySnowSun;
	codeTable[RainSun][0][true] = RainThunderSun;
	codeTable[RainSun][1][true] = HeavySleetThunderSun;
	codeTable[RainSun][2][true] = HeavySnowThunderSun;
}


}


namespace weather_symbol
{

WeatherData::
WeatherData()
: totalCloudCover( FLT_MAX ),
  lowCloudCover( FLT_MAX ),
  mediumCloudCover( FLT_MAX ),
  highCloudCover( FLT_MAX ),
  precipitation( FLT_MAX ),
  maxPrecipitation( FLT_MAX ),
  minPrecipitation( FLT_MAX ),
  thunder( false ),
  fog( false ),
  temperature( FLT_MAX ),
  wetBulbTemperature( FLT_MAX )
{
}


WeatherSymbol::WeatherSymbol(int hours, double cloud_cover_in_percent, double precipitation_in_mm)
	: precipitationPhase_( 0 ), thunder_( false ), fog_( false )
{
	setBaseCode_(hours, cloud_cover_in_percent, precipitation_in_mm);
}

WeatherSymbol::WeatherSymbol(int hours,
		                    double cloud_cover_in_percent, double precipitation_in_mm,
		                    double temperature_in_celsius, bool thunder, bool fog )
	: precipitationPhase_( 0 ), thunder_( false ), fog_( false )
{
	setBaseCode_(hours, cloud_cover_in_percent, precipitation_in_mm);
	WeatherData weatherData;
	weatherData.totalCloudCover = cloud_cover_in_percent;
	weatherData.precipitation = precipitation_in_mm;
	weatherData.thunder = thunder;
	weatherData.fog = fog;
	setDetailedCode_( hours, weatherData );
}

WeatherSymbol::WeatherSymbol( int hours, const WeatherData &weatherData )
	: precipitationPhase_( 0 ), thunder_( false ), fog_( false )
{
	setBaseCode_( hours, weatherData.totalCloudCover, weatherData.precipitation );
	setDetailedCode_( hours, weatherData );
}

WeatherSymbol::WeatherSymbol(int hours, Code base_code, const WeatherData &weather_data )
{
	CodeTable::const_iterator itBaseCode = codeTable.find( base_code );

	if( itBaseCode == codeTable.end() )
		throw range_error( name( base_code ) + " is not a base code.");

	setDetailedCode_( hours, weather_data );
}

WeatherSymbol::~WeatherSymbol()
{
}

Code WeatherSymbol::code() const
{
	Code ret = Error;

	if( codeTable.empty() )
		initCodeTable();

	if( fog_ )
		return Fog;

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

	ret = codeTable[ret][precipitationPhase_][thunder_];

	if( ret == Error )
		throw std::runtime_error("internal error: Add precipitation phase and thunder.");

	return ret;
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

void WeatherSymbol::setDetailedCode_( int hours, const WeatherData &wd )
{
	thunder_ = false;

	//Test if cloud cover is dominated by high clouds.
	if( wd.lowCloudCover <= 18.75 && wd.mediumCloudCover <= 18.75 && !wd.fog &&
		cloudCover_ == 3)
		cloudCover_ = 2;

	//If there is a chance for precipitation, set the cloud cover
	//to at least partly cloud.
	if( wd.maxPrecipitation != FLT_MAX &&
		cloudCover_ == 0 && wd.maxPrecipitation > 0 )
		cloudCover_ = 2;

	if( wd.fog && precipitationDroplets_ == 0 )
		fog_ = true;

	//Set the precipitation phase (rain, sleet, snow).
	//There is a choice between two temperature variables
	//with two different limits, wetbulb temperature and
	//air temperature. It is expected that the wetbulb temperature
	//give best result.
	if( precipitationDroplets_ > 0 ) {
		thunder_ = wd.thunder;
		if( wd.wetBulbTemperature != FLT_MAX  ) {
			if( wd.wetBulbTemperature <= 0.5 )
				precipitationPhase_ = 2;
			else if( wd.wetBulbTemperature <= 1.0 )
				precipitationPhase_ = 1;
			else
				precipitationPhase_ = 0;
		} else if( wd.temperature != FLT_MAX ) {
			if( wd.temperature <= 0.5 )
				precipitationPhase_ = 2;
			else if( wd.temperature <= 1.5 )
				precipitationPhase_ = 1;
			else
				precipitationPhase_ = 0;
		}
	}
}

void WeatherSymbol::setCloudiness_(double cloud_cover_in_percent)
{
	if ( cloud_cover_in_percent < 0 or cloud_cover_in_percent > 100 )
	{
		std::ostringstream errorMessage;
		errorMessage << "Invalid value for cloud cover: " << cloud_cover_in_percent;
		throw std::runtime_error(errorMessage.str());
	}

	if ( cloud_cover_in_percent <= 13 )
		cloudCover_ = 0;
	else if ( cloud_cover_in_percent <= 38 )
		cloudCover_ = 1;
	else if ( cloud_cover_in_percent <= 86 )
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

bool WeatherSymbol::operator < (const WeatherSymbol & other) const
{
	if ( cloudCover_ != other.cloudCover_ )
		return cloudCover_ < other.cloudCover_;

	return	precipitationDroplets_< other.precipitationDroplets_;
}

}
