set(O_RENDER_S
		main.cpp
		mrender.cpp
  mcamera.cpp
		mhelper.cpp
		qcustomplot.cpp

		gui/mgui.cpp
		perf/mperfw.cpp
		texture/mtexturemanager.cpp
		world/mworld.cpp
		)
set(O_RENDER_H
		main.h
		mrender.h
		mcamera.h
		mhelper.h
		qcustomplot.h

		gui/mgui.h
		perf/mperfw.h
		texture/mtexturemanager.h
		world/mworld.h
		)
SET(M_USING_MODULES Core Network Widgets OpenGl)

M_BUILD(O_RENDER)