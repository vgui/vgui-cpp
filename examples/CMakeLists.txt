cmake_minimum_required(VERSION 3.1)

project(examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#include_directories(${CMAKE_PREFIX_PATH}/include/cairo)
#include_directories(${CMAKE_PREFIX_PATH}/include/freetype2)
#include_directories(${CMAKE_PREFIX_PATH}/lib/cairomm-1.16/include ${CMAKE_PREFIX_PATH}/include/cairomm-1.16)
#include_directories(${CMAKE_PREFIX_PATH}/lib/sigc++-3.0/include ${CMAKE_PREFIX_PATH}/include/sigc++-3.0)
#find_package(PkgConfig)
#pkg_check_modules(CAIROMM cairomm-1.16)
#message("Cairomm-1.16 dirs: " ${CAIROMM_INCLUDE_DIRS} ${CAIROMM_LIBRARY_DIRS})
#include_directories( ${CAIROMM_INCLUDE_DIRS}  )
#link_directories( ${CAIROMM_LIBRARY_DIRS}  )
#find_library(CAIROMM_LIBRARY cairomm-1.16)

#link_libraries(${CAIROMM_LIBRARY})
add_executable(MainWindow MainWindow.cpp)
target_link_libraries(MainWindow mingw32)

