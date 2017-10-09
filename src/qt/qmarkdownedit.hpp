/**
 * @brief
 * @package LibMdHtmlQt
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibMdHtmlQt: A library for editing and showing documents of LibMdHtml++
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

#include <QTextEdit>

namespace mdhtml {
class QMarkDownSyntax;
}


/**
 * @brief A widget class that provides a QTextEdit with syntax highlighting for markdown, conversion to HTML and corresponding signals and slots
 */
class QMarkDownEdit
    :   public QTextEdit
{
    Q_OBJECT

    mdhtml::QMarkDownSyntax* m_syntax;
    
public:
    /**
     * @brief Constructor.
     * @param parent The parent widget
     */
    QMarkDownEdit( QWidget* parent = 0 );
    /**
     * @brief Destructor. Disconnects all signals and slots of this object.
     */
    ~QMarkDownEdit();
    
    /**
     * @brief Get a HTML version of the current markdown text of this QMarkDownEdit
     * @returns A QString containing the converted content obtained from mdhtml::md2html
     */
    const QString toHtml() const;

signals:
    /**
     * @brief This signal is emitted, when the current HTML has changed
     * @param html The HTML converted from the current markdown content of this QTextEdit
     */
    void htmlChanged( QString html );
    /**
     * @brief This signal is emitted, when the current markdown text has changed
     * @param markdown The current content of this QTextEdit
     */
    void markdownChanged( QString markdown );

private slots:
    void on_textChanged();
};
