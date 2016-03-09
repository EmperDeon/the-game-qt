set(M_SOURCE_FILES
		mmodloader.cpp
		mutils.cpp
		qcustomplot.cpp

		core/mcoremods.cpp

		core/level/mblock.cpp
		core/level/mchunk.cpp
		core/level/mgenerator.cpp
		core/level/mregion.cpp
		core/level/mlevel.cpp

		core/player/mplayer.cpp

		core/render/mcamera.cpp
		core/render/mhelper.cpp
		core/render/mrender.cpp
		core/render/perf/mperfw.cpp
		core/render/gui/mgui.cpp
		core/render/texture/mtexturemanager.cpp
		core/render/world/mworld.cpp

		core/events/mevents.cpp
		mods/mmods.cpp
		mods/mcontainers.cpp
		mods/mtext.cpp
		mods/mscript.cpp
		mods/mplugin.cpp
		)

set(M_HEADERS
		mmodloader.h
		mutils.h
		qcustomplot.h

		core/mcoremods.h

		core/level/mblock.h
		core/level/mchunk.h
		core/level/mgenerator.h
		core/level/mregion.h
		core/level/mlevel.h

		core/player/mplayer.h

		core/render/mcamera.h
		core/render/mhelper.h
		core/render/mrender.h
		core/render/perf/mperfw.h
		core/render/gui/mgui.h
		core/render/texture/mtexturemanager.h
		core/render/world/mworld.h

		core/events/mevents.h
		mods/mmods.h
		mods/mcontainers.h
		mods/mtext.h
		mods/mscript.h
		mods/mplugin.h
		)

qt5_wrap_cpp(GENERATED_SOURCES ${M_HEADERS})

add_library(ModLoader SHARED ${M_SOURCE_FILES} ${M_HEADERS})

qt5_use_modules(ModLoader Core Widgets Network OpenGL)

target_compile_features(ModLoader PRIVATE cxx_range_for)

target_link_libraries(ModLoader ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})