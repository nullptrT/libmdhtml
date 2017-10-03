
file (GLOB LIBMDHTML_HEADERS *.hpp )
file (GLOB LIBMDHTML_SOURCES *.cpp )

if( MDHTML_SHARED )
	add_library( MdHtml++ SHARED ${LIBMDHTML_SOURCES} )
	set( MDHTML_PKGCONFIG_LIBNAME "libMdHtml++.so" )
else()
	add_library( MdHtml++ STATIC ${LIBMDHTML_SOURCES} )
	set( MDHTML_PKGCONFIG_LIBNAME "libMdHtml++.a" )
endif()

if( MDHTML_QT_SUPPORT )
    add_subdirectory( qt )
endif()

if( MDHTML_BUILD_BIN )
    add_subdirectory( bin )
endif()

if( MDHTML_HEADER_INSTALL_DIR )
else()
	set( MDHTML_HEADER_INSTALL_DIR ${MDHTML_DESTDIR}/include/libMDHTML )
endif()

if ( MDHTML_LIB_INSTALL_DIR )
else()
	set ( MDHTML_LIB_INSTALL_DIR ${MDHTML_DESTDIR}/lib )
endif()

if( MDHTML_INSTALL_LIBS )
	install(TARGETS MdHtml++ DESTINATION ${MDHTML_LIB_INSTALL_DIR} )
	install(FILES ${LIBMDHTML_HEADERS} DESTINATION ${MDHTML_HEADER_INSTALL_DIR} )
	install(FILES ${PROJECT_SOURCE_DIR}/lib/LibMdHtml++Config.cmake DESTINATION "${MDHTML_LIB_INSTALL_DIR}/cmake/LibMDHTML" )
	configure_file(${PROJECT_SOURCE_DIR}/lib/libMdHtml++.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libMdHtml++.pc @ONLY)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libMdHtml++.pc DESTINATION "${MDHTML_LIB_INSTALL_DIR}/pkgconfig" )
endif()
