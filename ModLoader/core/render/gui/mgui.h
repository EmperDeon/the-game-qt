#ifndef GLOBALQT_MGUI_H
#define GLOBALQT_MGUI_H
#include <ModLoader/mdefines.h>

class MGuiRender : public IGuiRender{ // 2D
public:
	MGuiRender();

	virtual void render() override;
	virtual void close()  override;
};


#endif //GLOBALQT_MGUI_H
