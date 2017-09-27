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


#include "common.hpp"

#include <cstring>


namespace mdhtml {


bool startsWith( const std::string str, const std::string pattern ) {
    return str.compare( 0, pattern.length(), pattern ) == 0;
}


bool isEmpty( const std::string str ) {
    std::string no_whitespaces = stripWhitespaces( str );
    return ( no_whitespaces.length() == 0 
          || ( no_whitespaces.length() == 1 && (char)no_whitespaces[0] == '\n' ) );
}


bool isEnumeration( const std::string str, const unsigned int start ) {
    bool dot_found = false;
    for ( unsigned int c = start; c < str.length(); c++ ) {
        if ( !dot_found && !isNum(str.substr(c, 1)) ) {
            break;
        } else if ( !dot_found && (char)str[c] == '.' ) {
            dot_found = true;
        } else if ( dot_found && (char)str[c] == ' ' ) {
            return true;
        } else {
            break;
        }
    }
    
    return false;
}


bool isEnumeration2( const std::string str ) {
    if ( startsWith( str, "  " ) ) {
        return isEnumeration( str, 2 );
    } else if ( startsWith( str, "\t" ) ) {
        return isEnumeration( str, 1 );
    }
    
    return false;
}


bool isHeading( const std::string str ) {
    return startsWith( stripWhitespaces(str), "#" );
}


bool isHorizontalRule( const std::string str ) {
    return ( str == "___"
          || str == "---" );
}


bool isList( const std::string str, const unsigned int start ) {
    return str.compare( start, 2, "* " ) == 0;
}


bool isList2( const std::string str ) { 
    if ( startsWith( str, "\t" ) )
        return isList( str, 1 );
    else if ( startsWith( str, "  " ) )
        return isList( str, 2 );
    
    return false;
}


bool isListContent( const std::string str ) {
    return ( !isEmpty(str) 
          && !isEnumeration(str)
          && !isEnumeration2(str)
          && !isList(str)
          && !isList2(str) );
}



bool isMultilineCodeTag( const std::string str ) {
    return startsWith( stripWhitespaces(str), "```" );
}


bool isNum( const std::string str ) {
    for( unsigned int i = 0; i < str.size(); i++ ) {
        std::string test_str;
        test_str += (char)str[i];
        try {
            std::stoi(test_str);
        } catch(...) {
            return false;
        }
    }
    return true;
}


bool isSimpleText( const std::string str ) {
    return ( !isEmpty(str) 
          && !isEnumeration(str)
          && !isEnumeration2(str)
          && !isHeading(str)
          && !isHorizontalRule(str)
          && !isList(str)
          && !isList2(str)
          && !isMultilineCodeTag(str) );
}



size_t findEndTag( const std::string str, const size_t start_pos, const std::string tag_pattern, bool no_preceeding_space ) {
    
    size_t pos = str.find( tag_pattern, start_pos );
    while ( pos != std::string::npos ) {
        if ( no_preceeding_space ) {
            if ( (char)str[pos-1] != ' ' ) {
                return pos;
            }
        } else {
            return pos;
        }
        
        pos = str.find( tag_pattern, pos );
    }
    
    return std::string::npos;
}


const std::string replaceAll( const std::string str, const char search_char, const std::string replace_str ) {
    std::string new_str;

    for ( unsigned int c = 0; c < str.length(); c++ ) {
        if ( (char)str[c] == search_char ) {
            new_str += replace_str;
        } else {
            new_str += (char)str[c];
        }
    }
    
    return new_str;
}


const std::string stripWhitespaces( const std::string str ) {
    return replaceAll( replaceAll( str, ' ', "" ), '\t', "" );
}


std::vector<std::string> tokenize( const std::string str ) {
    std::vector< std::string > tokens = tokenize( str, "\n", true );
    
    // We want empty lines, but no trailing newlines.
    for ( unsigned int t = 0; t < tokens.size(); t++ ) {
        std::string no_whitespaces = stripWhitespaces( tokens[t] );
        if ( no_whitespaces.length() != 1 ) {
            tokens[t] = replaceAll( tokens[t], '\n', "" );
        }
    }
    
    return tokens;
}



std::vector< std::string > tokenize( const std::string str, const std::string delimiter, bool dont_strip ) {

	std::vector<std::string> tokens;
    size_t current_start_pos = 0;
	size_t end_pos = str.find( delimiter );
    
    while ( end_pos != std::string::npos ) {
        tokens.push_back( str.substr(current_start_pos, end_pos-current_start_pos+(dont_strip ? 1 : 0)) );
        current_start_pos = end_pos + delimiter.length();
        end_pos = str.find( delimiter, current_start_pos );
    }
    
    if ( current_start_pos < str.length() ) {
        tokens.push_back( str.substr(current_start_pos) );
    }

	return tokens;
}


const std::string globSection( const std::vector< std::string > lines, const size_t start_pos, const size_t n ) {
    std::string str;
    
    for ( unsigned int l = start_pos; l < lines.size() && l <= start_pos+n; l++ ) {
        str += lines.at(l) + "\n";
    }
    
    return str;
}


const std::string indent( const unsigned int depth ) {
    std::string str;
    
    for ( unsigned int i = 0; i < depth; i++ ) {
        str += " ";
    }
    
    return str;
}



} // namespace mdhtml

