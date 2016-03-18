set(E_ENGINE_S
		emain.cpp
		emods.cpp
		eutils.cpp
		ewidgets.cpp
)

set(E_ENGINE_H
		emain.h
		emods.h
		eutils.h
		ewidgets.h
)

SET(M_USING_MODULES Core Network Widgets OpenGl)
M_E_BUILD(E_ENGINE)
