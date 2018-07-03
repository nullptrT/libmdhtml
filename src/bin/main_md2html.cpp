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


#include "markdown_document.hpp"

#include <iostream>


// If enabled, produces a lot more outout than normal
bool debug = false;

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
