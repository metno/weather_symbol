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


#ifndef WEATHERSYMBOLCODE_H_
#define WEATHERSYMBOLCODE_H_


namespace weather_symbol
{

/**
 * Available weather symbols
 */
enum Code
{
	Error = 0,
	Sun = 1,
	LightCloud = 2,
	PartlyCloud = 3,
	Cloud = 4,
	LightRainSun = 5,
	LightRainThunderSun = 6,
	SleetSun = 7,
	SnowSun = 8,
	LightRain = 9,
	Rain = 10,
	RainThunder = 11,
	Sleet = 12,
	Snow = 13,
	SnowThunder = 14,
	Fog = 15,
	SleetSunThunder = 20,
	SnowSunThunder = 21,
	LightRainThunder = 22,
	SleetThunder = 23,
	DrizzleThunderSun = 24,
	RainThunderSun = 25,
	LightSleetThunderSun = 26,
	HeavySleetThunderSun = 27,
	LightSnowThunderSun = 28,
	HeavySnowThunderSun = 29,
	DrizzleThunder = 30,
	LightSleetThunder = 31,
	HeavySleetThunder = 32,
	LightSnowThunder = 33,
	HeavySnowThunder = 34,
	DrizzleSun = 40,
	RainSun = 41,
	LightSleetSun = 42,
	HeavySleetSun = 43,
	LightSnowSun = 44,
	HeavySnowSun = 45,
	Drizzle = 46,
	LightSleet = 47,
	HeavySleet = 48,
	LightSnow = 49,
	HeavySnow = 50,

	// Modified symbols when sun is below horizon
	Dark_Sun = 101,
	Dark_LightCloud = 102,
	Dark_PartlyCloud = 103,
	Dark_LightRainSun = 105,
	Dark_LightRainThunderSun = 106,
	Dark_SleetSun = 107,
	Dark_SnowSun = 108,
	Dark_SleetSunThunder = 120,
	Dark_SnowSunThunder = 121,
	Dark_DrizzleThunderSun = 124,
	Dark_RainThunderSun = 125,
	Dark_LightSleetThunderSun = 126,
	Dark_HeavySleetThunderSun = 127,
	Dark_LightSnowThunderSun = 128,
	Dark_HeavySnowThunderSun = 129,
	Dark_DrizzleSun = 140,
	Dark_RainSun = 141,
	Dark_LightSleetSun = 142,
	Dark_HeavySleetSun = 143,
	Dark_LightSnowSun = 144,
	Dark_HeavySnowSun = 145
};

}

#endif /* WEATHERSYMBOLCODE_H_ */
