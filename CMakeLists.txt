cmake_minimum_required(VERSION 3.3)
project(GlobalQt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(dir D:/GameTmp/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5WebKitWidgets)
find_package(Qt5Declarative)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11")
# -fPIC ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}
include_directories(zlib)
include_directories(Global)
include_directories(Launcher)
include_directories(ModLoader)

add_subdirectory(zlib)

#Sets

set(G_SOURCE_FILES
		Global/gcontainers.cpp
		Global/gmain.cpp
		Global/gmods.cpp
		Global/gutils.cpp
		Global/gwidgets.cpp
)

set(G_HEADERS
		Global/gcontainers.h
		Global/gmodinterfaces.h
		Global/gmain.h
		Global/gmods.h
		Global/gutils.h
		Global/gwidgets.h
		Global/qzipreader_p.h
		Global/qzipwriter_p.h
)

set(L_SOURCE_FILES
		Launcher/lmain.cpp
		Launcher/lutils.cpp
		Launcher/lwidgets.cpp
		Launcher/lparser.cpp
)

set(L_HEADERS
		Launcher/lmain.h
		Launcher/lutils.h
		Launcher/lwidgets.h
		Launcher/lparser.h
		Launcher/qzipreader_p.h
		Launcher/qzipwriter_p.h
)

set(M_SOURCE_FILES
		ModLoader/mmodloader.cpp
		ModLoader/mutils.cpp
		ModLoader/mparser.cpp
		ModLoader/mrender.cpp
)

set(M_HEADERS
		ModLoader/mmodloader.h
		ModLoader/mutils.h
		ModLoader/mparser.h
		ModLoader/mrender.h
)

qt5_wrap_cpp(GENERATED_SOURCES ${G_HEADERS})
qt5_wrap_cpp(GENERATED_SOURCES ${L_HEADERS})
qt5_wrap_cpp(GENERATED_SOURCES ${M_HEADERS})


add_executable(Global ${G_SOURCE_FILES} ${G_HEADERS})
qt5_use_modules(Global Core Widgets Network WebKitWidgets OpenGL)
target_compile_features(Global PRIVATE cxx_range_for)
target_link_libraries(Global zlib ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})

add_executable(Launcher ${L_SOURCE_FILES} ${L_HEADERS})
qt5_use_modules(Launcher Core Widgets Network WebKitWidgets)
target_compile_features(Launcher PRIVATE cxx_range_for)
target_link_libraries(Launcher ${Qt5Core_QTMAIN_LIBRARIES})

add_executable(Runner Runner/main.cpp)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
add_library(ModLoader SHARED ${M_SOURCE_FILES} ${M_HEADERS})
qt5_use_modules(ModLoader Core Widgets Network WebKitWidgets)
target_compile_features(ModLoader PRIVATE cxx_range_for)
target_link_libraries(ModLoader ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})

