/**
 * @brief
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


#include "qhtmlview.hpp"

#include "qmarkdownedit.hpp"


QHtmlView::QHtmlView(QWidget* parent)
    :   QWebView( parent )
{}


QHtmlView::~QHtmlView() {
    this->disconnect();
}


void QHtmlView::setEditor( QMarkDownEdit* mdEditor ) {
    if ( mdEditor != 0 ) {
        QObject::connect( mdEditor, SIGNAL(htmlChanged(QString)), this, SLOT(on_textChanged(QString)) );
    }
}



void QHtmlView::on_textChanged( QString html ) {
    setHtml( html );
}


