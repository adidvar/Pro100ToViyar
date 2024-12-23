cmake_minimum_required(VERSION 3.30)

project(Pro100toViyar VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

file(GLOB PROJECT_SOURCES
     src/*.hpp
     src/*.cpp
     src/*.ui
)

include_directories(src)

if (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/data/info.rc")
endif ()

qt_add_executable(Application
                ${PROJECT_SOURCES}
                ${APP_ICON_RESOURCE_WINDOWS}
                data/recources.qrc)

target_link_libraries(Application PRIVATE Qt6::Core Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS Application
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET Application
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
