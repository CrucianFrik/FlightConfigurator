set(LIB_NAME map_lib)

# QGIS
set(CMAKE_MODULE_PATH "$ENV{QGISPATH}/cmake" ${CMAKE_MODULE_PATH})
find_package(QGIS REQUIRED)

find_package(Qt5 COMPONENTS
				Core
				Gui
				Widgets
				Xml
				Svg
				REQUIRED)

# Source code
set(MAP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/mapwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mapbuttons.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mapcontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datamapwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/planmapwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dronemarker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/flightplan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/plan_attrs.cpp
    )

set(MAP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/mapwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mapbuttons.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mapcontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/datamapwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/planmapwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dronemarker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/flightplan.h
    ${CMAKE_CURRENT_SOURCE_DIR}/plan_attrs.h
    )

set(MAP_LIBRARIES
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    Qt5::Svg
    ${QGIS_LIBRARY}
)

add_library(${LIB_NAME} STATIC ${MAP_HEADERS} ${MAP_SOURCES})
target_sources(${LIB_NAME} PUBLIC ${MAP_HEADERS} ${MAP_SOURCES})

target_include_directories(${LIB_NAME} PRIVATE
                            ${QGIS_INCLUDE_DIR}
                          )
                          
target_link_libraries (${LIB_NAME} ${MAP_LIBRARIES})
