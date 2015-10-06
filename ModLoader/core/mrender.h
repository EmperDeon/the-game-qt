#ifndef M_RENDER
#define M_RENDER

#include <Global/gmodinterfaces.h>
#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>
#include <ModLoader/core/mcoremods.h>

class MCoreMods;

class MRender : public IRender{
	Q_INTERFACES(IRender)

	MCoreMods* loader;
public:
	MRender(MCoreMods* m);
	void init() Q_DECL_OVERRIDE;
	void render(QPaintDevice* dev) Q_DECL_OVERRIDE;

	~MRender();
};

#endif
