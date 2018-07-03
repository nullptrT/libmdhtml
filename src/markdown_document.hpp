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


namespace mdhtml {


/**
 * @brief A class providing convenient functions for converting of markdown documents to HTML
 */
class MarkdownDocument {
protected:
    /**
     * @brief The current text of this MarkdownDocument
     */
    std::string m_text;
public:
    /**
     * @brief Default constructor. Creates an empty MarkdownDocument
     */
    MarkdownDocument();
    /**
     * @brief constructor. Creates a MarkdownDocument from a given text
     * @param text The markdown text of this new MarkdownDocument
     */
    MarkdownDocument( const std::string text );
    
    /**
     * @brief Get a copy of the current text of this MarkdownDocument
     * @returns A copy of the current text of this MarkdownDocument
     */
    const std::string text() const;
    /**
     * @brief Convert the current text of this MarkdownDocument to formatted HTML
     * @returns Formatted HTML converted from the current markdown text of this MarkdownDocument
     */
    const std::string html() const;
    
    /**
     * @brief Append a string to the current text of this MarkdownDocument
     * @param text The additional text to the current markdown text
     */
    void operator+=( const std::string text );
    
    /**
     * @brief Set the current text of this MarkdownDocument
     * @param text The updated version of the current markdown text
     */
    void update_text( const std::string text );
    
    /**
     * @brief Converts the current text of this MarkdownDocument to HTML and writes the HTML to a given file
     * @param path The path of the file to write to
     * @returns False, if the file cannot be read.
     */
    bool html_toFile( const std::string path ) const;
    
    /**
     * @brief Writes a given HTML string to a file
     * @param path The path of the file to write to
     * @param html The HTML string to be written
     * @returns False, if the file cannot be read.
     */
    static bool html_toFile( const std::string path, const std::string html );
    
    /**
     * @brief Read a file containing markdown text and save the text to this class
     * @param path The path of the file to read from
     * @returns False, if the file cannot be read.
     */
    
     bool thisFromFile( const std::string path );
    
    /**
     * @brief Read a file containing markdown text and get a MarkdownDocument containing its text
     * @param path The path of the file to read from
     * @returns 0, if the file cannot be read. A valid MarkdownDocument containing the file's contents otherwise.
     */
    static MarkdownDocument* fromFile( const std::string path );
};


} // namespace mdhtml
