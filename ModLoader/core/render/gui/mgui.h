#ifndef GLOBALQT_MGUI_H
#define GLOBALQT_MGUI_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>

class MGuiRender : public IGuiRender{ // 2D
	QString className = "M-GuiRender";
	MCoreMods* loader;
public:
	MGuiRender(MCoreMods* m);
	virtual void render();
	virtual void close();
};


#endif //GLOBALQT_MGUI_H
