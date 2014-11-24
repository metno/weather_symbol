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

#ifndef WEATHERSYMBOLINTERPRETOR_H_
#define WEATHERSYMBOLINTERPRETOR_H_

#include "Code.h"
#include <map>
#include <set>
#include <string>


namespace weather_symbol
{

/**
 * Provides semantics to weather symbol codes
 */
class Interpretor
{
public:
	Interpretor();
	~Interpretor();

	/**
	 * Get the associated name for this code
	 */
	std::string name(Code c) const;

	/**
	 * Does the given symbol imply precipitation?
	 */
	bool hasPrecipitation(Code c) const;

	/**
	 * Does the given symbol indicate fog?
	 */
	bool hasFog(Code c) const;

	/**
	 * Does the given symbol imply thunder?
	 */
	bool hasThunder(Code c) const;

	/**
	 * If the symbol has thunder, return the same symbol without thunder.
	 */
	Code turnOffThunder( Code c ) const;

	/**
	 * If the symbol has no thunder, return the same symbol with thunder.
	 */
	Code turnOnThunder( Code c ) const;

	/**
	 * Get the code to use if sun is below horizon
	 */
	Code codeIfSunBelowHorizon(Code  code) const;

private:
	typedef std::map<Code, std::string> NameMap;
	typedef std::set<Code> CodeSet;
	typedef std::map<Code, Code> SymbolMap;
	typedef std::map<int, std::map<int, std::map< bool, weather_symbol::Code> > >  CodeTable;

	NameMap names;
	CodeSet precipitationFreeCodes;
	CodeSet thunderCodes;
	SymbolMap thunderToNoThunderCodes;
	SymbolMap noThunderToThunderCodes;
	SymbolMap sunBelowHorizonCodes;
	CodeTable codeTable;

};

} /* namespace weather_symbol_ */
#endif /* WEATHERSYMBOLINTERPRETOR_H_ */
