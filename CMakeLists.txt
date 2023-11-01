cmake_minimum_required(VERSION 3.5)

project(PostMachine VERSION 0.3.5 LANGUAGES CXX)

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
)

include_directories(src)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(Application
                MANUAL_FINALIZATION
                ${PROJECT_SOURCES}
                ${APP_ICON_RESOURCE_WINDOWS}
        )
else()
        add_executable(Application
                ${PROJECT_SOURCES}
                ${APP_ICON_RESOURCE_WINDOWS}
        )
endif()

target_link_libraries(Application PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
