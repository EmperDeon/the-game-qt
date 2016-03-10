set(E_LAUNCHER_S
		lmain.cpp
		lutils.cpp
		lwidgets.cpp
		lparser.cpp
		lwmodels.cpp
		widgets/lmodeditor.cpp
		widgets/lmods.cpp
)

set(E_LAUNCHER_H
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

SET(M_USING_MODULES Core Network Widgets)
M_BUILD(E_LAUNCHER)