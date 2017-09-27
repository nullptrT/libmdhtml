
if( MDHTML_BUILD_BIN )
    add_executable( md2html main.cpp )
    target_link_libraries( md2html MdHtml++ )
    
    if( MDHTML_INSTALL_LIBS )
		install(TARGETS md2html DESTINATION ${MDHTML_DESTDIR}/bin )
    endif()
endif()
