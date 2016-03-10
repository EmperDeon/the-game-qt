#ifndef GLOBALQT_MPERFW_H
#define GLOBALQT_MPERFW_H
#include <idefines.h>
#include <mrender.h>
#include <qcustomplot.h>

class MGlWidget;

class MPerformanceWidget : public QWidget{
	Q_OBJECT

	QHBoxLayout* layout;
	QCustomPlot* plot;
 QCPGraph* gr; // Fps graph
 QCPGraph* dn; // Down line
 float yMax = 10.0f;

	MGlWidget* render;

	QTimer* stab;
	int sec = 0;
	QVector<float>* v_fps;
	
public slots:
	void updateFps();
	
public:
	MPerformanceWidget();
};

#endif //GLOBALQT_MPERFW_H
