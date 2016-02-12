set(L_SOURCE_FILES
		lmain.cpp
		lutils.cpp
		lwidgets.cpp
		lparser.cpp
		lwmodels.cpp
		widgets/lmodeditor.cpp
		widgets/lmods.cpp
		)

set(L_HEADERS
		lmain.h
		lutils.h
		lwidgets.h
		lparser.h
		qzipreader_p.h
		qzipwriter_p.h
		ldefines.h
		lwmodels.h
		widgets/llevel.h
		widgets/lmodel.h
		widgets/lresources.h
		widgets/lmodeditor.h
		widgets/lmods.h
		)

qt5_wrap_cpp(GENERATED_SOURCES ${L_HEADERS})

add_executable(Launcher ${L_SOURCE_FILES} ${L_HEADERS})
qt5_use_modules(Launcher Core Widgets Network)
target_compile_features(Launcher PRIVATE cxx_range_for)
target_link_libraries(Launcher ${Qt5Core_QTMAIN_LIBRARIES})