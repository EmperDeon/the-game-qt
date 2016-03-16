#include <lwidgets.h>

// Json Viewers
LListManager::LListManager(QJsonArray &o, QString t){
	model = new LListModel  (o);
	list	 = new QListView  ();
	QVBoxLayout* vlay  = new QVBoxLayout();
	QHBoxLayout* hlay  = new QHBoxLayout();
	e_k		 = new QLineEdit  ("Mod name");
	QPushButton* b_add = new QPushButton("Add");
	QPushButton* b_del = new QPushButton("Delete selected");
	QPushButton* b_ok	 = new QPushButton("Ok");

	hlay->addWidget(e_k);
	hlay->addWidget(b_add);
	hlay->addWidget(b_del);
	vlay->addLayout(hlay);
	vlay->addWidget(list);
	vlay->addWidget(b_ok);
	list->setModel(model);

	connect(b_add, SIGNAL(clicked()), this, SLOT(add()));
	connect(b_del, SIGNAL(clicked()), this, SLOT(del()));
	connect(b_ok,  SIGNAL(clicked()), this, SLOT(hide()));

	this->setLayout(vlay);
	this->setWindowTitle(t);
}

LTableManager::LTableManager(QJsonObject &o, QString t){
	model = new LTableModel(o);
	table	= new QTableView ();
	QVBoxLayout* vlay  = new QVBoxLayout();
	QHBoxLayout* hlay  = new QHBoxLayout();
	e_k		 = new QLineEdit  ("Key");
	e_v		 = new QLineEdit  ("Value");
	QPushButton* b_add = new QPushButton("Add");
	QPushButton* b_del = new QPushButton("Delete selected");
	QPushButton* b_ok	 = new QPushButton("Ok");

	hlay->addWidget(e_k);
	hlay->addWidget(e_v);
	hlay->addWidget(b_add);
	hlay->addWidget(b_del);
	vlay->addLayout(hlay);
	vlay->addWidget(table);
	vlay->addWidget(b_ok);
	table->setModel(model);

	connect(b_add, SIGNAL(clicked()), this, SLOT(add()));
	connect(b_del, SIGNAL(clicked()), this, SLOT(del()));
	connect(b_ok,  SIGNAL(clicked()), this, SLOT(hide()));

	this->setLayout(vlay);
	this->setWindowTitle(t);
}
void LTableManager::add(){	this->model->add(e_k->text(), e_v->text());	}
void LTableManager::del(){	this->model->del(e_k->text());	}

LJsonOWidget::LJsonOWidget(){
	QVBoxLayout* lay = new QVBoxLayout();
	QPushButton* b_open = new QPushButton(tr("Open Json file"));
	list = new QTableView();
	connect(b_open, SIGNAL(clicked()), this,SLOT(open()));

	lay->addWidget(b_open);
	lay->addWidget(list);
	this->setLayout(lay);
	this->setWindowTitle("JsonObject viewer");
}
void LListManager::add(){	this->model->add(e_k->text());}
void LListManager::del(){	this->model->del(list);}

void LJsonOWidget::open(){
	obj = new QJsonObject(loadJson(QFileDialog::getOpenFileName(this, tr("Open Json file"),"/home",qPrintable("Json (*.*)"))));
	model = new LTableModel(*obj);
	list->setModel(model);
}

LJsonAWidget::LJsonAWidget(){
	QVBoxLayout* lay = new QVBoxLayout();
	QPushButton* b_open = new QPushButton(tr("Open Json file"));
	list = new QListView();
	connect(b_open, SIGNAL(clicked()), this,SLOT(open()));

	lay->addWidget(b_open);
	lay->addWidget(list);
	this->setLayout(lay);
	this->setWindowTitle("JsonArray viewer");
}

void LJsonAWidget::open(){
	obj = new QJsonArray(loadJsonA(QFileDialog::getOpenFileName(this, tr("Open Json file"),"/home",qPrintable("Json (*.*)"))));
	model = new LListModel(*obj);
	list->setModel(model);
}
// Json Viewers


// LSettings
LSettWidget::LSettWidget(){
	this->tabs = new QTabWidget();
	this->wgts = new QMap<QString, QTableView*>;
	this->mdls = new QMap<QString, LSettingsModel *>;
	this->map  = new QMap<QString, QJsonObject>;
	QPushButton* b_save = new QPushButton("Save settings");
	QPushButton* b_load = new QPushButton("Load settings");
	QVBoxLayout* vbox = new QVBoxLayout();
	QHBoxLayout* hbox = new QHBoxLayout();

	hbox->addWidget(b_load);
	hbox->addWidget(b_save);
	vbox->addLayout(hbox);
	vbox->addWidget(tabs);
	this->setLayout(vbox);

	connect(b_save,SIGNAL(clicked()),this,SLOT(saveS()));
	connect(b_load,SIGNAL(clicked()),this,SLOT(loadS()));

	init();
}

void LSettWidget::clear(){
	this->map->clear();
	this->wgts->clear();
	this->mdls->clear();
	this->tabs->clear();
}

void LSettWidget::init(){
			for(QString k : map->keys()){
			wgts->insert(k, new QTableView());
			mdls->insert(k, new LSettingsModel(k, map, wgts->value(k)));

			wgts->value(k)->setModel(mdls->value(k));

			tabs->addTab(wgts->value(k),k);
		}
}

void LSettWidget::saveS(){
	QFile saveFile("settings.dat");

	if (!saveFile.open(QIODevice::WriteOnly)) {
		return;
	}

	QJsonArray obj;

			for (QJsonObject e : *map) {
			obj << e;
		}

	QJsonDocument doc(obj);
	saveFile.write(qCompress(doc.toBinaryData(),5));
}

void LSettWidget::loadS(){
	clear();
	QFile loadFile("settings.dat");

	if (!loadFile.open(QIODevice::ReadOnly)) {
		return;
	}

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	QJsonArray obj = loadDoc.array();
	QJsonObject t;
			for(QJsonValue e : obj){
			t = e.toObject();
			this->map->insert(t["name"].toString(), QJsonObject(t));
		}

	init();
}
// LSettings


// LDevelop
LDevelop::LDevelop(LMainWindow* w){
	this->launcher = w;
	QVBoxLayout* lay = new QVBoxLayout();

	w_mod = new LModsWidget(w);
	w_mode = new LModEditor();
	w_pac = new LPacker();

	wsett = new LSettWidget();
	wlevl = new LLevlWidget();
	wmodel = new LModelWidget();
	wresm = new LResmWidget();

	jsono = new LJsonOWidget();
	jsona = new LJsonAWidget();

	QPushButton* bjsono = new QPushButton(tr("Show Json Object viewer"));
	QPushButton* bjsona = new QPushButton(tr("Show Json Array viewer"));
	QPushButton* bsett = new QPushButton("Settings Editor");
	QPushButton* blevl = new QPushButton("Level Editor");
	QPushButton* bmodel = new QPushButton("Model Editor");
	QPushButton* bresm = new QPushButton("Resource Manager");
	QPushButton* bmods = new QPushButton("Mods List");
	QPushButton* bmodl = new QPushButton("Mods Editor");
	QPushButton* bpack = new QPushButton("Resource Packer");

	QPushButton* binit = new QPushButton(tr("Reinit modloader"));
	QPushButton* bparse = new QPushButton(tr("Reparse downloads"));

	lay->addWidget(bsett);
	lay->addWidget(blevl);
	lay->addWidget(bmodel);
	lay->addWidget(bresm);

	lay->addWidget(bmods);
	lay->addWidget(bmodl);
	lay->addWidget(bpack);

	lay->addSpacing(10);
	lay->addWidget(bjsona);
	lay->addWidget(bjsono);

	lay->addSpacing(10);
	lay->addWidget(binit);
	lay->addWidget(bparse);

	this->setLayout(lay);
	this->setFixedSize(lay->minimumSize());

	connect(bsett, SIGNAL(clicked()), wsett, SLOT(show()));
	connect(blevl, SIGNAL(clicked()), wlevl, SLOT(show()));
	connect(bmods, SIGNAL(clicked()), w_mod, SLOT(show()));
	connect(bmodl, SIGNAL(clicked()), w_mode,SLOT(show()));
	connect(bpack, SIGNAL(clicked()), w_pac, SLOT(show()));
	connect(bmodel,SIGNAL(clicked()), wmodel,SLOT(show()));
	connect(bresm, SIGNAL(clicked()), wresm, SLOT(show()));
	connect(bjsona, SIGNAL(clicked()), jsona, SLOT(show()));
	connect(bjsono, SIGNAL(clicked()), jsono, SLOT(show()));
	connect(bparse, SIGNAL(clicked()), this, SLOT(parse()));
}

void LDevelop::parse(){	this->launcher->parser->parse();}
// LDevelop


// LPacker
LPacker::LPacker(){}
// LPacker
