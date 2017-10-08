# FindLibMdHtmlQt
# ---------------
#
# Try to find the LibMdHtmlQt library
#
# Once done this will define
#   LIBMDHTMLQT_FOUND - System has LibMdHtmlQt
#   LIBMDHTMLQT_INCLUDE_DIR - The LibMdHtmlQt include directory
#   LIBMDHTMLQT_LIBRARY - The libraries needed to use LibMdHtmlQt
#   LIBMDHTMLQT_VERSION - the version of LibMdHtmlQt found (since CMake 2.8.8)
#   LIBMDHTMLQT_VERSION_STRING - the version of LibMdHtmlQt found (since CMake 2.8.8)
#
#
#	LibMdHtmlQt: A library for converting markdown to html
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


find_path(LIBMDHTMLQT_INCLUDE_DIR NAMES qmarkdownedit.hpp)
find_library(LIBMDHTMLQT_LIBRARY NAMES MdHtmlQt)

if(LIBMDHTMLQT_INCLUDE_DIR AND EXISTS "${LIBMDHTMLQT_INCLUDE_DIR}/../version_mdhtml.hpp")
    file(STRINGS "${LIBMDHTMLQT_INCLUDE_DIR}/../version_mdhtml.hpp" libmdhtml_version_str
         REGEX "^#define[\t ]+LIBMDHTML_DOTTED_VERSION[\t ]+\".*\"")

    string(REGEX REPLACE "^#define[\t ]+LIBMDHTML_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
           LIBMDHTMLQT_VERSION_STRING "${libmdhtml_version_str}")
    unset(libmdhtml_version_str)
endif()

# handle the QUIETLY and REQUIRED arguments and set LIBMDHTMLQT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibMdHtmlQt
                                  REQUIRED_VARS LIBMDHTMLQT_LIBRARY LIBMDHTMLQT_INCLUDE_DIR
                                  VERSION_VAR LIBMDHTMLQT_VERSION_STRING)

set( LIBMDHTMLQT_VERSION ${LIBMDHTMLQT_VERSION_STRING} )
mark_as_advanced(LIBMDHTMLQT_INCLUDE_DIR LIBMDHTMLQT_LIBRARY LIBMDHTMLQT_VERSION)

message("-- Found LibMdHtmlQt (version ${LIBMDHTMLQT_VERSION})") 
