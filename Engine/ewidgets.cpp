#include <ewidgets.h>

// EDeveloper
EDeveloper::EDeveloper(){
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

//	connect(bsett, SIGNAL(clicked()), this, SLOT(showSett()));
//	connect(blevl, SIGNAL(clicked()), this, SLOT(showLevl()));
//	connect(bmods, SIGNAL(clicked()), this, SLOT(showMods()));
//	connect(bmodl, SIGNAL(clicked()), this, SLOT(showModl()));
//	connect(bpack, SIGNAL(clicked()), this, SLOT(showPack()));
//	connect(bresm, SIGNAL(clicked()), this, SLOT(showResm()));
}
// EDeveloper