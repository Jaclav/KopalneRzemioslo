cmake_minimum_required(VERSION 3.10)

project(KopalneRzemioslo VERSION 5.0 DESCRIPTION Beta)

configure_file(include/version.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/version.hpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic -std=c++11 -Os -s)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (WIN32)
	file(GLOB SOURCES main.rc src/*.cpp)
else()
	file(GLOB SOURCES src/*.cpp)
endif(WIN32)

add_executable(KopalneRzemioslo ${SOURCES})

find_package(SFML 2.5.1 COMPONENTS audio graphics system window REQUIRED)
target_link_libraries(KopalneRzemioslo sfml-audio sfml-graphics sfml-system sfml-window)
