cmake_minimum_required(VERSION 3.3)
project(GlobalQt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(MBUILDDIR D:/GameTmp/)

MACRO(M_SET_BUILD_DIR M_DIR)
 set(EXECUTABLE_OUTPUT_PATH ${M_DIR} CACHE PATH "Build directory" FORCE)
 set(LIBRARY_OUTPUT_PATH ${M_DIR} CACHE PATH "Build directory" FORCE)
 set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${M_DIR})
 set(CMAKE_BUILD_FILES_DIRECTORY ${M_DIR})
 set(CMAKE_BUILD_DIRECTORY ${M_DIR})
 set(CMAKE_BINARY_DIR ${M_DIR})
 set(EXECUTABLE_OUTPUT_PATH ${M_DIR})
 set(LIBRARY_OUTPUT_PATH ${M_DIR}lib)
 set(CMAKE_CACHEFILE_DIR ${M_DIR})
ENDMACRO(M_SET_BUILD_DIR)

MACRO(M_ADD_COREMOD M_NAME)
 M_SET_BUILD_DIR(${MBUILDDIR}/mods/coremods/${M_NAME})
	add_subdirectory(${M_NAME})
ENDMACRO(M_ADD_COREMOD)

MACRO(M_ADD_MOD M_NAME)
	M_SET_BUILD_DIR(${MBUILDDIR}/mods/mods/${M_NAME})
	add_subdirectory(${M_NAME})
ENDMACRO(M_ADD_MOD)

find_package(Qt5Core)
find_package(Qt5Concurrent)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Declarative)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(../GlobalQt) #crutch

# SUBDIRS

M_SET_BUILD_DIR(D:/GameTmp/)

add_subdirectory(Engine)
add_subdirectory(Launcher)
add_subdirectory(ModLoader)

add_executable(Runner Runner/main.cpp)

add_subdirectory(CoreMods)

add_subdirectory(Mods)
