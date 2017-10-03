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


#include "qmarkdownedit.hpp"

#include "../md2html.hpp"


QMarkDownEdit::QMarkDownEdit( QWidget* parent )
    :   QTextEdit( parent )
{
    QObject::connect( this, &QTextEdit::textChanged, this, &QMarkDownEdit::on_textChanged );
}


QMarkDownEdit::~QMarkDownEdit() {
    this->disconnect();
}


const QString QMarkDownEdit::toHtml() const {
    return QString().fromStdString( mdhtml::md2html(toPlainText().toStdString()) );
}


void QMarkDownEdit::on_textChanged() {
    std::string html = mdhtml::md2html( toPlainText().toStdString() );
    
    emit htmlChanged( QString().fromStdString(html) );
    emit markdownChanged( toPlainText() );
}

