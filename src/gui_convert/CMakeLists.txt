
include_directories(.)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

include_directories( ${Qt5Core_INCLUDE_DIRS}
                     ${Qt5Widgets_INCLUDE_DIRS}
                     ${Qt5Gui_INCLUDE_DIRS} )

add_library( MdHtmlGUI_convert mainwindow.cpp )
target_link_libraries( MdHtmlGUI_convert MdHtml++ Qt5::Core Qt5::Widgets Qt5::Gui )

if ( UNIX )
    add_executable( MdHtmlGUI main.cpp )
else()
    add_executable( MdHtmlGUI WIN32 main.cpp )
endif()
target_link_libraries( MdHtmlGUI MdHtmlGUI_convert MdHtml++ Qt5::Core )


install(TARGETS MdHtmlGUI DESTINATION ${MDHTML_DESTDIR}/bin )
