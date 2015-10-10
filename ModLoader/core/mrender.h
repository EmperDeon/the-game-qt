#ifndef M_RENDER
#define M_RENDER

#include <ModLoader/mdefines.h>
#include <Global/gmodinterfaces.h>
#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>
#include <ModLoader/core/mcoremods.h>

class MCoreMods;

class MRender : public IRender{
	Q_INTERFACES(IRender)
	QString className = "M-Render";
	MCoreMods* loader;
public:
	MRender(MCoreMods* m);
	void init() Q_DECL_OVERRIDE;
	void render(QPaintDevice* dev) Q_DECL_OVERRIDE;

	~MRender();
};

#endif
