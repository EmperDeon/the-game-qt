#ifndef GLOBALQT_MPERFW_H
#define GLOBALQT_MPERFW_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/render/mrender.h>
#include <ModLoader/qcustomplot.h>

class MCoreMods;
class MGlWidget;

class MPerfomanceWidget : public QWidget{
	QHBoxLayout* layout;
	QCustomPlot* customPlot;
 QCPGraph* gr; // Fps graph
 QCPGraph* dn; // Down line

	MCoreMods* loader;
	MGlWidget* render;

	QTimer* stab;
	QVector<int>* fps_v;
public:
	MPerfomanceWidget(MCoreMods* m);
public slots:
	void updateFps();
};

#endif //GLOBALQT_MPERFW_H
