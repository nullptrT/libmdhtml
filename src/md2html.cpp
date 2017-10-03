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


#include "md2html.hpp"

#include "mdhtml_common.hpp"
#include "html_tag.hpp"


namespace mdhtml {

HtmlTag* process_heading( const std::string md_text );
HtmlTag* process_simple_text( const std::string md_text );
HtmlTag* process_something( HtmlTag* root_tag );


const std::string md2html( const std::string markdown_text ) {
    HtmlTag* html = new HtmlTag("<html>", markdown_text + "\n\n", "</html>");

    return process_something( html )->html(0);
}


HtmlTag* process_something( HtmlTag* root_tag ) {
    const std::string markdown_text = root_tag->content();

    std::vector< std::string > md_lines = tokenize( markdown_text );
    bool last_line = false;
    for ( unsigned int l = 0; l < md_lines.size(); l++ ) {
        if ( last_line ) {
            break;
        } else if ( l == md_lines.size() - 1 ) {
            last_line = true;
        }

        std::string md_line = md_lines.at(l);
        if ( root_tag->start_tag() != "<ul>" && (isList(md_line) || isList2(md_line)) ) {

            std::string str;
            size_t end_pos = l;

            if ( isList(md_line) ) {
                while ( ( isList(md_lines.at(end_pos))
                       || isList2(md_lines.at(end_pos))
                       || isListContent(md_lines.at(end_pos))
                       || isEnumeration2(md_lines.at(end_pos)) )
                     && end_pos < md_lines.size() - 1
                ) {
                    ++end_pos;
                }

                str = globSection( md_lines, l, end_pos-l );
                l = end_pos; // l is incremented by loop
            } else {
                while ( ( isList2(md_lines.at(end_pos))
                       || isListContent(md_lines.at(end_pos))
                       || isEnumeration2(md_lines.at(end_pos)) )
                     && end_pos < md_lines.size() - 1
                ) {
                    ++end_pos;
                }

                /*if ( end_pos == md_lines.size() - 1
                  && !isList2(md_lines.at(end_pos)) ) {
                    ++ end_pos;
                }*/

                str = globSection( md_lines, l, end_pos-l  );
                l = end_pos+1; // l is incremented by loop
            }

            HtmlTag* list_tag = new HtmlTag("<ul>", str, "</ul>");
            root_tag->addChild( list_tag );
            process_something( list_tag );
        } else if ( root_tag->start_tag() != "<ol>" && (isEnumeration(md_line) || isEnumeration2(md_line)) ) {

            std::string str;
            size_t end_pos = l;

            if ( isEnumeration(md_line) ) {
                while ( ( isEnumeration(md_lines.at(end_pos))
                       || isEnumeration2(md_lines.at(end_pos))
                       || isListContent(md_lines.at(end_pos))
                       || isList2(md_lines.at(end_pos)) )
                     && end_pos < md_lines.size() - 1
                ) {
                    ++end_pos;
                }

                str = globSection( md_lines, l, end_pos-l );
                l = end_pos; // l is incremented by loop
            } else {
                while ( ( isEnumeration2(md_lines.at(end_pos))
                       || isListContent(md_lines.at(end_pos))
                       || isList2(md_lines.at(end_pos)) )
                     && end_pos < md_lines.size() - 1
                ) {
                    ++end_pos;
                }

                str = globSection( md_lines, l, end_pos-l  );
                l = end_pos+1; // l is incremented by loop
            }

            HtmlTag* list_tag = new HtmlTag("<ol>", str, "</ol>");
            root_tag->addChild( list_tag );
            process_something( list_tag );
        } else if ( root_tag->start_tag() == "<ul>" && isList(md_line) ) {

            md_lines[l] = md_lines[l].substr(2);

            size_t end_pos = l;
            while ( ( isListContent(md_lines.at(end_pos))
                   || isList2(md_lines.at(end_pos))
                   || isEnumeration2(md_lines.at(end_pos)) )
                 && end_pos < md_lines.size() - 1
            ) {
                ++end_pos;
            }

            size_t len = (end_pos == l ? 0 : end_pos-l-1);
            std::string str = globSection( md_lines, l, len );

            HtmlTag* list_item_tag = new HtmlTag("<li>", str, "</li>");
            root_tag->addChild( list_item_tag );
            process_something( list_item_tag );

            l += len; // l is incremented by loop
        } else if ( root_tag->start_tag() == "<ul>" && isList2(md_line) ) {

            md_lines[l] = md_lines[l].substr(4);

            size_t end_pos = l;
            while ( ( isListContent(md_lines.at(end_pos))
                   || isEnumeration2(md_lines.at(end_pos)) )
                 && end_pos < md_lines.size() - 1
            ) {
                ++end_pos;
            }

            size_t len = (end_pos == l ? 0 : end_pos-l-1);

            if ( end_pos == md_lines.size() - 1
              && !isList2(md_lines.at(end_pos)) ) {
                ++len;
            }

            std::string str = globSection( md_lines, l, len );

            HtmlTag* list_item_tag = new HtmlTag("<li>", str, "</li>");
            root_tag->addChild( list_item_tag );
            process_something( list_item_tag );

            l += len; // l is incremented by loop
        } else if ( root_tag->start_tag() == "<ol>" && isEnumeration(md_line) ) {

            md_lines[l] = md_lines[l].substr(md_lines[l].find(". ")+2);

            size_t end_pos = l;
            while ( ( isListContent(md_lines.at(end_pos))
                   || isEnumeration2(md_lines.at(end_pos))
                   || isList2(md_lines.at(end_pos)) )
                 && end_pos < md_lines.size() - 1
            ) {
                ++end_pos;
            }

            size_t len = (end_pos == l ? 0 : (end_pos == md_lines.size()-1 ? md_lines.size()-l : end_pos-l-1));
            std::string str = globSection( md_lines, l, len );

            HtmlTag* enum_item_tag = new HtmlTag("<li>", str, "</li>");
            root_tag->addChild( enum_item_tag );
            process_something( enum_item_tag );

            l += len; // l is incremented by loop
        } else if ( root_tag->start_tag() == "<ol>" && isEnumeration2(md_line) ) {

            md_lines[l] = md_lines[l].substr(md_lines[l].find(". ")+2);

            size_t end_pos = l;
            while ( ( isListContent(md_lines.at(end_pos))
                   || isList2(md_lines.at(end_pos)) )
                 && end_pos < md_lines.size() - 1
            ) {
                ++end_pos;
            }

            size_t len = (end_pos == l ? 0 : end_pos-l-1);
            std::string str = globSection( md_lines, l, len );

            HtmlTag* enum_item_tag = new HtmlTag("<li>", str, "</li>");
            root_tag->addChild( enum_item_tag );
            process_something( enum_item_tag );

            l += len; // l is incremented by loop
        } else if ( isHeading( md_line ) ) { // A heading line
            root_tag->addChild( process_heading( md_line ) );
        } else if ( isHorizontalRule( md_line ) ) {
            root_tag->addChild( new HtmlTag("<hr>", "", "") );
        } else if ( isMultilineCodeTag( md_line ) ) {

            size_t end_pos = l + 1;
            while ( !isMultilineCodeTag(md_lines.at(end_pos))
                 && end_pos < md_lines.size() - 1
            ) {
                ++end_pos;
            }

            std::string str = globSection( md_lines, l + 1, end_pos-l-2 );

            HtmlTag* multiline_code_tag = new HtmlTag("<pre>", str, "</pre>");
            root_tag->addChild( multiline_code_tag );
            multiline_code_tag->addChild( new HtmlTag("<code>", str, "</code>") );

            l = end_pos; // l is incremented by loop
        }
        // TODO: Comments
        // TODO: Tables
        else if ( root_tag->start_tag() == "<html>" && isSimpleText(md_line) ) { // Paragraph

            size_t end_pos = l;
            while ( isSimpleText(md_lines.at(end_pos))
                 && end_pos < md_lines.size() - 1
            ) {
                ++end_pos;
            }

            std::string str = globSection( md_lines, l, end_pos-l );

            HtmlTag* paragraph_tag = new HtmlTag("<p>", str, "</p>");
            root_tag->addChild( paragraph_tag );
            process_something( paragraph_tag );

            l = end_pos; // l is incremented by loop
        } else if ( isEmpty(md_line) ) {
          continue;
        } else { // Normal text
            root_tag->addChild( process_simple_text(md_line) );
        }
    }

    return root_tag;
}


HtmlTag* process_heading( const std::string md_text ) {
    HtmlTag* html = 0;

    if ( startsWith(md_text, "######") ) {
        html = new HtmlTag("<h6>", md_text.substr(6), "</h6>");
    } else if ( startsWith(md_text, "#####") ) {
        html = new HtmlTag("<h5>", md_text.substr(5), "</h5>");
    } else if ( startsWith(md_text, "####") ) {
        html = new HtmlTag("<h4>", md_text.substr(4), "</h4>");
    } else if ( startsWith(md_text, "###") ) {
        html = new HtmlTag("<h3>", md_text.substr(3), "</h3>");
    } else if ( startsWith(md_text, "##") ) {
        html = new HtmlTag("<h2>", md_text.substr(2), "</h2>");
    } else if ( startsWith(md_text, "#") ) {
        html = new HtmlTag("<h1>", md_text.substr(1), "</h1>");
    } else {
        html = new HtmlTag("", md_text, "");
    }

    HtmlTag* html_content = process_simple_text( html->content() );
    html->addChild( html_content );

    return html;
}


HtmlTag* process_simple_text( const std::string md_text ) {
    HtmlTag* html = new HtmlTag("", md_text, "");

    unsigned int current_substr_start = 0;
    for ( unsigned int c = current_substr_start; c < md_text.length(); c++ ) {
        const char character = (char)md_text[c];
        if ( character == '*' ) { // Possible italic tag
            if ( md_text.length() > c+2 ) { // At least three characters needed for an italic tag
                if ( (char)md_text[c+1] == ' ' ) { // No start tag
                    continue;
                } else if ( (char)md_text[c+1] == '*' ) { // Possible bold tag
                    if ( md_text.length() > c+4 ) { // At least 5 characters needed for bold tag
                        if ( (char)md_text[c+2] == ' ' ) { // No start tag
                            continue;
                        } else if ( (char)md_text[c+2] == '*' ) { // Possible bold italic tag
                            if ( md_text.length() > c+6 ) { // At least 7 characters needed for bold italic tag
                                if ( (char)md_text[c+3] == ' ' ) { // No start tag
                                    continue;
                                } else { // Find end tag of bold italic
                                    size_t end_tag = findEndTag( md_text, c+3, "***" );
                                    if ( end_tag != std::string::npos ) {
                                        // Copy preceeding text
                                        if ( c-current_substr_start > 0 ) {
                                            HtmlTag* pre_tag = new HtmlTag("", md_text.substr(current_substr_start, c-current_substr_start), "");
                                            html->addChild( pre_tag );
                                        }

                                        // Create outter bold tag
                                        HtmlTag* bold_tag = new HtmlTag("<strong>", md_text.substr(c+2, end_tag-c-2), "</strong>");
                                        html->addChild( bold_tag );

                                        // Create inner italic tag
                                        HtmlTag* italic_tag = new HtmlTag("<em>", md_text.substr(c+3, end_tag-c-3), "</em>");
                                        bold_tag->addChild( italic_tag );

                                        // Check italic tag for some other text formating inside
                                        italic_tag->addChild( process_simple_text(italic_tag->content()) );

                                        // Continue iteration after the end_tag
                                        current_substr_start = end_tag + 3;
                                        c = end_tag + 2; // c is incremented by the loop
                                    }
                                }
                            }
                        } else { // Find end tag of bold
                            size_t end_tag = findEndTag( md_text, c+2, "**" );
                            if ( end_tag != std::string::npos ) {
                                // Copy preceeding text
                                if ( c-current_substr_start > 0 ) {
                                    HtmlTag* pre_tag = new HtmlTag("", md_text.substr(current_substr_start, c-current_substr_start), "");
                                    html->addChild( pre_tag );
                                }

                                // Create bold tag
                                HtmlTag* bold_tag = new HtmlTag("<strong>", md_text.substr(c+2, end_tag-c-2), "</strong>");
                                html->addChild( bold_tag );

                                // Check bold tag for some other text formating inside
                                bold_tag->addChild( process_simple_text(bold_tag->content()) );

                                // Continue iteration after the end_tag
                                current_substr_start = end_tag + 2;
                                c = end_tag + 1; // c is incremented by the loop
                            }
                        }
                    }
                } else { // Find end tag of italic
                    size_t end_tag = findEndTag( md_text, c+1, "*" );
                    if ( end_tag != std::string::npos ) {
                        // Copy preceeding text
                        if ( c-current_substr_start > 0 ) {
                            HtmlTag* pre_tag = new HtmlTag("", md_text.substr(current_substr_start, c-current_substr_start), "");
                            html->addChild( pre_tag );
                        }

                        // Create italic tag
                        HtmlTag* italic_tag = new HtmlTag("<em>", md_text.substr(c+1, end_tag-c-1), "</em>");
                        html->addChild( italic_tag );

                        // Check italic tag for some other text formating inside
                        italic_tag->addChild( process_simple_text(italic_tag->content()) );

                        // Continue iteration after the end_tag
                        current_substr_start = end_tag + 1;
                        c = end_tag; // c is incremented by the loop
                    }
                }
            }
        } else if ( character == '`') { // Possible code tag
            if ( md_text.length() > c+2 ) { // At least 3 characters needed for code tag
                size_t end_tag = findEndTag( md_text, c+1, "`", false );
                if ( end_tag != std::string::npos ) {
                    // Copy preceeding text
                    if ( c-current_substr_start > 0 ) {
                        HtmlTag* pre_tag = new HtmlTag("", md_text.substr(current_substr_start, c-current_substr_start), "");
                        html->addChild( pre_tag );
                    }

                    // Escape code
                    std::string code = md_text.substr(c+1, end_tag-c-1);
                    code = replaceAll( code, '<', "&lt;" );
                    code = replaceAll( code, '>', "&gt;");

                    // Create code tag
                    HtmlTag* code_tag = new HtmlTag("<code>", code, "</code>");
                    html->addChild( code_tag );

                    // Check code tag for some other text formating inside
                    code_tag->addChild( process_simple_text(code_tag->content()) );

                    // Continue iteration after the end_tag
                    current_substr_start = end_tag + 1;
                    c = end_tag; // c is incremented by the loop
                }
            }
        } else if ( character == '~' ) { // Possible strikethrough tag
            if ( md_text.length() > c+4 ) { // At least 5 characters needed for strikethrough tag
                if ( (char)md_text[c+1] == '~' && (char)md_text[c+2] != ' ' ) {
                    size_t end_tag = findEndTag( md_text, c+2, "~~" );
                    if ( end_tag != std::string::npos ) {
                        // Copy preceeding text
                        if ( c-current_substr_start > 0 ) {
                            HtmlTag* pre_tag = new HtmlTag("", md_text.substr(current_substr_start, c-current_substr_start), "");
                            html->addChild( pre_tag );
                        }

                        // Create strikethrough tag
                        HtmlTag* strikethrough_tag = new HtmlTag("<del>", md_text.substr(c+2, end_tag-c-2), "</del>");
                        html->addChild( strikethrough_tag );

                        // Check strikethrough tag for some other text formating inside
                        strikethrough_tag->addChild( process_simple_text(strikethrough_tag->content()) );

                        // Continue iteration after the end_tag
                        current_substr_start = end_tag + 2;
                        c = end_tag + 1; // c is incremented by the loop
                    }
                }
            }
        }
    }

    // Copy remaining text
    if ( current_substr_start != 0 && current_substr_start < md_text.size() ) {
        HtmlTag* post_tag = new HtmlTag("", md_text.substr(current_substr_start), "");
        html->addChild( post_tag );
    }

    return html;
}


} // namespace mdhtml

