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
find_package(Qt5Concurrent)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Declarative)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11")
# -fPIC ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}

include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(Engine)
include_directories(Launcher)
include_directories(ModLoader)

#Sets

set(G_SOURCE_FILES
		Engine/econtainers.cpp
		Engine/emain.cpp
		Engine/emods.cpp
		Engine/eutils.cpp
		Engine/ewidgets.cpp
)

set(G_HEADERS
		Engine/econtainers.h
		Engine/edefines.h

		Engine/interfaces/iinventory.h
		Engine/interfaces/ilevel.h
		Engine/interfaces/imain.h
		Engine/interfaces/imods.h
		Engine/interfaces/irender.h
		Engine/interfaces/itext.h
		Engine/interfaces/iutils.h
		Engine/einterfaces.h

		Engine/emain.h
		Engine/emods.h
		Engine/eutils.h
		Engine/ewidgets.h
		Engine/qzipreader_p.h
		Engine/qzipwriter_p.h
		Engine/interfaces/iplayer.h)

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
		ModLoader/qcustomplot.cpp

		ModLoader/core/mcoremods.cpp
		 ModLoader/core/level/mblock.cpp
		 ModLoader/core/level/mchunk.cpp
	 	ModLoader/core/level/mgenerator.cpp
		 ModLoader/core/level/mregion.cpp
		 ModLoader/core/level/mlevel.cpp

	 	ModLoader/core/render/mcamera.cpp
		 ModLoader/core/render/mhelper.cpp
	 	ModLoader/core/render/mrender.cpp
	 	ModLoader/core/render/perf/mperfw.cpp
	 	ModLoader/core/render/gui/mgui.cpp
	 	ModLoader/core/render/world/mworld.cpp

		ModLoader/core/mactions.cpp
		ModLoader/mods/mmods.cpp
		ModLoader/mods/mcontainers.cpp
		ModLoader/mods/mtext.cpp
		ModLoader/mods/mscript.cpp
		ModLoader/mods/mplugin.cpp
		ModLoader/core/player/mplayer.cpp)

set(M_HEADERS
		ModLoader/mmodloader.h
		ModLoader/mutils.h
		ModLoader/mdefines.h
		ModLoader/qcustomplot.h

		ModLoader/core/mcoremods.h
		 ModLoader/core/level/mblock.h
	 	ModLoader/core/level/mchunk.h
		 ModLoader/core/level/mgenerator.h
		 ModLoader/core/level/mregion.h
		 ModLoader/core/level/mlevel.h

		 ModLoader/core/render/mcamera.h
	 	ModLoader/core/render/mhelper.h
	 	ModLoader/core/render/mrender.h
		 ModLoader/core/render/perf/mperfw.h
		 ModLoader/core/render/gui/mgui.h
		 ModLoader/core/render/world/mworld.h

		ModLoader/core/mactions.h
		ModLoader/mods/mmods.h
		ModLoader/mods/mcontainers.h
		ModLoader/mods/mtext.h
		ModLoader/mods/mscript.h
		ModLoader/mods/mplugin.h
		ModLoader/core/player/mplayer.h)

qt5_wrap_cpp(GENERATED_SOURCES ${G_HEADERS})
qt5_wrap_cpp(GENERATED_SOURCES ${L_HEADERS})
qt5_wrap_cpp(GENERATED_SOURCES ${M_HEADERS})

add_executable(Engine ${G_SOURCE_FILES} ${G_HEADERS})
qt5_use_modules(Engine Core Widgets Network OpenGL)
target_compile_features(Engine PRIVATE cxx_range_for)
target_link_libraries(Engine ${ZLIB_LIBRARIES} ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})

add_executable(Launcher ${L_SOURCE_FILES} ${L_HEADERS})
qt5_use_modules(Launcher Core Widgets Network)
target_compile_features(Launcher PRIVATE cxx_range_for)
target_link_libraries(Launcher ${Qt5Core_QTMAIN_LIBRARIES})

add_executable(Runner Runner/main.cpp)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
add_library(ModLoader SHARED ${M_SOURCE_FILES} ${M_HEADERS})
qt5_use_modules(ModLoader Core Widgets Network OpenGL)
target_compile_features(ModLoader PRIVATE cxx_range_for)
target_link_libraries(ModLoader ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})

