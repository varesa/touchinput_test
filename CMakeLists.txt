cmake_minimum_required(VERSION 3.4)
project(touchinput)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0")

FIND_PACKAGE(X11 REQUIRED)

IF ( X11_FOUND )
        INCLUDE_DIRECTORIES( ${X11_INCLUDE_DIR} )
        LINK_LIBRARIES( ${X11_LIBRARIES} )
ENDIF (X11_FOUND)

set(SOURCE_FILES main.cpp Serial.cpp Serial.h MouseUInput.cpp MouseUInput.h MouseX11.cpp MouseX11.h)
add_executable(touchinput ${SOURCE_FILES})