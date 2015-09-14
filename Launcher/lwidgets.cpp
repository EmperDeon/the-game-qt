#include "lwidgets.h"

//Logger
LLogWidget::LLogWidget():QWidget(){
	list = new QList<GLogE>;
	last = "";

	vlay = new QVBoxLayout();
	hlay = new QHBoxLayout();

	w_edit = new QTextEdit();

	w_l = new QLabel("Show log level:");
	be = new QPushButton("Errors");
	bw = new QPushButton("Warnings");
	bi = new QPushButton("Info");
	bd = new QPushButton("Debug");
	bf = new QPushButton("All");
	w_l1 = new QLabel("Current collect value:");
	w_c = new QLabel("-- ms");
	br = new QPushButton("Refresh");

	QObject::connect(be,SIGNAL(clicked()),this,SLOT(switchE()));
	QObject::connect(bw,SIGNAL(clicked()),this,SLOT(switchW()));
	QObject::connect(bi,SIGNAL(clicked()),this,SLOT(switchI()));
	QObject::connect(bd,SIGNAL(clicked()),this,SLOT(switchD()));
	QObject::connect(bf,SIGNAL(clicked()),this,SLOT(switchF()));
	QObject::connect(br,SIGNAL(clicked()),this,SLOT(refresh()));

	hlay->addWidget(w_l);
	hlay->addWidget(be);
	hlay->addWidget(bw);
	hlay->addWidget(bi);
	hlay->addWidget(bd);
	hlay->addWidget(bf);
	hlay->addSpacing(20);
	hlay->addWidget(w_l1);
	hlay->addWidget(w_c);
	hlay->addWidget(br);

	vlay->addLayout(hlay);
	vlay->addWidget(w_edit);

	w_edit->setStyleSheet("font: 10pt \"Courier\";");
	this->setLayout(vlay);

	switchL(GLogLevel::FINE);
}
LLogWidget::~LLogWidget(){

}
void LLogWidget::addL(GLogLevel lv, QString cl, QString m){
	addL(GLogE(lv, QDateTime::currentDateTime(), cl, m ));
}
void LLogWidget::addL(GLogE e){
if(e.lv <= curr){
	last += e.toString();
	w_edit->setHtml(last);
}
list->append(e);
qDebug() << e.toString();
}
void LLogWidget::switchL(GLogLevel lv){
	curr = lv;
	refresh();
}
void LLogWidget::refresh(){
	last = "";

	QTime st;
	st.start();
	foreach (GLogE e, *list) {
		if(curr >= e.lv){
			last += e.toString();
		}
	}
	w_l1->setText(QString::number(st.elapsed()) + " ms " + QString::number(list->size()) + " total");

	w_edit->setHtml(last);
	QScrollBar *sb = w_edit->verticalScrollBar();
	sb->setValue(sb->maximum());
}
void LLogWidget::switchE(){
	switchL(GLogLevel::ERR);
}
void LLogWidget::switchW(){
	switchL(GLogLevel::WARN);
}
void LLogWidget::switchI(){
	switchL(GLogLevel::INFO);
}
void LLogWidget::switchD(){
	switchL(GLogLevel::DEBUG);
}
void LLogWidget::switchF(){
	switchL(GLogLevel::FINE);
}
//Logger

//Settings
GSettWidget::GSettWidget():tabs(),wgts(),mdls(),map(){
	b_save = new QPushButton("Save settings");
	b_load = new QPushButton("Load settings");
	tabs = new QTabWidget();
	vbox = new QVBoxLayout();
	hbox = new QHBoxLayout();

	hbox->addWidget(b_load);
	hbox->addWidget(b_save);
	vbox->addLayout(hbox);
	vbox->addWidget(tabs);
	this->setLayout(vbox);


	connect(b_save,SIGNAL(clicked()),this,SLOT(saveS()));
	connect(b_load,SIGNAL(clicked()),this,SLOT(loadS()));


	init();
}
void GSettWidget::clear(){
	this->map.clear();
	this->wgts.clear();
	this->mdls.clear();
	this->tabs->clear();
}
void GSettWidget::init(){
	foreach(QString k, map.keys()){
		wgts[k] = new QTableView();
		mdls[k] = new GSettingsModel(k, map, wgts[k]);

		wgts[k]->setModel(mdls[k]);

		tabs->addTab(wgts[k],k);
	}
}
void GSettWidget::saveS(){
	QFile saveFile("settings.dat");

	if (!saveFile.open(QIODevice::WriteOnly)) {
		return;
	}

	QJsonArray obj;

	foreach (QJsonObject e, map) {
		obj << e;
	}

	QJsonDocument doc(obj);
	saveFile.write(qCompress(doc.toBinaryData(),5));
}
void GSettWidget::loadS(){
	clear();
	QFile loadFile("settings.dat");

	if (!loadFile.open(QIODevice::ReadOnly)) {
		return;
	}

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	QJsonArray obj = loadDoc.array();
	QJsonObject t;
	foreach(QJsonValue e , obj){
		t = e.toObject();
		this->map[t["name"].toString()] = QJsonObject(t);
	}

	init();
}
//!Settings

//GDevelop
void GDevelop::reloadModLoader(){
	this->launcher->initModLoaders();
	this->modloader = this->launcher->getModLoader();
}
void GDevelop::parse(){
	if(!modloader){
		launcher->w_log->addL(GLogLevel::ERR, "L-GDevelop", "Modloader are null!");
	}else{
		this->modloader->parseZips();
	}
}
void GDevelop::showModEditor(){
	if(!modloader){
		launcher->w_log->addL(GLogLevel::ERR, "L-GDevelop", "Modloader are null!");
	}else{
		this->modloader->showModEditor();
	}
}
void GDevelop::showModList(){
	if(!modloader){
		launcher->w_log->addL(GLogLevel::ERR, "L-GDevelop", "Modloader are null!");
	}else{
		this->modloader->showMods();
	}
}
void GDevelop::showPacker(){
	if(!modloader){
		launcher->w_log->addL(GLogLevel::ERR, "L-GDevelop", "Modloader are null!");
	}else{
		this->modloader->showPacker();
	}
}
GDevelop::GDevelop(LMainWindow* w){
	this->launcher = w;
	lay = new QVBoxLayout();

	wsett = new GSettWidget();
	wlevl = new GLevlWidget();
	wmodel = new GModelWidget();
	wresm = new GResmWidget();

	jsono = new LJsonOWidget();
	jsona = new LJsonAWidget();

	bjsono = new QPushButton(tr("Show Json Object viewer"));
	bjsona = new QPushButton(tr("Show Json Array viewer"));

	bsett = new QPushButton("Settings Editor");
	blevl = new QPushButton("Level Editor");
	bmodel = new QPushButton("Model Editor");
	bresm = new QPushButton("Resource Manager");

	bmods = new QPushButton("Mods List");
	bmodl = new QPushButton("Mods Editor");
	bpack = new QPushButton("Resource Packer");

	binit = new QPushButton(tr("Reinit modloader"));
	bparse = new QPushButton(tr("Reparse downloads"));

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
	connect(bmods, SIGNAL(clicked()), this , SLOT(showModList()));
	connect(bmodl, SIGNAL(clicked()), this , SLOT(showModEditor()));
	connect(bpack, SIGNAL(clicked()), this , SLOT(showPacker()));
	connect(bmodel,SIGNAL(clicked()), wmodel,SLOT(show()));
	connect(bresm, SIGNAL(clicked()), wresm, SLOT(show()));
	connect(bjsona, SIGNAL(clicked()), jsona, SLOT(show()));
	connect(bjsono, SIGNAL(clicked()), jsono, SLOT(show()));
	connect(binit, SIGNAL(clicked()), this, SLOT(reloadModLoader()));
	connect(bparse, SIGNAL(clicked()), this, SLOT(parse()));
}

GResmWidget::GResmWidget(){

}

GLevlWidget::GLevlWidget(){

}

GModelWidget::GModelWidget(){

}
//!GDevelop

//ListManager
LListManager::LListManager(QJsonArray &o, QString t){
	model = new LListModel  (o);
	list	 = new QListView  ();
	vlay  = new QVBoxLayout();
	hlay  = new QHBoxLayout();
	e_k		 = new QLineEdit  ("Mod name");
	b_add = new QPushButton("Add");
	b_del = new QPushButton("Delete selected");
	b_ok	 = new QPushButton("Ok");

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
void LListManager::add(){
	this->model->add(e_k->text());
}
void LListManager::del(){
	this->model->del(list);
}
//!ListManager

//TableManager
LTableManager::LTableManager(QJsonObject &o, QString t){
	model = new LTableModel(o);
	table	= new QTableView ();
	vlay  = new QVBoxLayout();
	hlay  = new QHBoxLayout();
	e_k		 = new QLineEdit  ("Key");
	e_v		 = new QLineEdit  ("Value");
	b_add = new QPushButton("Add");
	b_del = new QPushButton("Delete selected");
	b_ok	 = new QPushButton("Ok");

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
void LTableManager::add(){
	this->model->add(e_k->text(), e_v->text());
}
void LTableManager::del(){
	this->model->del(e_k->text());
}
//!TableMananger

LJsonOWidget::LJsonOWidget(){
	lay = new QVBoxLayout();
	b_open = new QPushButton(tr("Open Json file"));
	list = new QTableView();
	connect(b_open, SIGNAL(clicked()), this,SLOT(open()));

	lay->addWidget(b_open);
	lay->addWidget(list);
	this->setLayout(lay);
	this->setWindowTitle("JsonObject viewer");
}
void LJsonOWidget::open(){
	obj = new QJsonObject(loadJson(QFileDialog::getOpenFileName(this, tr("Open Json file"),"/home",qPrintable("Json (*.*)"))));
	model = new LTableModel(*obj);
	list->setModel(model);
}

LJsonAWidget::LJsonAWidget(){
	lay = new QVBoxLayout();
	b_open = new QPushButton(tr("Open Json file"));
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

