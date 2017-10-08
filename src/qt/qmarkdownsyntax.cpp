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


#include "qmarkdownsyntax.hpp"

#include <QTextDocument>
#include <QVector>


namespace mdhtml {


QMarkDownSyntax::QMarkDownSyntax( QTextDocument* parent )
    :   QSyntaxHighlighter( parent )
    ,   m_rules()
    ,   m_multilineCodeExpr( "^(```){1,1}(.)*" )
    ,   m_boldFormat()
    ,   m_boldItalicFormat()
    ,   m_codeFormat()
    ,   m_headingFormat()
    ,   m_italicFormat()
    ,   m_listFormat()
    ,   m_strikethroughFormat()
{
    QHighlightingRule rule;
    
    // Make rules for all heading formats
    m_headingFormat.setForeground(Qt::darkGreen);
    QStringList keywordPatterns;
    keywordPatterns << "^(#\\040){1,1}(.)*" << "^(##\\040){1,1}(.)*"
                    << "^(###\\040){1,1}(.)*" << "^(####\\040){1,1}(.)*"
                    << "^(#####\\040){1,1}(.)*" << "^(######\\040){1,1}(.)*";
    foreach( const QString& pattern, keywordPatterns ) {
        rule.pattern = QRegularExpression( pattern );
        rule.format = m_headingFormat;
        m_rules.append( rule );
    }
    
    // Make rules for all types of lists and enumerations
    m_listFormat.setForeground(Qt::darkCyan);
    m_listFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression( "^(\\040){0,2}(\\*\\040){1,1}" );
    rule.format = m_listFormat;
    m_rules.append( rule );
    rule.pattern = QRegularExpression( "^(\\040){0,2}[0-9]+(\\040){1,1}" );
    m_rules.append( rule );

    // Make rules for all types of links
    m_linkFormat.setForeground(Qt::darkBlue);
    m_linkFormat.setFontItalic(true);
    rule.pattern = QRegularExpression( "(!)*(\\[(.)*\\]){1,1}(\\((.)*\\)){1,1}" );
    rule.format = m_linkFormat;
    m_rules.append( rule );
    
    // Make rules for all types of text formatting
    m_boldItalicFormat.setFontWeight(QFont::Bold);
    m_boldItalicFormat.setFontItalic( true );
    rule.pattern = QRegularExpression( "(\\*\\*\\*){1,1}(.)*(\\*\\*\\*){1,1}" );
    rule.format = m_boldItalicFormat;
    m_rules.append( rule );
    m_boldFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression( "[\\*](\\*\\*){1,1}[\\*](.)*[\\*](\\*\\*){1,1}[\\*]" );
    rule.format = m_boldFormat;
    m_rules.append( rule );
    m_italicFormat.setFontItalic( true );
    rule.pattern = QRegularExpression( "[\\*\\*](\\*){1,1}[\\*\\*](.)*[\\*\\*](\\*){1,1}[\\*\\*]" );
    rule.format = m_italicFormat;
    m_rules.append( rule );
    m_strikethroughFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegularExpression( "(~~){1,1}(.)*(~~){1,1}" );
    rule.format = m_strikethroughFormat;
    m_rules.append( rule );
    
    // Make rules for all types of code
    m_codeFormat.setForeground(Qt::darkYellow);
    m_codeFormat.setFontStyleHint(QFont::Monospace);
    rule.pattern = QRegularExpression( "(`){1,1}(.)*(`){1,1}" );
    rule.format = m_codeFormat;
    m_rules.append( rule );
}


void QMarkDownSyntax::highlightBlock( const QString& text ) {
    if ( text.length() == 0 ) return;

    // Match simple rules
    foreach( const QHighlightingRule& rule, m_rules ) {
        QRegularExpressionMatchIterator matchIt = rule.pattern.globalMatch( text );
        while ( matchIt.hasNext() ) {
            QRegularExpressionMatch match = matchIt.next();
            setFormat( match.capturedStart()
                     , match.capturedLength()
                     , rule.format
            );
        }
    }
    setCurrentBlockState(0);
    
    // Match multiline code
    int start = 0;
    if ( previousBlockState() != 1 ) {
        start = text.indexOf( m_multilineCodeExpr );
    }
    while ( start >= 0 ) {
        QRegularExpressionMatch match = m_multilineCodeExpr.match( text, start );
        int end = match.capturedStart();
        int codeLen = 0;
        if ( end != -1 ) {
            setCurrentBlockState(1);
            codeLen = end - start + match.capturedLength();
        } else {
            break;
        }
        
        setFormat( start, codeLen, m_codeFormat );
        start = text.indexOf( m_multilineCodeExpr, start + codeLen );
    }
    if ( previousBlockState() == 1 ) {
        setFormat( 0, text.length(), m_codeFormat );
        setCurrentBlockState(1);
    }
}




} // namespace mdhtml

