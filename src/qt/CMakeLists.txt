
if( MDHTML_QT_SUPPORT )
  # Instruct CMake not to run moc automatically when needed.
	set(CMAKE_AUTOMOC ON)
	# Find the Qt libraries
	find_package(Qt5Core)
	find_package(Qt5Gui)
	find_package(Qt5WebKitWidgets)
	find_package(Qt5Widgets)
	include_directories( ${Qt5Core_INCLUDE_DIRS} ${Qt5WebKitWidgets_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} )
	# Build the qt library
	file ( GLOB LIBMDHTML_QT_SOURCES *.cpp )
	file ( GLOB LIBMDHTML_QT_HEADERS *.hpp )
	add_library( MdHtmlQt ${LIBMDHTML_QT_SOURCES} )
	target_link_libraries( MdHtmlQt MdHtml++ Qt5::Core Qt5::Gui Qt5::WebKitWidgets Qt5::Widgets )

	if( MDHTML_INSTALL_LIBS )
		install(TARGETS MdHtmlQt DESTINATION ${MDHTML_LIB_INSTALL_DIR} )
		install(FILES ${LIBMDHTML_QT_HEADERS} DESTINATION ${MDHTML_HEADER_INSTALL_DIR}/qt )install(FILES ${PROJECT_SOURCE_DIR}/lib/LibMdHtmlQtConfig.cmake DESTINATION "${MDHTML_LIB_INSTALL_DIR}/cmake/LibMdHtmlQt" )
        configure_file(${PROJECT_SOURCE_DIR}/lib/LibMdHtmlQt.pc.in ${CMAKE_CURRENT_BINARY_DIR}/LibMdHtmlQt.pc @ONLY)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libMdHtmlQt.pc DESTINATION "${MDHTML_LIB_INSTALL_DIR}/pkgconfig" )
	endif()
endif()
