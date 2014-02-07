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
