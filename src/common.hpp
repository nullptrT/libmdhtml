/**
 * @brief
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibMdHtml++: A library for converting markdown to html
	Copyright (C) 2017 Sebastian Lau <lauseb644@gmail.com>


	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/


#pragma once

#include "config.hpp"

#include <string>
#include <vector>


namespace mdhtml {


bool startsWith( const std::string str, const std::string pattern );

bool isEmpty( const std::string str );
bool isEnumeration( const std::string str, const unsigned int start = 0 );
bool isEnumeration2( const std::string str );
bool isHeading( const std::string str );
bool isHorizontalRule( const std::string str );
bool isList( const std::string str, const unsigned int start = 0 );
bool isList2( const std::string str );
bool isListContent( const std::string str );
bool isMultilineCodeTag( const std::string str );
bool isNum( const std::string str );
bool isSimpleText( const std::string str );

size_t findEndTag( const std::string str, const size_t start_pos, const std::string tag_pattern, bool no_preceeding_space = true );

const std::string replaceAll( const std::string str, const char search_char, const std::string replace_str );
const std::string stripWhitespaces( const std::string str );

std::vector< std::string > tokenize( const std::string str );
std::vector< std::string > tokenize( const std::string str, const std::string delimiter, bool dont_strip = false );

const std::string globSection( const std::vector< std::string > lines, const size_t start_pos, const size_t n );

const std::string indent( const unsigned int depth );


} // namespace mdhtml

