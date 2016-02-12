set(E_SOURCE_FILES
		econtainers.cpp
		emain.cpp
		emods.cpp
		eutils.cpp
		ewidgets.cpp
		)

set(E_HEADERS
		econtainers.h
		edefines.h

		interfaces/iinventory.h
		interfaces/ilevel.h
		interfaces/imain.h
		interfaces/imods.h
		interfaces/iplayer.h
		interfaces/irender.h
		interfaces/itext.h
		interfaces/iutils.h
		einterfaces.h

		emain.h
		emods.h
		eutils.h
		ewidgets.h
		edvars.h
		interfaces/ievent.h)

qt5_wrap_cpp(GENERATED_SOURCES ${E_HEADERS})

add_executable(Engine ${E_SOURCE_FILES} ${E_HEADERS})
qt5_use_modules(Engine Core Widgets Network OpenGL)
target_compile_features(Engine PRIVATE cxx_range_for)
target_link_libraries(Engine ${ZLIB_LIBRARIES} ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})