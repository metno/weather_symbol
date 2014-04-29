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
#include <Factory.h>
#include <stdexcept>

using namespace weather_symbol;

namespace
{
const Factory factory(6);
}

TEST(SimpleWeatherSymbolTest, tooCloudy)
{
	ASSERT_THROW(factory.getSymbol(110, 0.1), std::runtime_error);
}

TEST(SimpleWeatherSymbolTest, negativePrecipitation)
{
	ASSERT_THROW(factory.getSymbol(10, -0.1), std::runtime_error);
}

TEST(SimpleWeatherSymbolTest, sunNoRain)
{
	ASSERT_EQ(Sun, factory.getSymbol(10, 0.1));
}

TEST(SimpleWeatherSymbolTest, sunRain)
{
	ASSERT_EQ(DrizzleSun, factory.getSymbol(10, 0.5));
}

TEST(SimpleWeatherSymbolTest, lightCloundNoRain)
{
	ASSERT_EQ(LightCloud, factory.getSymbol(30, 0));
}

TEST(SimpleWeatherSymbolTest, lightCloudRain)
{
	ASSERT_EQ(RainSun, factory.getSymbol(30, 45));
}

TEST(SimpleWeatherSymbolTest, partlyCloudNoRain)
{
	ASSERT_EQ(PartlyCloud, factory.getSymbol(50, 0.1));
}

TEST(SimpleWeatherSymbolTest, partlyCloudLittleRain)
{
	ASSERT_EQ(DrizzleSun, factory.getSymbol(50, 0.5));
}

TEST(SimpleWeatherSymbolTest, partlyCloudSomeRain)
{
	ASSERT_EQ(LightRainSun, factory.getSymbol(50, 0.96));
}

TEST(SimpleWeatherSymbolTest, partlyCloudHeavyRain)
{
	ASSERT_EQ(RainSun, factory.getSymbol(50, 7));
}

TEST(SimpleWeatherSymbolTest, cloudyNoRain)
{
	ASSERT_EQ(Cloud, factory.getSymbol(90, 0.1));
}

TEST(SimpleWeatherSymbolTest, cloudySomeRain)
{
	ASSERT_EQ(LightRain, factory.getSymbol(90, 0.96));
}

TEST(SimpleWeatherSymbolTest, cloudyHeavyRain)
{
	ASSERT_EQ(Rain, factory.getSymbol(90, 6));
}

TEST(SimpleWeatherSymbolTest, dominatedByHighClouds )
{
	WeatherData wd;
	wd.precipitation = 0;
	wd.totalCloudCover = 100;
	wd.highCloudCover = 90;
	wd.mediumCloudCover = 12;
	wd.lowCloudCover = 12;
	ASSERT_EQ(PartlyCloud, factory.getSymbol(wd));
}

TEST(SimpleWeatherSymbolTest, sunButMaybeRain )
{
	WeatherData wd;
	wd.totalCloudCover = 10;
	wd.precipitation = 0;
	wd.maxPrecipitation = 1;
	ASSERT_EQ(PartlyCloud, factory.getSymbol(wd));
}

TEST(SimpleWeatherSymbolTest, wetBulbTemperaturePrecipitationPhase )
{
	WeatherData wd;
	wd.totalCloudCover = 90;

	wd.precipitation = 5;
	wd.temperature = 0.5;
	ASSERT_EQ(HeavySnow, factory.getSymbol(wd) ) << "HeavySnow";

	wd.temperature = 0.6;
	ASSERT_EQ(HeavySleet, factory.getSymbol(wd) ) << "HeavySleet";

	wd.temperature = 1.5;
	ASSERT_EQ(HeavySleet, factory.getSymbol(wd) ) << "HeavySleet";

	wd.temperature = 1.6;
	ASSERT_EQ(Rain, factory.getSymbol(wd) ) << "Rain";
}

TEST(SimpleWeatherSymbolTest, airTemperaturePrecipitationPhase )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 5;

	wd.wetBulbTemperature = 0.5;
	ASSERT_EQ(HeavySnow, factory.getSymbol(wd) ) << "HeavySnow";

	wd.wetBulbTemperature = 0.6;
	ASSERT_EQ(HeavySleet, factory.getSymbol(wd) ) << "HeavySleet";

	wd.wetBulbTemperature = 1.0;
	ASSERT_EQ(HeavySleet, factory.getSymbol(wd) ) << "HeavySleet";

	wd.wetBulbTemperature = 1.1;
	ASSERT_EQ(Rain, factory.getSymbol(wd) ) << "Rain";
}


TEST(SimpleWeatherSymbolTest, thunderStorm )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 5;
	wd.thunder = true;

	wd.wetBulbTemperature = 0.5;
	ASSERT_EQ(HeavySnowThunder, factory.getSymbol(wd) ) << "HeavySnowThunder";

	wd.wetBulbTemperature = 0.6;
	ASSERT_EQ(HeavySleetThunder, factory.getSymbol(wd) ) << "HeavySleetThunder";

	wd.wetBulbTemperature = 1.0;
	ASSERT_EQ(HeavySleetThunder, factory.getSymbol(wd) ) << "HeavySleetThunder";

	wd.wetBulbTemperature = 1.1;
	ASSERT_EQ(RainThunder, factory.getSymbol(wd) ) << "RainThunder";
}

TEST(SimpleWeatherSymbolTest, fog )
{
	WeatherData wd;
	wd.totalCloudCover = 90;
	wd.precipitation = 0.4;
	wd.fog = true;

	ASSERT_EQ(Fog, factory.getSymbol(wd) ) << "Fog";

	wd.precipitation = 0.5;
	ASSERT_EQ(Drizzle, factory.getSymbol(wd) ) << "Drizzle";
}


TEST(SimpleWeatherSymbolTest, sunBelowHorizon )
{
	boost::shared_ptr<Interpretor> i = factory.interpretor();
	ASSERT_EQ(i->codeIfSunBelowHorizon( Error ), Error );
	ASSERT_EQ(i->codeIfSunBelowHorizon(Sun) , Dark_Sun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightCloud), Dark_LightCloud);
	ASSERT_EQ(i->codeIfSunBelowHorizon(PartlyCloud), Dark_PartlyCloud);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Cloud), Cloud);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightRainSun), Dark_LightRainSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightRainThunderSun), Dark_LightRainThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(SleetSun), Dark_SleetSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(SnowSun), Dark_SnowSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Rain), Rain);
	ASSERT_EQ(i->codeIfSunBelowHorizon(RainThunder), RainThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Sleet), Sleet);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Snow), Snow);
	ASSERT_EQ(i->codeIfSunBelowHorizon(SnowThunder), SnowThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Fog), Fog);
	ASSERT_EQ(i->codeIfSunBelowHorizon(SleetSunThunder), Dark_SleetSunThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(SnowSunThunder), Dark_SnowSunThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(SleetThunder), SleetThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(DrizzleThunderSun), Dark_DrizzleThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(RainThunderSun), Dark_RainThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSleetThunderSun), Dark_LightSleetThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySleetThunderSun), Dark_HeavySleetThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSnowThunderSun), Dark_LightSnowThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySnowThunderSun), Dark_HeavySnowThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(DrizzleThunder), DrizzleThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSleetThunder), LightSleetThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySleetThunder), HeavySleetThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSnowThunder), LightSnowThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySnowThunder), HeavySnowThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(DrizzleSun), Dark_DrizzleSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(RainSun), Dark_RainSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSleetSun), Dark_LightSleetSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySleetSun), Dark_HeavySleetSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSnowSun), Dark_LightSnowSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySnowSun), Dark_HeavySnowSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Drizzle), Drizzle);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSleet), LightSleet);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySleet), HeavySleet);
	ASSERT_EQ(i->codeIfSunBelowHorizon(LightSnow), LightSnow);
	ASSERT_EQ(i->codeIfSunBelowHorizon(HeavySnow), HeavySnow);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_Sun), Dark_Sun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightCloud), Dark_LightCloud);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_PartlyCloud), Dark_PartlyCloud);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightRainSun), Dark_LightRainSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightRainThunderSun), Dark_LightRainThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_SleetSun), Dark_SleetSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_SnowSun), Dark_SnowSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_SleetSunThunder), Dark_SleetSunThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_SnowSunThunder), Dark_SnowSunThunder);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_DrizzleThunderSun), Dark_DrizzleThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_RainThunderSun), Dark_RainThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightSleetThunderSun), Dark_LightSleetThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_HeavySleetThunderSun), Dark_HeavySleetThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightSnowThunderSun), Dark_LightSnowThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_HeavySnowThunderSun), Dark_HeavySnowThunderSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_DrizzleSun), Dark_DrizzleSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_RainSun), Dark_RainSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightSleetSun), Dark_LightSleetSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_HeavySleetSun), Dark_HeavySleetSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_LightSnowSun), Dark_LightSnowSun);
	ASSERT_EQ(i->codeIfSunBelowHorizon(Dark_HeavySnowSun), Dark_HeavySnowSun);
}
