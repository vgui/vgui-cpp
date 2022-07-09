cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(vgui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directory where exe,dll and static library saved
set(VGUI_BINARY_DIR ${CMAKE_BINARY_DIR}/bin-${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VGUI_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VGUI_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${VGUI_BINARY_DIR})

add_subdirectory(3dparty/kcanvas/src)
include_directories(3dparty/kcanvas/include)
include_directories(3dparty/kcommon/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(examples)
