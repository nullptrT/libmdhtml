/**
 * @brief
 * @package LibMdHtmlQt
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

#include <QRegularExpression>
#include <QSyntaxHighlighter>


namespace mdhtml {


/**
 * @brief A struct representing a syntax highlighting rule
 */
struct QHighlightingRule {
    /**
     * @brief The regular expression used for pattern-matching of this rule
     */
    QRegularExpression pattern;
    /**
     * @brief The QTextCharFormat to be applied if pattern is matched
     */
    QTextCharFormat format;
};


/**
 * @brief A class containing rules and functions for matching and highlighting markdown syntax in a QTextDocument
 */
class QMarkDownSyntax
    :   public QSyntaxHighlighter
{
    Q_OBJECT
    
    QRegularExpression m_multilineCodeExpr;
    
protected:
    /**
     * @brief All simple rules
     */
    QVector< QHighlightingRule > m_rules;
    
    /**
     * @brief The formatting for matched bold markdown
     */
    QTextCharFormat m_boldFormat;
    /**
     * @brief The formatting for matched bold+italic markdown
     */
    QTextCharFormat m_boldItalicFormat;
    /**
     * @brief The formatting for matched code markdown
     */
    QTextCharFormat m_codeFormat;
    /**
     * @brief The formatting for matched comment markdown
     */
    QTextCharFormat m_commentFormat;
    /**
     * @brief The formatting for matched heading markdown
     */
    QTextCharFormat m_headingFormat;
    /**
     * @brief The formatting for matched italic markdown
     */
    QTextCharFormat m_italicFormat;
    /**
     * @brief The formatting for matched link markdown
     */
    QTextCharFormat m_linkFormat;
    /**
     * @brief The formatting for matched list and enumeration item markdown
     */
    QTextCharFormat m_listFormat;
    /**
     * @brief The formatting for matched strikethrough markdown
     */
    QTextCharFormat m_strikethroughFormat;
    
public:
    /**
     * @brief Constructor. Installs this new QMarkDownSyntax object on parent
     * @param parent The QTextDocument this QMarkDownSyntax should match and manipulate
     */
    QMarkDownSyntax( QTextDocument* parent = 0 );
    
protected:
    /**
     * @brief The highlighting function for matching and highlighting of a text block
     * @param text The text block to manipulate
     */
    void highlightBlock( const QString& text ) override;
};


} // namespace mdhtml
