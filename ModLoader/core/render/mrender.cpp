#include <ModLoader/core/render/mrender.h>


MGlWidget::MGlWidget(){
	player = new MPlayer(10, 5, 10);
	cam = new MCamera();
	cam->attachTo(player);

	this->pointer = new QCursor(Qt::CrossCursor);
	this->setCursor(*pointer);

	this->keyList = new QList<int>;

	world = new MWorldRender();
	gui = new MGuiRender();

	mVarS(world, "mWorldRender");
	mVarS(gui, "mGuiRender");

	// Fps
	fps_t = new QElapsedTimer;
	fps_stabilizer = new QTimer;
	fps_stabilizer->setInterval(1000/MFPS_COUNT);
	connect(fps_stabilizer, SIGNAL(timeout()), this, SLOT(updateGL()));
//	fps_stabilizer->start();

	inp_stabilizer = new QTimer;
	inp_stabilizer->setInterval(10);
	connect(inp_stabilizer, SIGNAL(timeout()), this, SLOT(updateInput()));
	inp_stabilizer->start();
}

void MGlWidget::initializeGL(){
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
	glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	world->setPlayer(player);
	world->init();
//	gui->init();
	fps_stabilizer->start();
}

void MGlWidget::resizeGL(int nWidth, int nHeight){
	glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
	glLoadIdentity();            // присваивает проекционной матрице единичную матрицу

	//GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth; // отношение высоты окна виджета к его ширине
 GLfloat ratio = 2.0f;
	gluPerspective(85.0f, ratio, 0.01f, 1000.0f);
	glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void MGlWidget::paintGL(){
 fps_t->start();

	// glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

 cam->apply();
	world->render();
	//gui->render();
	this->fps = fps_t->nsecsElapsed();
}

void MGlWidget::mousePressEvent(QMouseEvent* pe) {}
void MGlWidget::mouseReleaseEvent(QMouseEvent* pe){}
void MGlWidget::mouseMoveEvent(QMouseEvent* pe){}
void MGlWidget::wheelEvent(QWheelEvent* pe){}

void MGlWidget::keyPressEvent(QKeyEvent* pe) {
	if(pe->key() == Qt::Key_Escape) {
		switchFocus();
	}else	{
		keyList->append(pe->key());
	}
}
void MGlWidget::keyReleaseEvent(QKeyEvent *ke) {
	keyList->removeAll(ke->key());
}
void MGlWidget::switchFocus() {
 this->wFocus = !this->wFocus;
}

void MGlWidget::closeEvent(QCloseEvent *event) {
	this->world->close();
//	this->gui->close()
}


void MGlWidget::updateInput() {
	// MouseControl
	if(wFocus && (width() > 0) && (height() > 0)) {
		QPoint pos = pointer->pos();
		pos.setX(pos.x() - width() / 2  - this->pos().x());
		pos.setY(pos.y() - height() / 2 - this->pos().y());

		if (pos.x() != 0) player->pitch(xSense * pos.x()) ;
		if (pos.y() != 0) player->yaw(-ySense * pos.y());

		pointer->setPos(this->pos().x() + width() / 2, this->pos().y() +  height() / 2);
	}

	for(int k : *keyList)
		switch (k)	{
			case Qt::Key_W: player->moveF(); break;
			case Qt::Key_S: player->moveB(); break;

			case Qt::Key_D: player->moveR(); break;
			case Qt::Key_A: player->moveL(); break;

			case Qt::Key_Space: player->moveU(); break;
			case Qt::Key_E: player->moveD(); break;

			case Qt::Key_Escape:	switchFocus();	break;

			default:;
		}
}
