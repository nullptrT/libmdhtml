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


#include "html_tag.hpp"

#include "mdhtml_common.hpp"


namespace mdhtml {


HtmlTag::HtmlTag( const std::string start_tag
                , const std::string content
                , const std::string end_tag )
    :   m_start_tag( start_tag )
    ,   m_content( content )
    ,   m_end_tag( end_tag )
    ,   m_childs( new std::vector< HtmlTag* >() )
{}


const std::string HtmlTag::start_tag() const {
    return m_start_tag;
}


const std::string HtmlTag::content() const {
    return m_content;
}


const std::string HtmlTag::end_tag() const {
    return m_end_tag;
}


std::vector< HtmlTag* >* HtmlTag::childs() const {
    return m_childs;
}


void HtmlTag::addChild( HtmlTag* child ) {
    if ( child != 0 ) {
        m_childs->push_back( child );
    }
}


void HtmlTag::appendContent(const std::string content) {
    m_content += " " + content;
}


const std::string HtmlTag::join( const unsigned int indent_depth ) const {
    std::string html;

    if ( m_start_tag.length() > 0 ) {
        html += m_start_tag;
    }

    /*if ( m_content.length() == 0 && m_childs->size() == 0 ) {
        return html;
    }*/

    if ( m_childs->size() > 0 ) {
        for ( unsigned int c = 0; c < m_childs->size(); c++ ) {
            const std::string child_html = m_childs->at(c)->html( indent_depth + 4 );
            /*if ( child_html.length() == 0 ) {
                continue;
            } else*/ if ( m_start_tag == "<html>"
                     || m_start_tag == "<li>"
                     || m_start_tag == "<ul>"
            ) {
                html += "\n" + indent( indent_depth + 4 );
            } else if ( m_start_tag == "<pre>" ) {
                html += "\n";
            }
            html += child_html;
        }
    } else if ( m_content.length() > 0 ) {
        html += m_content;
    }

    if ( m_end_tag.length() > 0 ) {
        if ( m_start_tag == "<html>"
          || m_start_tag == "<li>"
          || m_start_tag == "<ul>"
          || m_start_tag == "<pre>"
        ) {
            html += "\n" + indent( indent_depth );
        }
        html += m_end_tag;
    }
    
    return html;
}


const std::string HtmlTag::html( const unsigned int indent_depth ) const {
    return this->join( indent_depth );
}



} // namespace mdhtml

