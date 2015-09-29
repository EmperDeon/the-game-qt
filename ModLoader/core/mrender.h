#ifndef M_RENDER
#define M_RENDER

#include <Global/gmodinterfaces.h>
#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>
#include <ModLoader/mmodloader.h>

class ModLoader;

class MRender : public IRender{
	Q_INTERFACES(IRender)

	ModLoader* loader;
public:
	MRender(ModLoader* m);
	void init() Q_DECL_OVERRIDE;
	void render(QPaintDevice* dev) Q_DECL_OVERRIDE;

	~MRender();
};

#endif
