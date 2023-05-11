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

set(SOURCES
	main.cpp
    mainwindow.cpp
    logger.cpp
    horizon.cpp
    )


set(HEADERS
    mainwindow.h
    logger.h
    horizon.h
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

               ${RESOURCES})


target_include_directories(${PROJECT} PRIVATE
                                      ${QGIS_INCLUDE_DIR}
                          )


#target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/map ${CMAKE_SOURCE_DIR}/pix)
target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/pix)

#target_link_libraries(${PROJECT} PRIVATE map_lib pix_lib ${LIBRARIES})
target_link_libraries(${PROJECT} PRIVATE pix_lib ${LIBRARIES})
