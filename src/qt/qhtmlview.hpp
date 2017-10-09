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

#include <QtWebKitWidgets/QWebView>

class QMarkDownEdit;


/**
 * @brief A widget class that can display HTML and is reponsive to the changing of the text of a QMarkDownEdit
 */
class QHtmlView
    :   public QWebView
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent The parent widget
     */
    QHtmlView( QWidget* parent = 0 );
    /**
     * @brief Destructor. Disconnects all signals and slots of this object.
     */
    ~QHtmlView();
    
    /**
     * @brief Set the QMarkDownEdit this QHtmlView has to respond to, that means, everytime the QMarkDownEdit object emits &QMarkDownEdit::htmlChanged, the slot &QHtmlView::on_textChanged is called.
     * @param mdEditor The QMarkDownEdit to connect with. Nothing is connected, if mdEditor == 0. Calling this function multiple times with different parameters connects all QMarkDownEdit objects.
     */
    void setEditor( QMarkDownEdit* mdEditor );
    
public slots:
    /**
     * @brief Set the received string as HTML content of this QWebView
     * @param html A HTML string to render
     */
    void on_textChanged( QString html );
};
