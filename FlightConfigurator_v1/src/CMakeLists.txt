cmake_minimum_required(VERSION 3.8)
set(PROJECT FlightConfigurator_v1_build)
project(${PROJECT})
# project(${PROJECT} VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# QGIS
set(CMAKE_MODULE_PATH "$ENV{QGISPATH}/cmake" ${CMAKE_MODULE_PATH})
#find_package(QGIS REQUIRED)

#add_subdirectory(${CMAKE_SOURCE_DIR}/pix)
# set(TARGET_SOURCE_DIR ${CMAKE_SOURCE_DIR})

# Find includes in corresponding build directories
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# CMake modules
# include(cmake/RecurseSubdirs.cmake)

# Includes
# HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${INCLUDES} ${INTERNAL_INCLUDES})

# Add compiler flags
# add_compile_options(-std=c++11 -Wall)

# Enable Qt modules
# find_path(MAP_LIB ${CMAKE_SOURCE_DIR}/map ${CMAKE_SOURCE_DIR}/pix)

find_package(Qt5 COMPONENTS
				Core
				Gui
				Widgets
				Network
				SerialPort
				Positioning
				Xml
				Sql
				Svg
				REQUIRED)

set(LIBRARIES
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::SerialPort
    Qt5::Positioning
    Qt5::Xml
    Qt5::Sql
    Qt5::Svg
    ${QGIS_LIBRARY}
)

# Sources
# file(GLOB_RECURSE INTERNAL_SOURCES "pixhawk_manager/*.cpp" "pixhawk_manager/*.h")

# Include mavlink headers globaly
# include_directories("3dparty/mavlink_v2")
# include_directories("3dparty/mavlink_v2/ardupilotmega")

set(SOURCES
	main.cpp
    mainwindow.cpp
    )


set(HEADERS
    mainwindow.h
    )


set(UIS
    mainwindow.ui
    )

set(RESOURCES
    resources.qrc
    )

add_executable(${PROJECT}
               ${SOURCES}
               ${HEADERS}
               ${UIS}
			#    ${INTERNAL_SOURCES}
               ${RESOURCES})


target_include_directories(${PROJECT} PRIVATE
                                      ${QGIS_INCLUDE_DIR}
                          )

# target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/map ${CMAKE_SOURCE_DIR}/pix)  
target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/map ${CMAKE_SOURCE_DIR}/pix)  

# target_link_libraries(${PROJECT} PRIVATE map_lib pix_lib ${LIBRARIES})
target_link_libraries(${PROJECT} PRIVATE pix_lib ${LIBRARIES})
