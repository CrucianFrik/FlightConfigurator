cmake_minimum_required(VERSION 3.16)
project(fc_maptest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(TARGET_SOURCE_DIR ${CMAKE_SOURCE_DIR})


set(CMAKE_MODULE_PATH "$ENV{QGISPATH}/cmake" ${CMAKE_MODULE_PATH})
#set(LD_LIBRARY_PATH "$ENV{LD_LIBRARY_PATH}" ${LD_LIBRARY_PATH})

find_package(QGIS REQUIRED)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        Sql
        REQUIRED)

find_library(GDAL_LIBRARY NAMES gdal PATHS /usr/lib)
message(STATUS "GDALL_LIBRARY: ${GDAL_LIBRARY}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(fc_maptest  main.cpp
                           mapwindow.cpp
                           mapwindow.h)

target_include_directories(fc_maptest PRIVATE
                                      ${QGIS_INCLUDE_DIR}
                                      /usr/include/gdal)

target_link_libraries(fc_maptest
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Sql
        ${GDAL_LIBRARY}
        ${QGIS_LIBRARY}
        )
