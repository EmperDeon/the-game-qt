#include <ModLoader/core/render/perf/mperfw.h>

MPerfomanceWidget::MPerfomanceWidget() {
	this->render = mVarG(MGlWidget*, "mRender");
 this->v_fps = new QVector<float>;

 this->stab = new QTimer;
	this->layout = new QHBoxLayout;
	this->plot = new QCustomPlot;

	this->gr = plot->addGraph(); // blue line
	this->gr->setPen(QPen(Qt::blue));
	this->gr->setBrush(QBrush(QColor(240, 255, 200)));
	this->gr->setAntialiasedFill(true);

	this->dn = plot->addGraph(); // red line
	this->dn->setPen(QPen(Qt::red));
	this->gr->setChannelFillGraph(dn);

	this->plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	this->plot->xAxis->setDateTimeFormat("hh:mm:ss");
	this->plot->xAxis->setAutoTickStep(false);
	this->plot->xAxis->setTickStep(2);
	this->plot->axisRect()->setupFullAxesBox();

// make left and bottom axes transfer their ranges to right and top axes:
	connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
	connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

	this->stab->connect(stab, SIGNAL(timeout()), this, SLOT(updateFps()));
 this->stab->start(20);

	this->layout->addWidget(plot);
	this->setLayout(layout);
	this->setMinimumSize(500, 300);

	this->plot->yAxis->setRange(0.0f, yMax);
}

void MPerfomanceWidget::updateFps() {
	double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
	double f = render->getFps();
	double k = (f / 1000 + (render->getFps() % 1000)/1000)/1000 ;
	this->gr->addData(key, k);
	this->dn->addData(key, 0.0f); // value1
	this->gr->removeDataBefore(key-8);
	this->dn->removeDataBefore(key-8);
 if(k > yMax) yMax += 10.0f, this->plot->yAxis->setRange(0.0f, yMax);

	this->plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
	this->plot->replot();
	if(sec != QTime::currentTime().second()){
		int size = v_fps->size();
	 if(size > 20) v_fps->pop_back(), size--;
		if(k > 0)      v_fps->push_front(k), size++;
		float avg = 0.0f;
		for(float n : *v_fps){
			avg += n;
		}
		if(avg > 0) avg = avg/(size);

		this->setWindowTitle(QString("Average fps: %1 ms").arg(avg,4, 'f', 2));
  render->setWindowTitle(QString("Average fps: %1 ms").arg(avg,4, 'f', 2));
		sec = QTime::currentTime().second();
	}
}

