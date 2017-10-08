# FindLibMdHtml++
# ---------------
#
# Try to find the LibMdHtml++ library
#
# Once done this will define
#   LIBMDHTML_FOUND - System has LibMdHtml++
#   LIBMDHTML_INCLUDE_DIR - The LibMdHtml++ include directory
#   LIBMDHTML_LIBRARY - The libraries needed to use LibMdHtml++
#   LIBMDHTML_VERSION - the version of LibMdHtml++ found (since CMake 2.8.8)
#   LIBMDHTML_VERSION_STRING - the version of LibMdHtml++ found (since CMake 2.8.8)
#
#
#	LibMdHtml++: A library for converting markdown to html
#	Copyright (C) 2017 Sebastian Lau
#
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public
#	License as published by the Free Software Foundation; either
#	version 2.1 of the License, or (at your option) any later version.
#
#	This library is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	Lesser General Public License for more details.
#
#	You should have received a copy of the GNU Lesser General Public
#	License along with this library; if not, write to the Free Software
#	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
#	USA
#


find_path(LIBMDHTML_INCLUDE_DIR NAMES md2html.hpp)
find_library(LIBMDHTML_LIBRARY NAMES MdHtml++)

if(LIBMDHTML_INCLUDE_DIR AND EXISTS "${LIBMDHTML_INCLUDE_DIR}/version_mdhtml.hpp")
    file(STRINGS "${LIBMDHTML_INCLUDE_DIR}/version_mdhtml.hpp" libmdhtml_version_str
         REGEX "^#define[\t ]+LIBMDHTML_DOTTED_VERSION[\t ]+\".*\"")

    string(REGEX REPLACE "^#define[\t ]+LIBMDHTML_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
           LIBMDHTML_VERSION_STRING "${libmdhtml_version_str}")
    unset(libmdhtml_version_str)
endif()

# handle the QUIETLY and REQUIRED arguments and set LIBMDHTML_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMdHtml++
                                  REQUIRED_VARS LIBMDHTML_LIBRARY LIBMDHTML_INCLUDE_DIR
                                  VERSION_VAR LIBMDHTML_VERSION_STRING)

set( LIBMDHTML_VERSION ${LIBMDHTML_VERSION_STRING} )
mark_as_advanced(LIBMDHTML_INCLUDE_DIR LIBMDHTML_LIBRARY LIBMDHTML_VERSION)

message("-- Found LibMdHtml++ (version ${LIBMDHTML_VERSION})") 
