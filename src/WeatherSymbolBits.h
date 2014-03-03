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

#ifndef __WEATHERSYMBOLPBITS_H_
#define __WEATHERSYMBOLPBITS_H_
#include <map>
#include <set>
#include <string>
#include "WeatherSymbolCode.h"

namespace weather_symbol {
namespace bits {

typedef std::map<Code, std::string> NameMap;
typedef std::set<Code> CodeSet;
typedef std::map<Code, Code> SymbolMap;
typedef std::map<int, std::map<int, std::map< bool, weather_symbol::Code> > >  CodeTable;

extern NameMap names;
extern CodeSet precipitationFreeCodes;
extern CodeSet thunderCodes;
extern SymbolMap sunBelowHorizonCodes;
extern CodeTable codeTable;

void init();

}

}


#endif /* WEATHERSYMBOLPRIVATE_H_ */
