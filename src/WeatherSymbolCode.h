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

#include <string>

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
	Sun_Dark = 16,
	LightCloud_Dark = 17,
	LightRainSun_Dark = 18,
	SleetSunThunder = 20,
	SnowSunThunder = 21,
	LightRainThunder = 22,
	SleetThunder = 23,
	Drizzle = 24,
	LightSnow = 25
};

}

#endif /* WEATHERSYMBOLCODE_H_ */
