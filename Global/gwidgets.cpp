#include <gwidgets.h>

#undef CLASS_NAME
#define CLASS_NAME "GMWidget"

GMWidget::GMWidget():QOpenGLWidget(){
	setAutoFillBackground(false);
}

void GMWidget::animate(){
	update();
}

void GMWidget::paintEvent(QPaintEvent *event){
	GV_RENDER.render(this);
	event->accept();
}

#undef CLASS_NAME
#define CLASS_NAME "GDeveloper"


GDeveloper::GDeveloper(){
	lay = new QVBoxLayout();

	bsett = new QPushButton("Settings Editor");
	blevl = new QPushButton("Level Editor");
	bmods = new QPushButton("Mods Editor");
	bmodl = new QPushButton("Model Editor");
	bpack = new QPushButton("Resource Packer");
	bresm = new QPushButton("Resource Manager");

	lay->addWidget(bsett);
	lay->addWidget(blevl);
	lay->addWidget(bmods);
	lay->addWidget(bmodl);
	lay->addWidget(bpack);
	lay->addWidget(bresm);

	this->setLayout(lay);

	connect(bsett, SIGNAL(clicked()), this, SLOT(showSett()));
	connect(blevl, SIGNAL(clicked()), this, SLOT(showLevl()));
	connect(bmods, SIGNAL(clicked()), this, SLOT(showMods()));
	connect(bmodl, SIGNAL(clicked()), this, SLOT(showModl()));
	connect(bpack, SIGNAL(clicked()), this, SLOT(showPack()));
	connect(bresm, SIGNAL(clicked()), this, SLOT(showResm()));
}

void GDeveloper::showSett(){
	logI("Test");
}

void GDeveloper::showLevl(){
	GV_LOGGER.connec();
}

void GDeveloper::showMods(){

}

void GDeveloper::showModl(){

}

void GDeveloper::showPack(){

}

void GDeveloper::showResm(){

}

#undef CLASS_NAME
#define CLASS_NAME "Not_Defined"
