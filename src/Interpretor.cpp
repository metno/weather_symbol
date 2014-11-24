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

#include "Interpretor.h"
#include <boost/assign/list_of.hpp>
#include <utility>
#include <algorithm>

using namespace std;

namespace weather_symbol
{

namespace {

template < typename T>
T swapKeyVal( const  T &p  )
{
	T tmp;
	for( typename T::const_iterator it=p.begin(); it != p.end(); ++it )
		tmp.insert(make_pair( it->second, it->first ) );

	return tmp;
}

}

Interpretor::Interpretor()
{
	names = boost::assign::map_list_of
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
		(Dark_PartlyCloud, "Dark_PartlyCloud")
		(Dark_LightRainSun, "Dark_LightRainSun")
		(Dark_LightRainThunderSun, "Dark_LightRainThunderSun")
		(Dark_SleetSun, "Dark_SleetSun")
		(Dark_SnowSun, "Dark_SnowSun")
		(Dark_SleetSunThunder, "Dark_SleetSunThunder")
		(Dark_SnowSunThunder, "Dark_SnowSunThunder")
		(Dark_DrizzleThunderSun, "Dark_DrizzleThunderSun")
		(Dark_RainThunderSun, "Dark_RainThunderSun")
		(Dark_LightSleetThunderSun, "Dark_LightSleetThunderSun")
		(Dark_HeavySleetThunderSun, "Dark_HeavySleetThunderSun")
		(Dark_LightSnowThunderSun, "Dark_LightSnowThunderSun")
		(Dark_HeavySnowThunderSun, "Dark_HeavySnowThunderSun")
		(Dark_DrizzleSun, "Dark_DrizzleSun")
		(Dark_RainSun, "Dark_RainSun")
		(Dark_LightSleetSun, "Dark_LightSleetSun")
		(Dark_HeavySleetSun, "Dark_HeavySleetSun")
		(Dark_LightSnowSun, "Dark_LightSnowSun")
		(Dark_HeavySnowSun, "Dark_HeavySnowSun")
	;

	precipitationFreeCodes = boost::assign::list_of
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

	thunderCodes = boost::assign::list_of
		(LightRainThunderSun)
		(RainThunder)
		(SnowThunder)
		(SleetSunThunder)
		(SnowSunThunder)
		(LightRainThunder)
		(SleetThunder)
		(DrizzleThunderSun)
		(RainThunderSun)
		(LightSleetThunderSun)
		(HeavySleetThunderSun)
		(LightSnowThunderSun)
		(HeavySnowThunderSun)
		(DrizzleThunder)
		(LightSleetThunder)
		(HeavySleetThunder)
		(LightSnowThunder)
		(HeavySnowThunder)
		(Dark_LightRainThunderSun)
		(Dark_SleetSunThunder)
		(Dark_SnowSunThunder)
		(Dark_DrizzleThunderSun)
		(Dark_RainThunderSun)
		(Dark_LightSleetThunderSun)
		(Dark_HeavySleetThunderSun)
		(Dark_LightSnowThunderSun)
		(Dark_HeavySnowThunderSun)
		;

	thunderToNoThunderCodes = boost::assign::map_list_of
			(LightRainThunderSun, LightRainSun )
			(RainThunder, Rain)
			(SnowThunder, Snow)
			(SleetSunThunder, SleetSun )
			(SnowSunThunder, SnowSun)
			(LightRainThunder,LightRain)
			(SleetThunder, Sleet)
			(DrizzleThunderSun, DrizzleSun)
			(RainThunderSun, RainSun)
			(LightSleetThunderSun, LightSleetSun)
			(HeavySleetThunderSun, HeavySleetSun)
			(LightSnowThunderSun, LightSnowSun)
			(HeavySnowThunderSun, HeavySnowSun)
			(DrizzleThunder, Drizzle)
			(LightSleetThunder, LightSleet)
			(HeavySleetThunder, HeavySleet)
			(LightSnowThunder, LightSnow)
			(HeavySnowThunder, HeavySnow)
			(Dark_LightRainThunderSun, Dark_LightRainSun)
			(Dark_SleetSunThunder, Dark_SleetSun)
			(Dark_SnowSunThunder, Dark_SnowSun)
			(Dark_DrizzleThunderSun, Dark_DrizzleSun)
			(Dark_RainThunderSun, Dark_RainSun)
			(Dark_LightSleetThunderSun, Dark_LightSleetSun)
			(Dark_HeavySleetThunderSun, Dark_HeavySleetSun)
			(Dark_LightSnowThunderSun, Dark_LightSnowSun)
			(Dark_HeavySnowThunderSun, Dark_HeavySnowSun)
			;
	noThunderToThunderCodes = swapKeyVal( thunderToNoThunderCodes );

	sunBelowHorizonCodes = boost::assign::map_list_of
		(Error, Error)
		(Sun, Dark_Sun)
		(LightCloud, Dark_LightCloud)
		(PartlyCloud, Dark_PartlyCloud)
		(Cloud, Cloud)
		(LightRainSun, Dark_LightRainSun)
		(LightRainThunderSun, Dark_LightRainThunderSun)
		(SleetSun, Dark_SleetSun)
		(SnowSun, Dark_SnowSun)
		(Rain, Rain)
		(RainThunder, RainThunder)
		(Sleet, Sleet)
		(Snow, Snow)
		(SnowThunder, SnowThunder)
		(Fog, Fog)
		(SleetSunThunder, Dark_SleetSunThunder)
		(SnowSunThunder, Dark_SnowSunThunder)
		(SleetThunder, SleetThunder)
		(DrizzleThunderSun, Dark_DrizzleThunderSun)
		(RainThunderSun, Dark_RainThunderSun)
		(LightSleetThunderSun, Dark_LightSleetThunderSun)
		(HeavySleetThunderSun, Dark_HeavySleetThunderSun)
		(LightSnowThunderSun, Dark_LightSnowThunderSun)
		(HeavySnowThunderSun, Dark_HeavySnowThunderSun)
		(DrizzleThunder, DrizzleThunder)
		(LightSleetThunder, LightSleetThunder)
		(HeavySleetThunder, HeavySleetThunder)
		(LightSnowThunder, LightSnowThunder)
		(HeavySnowThunder, HeavySnowThunder)
		(DrizzleSun, Dark_DrizzleSun)
		(RainSun, Dark_RainSun)
		(LightSleetSun, Dark_LightSleetSun)
		(HeavySleetSun, Dark_HeavySleetSun)
		(LightSnowSun, Dark_LightSnowSun)
		(HeavySnowSun, Dark_HeavySnowSun)
		(Drizzle, Drizzle)
		(LightSleet, LightSleet)
		(HeavySleet, HeavySleet)
		(LightSnow, LightSnow)
		(HeavySnow, HeavySnow)
		(Dark_Sun, Dark_Sun)
		(Dark_LightCloud, Dark_LightCloud)
		(Dark_PartlyCloud, Dark_PartlyCloud)
		(Dark_LightRainSun, Dark_LightRainSun)
		(Dark_LightRainThunderSun, Dark_LightRainThunderSun)
		(Dark_SleetSun, Dark_SleetSun)
		(Dark_SnowSun, Dark_SnowSun)
		(Dark_SleetSunThunder, Dark_SleetSunThunder)
		(Dark_SnowSunThunder, Dark_SnowSunThunder)
		(Dark_DrizzleThunderSun, Dark_DrizzleThunderSun)
		(Dark_RainThunderSun, Dark_RainThunderSun)
		(Dark_LightSleetThunderSun, Dark_LightSleetThunderSun)
		(Dark_HeavySleetThunderSun, Dark_HeavySleetThunderSun)
		(Dark_LightSnowThunderSun, Dark_LightSnowThunderSun)
		(Dark_HeavySnowThunderSun, Dark_HeavySnowThunderSun)
		(Dark_DrizzleSun, Dark_DrizzleSun)
		(Dark_RainSun, Dark_RainSun)
		(Dark_LightSleetSun, Dark_LightSleetSun)
		(Dark_HeavySleetSun, Dark_HeavySleetSun)
		(Dark_LightSnowSun, Dark_LightSnowSun)
		(Dark_HeavySnowSun, Dark_HeavySnowSun)
		;


}

Interpretor::~Interpretor()
{
}

std::string Interpretor::name(Code c) const
{
	NameMap::const_iterator find = names.find(c);
	if ( find == names.end() )
		return "Unknown";
	return find->second;
}

bool Interpretor::hasPrecipitation(Code c) const
{
	return precipitationFreeCodes.find(c) == precipitationFreeCodes.end();
}

bool Interpretor::hasFog(Code c) const
{
	return c == Fog;
}

bool Interpretor::hasThunder( Code c ) const
{
	CodeSet::const_iterator find = thunderCodes.find(c);
	return find != thunderCodes.end();
}


Code Interpretor::turnOffThunder( Code c ) const
{
	SymbolMap::const_iterator find = thunderToNoThunderCodes.find(c);
	if( find != thunderToNoThunderCodes.end() ) return find->second;
	else return c;
}

/**
 * If the symbol has no thunder, return the same symbol with thunder.
 */
Code Interpretor::turnOnThunder( Code c ) const
{
	SymbolMap::const_iterator find = noThunderToThunderCodes.find( c );
	if( find != noThunderToThunderCodes.end() ) return find->second;
	else return c;
}


Code
Interpretor::codeIfSunBelowHorizon( Code  code ) const
{
	SymbolMap::const_iterator find = sunBelowHorizonCodes.find(code);
	if ( find == sunBelowHorizonCodes.end() )
		return Error;
	return find->second;
}

} /* namespace weather_symbol_ */
