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

#include <boost/assign.hpp>
#include "WeatherSymbolBits.h"


namespace weather_symbol {
namespace bits {

namespace {
void initCodeTable();
void initNames();
void initPrecipFreeCodes();
void initThunderCodes();
void initSunBelowHorizonCodes();
}


NameMap names;
CodeSet precipitationFreeCodes;
CodeSet thunderCodes;
SymbolMap sunBelowHorizonCodes;
CodeTable codeTable;

void
init()
{
	if( ! codeTable.empty() )
		return;

	initCodeTable();
	initNames();
	initPrecipFreeCodes();
	initThunderCodes();
	initSunBelowHorizonCodes();
}

namespace {
void
initCodeTable()
{
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


void
initNames()
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
		(Dark_PartlyCloud, "PartlyCloud")
		(Dark_LightRainSun, "LightRainSun")
		(Dark_LightRainThunderSun, "LightRainThunderSun")
		(Dark_SleetSun, "SleetSun")
		(Dark_SnowSun, "SnowSun")
		(Dark_LightRain, "LightRain")
		(Dark_SleetSunThunder, "SleetSunThunder")
		(Dark_SnowSunThunder, "SnowSunThunder")
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

}

void
initPrecipFreeCodes()
{
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
}

void
initThunderCodes()
{
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
}

void
initSunBelowHorizonCodes()
{
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
		(LightRain, Dark_LightRain)
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
		(Dark_LightRain, Dark_LightRain)
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

}


}

}
