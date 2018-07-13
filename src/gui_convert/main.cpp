/**
 * @brief
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

#include "mainwindow.hpp"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "BibTeX2WebsiteGUI v" << LIBMDHTML_VERSION << " (https://git.0ptr.de/nullptr_t/bibtex2website)" << std::endl;
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
