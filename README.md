# LibMdHtml
##### A library for converting markdown to html
###### v0.5.0

This library provides the possibility to create the easy-to-use markdown documents and convert them to HTML documents.

* A documentation can be found [here](https://doc.0ptr.de/libmdhtml)

#### Currently supported features

* Markdown for headings, simple text formatting and lists
* CMake and pkgconfig files
* Syntax highlighting for Qt
* Simple Qt GUI for converting markdown files to html
* Documentation
* PKGBUILD for Arch Linux

###### Future features

* Simple Qt GUI for editing markdown documents with live html preview
* Support all Markdown formats including tables
* Test on windows

___

## LICENSE

The library is published and usable under the terms of the LGPLv3:

```
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
```

___

## Building

You can simply build this with:

```
 % cd /path/to/clone/in
 % git clone https://github.com/nullptrT/libmdhtml.git
 % mkdir libmdhtml/build
 % cd libmdhtml/build
 % cmake .. # You may add CMake options here (see below)
 % make
```

On windows you may use the `cmake-gui` or `qtcreator` to create build files for MSVC 2015 or later.


#### CMake options

Additionally to the default options CMake currently offers the following options (can be specified with `-DOPTION=ON`):

* `MDHTML_SHARED`: Enables building a shared library `libMdHtml++.so`. Not using this option builds a static `libMdHtml++.a` by default.
* `MDHTML_DONT_BUILD_BIN`: Don't build the command line utility that converts a markdown document into a html document.
* `MDHTML_DONT_BUILD_GUI_CONVERT`: Don't build the QtGUI for converting markdown documents to html documents.
* `MDHTML_QT_SUPPORT`: Build the libMdHtmlQt library providing some widgets and convenience functions for editing markdown with Qt.
* `MDHTML_DESTDIR`: Where are the files installed to. Defaults to `CMAKE_INSTALL_PREFIX` (`/usr` on UNIX and `C:\Program Files` on WIN32)
* `MDHTML_HEADER_INSTALL_DIR`: Can be set to control, where headers are installed. Defaults to `MDHTML_DESTDIR/include/libMDHTML`.
* `MDHTML_LIB_INSTALL_DIR`: Can be set to control where the library is installed. Defaults to `MDHTML_DESTDIR/lib`.
* `MDHTML_INSTALL_LIBS`: Enables targets for installation of library files. Because it is useful not to install the library (e.g. when used as submodule of a project) this defaults to off. If enabled, it installs all headers to `MDHTML_HEADER_INSTALL_DIR` and the libraries to `MDHTML_LIB_INSTALL_DIR`

#### Compiler options / Config variables

You can define the following with your g++-compiler by `-DOPTION=ON` or cmake's `add_definitions( -DOPTION=ON )` function:

*

___

#### Usage

The most simple way to convert a markdown string to html is the following:
```c++
#include <iostream>
#include <libmdhtml/md2html.hpp>

int main(int argc, char **argv) {
    if ( argc != 2) {
        std::cout << "Usage: /path/to/binary <MARKDOWN_STRING>"
        return 1;
    }
    
    std::cout << "Markdown string:" << std::endl << argv[1] << std::endl << std::endl;
    
    const std::string html = mdhtml::md2html( argv[1] );
    
    std::cout << "HTML string:" << std::endl << html << std::endl;
    
    return 0;
}
```

There is a class for handling markdown from files and its html to string or file, too:
```c++
#include <iostream>
#include <libmdhtml/markdown_document.hpp>


void help() {
    std::cout << "md2html [-h] infile outfile" << std::endl;
    std::cout << std::endl;
    std::cout << "    infile: The input file in markdown format." << std::endl;
    std::cout << "    outfile: The output file in html format." << std::endl;
}


int main(int argc, char **argv) {
    
    if ( argc == 2 && std::string(argv[1]) == "-h" ) {
        help();
        return 0;
    } else if ( argc != 3 ) {
        help();
        return 1;
    }
    
    mdhtml::MarkdownDocument* md = mdhtml::MarkdownDocument::fromFile( argv[1] );
    if ( md == 0 ) {
        std::cerr << "Failed to read file '" << argv[1] << "'." << std::endl;
        return 1;
    } else if ( !md->html_toFile( argv[2]) ) {
        std::cerr << "Failed to generate html and write to file '" << argv[2] << "'." << std::endl;
        return 1;
    }
    
    return 0;
}
```
