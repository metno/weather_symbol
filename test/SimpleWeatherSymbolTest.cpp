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
#include <stdexcept>

using namespace weather_symbol;

TEST(SimpleWeatherSymbolTest, tooCloudy)
{
	ASSERT_THROW(WeatherSymbol(6, 110, 0.1), std::runtime_error);
	//	ASSERT_EQ(Error, WeatherSymbol(6, 6, 110, 0.1));
}

TEST(SimpleWeatherSymbolTest, negativePrecipitation)
{
	ASSERT_THROW(WeatherSymbol(6, 10, -0.1), std::runtime_error);
	//ASSERT_EQ(Error, WeatherSymbol(6, 10, -0.1));
}

TEST(SimpleWeatherSymbolTest, sunNoRain)
{
	ASSERT_EQ(Sun, WeatherSymbol(6, 10, 0.1));
}

TEST(SimpleWeatherSymbolTest, sunRain)
{
	ASSERT_EQ(DrizzleSun, WeatherSymbol(6, 10, 0.5));
}

TEST(SimpleWeatherSymbolTest, lightCloundNoRain)
{
	ASSERT_EQ(LightCloud, WeatherSymbol(6, 30, 0));
}

TEST(SimpleWeatherSymbolTest, lightCloudRain)
{
	ASSERT_EQ(RainSun, WeatherSymbol(6, 30, 45));
}

TEST(SimpleWeatherSymbolTest, partlyCloudNoRain)
{
	ASSERT_EQ(PartlyCloud, WeatherSymbol(6, 50, 0.1));
}

TEST(SimpleWeatherSymbolTest, partlyCloudLittleRain)
{
	ASSERT_EQ(DrizzleSun, WeatherSymbol(6, 50, 0.5));
}

TEST(SimpleWeatherSymbolTest, partlyCloudSomeRain)
{
	ASSERT_EQ(LightRainSun, WeatherSymbol(6, 50, 0.96));
}

TEST(SimpleWeatherSymbolTest, partlyCloudHeavyRain)
{
	ASSERT_EQ(RainSun, WeatherSymbol(6, 50, 7));
}

TEST(SimpleWeatherSymbolTest, cloudyNoRain)
{
	ASSERT_EQ(Cloud, WeatherSymbol(6, 90, 0.1));
}

TEST(SimpleWeatherSymbolTest, cloudySomeRain)
{
	ASSERT_EQ(LightRain, WeatherSymbol(6, 90, 0.96));
}

TEST(SimpleWeatherSymbolTest, cloudyHeavyRain)
{
	ASSERT_EQ(Rain, WeatherSymbol(6, 90, 6));
}

TEST(SimpleWeatherSymbolTest, dominatedByHighClouds )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 0;
	wd.mediumCloudCover = 18;
	wd.lowCloudCover = 18;
	ASSERT_EQ(PartlyCloud, WeatherSymbol( 6, wd ));
}

TEST(SimpleWeatherSymbolTest, sunButMaybeRain )
{
	WeatherData wd;
	wd.totalCloudCover = 10;
	wd.precipitation = 0;
	wd.maxPrecipitation = 1;
	ASSERT_EQ(PartlyCloud, WeatherSymbol( 6, wd ));
}

TEST(SimpleWeatherSymbolTest, wetBulbTemperaturePrecipPhase )
{
	WeatherData wd;
	wd.totalCloudCover = 90;

	wd.precipitation = 5;
	wd.temperature = 0.5;
	ASSERT_EQ(HeavySnow, WeatherSymbol(6, wd) ) << "HeavySnow";

	wd.temperature = 0.6;
	ASSERT_EQ(HeavySleet, WeatherSymbol(6, wd) ) << "HeavySleet";

	wd.temperature = 1.5;
	ASSERT_EQ(HeavySleet, WeatherSymbol(6, wd) ) << "HeavySleet";

	wd.temperature = 1.6;
	ASSERT_EQ(Rain, WeatherSymbol(6, wd) ) << "Rain";
}

TEST(SimpleWeatherSymbolTest, airTemperaturePrecipPhase )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 5;

	wd.wetBulbTemperature = 0.5;
	ASSERT_EQ(HeavySnow, WeatherSymbol(6, wd) ) << "HeavySnow";

	wd.wetBulbTemperature = 0.6;
	ASSERT_EQ(HeavySleet, WeatherSymbol(6, wd) ) << "HeavySleet";

	wd.wetBulbTemperature = 1.0;
	ASSERT_EQ(HeavySleet, WeatherSymbol(6, wd) ) << "HeavySleet";

	wd.wetBulbTemperature = 1.1;
	ASSERT_EQ(Rain, WeatherSymbol(6, wd) ) << "Rain";
}


TEST(SimpleWeatherSymbolTest, thunderStorm )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 5;
	wd.thunder = true;

	wd.wetBulbTemperature = 0.5;
	ASSERT_EQ(HeavySnowThunder, WeatherSymbol(6, wd) ) << "HeavySnowThunder";

	wd.wetBulbTemperature = 0.6;
	ASSERT_EQ(HeavySleetThunder, WeatherSymbol(6, wd) ) << "HeavySleetThunder";

	wd.wetBulbTemperature = 1.0;
	ASSERT_EQ(HeavySleetThunder, WeatherSymbol(6, wd) ) << "HeavySleetThunder";

	wd.wetBulbTemperature = 1.1;
	ASSERT_EQ(RainThunder, WeatherSymbol(6, wd) ) << "RainThunder";
}

TEST(SimpleWeatherSymbolTest, fog )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 0.4;
	wd.fog = true;

	ASSERT_EQ(Fog, WeatherSymbol(6, wd) ) << "Fog";

	wd.precipitation = 0.5;
	ASSERT_EQ(Drizzle, WeatherSymbol(6, wd) ) << "Drizzle";
}


TEST(SimpleWeatherSymbolTest, sunBelowHorizon )
{
	ASSERT_EQ(codeIfSunBelowHorizon( Error ), Error );
	ASSERT_EQ(codeIfSunBelowHorizon(Sun) , Dark_Sun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightCloud), Dark_LightCloud);
	ASSERT_EQ(codeIfSunBelowHorizon(PartlyCloud), Dark_PartlyCloud);
	ASSERT_EQ(codeIfSunBelowHorizon(Cloud), Cloud);
	ASSERT_EQ(codeIfSunBelowHorizon(LightRainSun), Dark_LightRainSun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightRainThunderSun), Dark_LightRainThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(SleetSun), Dark_SleetSun);
	ASSERT_EQ(codeIfSunBelowHorizon(SnowSun), Dark_SnowSun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightRain), Dark_LightRain);
	ASSERT_EQ(codeIfSunBelowHorizon(Rain), Rain);
	ASSERT_EQ(codeIfSunBelowHorizon(RainThunder), RainThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(Sleet), Sleet);
	ASSERT_EQ(codeIfSunBelowHorizon(Snow), Snow);
	ASSERT_EQ(codeIfSunBelowHorizon(SnowThunder), SnowThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(Fog), Fog);
	ASSERT_EQ(codeIfSunBelowHorizon(SleetSunThunder), Dark_SleetSunThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(SnowSunThunder), Dark_SnowSunThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(SleetThunder), SleetThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(DrizzleThunderSun), Dark_DrizzleThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(RainThunderSun), Dark_RainThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSleetThunderSun), Dark_LightSleetThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySleetThunderSun), Dark_HeavySleetThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSnowThunderSun), Dark_LightSnowThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySnowThunderSun), Dark_HeavySnowThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(DrizzleThunder), DrizzleThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSleetThunder), LightSleetThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySleetThunder), HeavySleetThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSnowThunder), LightSnowThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySnowThunder), HeavySnowThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(DrizzleSun), Dark_DrizzleSun);
	ASSERT_EQ(codeIfSunBelowHorizon(RainSun), Dark_RainSun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSleetSun), Dark_LightSleetSun);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySleetSun), Dark_HeavySleetSun);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSnowSun), Dark_LightSnowSun);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySnowSun), Dark_HeavySnowSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Drizzle), Drizzle);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSleet), LightSleet);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySleet), HeavySleet);
	ASSERT_EQ(codeIfSunBelowHorizon(LightSnow), LightSnow);
	ASSERT_EQ(codeIfSunBelowHorizon(HeavySnow), HeavySnow);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_Sun), Dark_Sun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightCloud), Dark_LightCloud);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_PartlyCloud), Dark_PartlyCloud);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightRainSun), Dark_LightRainSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightRainThunderSun), Dark_LightRainThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_SleetSun), Dark_SleetSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_SnowSun), Dark_SnowSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightRain), Dark_LightRain);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_SleetSunThunder), Dark_SleetSunThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_SnowSunThunder), Dark_SnowSunThunder);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_DrizzleThunderSun), Dark_DrizzleThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_RainThunderSun), Dark_RainThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightSleetThunderSun), Dark_LightSleetThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_HeavySleetThunderSun), Dark_HeavySleetThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightSnowThunderSun), Dark_LightSnowThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_HeavySnowThunderSun), Dark_HeavySnowThunderSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_DrizzleSun), Dark_DrizzleSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_RainSun), Dark_RainSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightSleetSun), Dark_LightSleetSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_HeavySleetSun), Dark_HeavySleetSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_LightSnowSun), Dark_LightSnowSun);
	ASSERT_EQ(codeIfSunBelowHorizon(Dark_HeavySnowSun), Dark_HeavySnowSun);
}
