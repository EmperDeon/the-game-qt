#include "mperfw.h"

//MPerfomanceWidget::MPerfomanceWidget(MCoreMods *m) {
//	this->loader = m;
//	this->render = mVarG(MGlWidget*, "mRender");
// this->fps_v = new QVector<int>;
//
// this->stab = new QTimer;
//	this->layout = new QHBoxLayout;
//	this->plot = new QCustomPlot;
//
//	this->plot->addGraph(); // blue line
//	this->plot->graph(0)->setPen(QPen(Qt::blue));
//	this->plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
//	this->plot->graph(0)->setAntialiasedFill(false);
//
//	this->plot->addGraph(); // red line
//	this->plot->graph(0)->setPen(QPen(Qt::red));
//
//	this->plot->graph(0)->setChannelFillGraph(this->plot->graph(1));
//
//	this->plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
//	this->plot->xAxis->setDateTimeFormat("hh:mm:ss");
//	this->plot->xAxis->setAutoTickStep(false);
//	this->plot->xAxis->setTickStep(2);
//	this->plot->axisRect()->setupFullAxesBox();
//
//// make left and bottom axes transfer their ranges to right and top axes:
//	connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
//	connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
//
//	this->stab->setInterval(10);
//	connect(stab, SIGNAL(timeout()), this, SLOT(updateFPS()));
// this->stab->start();
//
//	this->layout->addWidget(plot);
//	this->setLayout(layout);
//}
//
//void MPerfomanceWidget::updateFps() {
//// if(fps_v->size() > 19) fps_v->takeLast();
////	fps_v->push_front(int(render->getFps() % 1000));
//
//	double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
//	double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
//
//	this->plot->graph(0)->addData(key, value0);
//	this->plot->graph(1)->addData(key, 0.0f); // value1
//	this->plot->graph(0)->removeDataBefore(key-8);
//	this->plot->graph(1)->removeDataBefore(key-8);
//
//	this->plot->graph(0)->rescaleValueAxis();
//	this->plot->graph(1)->rescaleValueAxis(true);
//
//	this->plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
//	this->plot->replot();
//}

MPerfomanceWidget::MPerfomanceWidget(MCoreMods *m) {
	this->loader = m;
	this->render = mVarG(MGlWidget*, "mRender");
	this->fps_v = new QVector<int>;

	this->stab = new QTimer;
	this->layout = new QHBoxLayout;
	this->customPlot = new QCustomPlot;

	customPlot->addGraph(); // blue line
	customPlot->graph(0)->setPen(QPen(Qt::blue));
	customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
	customPlot->graph(0)->setAntialiasedFill(false);
	customPlot->addGraph(); // red line
	customPlot->graph(1)->setPen(QPen(Qt::red));
	customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

	customPlot->addGraph(); // blue dot
	customPlot->graph(2)->setPen(QPen(Qt::blue));
	customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
	customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
	customPlot->addGraph(); // red dot
	customPlot->graph(3)->setPen(QPen(Qt::red));
	customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
	customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

	customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
	customPlot->xAxis->setAutoTickStep(false);
	customPlot->xAxis->setTickStep(2);
	customPlot->axisRect()->setupFullAxesBox();

// make left and bottom axes transfer their ranges to right and top axes:
	connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
	connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

//
//	connect(stab, SIGNAL(timeout()), this, SLOT(updateFps()));
//	stab->start(0); // Interval 0 means to refresh as fast as possible



	this->stab->setInterval(10);
	connect(stab, SIGNAL(timeout()), this, SLOT(updateFps()));
	this->stab->start();

	this->layout->addWidget(customPlot);
	this->setLayout(layout);

//	this->show();

}

void MPerfomanceWidget::updateFps() {
// calculate two new data points:
	double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
	static double lastPointKey = 0;
	if (key-lastPointKey > 0.01) // at most add point every 10 ms
	{
		double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
		double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
		// add data to lines:
		customPlot->graph(0)->addData(key, value0);
		customPlot->graph(1)->addData(key, value1);
		// set data of dots:
		customPlot->graph(2)->clearData();
		customPlot->graph(2)->addData(key, value0);
		customPlot->graph(3)->clearData();
		customPlot->graph(3)->addData(key, value1);
		// remove data of lines that's outside visible range:
		customPlot->graph(0)->removeDataBefore(key-8);
		customPlot->graph(1)->removeDataBefore(key-8);
		// rescale value (vertical) axis to fit the current data:
		customPlot->graph(0)->rescaleValueAxis();
		customPlot->graph(1)->rescaleValueAxis(true);
		lastPointKey = key;
	}
// make key axis range scroll with the data (at a constant range size of 8):
	customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
	customPlot->replot();

// calculate frames per second:
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key-lastFpsKey > 2) // average fps over 2 seconds
	{
		this->setWindowTitle(
			QString("%1 FPS, Total Data points: %2")
				.arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
				.arg(customPlot->graph(0)->data()->count()+customPlot->graph(1)->data()->count())
			);
		lastFpsKey = key;
		frameCount = 0;
	}
}
