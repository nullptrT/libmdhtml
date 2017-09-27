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


class HtmlTag {
    const std::string m_start_tag;
    std::string m_content;
    const std::string m_end_tag;
    std::vector< HtmlTag* >* m_childs;
    
    const std::string join( const unsigned int indent_depth = 4 ) const;
public:
    HtmlTag( const std::string start_tag
           , const std::string content
           , const std::string end_tag
    );
    
    const std::string start_tag() const;
    const std::string content() const;
    const std::string end_tag() const;
    std::vector< HtmlTag* >* childs() const;
    
    void addChild( HtmlTag* child );
    void appendContent( const std::string content );
    
    const std::string html( const unsigned int indent_depth = 4 ) const;
};


} // namespace mdhtml
