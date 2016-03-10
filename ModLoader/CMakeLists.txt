set(E_MODLOADER_S
		mmodloader.cpp
		mutils.cpp

		core/mcoremods.cpp

		mods/mmods.cpp
		mods/mcontainers.cpp
		mods/mtext.cpp
		mods/mscript.cpp
		mods/mplugin.cpp
		)

set(E_MODLOADER_H
		mmodloader.h
		mutils.h

		core/mcoremods.h

		mods/mmods.h
		mods/mcontainers.h
		mods/mtext.h
		mods/mscript.h
		mods/mplugin.h
		)

SET(M_USING_MODULES Core Network Widgets OpenGl)
M_BUILD(E_MODLOADER)
