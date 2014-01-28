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

#include <gtest/gtest.h>
#include <WeatherSymbol.h>

using namespace weather_symbol;

TEST(classificationTest, testRain)
{
	EXPECT_TRUE(WeatherSymbol(LightRainSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightRainThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SleetSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SnowSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightRain).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Rain).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(RainThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Sleet).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Snow).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SnowThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightRainSun_Dark).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SleetSunThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SnowSunThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightRainThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SleetThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Drizzle).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSnow).hasPrecipitation());

}

TEST(classificationTest, testNoRain)
{
	EXPECT_FALSE(WeatherSymbol(Error).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Sun).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(LightCloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(PartlyCloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Cloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Fog).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Sun_Dark).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(LightCloud_Dark).hasPrecipitation());
}
