
if( MDHTML_QT_SUPPORT )
  # Instruct CMake not to run moc automatically when needed.
	set(CMAKE_AUTOMOC ON)
	# Find the Qt libraries
	find_package(Qt5Core)
	find_package(Qt5Widgets)
	include_directories( ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} )
	# Build the qt library
	file ( GLOB LIBMDHTML_QT_SOURCES *.cpp )
	file ( GLOB LIBMDHTML_QT_HEADERS *.hpp )
	add_library( MdHtmlQt ${LIBMDHTML_QT_SOURCES} )
	target_link_libraries( MdHtmlQt MdHtml++ Qt5::Core Qt5::Widgets )

	if( MDHTML_INSTALL_LIBS )
		install(TARGETS MdHtmlQt DESTINATION ${MDHTML_LIB_INSTALL_DIR} )
		install(FILES ${LIBMDHTML_QT_HEADERS} DESTINATION ${MDHTML_HEADER_INSTALL_DIR}/qt )
	endif()
endif()
