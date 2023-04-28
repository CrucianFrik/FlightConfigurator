cmake_minimum_required(VERSION 3.16)
set(PROJECT FlyghtConfigurator_v1)
project(${PROJECT} VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(TARGET_SOURCE_DIR ${CMAKE_SOURCE_DIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Add compiler flags
add_compile_options(-std=c++11 -Wall)

# Enable Qt modules
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
	Network
	SerialPort
	Positioning
	REQUIRED)

set(LIBRARIES
# Qt5
    Qt5::Widgets
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Positioning
)

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "binder/*.cpp" "binder/*.h")

# Include mavlink headers globaly
include_directories("3dparty/mavlink_v2")
include_directories("3dparty/mavlink_v2/ardupilotmega")

set(SOURCES
    main.cpp
    mainwindow.cpp
    )

set(HEADERS
    gismainwindow.h
    mainwindow.h
    )

set(UIS
    mainwindow.ui
    )

set(RESOURCES
    )

add_executable(${PROJECT}
               ${SOURCES}
               ${HEADERS}
	       ${UIS}
	       ${INTERNAL_SOURCES}
	       ${RESOURCE})

target_link_libraries (${PROJECT} ${LIBRARIES})
