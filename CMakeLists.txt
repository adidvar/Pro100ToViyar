cmake_minimum_required(VERSION 3.5)

project(PRO100C VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB PROJECT_SOURCES
     src/*.hpp
     src/*.cpp
     src/*.ui
)

include_directories(src)

if (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/data/info.rc")
endif ()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(PRO100C
                MANUAL_FINALIZATION
                ${PROJECT_SOURCES}
                ${APP_ICON_RESOURCE_WINDOWS}
                data/recources.qrc
        )
else()
        add_executable(PRO100C
                ${PROJECT_SOURCES}
                ${APP_ICON_RESOURCE_WINDOWS}
                data/recources.qrc
        )
endif()

target_link_libraries(PRO100C PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.Adidvar.PRO100C)
endif()
set_target_properties(PRO100C PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PRO100C
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PRO100C)
endif()
