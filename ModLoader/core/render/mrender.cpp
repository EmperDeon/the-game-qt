#include <ModLoader/core/render/mrender.h>


MGlWidget::MGlWidget(){
	player = new MPlayer(10, 5, 10);
	cam = new MCamera();
	cam->attachTo(player);
	events = mVarG(IEvents*, "mEvents");
	events->addNewEventReciever(player);

	input = new MRInput(this);

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
	paused = input->keybr->keys.size() == 1;

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

void MGlWidget::closeEvent(QCloseEvent *event) {
	this->world->close();
//	this->gui->close()
}

void MGlWidget::keyPressEvent  (QKeyEvent *pe) { input->keybr->keyPressEvent(pe);}
void MGlWidget::keyReleaseEvent(QKeyEvent *pe) { input->keybr->keyReleaseEvent(pe);}
void MGlWidget::mousePressEvent(QMouseEvent *pe) {input->mouse->mousePressEvent(pe);	}
void MGlWidget::mouseMoveEvent(QMouseEvent *pe) {input->mouse->mouseMoveEvent(pe);	}
void MGlWidget::mouseReleaseEvent(QMouseEvent *pe) {input->mouse->mouseReleaseEvent(pe);}
void MGlWidget::wheelEvent(QWheelEvent *pe) {input->mouse->wheelEvent(pe); }
// MGlWidget


// MRInput
void MRInput::updateInput() {
	mouse->update();
	keybr->update();
}

void MRInput::keyInitEnd() {
	render->paused = false;
}

MRInput::MRInput(MGlWidget *w): render(w){
	this->keybr = new MRKeyboardInput(w);
	this->mouse = new MRMouseInput(w);


	inp_stabilizer = new QTimer;
	inp_stabilizer->setInterval(10);
	render->connect(inp_stabilizer, SIGNAL(timeout()), this, SLOT(updateInput()));
	inp_stabilizer->start();
}
// MRInput


// MRKeyboardInput
void MRKeyboardInput::keyPressEvent(QKeyEvent* pe) {
	int key = pe->key();
	if(key == Qt::Key_Escape) {
		render->input->mouse->switchFocus();
	}else	if( key == Qt::Key_L){
		render->world->lockPos();
	}else {
		keyList->append(key);
	}
}

void MRKeyboardInput::keyReleaseEvent(QKeyEvent *ke) {
	keyList->removeAll(ke->key());
}

MRKeyboardInput::MRKeyboardInput(MGlWidget *w): render(w), keys(MV_SETT->get("Keys")) {
	keyList = new QList<int>;
	if(keys.size() == 1){
		MRKeyboardInit *init = new MRKeyboardInit(this);
		init->show();
		qApp->setActiveWindow(init);
	}

	insertKeysTo(keysMov, {{"forw"}, {"back"}, {"left"}, {"righ"}, {"jump"}, {"sneak"}, {"sprint"}});

	keysOnT
	<< Qt::Key_Escape
	<< Qt::Key_L;
}

void MRKeyboardInput::insertKeysTo(QList<int> &list, QStringList key) {
	int l;
	for(QString i : keys.keys()){
		if(key.contains(keys.value(i).toString())){
			l = i.toInt();
			if(!list.contains(l)) list << l;
		}
	}
}

void MRKeyboardInput::update() {
	if(render->paused){

	}else{
		QJsonArray kMove, kOthr;

		for(int i : *keyList){
			if(isMovement(i)){
			 kMove << i;
			}else{
				kOthr << i;
			}
		}

		render->events->triggerEvent("Keyboard.keyPressMove", {{"keys", kMove}});
		render->events->triggerEvent("Keyboard.keyPressOther", {{"keys", kOthr}});
	}
}
// MRKeyboardInput


// MRMouseInput
void MRMouseInput::mousePressEvent(QMouseEvent* pe)  {}
void MRMouseInput::mouseReleaseEvent(QMouseEvent* pe){}
void MRMouseInput::mouseMoveEvent(QMouseEvent* pe)   {}
void MRMouseInput::wheelEvent(QWheelEvent* pe)       {}

MRMouseInput::MRMouseInput(MGlWidget *w): render(w) {
	this->normalp = new QCursor(Qt::ArrowCursor);
	this->pointer = new QCursor(QPixmap("res/ncursor.png"));
	w->setCursor(*pointer);
}

void MRMouseInput::switchFocus() {
	render->paused = !render->paused;
	if(render->paused){
		render->setCursor(*normalp);
	}else{
		render->setCursor(*pointer);
	}
}

void MRMouseInput::update() {
	int	width  = render->width(),
		height = render->height(),
		posx   = render->pos().x(),
		posy   = render->pos().y();

	if(!render->paused && (width > 0) && (height > 0)) {
		QPoint p = pointer->pos();
		p.setX(p.x() - width / 2 - posx);
		p.setY(p.y() - height / 2 - posy);

		if (p.x() != 0) render->player->pitch(xSense * p.x()) ;
		if (p.y() != 0) render->player->yaw(-ySense * p.y());

		pointer->setPos(posx + width / 2, posy +  height / 2);
	}
}

MRKeyboardInit::MRKeyboardInit(MRKeyboardInput* i): in(i){
	QHBoxLayout *l = new QHBoxLayout;
	lab = new QLabel;
	l->addWidget(lab, 0, Qt::AlignCenter);
	this->setLayout(l);
	this->setMinimumSize(150, 30);

	k << "forw"  ;  v << "Move Forward" ;
	k << "back"  ;  v << "Move Backward";
	k << "left"  ;  v << "Move Left"    ;
	k << "righ"  ;  v << "Move Right"   ;
	k << "jump"  ;  v << "Jump"         ;
	k << "sneak" ;  v << "Sneak"        ;
	k << "sprint";  v << "Sprint"       ;

	next();
}

void MRKeyboardInit::keyPressEvent(QKeyEvent *pe) {
	in->keys.insert(QString::number(pe->key()), k[current]);
	next();
}

void MRKeyboardInit::next() {
	current++;
	if(current < v.size()){
		auto key = v[current];
		lab->setText(QString("Press key for action \"%1\"").arg(key));
	}else{
		close();
	}
}


