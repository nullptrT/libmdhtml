project(libMdHtml++)

cmake_minimum_required( VERSION 3.0 )

set( LIBMDHTML_STABLE_VERSION 0 )
set( LIBMDHTML_RELEASE 0 )
set( LIBMDHTML_PATCH_VERSION 1 )
set( LIBMDHTML_SUFFIX "" )
set( LIBMDHTML_VERSION "${LIBMDHTML_STABLE_VERSION}.${LIBMDHTML_RELEASE}.${LIBMDHTML_PATCH_VERSION}${LIBMDHTML_SUFFIX}" )

set( LIBMDHTML_SRC_DIR ${PROJECT_SOURCE_DIR}/src )

if( UNIX )
	add_definitions( -std=c++11 )
endif()


if( MDHTML_DESTDIR )
else()
	set( MDHTML_DESTDIR "${CMAKE_INSTALL_PREFIX}" )
endif()

if( MDHTML_HEADER_INSTALL_DIR )
else()
	set( MDHTML_HEADER_INSTALL_DIR ${MDHTML_DESTDIR}/include/libMdHtml )
endif()

if ( MDHTML_LIB_INSTALL_DIR )
else()
	set ( MDHTML_LIB_INSTALL_DIR ${MDHTML_DESTDIR}/lib )
endif()


add_subdirectory( src )


if( UNIX )
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		message("-- Enabled doc_MdHtml target for make")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc_MdHtml ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
	endif()
endif()
