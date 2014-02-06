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
//	EXPECT_TRUE(WeatherSymbol(LightRainSun).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(LightRainThunderSun).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(SleetSun).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(SnowSun).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(LightRain).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(Rain).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(RainThunder).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(Sleet).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(Snow).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(SnowThunder).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(Dark_LightRainSun).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(SleetSunThunder).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(SnowSunThunder).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(LightRainThunder).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(SleetThunder).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(Drizzle).hasPrecipitation());
//	EXPECT_TRUE(WeatherSymbol(LightSnow).hasPrecipitation());

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
	EXPECT_TRUE(WeatherSymbol(SleetSunThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SnowSunThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightRainThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(SleetThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(DrizzleThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(RainThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSleetThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySleetThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSnowThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySnowThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(DrizzleThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSleetThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySleetThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSnowThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySnowThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(DrizzleSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(RainSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSleetSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySleetSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSnowSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySnowSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Drizzle).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSleet).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySleet).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(LightSnow).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(HeavySnow).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightRainSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightRainThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_SleetSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_SnowSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightRain).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_SleetSunThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_SnowSunThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightRainThunder).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_DrizzleThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_RainThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightSleetThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_HeavySleetThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightSnowThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_HeavySnowThunderSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_DrizzleSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_RainSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightSleetSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_HeavySleetSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_LightSnowSun).hasPrecipitation());
	EXPECT_TRUE(WeatherSymbol(Dark_HeavySnowSun).hasPrecipitation());
}

TEST(classificationTest, testNoRain)
{
//	EXPECT_FALSE(WeatherSymbol(Error).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(Sun).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(LightCloud).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(PartlyCloud).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(Cloud).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(Fog).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(Dark_Sun).hasPrecipitation());
//	EXPECT_FALSE(WeatherSymbol(Dark_LightCloud).hasPrecipitation());

	EXPECT_FALSE(WeatherSymbol(Error).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Sun).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(LightCloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(PartlyCloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Cloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Fog).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Dark_Sun).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Dark_LightCloud).hasPrecipitation());
	EXPECT_FALSE(WeatherSymbol(Dark_PartlyCloud).hasPrecipitation());
}
