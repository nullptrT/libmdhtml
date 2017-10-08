
if( MDHTML_BUILD_BIN )
    include_directories( .. )
    add_executable( md2html main_md2html.cpp )
    target_link_libraries( md2html MdHtml++ )
    
    if( MDHTML_INSTALL_LIBS )
		install(TARGETS md2html DESTINATION ${MDHTML_DESTDIR}/bin )
    endif()
endif()
