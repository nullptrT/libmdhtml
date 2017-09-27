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


#include "markdown_document.hpp"

#include "md2html.hpp"

#include <fstream>
#include <sstream>


namespace mdhtml {


MarkdownDocument::MarkdownDocument()
    :   m_text()
{}


MarkdownDocument::MarkdownDocument( const std::string text )
    :   m_text( text )
{}


const std::string MarkdownDocument::text() const {
    return m_text;
}


const std::string MarkdownDocument::html() const {
    return md2html( m_text );
}


bool MarkdownDocument::html_toFile( const std::string path ) const {
    std::ofstream file( path );
    if ( !file.good() ) {
        return false;
    }
    
    std::string html = this->html();
    file << html << std::endl;
    file.close();
    
    return true;
}


MarkdownDocument* MarkdownDocument::fromFile( const std::string path ) {
    std::ifstream file( path );
    if ( !file.good() ) {
        return 0;
    }
    
    std::stringstream file_buf;
    file_buf << file.rdbuf();
    std::string file_str( file_buf.str() );
    file.close();
    
    return new MarkdownDocument( file_str );
}



} // namespace mdhtml

