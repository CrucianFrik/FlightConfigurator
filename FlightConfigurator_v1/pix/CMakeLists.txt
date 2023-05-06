set(LIB_NAME pix_lib)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/RecurseSubdirs.cmake)

# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/pixhawk_manager/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/pixhawk_manager/*.h")

find_package(Qt5 COMPONENTS
            Core
            Gui
            Widgets
            Network
            SerialPort
            Positioning
            Xml
            REQUIRED)

set(PIX_LIBRARIES
    Qt5::Widgets
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Positioning
    Qt5::Xml
)

add_library(${LIB_NAME} STATIC ${INTERNAL_SOURCES})
target_sources(${LIB_NAME} PUBLIC ${INTERNAL_SOURCES})

HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${LIB_NAME} PUBLIC ${INCLUDES} ${INTERNAL_INCLUDES})

# Include mavlink headers globaly
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3dparty/mavlink_v2)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3dparty/mavlink_v2/ardupilotmega)


target_link_libraries (${LIB_NAME} ${PIX_LIBRARIES})
