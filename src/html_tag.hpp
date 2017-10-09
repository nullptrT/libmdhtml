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

#include "config_mdhtml.hpp"

#include <string>
#include <vector>


namespace mdhtml {


/**
 * @brief A class representing a HTML tag with its content or child tags
 */
class HtmlTag {
protected:
    /**
     * @brief The start tag of this HTML tag
     */
    const std::string m_start_tag;
    /**
     * @brief The content between start tag and end tag
     */
    std::string m_content;
    /**
     * @brief The end tag of this HTML tag
     */
    const std::string m_end_tag;
    /**
     * @brief A vector containing all child-/sub-tags of this HTML tag
     */
    std::vector< HtmlTag* >* m_childs;
    
    /**
     * @brief Get a string concatenating the start tag (if any), a joined version of all concatenated child tags (preferred) or the current content of this HtmlTag (if no child tags are found) followed by the end tag, if any.
     * @param indent_depth The depth of indent to indent child HTML tags with
     * @returns A string version of this HtmlTag matching the conditions
     */
    virtual const std::string join( const unsigned int indent_depth = 4 ) const;
public:
    /**
     * @brief Constructor
     * @param start_tag The start tag (like "<a href="url">")
     * @param content The content between start tag and end tag, if any
     * @param end_tag The end tag (like "</a>")
     */
    HtmlTag( const std::string start_tag
           , const std::string content = ""
           , const std::string end_tag = ""
    );
    
    /**
     * @brief Get the start tag of this HtmlTag
     * @returns The start tag of this HtmlTag
     */
    const std::string start_tag() const;
    /**
     * @brief Get the current content of this HtmlTag to (e.g. to reprocess it)
     * @returns The current content of this HtmlTag
     */
    const std::string content() const;
    /**
     * @brief Get the end tag of this HtmlTag, if any.
     * @returns The end tag of this HtmlTag
     */
    const std::string end_tag() const;
    /**
     * @brief Get all child tags of this HtmlTag
     * @returns A pointer to the vector containing all sub-tags of this HtmlTag
     */
    std::vector< HtmlTag* >* childs() const;
    
    /**
     * @brief Add a HtmlTag as child. The child may contain a start tag only, content only, or a start tag and a end tag with all possible combination of content/child tags.
     * @param child A valid HtmlTag. If child == 0, nothing is added
     */
    void addChild( HtmlTag* child );
    /**
     * @brief Append a space character followed by another string to the current content string
     * @param content The content to append to the current content
     */
    void appendContent( const std::string content );
    
    /**
     * @brief Get a string concatenating the start tag (if any), a joined version of all concatenated child tags (preferred) or the current content of this HtmlTag (if no child tags are found) followed by the end tag, if any.
     * @param indent_depth The depth of indent to indent child HTML tags with
     * @returns A string version of this HtmlTag matching the conditions
     */
    const std::string html( const unsigned int indent_depth = 4 ) const;
};


} // namespace mdhtml
