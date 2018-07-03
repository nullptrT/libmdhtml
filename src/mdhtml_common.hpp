/**
 * @brief
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibMdHtml++: A library for converting markdown to html
	Copyright (C) 2017-2018 Sebastian Lau <lauseb644@gmail.com>


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

#include "config_mdhtml.hpp"

#include <string>
#include <vector>


namespace mdhtml {


/**
 * @brief Check, if a given string starts with a specific pattern
 * @param str The string to check
 * @param pattern The pattern to check
 * @returns True, if str starts with pattern
 */
bool startsWith( const std::string str, const std::string pattern );

/**
 * @brief Check, if this is an empty string or a string only containing '\n'
 * @param str The string to check
 * @returns True, if the conditions are met
 */
bool isEmpty( const std::string str );
/**
 * @brief Checks, if str, starting at start, starts with numbers followed by ". ".
 * @param str The string to check
 * @param start The character position in str to start with
 * @return True, if the conditions are met
 */
bool isEnumeration( const std::string str, const unsigned int start = 0 );
/**
 * @brief Checks, if str, starting at index 2, starts with numbers followed by ". ".
 * @param str The string to check
 * @return True, if the conditions are met
 */
bool isEnumeration2( const std::string str );
/**
 * @brief Checks, if str start with one to six '#'.
 * @param str The string to check
 * @return True, if the conditions are met
 */
bool isHeading( const std::string str );
/**
 * @brief Checks, if str equals "___" or "---"
 * @param str The string to check
 * @returns True, if the conditions are met
 */
bool isHorizontalRule( const std::string str );
/**
 * @brief Checks, if str, starting with the character at start, begins with "* ".
 * @param str The string to check
 * @param start The character to start with
 * @returns True, if the conditions are met
 */
bool isList( const std::string str, const unsigned int start = 0 );
/**
 * @brief Checks, if str, starting with the character at index 2, begins with "* ".
 * @param str The string to check
 * @returns True, if the conditions are met
 */
bool isList2( const std::string str );
/**
 * @brief Checks, if str is a line representing list content
 * @param str The string to check
 * @return True, if ( !isEmpty(str) && !isEnumeration(str) && !isEnumeration2(str) && !isList(str) && !isList2(str))
 */
bool isListContent( const std::string str );
/**
 * @brief Checks, if str begins with "```"
 * @param str The string to check
 * @returns True, if the conditions are met
 */
bool isMultilineCodeTag( const std::string str );
/**
 * @brief Checks character-by-character, if str is a number
 * @param str The string to check
 * @returns True, if all characters of str are numbers
 */
bool isNum( const std::string str );
/**
 * @brief Checks, if the string is simple text
 * @param str The string to check
 * @returns True, if ( !isEmpty(str) && !isEnumeration(str) && !isEnumeration2(str) && !isHeading(str) && !isHorizontalRule(str) && !isList(str) && !isList2(str) && !isMultilineCodeTag(str) )
 */
bool isSimpleText( const std::string str );

/**
 * @brief Find the position of the next occurence of a given pattern in a string
 * @param str The string to be searched
 * @param start_pos The character index in str to start searching with
 * @param tag_pattern The pattern to search for
 * @param no_preceeding_space If set to true, the pattern will only be matched, if there is no space character preceeding to the occurence of the pattern
 * @returns The position of the next matching occurence of tag_pattern or std::string::npos
 */
size_t findNextTag( const std::string str, const size_t start_pos, const std::string tag_pattern, bool no_preceeding_space = true );

/**
 * @brief Replace all occurences of a character in a string with a string
 * @param str The string to be manipulated
 * @param search_char The character to search for
 * @param replace_str The string to replace search_char with
 * @returns A copy of str with all occurences of search_char replaced with replace_str
 */
const std::string replaceAll( const std::string str, const char search_char, const std::string replace_str );

/**
 * @brief Remove all '\t' and ' ' characters from a string
 * @param str The string to be manipulated
 * @returns A copy of str with all occurences of '\t' and ' ' erased.
 */
const std::string stripWhitespaces( const std::string str );

/**
 * @brief Split a string at every occurence of '\n' into tokens
 * @param str The string to split at every occurence of '\n'
 * @returns A vector containing all splitted tokens (The '\n' delimiter is still included)
 */
std::vector< std::string > tokenize( const std::string str );
/**
 * @brief Split a string at every occurence of a delimiter string.
 * @param str The string to split at every occurence of delimiter
 * @param delimiter The delimiter string to search for (as whole string)
 * @param dont_strip If set to true, the delimiter is not stripped from the resulting token strings, leaving it at the end of every matched token
 * @returns A vector containing all splitted tokens
 */
std::vector< std::string > tokenize( const std::string str, const std::string delimiter, bool dont_strip = false );

/**
 * @brief Re-unite splitted lines to a whole string
 * @param lines The strings (representing lines of a text) to operate on
 * @param start_pos The index to start globbing with
 * @param n The number of lines to glob
 * @returns A string containing all strings in lines matching the condition (l=start_pos; l < lines.size() && l<=start_pos+n) followed by a '\n' character per element
 */
const std::string globSection( const std::vector< std::string > lines, const size_t start_pos, const size_t n );

/**
 * @brief Returns a string containing a specific number of spaces
 * @param depth The number of spaces needed
 * @returns A string containing depth space characters
 */
const std::string indent( const unsigned int depth );


} // namespace mdhtml

