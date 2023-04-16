cmake_minimum_required(VERSION 3.16)
set(PROJECT FlightConfigurator_v1)
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

# QGIS
set(CMAKE_MODULE_PATH "$ENV{QGISPATH}/cmake" ${CMAKE_MODULE_PATH})
find_package(QGIS REQUIRED)

# Enable Qt modules
find_package(Qt5 COMPONENTS
				Core
				Gui
				Widgets
				Network
				SerialPort
				Positioning
				Xml
				Sql
				REQUIRED)

# GDAL
find_library(GDAL_LIBRARY NAMES gdal PATHS /usr/lib)
message(STATUS "GDALL_LIBRARY: ${GDAL_LIBRARY}")


set(LIBRARIES
    Qt5::Widgets
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Positioning
    Qt5::Xml
    Qt5::Sql
    ${GDAL_LIBRARY}
    ${QGIS_LIBRARY}
)

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "binder/*.cpp" "binder/*.h")

# Include mavlink headers globaly
include_directories("3dparty/mavlink_v2")
include_directories("3dparty/mavlink_v2/ardupilotmega")

set(SOURCES
	main.cpp
    mainwindow.cpp
    mapwidget.cpp
	mapbuttons.cpp
	mapcontroller.cpp
    )


set(HEADERS
    mainwindow.h
	mapwidget.h
	mapbuttons.h
	mapcontroller.h
    )


set(UIS
    mainwindow.ui
    )


add_executable(${PROJECT}
               ${SOURCES}
               ${HEADERS}
			   ${UIS}
			   ${INTERNAL_SOURCES}
               ${RESOURCES})

target_include_directories(${PROJECT} PRIVATE
                                      ${QGIS_INCLUDE_DIR}
                                      /usr/include/gdal)

target_link_libraries (${PROJECT} ${LIBRARIES})
