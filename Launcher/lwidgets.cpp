#include "Launcher/lwidgets.h"

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
void GDevelop::parse(){
	this->launcher->parser->parse();
}
GDevelop::GDevelop(LMainWindow* w){
	this->launcher = w;
	lay = new QVBoxLayout();

	w_mod = new LModsWidget(w);
	w_mode = new LModEditor(w);
	w_pac = new LPacker(w);

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
	connect(bmods, SIGNAL(clicked()), w_mod, SLOT(show()));
	connect(bmodl, SIGNAL(clicked()), w_mode,SLOT(show()));
	connect(bpack, SIGNAL(clicked()), w_pac, SLOT(show()));
	connect(bmodel,SIGNAL(clicked()), wmodel,SLOT(show()));
	connect(bresm, SIGNAL(clicked()), wresm, SLOT(show()));
	connect(bjsona, SIGNAL(clicked()), jsona, SLOT(show()));
	connect(bjsono, SIGNAL(clicked()), jsono, SLOT(show()));
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

LModsWidget::LModsWidget(LMainWindow *l){
	loader = l;
	log = loader->w_log;
	layout = new QVBoxLayout;
	l_model = new QHBoxLayout;
	l_wgt = new QHBoxLayout;

	b_rl = new QPushButton(tr("Reload mods list"));
	b_add = new QPushButton(tr("Add .zip"));
	b_del = new QPushButton(tr("Disable mod"));

	list = new QListView;

	connect(b_rl, SIGNAL(clicked()), this, SLOT(reload()));
	connect(b_add, SIGNAL(clicked(bool)), this, SLOT(add()));
	connect(b_del, SIGNAL(clicked(bool)), this, SLOT(del()));

	l_model->addWidget(b_add);
	l_model->addWidget(b_del);
	l_wgt->addWidget(b_rl);
	layout->addLayout(l_model);
	layout->addWidget(list);
	layout->addLayout(l_wgt);

	loader->modsMap->load();
	model = new LListModel(loader->modsMap->lst);
	list->setModel(model);
	this->setLayout(layout);
	log->addL(GLogLevel::DEBUG, "ModsList", "Constructed");
}
void LModsWidget::closeEvent(QCloseEvent *event){
	loader->modsMap->save();
	event->accept();
}
void LModsWidget::reload(){
	loader->modsMap->reload();
}
void LModsWidget::add(){
	loader->modsMap->addNew();
}
void LModsWidget::del(){
	model->del(list);
}

LPacker::LPacker(LMainWindow *l){
	loader = l;
	log = loader->w_log;
}

LTextModItemEditor::LTextModItemModel::LTextModItemModel(QJsonArray& o, QObject *pobj):QAbstractTableModel(pobj), obj(o){}
QVariant LTextModItemEditor::LTextModItemModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {
		return QVariant();
	}else if (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
		switch (index.column()){
			case 0 : return (obj[index.row()].toObject())["ii"].toString();
			case 1 : return (obj[index.row()].toObject())["ik"].toString();
			case 2 : return (obj[index.row()].toObject())["is"].toString();
			case 3 : return (obj[index.row()].toObject())["type"].toString();
			case 4 : return (obj[index.row()].toObject())["drb"].toString();
			default: return QVariant("error");
		}
	else return QVariant();
}
bool LTextModItemEditor::LTextModItemModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		QJsonObject o(obj[index.row()].toObject());
		switch (index.column()){
			case 0: o["ii"] = value.toString(); break;
			case 1: o["ik"] = value.toString(); break;
			case 2: o["is"] = value.toString(); break;
			case 3: o["type"]= value.toString(); break;
			case 4: o["drb"] = value.toString(); break;
			default: break;
		}
		obj.removeAt(index.row());
		obj.insert(index.row(), o);
		emit dataChanged(index, index);
	}
	return false;
}
Qt::ItemFlags LTextModItemEditor::LTextModItemModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid()) ? (flags | Qt::ItemIsEditable) : flags;
}
void LTextModItemEditor::LTextModItemModel::add(LTextModItemEditor *e){
	QJsonObject o;
	o["ii"] = e->l_ii->text();
	o["ik"] = e->l_ik->text();
	o["is"] = e->l_is->text();
	o["type"] = e->l_type->text();
	o["drb"] = e->l_drb->text();

	obj << o;
}
void LTextModItemEditor::LTextModItemModel::del(LTextModItemEditor *e){
			foreach(QModelIndex i, e->table->selectionModel()->selectedIndexes()){
			e->log->addL(GLogLevel::INFO, "TextModEditor", "deleting "+QString::number(i.row())+" "+QString::number(i.column()));
		}
}
int LTextModItemEditor::LTextModItemModel::rowCount(const QModelIndex&) const{
	return obj.size();
}
int LTextModItemEditor::LTextModItemModel::columnCount(const QModelIndex&) const{
	return 5;
}
QVariant LTextModItemEditor::LTextModItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if(orientation == Qt::Horizontal && role == 0){
		switch(section){
			case 0: return QVariant("Item");
			case 1: return QVariant("Kind");
			case 2: return QVariant("State");
			case 3: return QVariant("Type");
			case 4: return QVariant("Durability");
		}
	}else {
		return QAbstractTableModel::headerData(section, orientation, role);
	}
}

LTextModItemEditor::LTextModItemEditor(LMainWindow *m, QJsonArray* a) {
	this->launcher = m;
	this->log = m->w_log;
	this->ob = a;

	this->l = new QVBoxLayout;
	this->l_h = new QHBoxLayout;
	f_r = new QFormLayout;
	f_c = new QFormLayout;
	f_l = new QVBoxLayout;

	this->table = new QTableView;
	this->model = new LTextModItemModel(*ob);

	l_ii     = new QLineEdit;
	l_ik     = new QLineEdit;
	l_is     = new QLineEdit;

	l_type   = new QLineEdit;
	l_drb    = new QLineEdit;

	b_add    = new QPushButton(tr("Add"));
	b_del    = new QPushButton(tr("Delete"));
	b_fill   = new QPushButton(tr("Fill"));

	f_r->addRow("Item name:", l_ii);
	f_r->addRow("Item kind:", l_ik);
	f_r->addRow("Item state:",l_is);

	f_c->addRow("Type: ", l_type);
	f_c->addRow("Durability: ", l_drb);

	f_l->addWidget(b_add);
	f_l->addWidget(b_del);
 f_l->addWidget(b_fill);

	l_h->addLayout(f_r);
	l_h->addLayout(f_c);
	l_h->addLayout(f_l);

	this->l->addLayout(l_h);
	this->l->addWidget(table);

	connect(b_add, SIGNAL(clicked()), this, SLOT(sadd()));
	connect(b_del, SIGNAL(clicked()), this, SLOT(sdel()));
 connect(b_fill,SIGNAL(clicked()), this, SLOT(sfill()));

	this->setLayout(l);
}
void LTextModItemEditor::sadd() {
	model->add(this);
	model = new LTextModItemModel(*ob);
	this->table->setModel(model);
}
void LTextModItemEditor::sdel() {
	model->del(this);
	model = new LTextModItemModel(*ob);
	this->table->setModel(model);
}
void LTextModItemEditor::sfill() {
	for(int i = 0 ; i < 256 ; i++) {
		for(int k = 0 ; k < 256 ; k++) {
			for(int s = 0 ; s < 2 ; s++) {
				QJsonObject o;
				o["ii"] = "Item" + QString::number(i);
				o["ik"] = "Kind" + QString::number(k);
				o["is"] = "State" + QString::number(s);
				o["type"] = "Item";
				o["drb"] = 100;
				o["tex"] = "null.png";
				o["add"] = "";
				(*ob) << o;
			}
		}
	}
}

LTextModEditor::LTextModEditor(LMainWindow *t, QJsonObject* o) {
	this->launcher = t;
	this->log = t->w_log;

	l = new QVBoxLayout;
	tabs = new QTabWidget;

	obj = o;
	items = new QJsonArray();

	w_items = new LTextModItemEditor(t, items);
	bsave = new QPushButton(tr("Save"));

	tabs->addTab(w_items, "Items");

	l->addWidget(tabs);
	l->addWidget(bsave);

	connect(bsave, SIGNAL(clicked()), this, SLOT(ssave()));

	this->setLayout(l);
}
void LTextModEditor::ssave() {
	obj->insert("items", *items);
}

LScriptModEditor::LScriptModEditor(LMainWindow *t, QJsonObject *o) {
	this->launcher = t;
	this->log = t->w_log;
	this->obj = o;
}

LModEditor::LModEditor(LMainWindow *l){
	this->REVISION = QString("0.1");
	this->loader = l;
	this->log = loader->w_log;
	this->pluginFile = "";

	this->other = new QJsonObject();
	this->textMod = new QJsonObject();
	this->scriptMod = new QJsonObject();
	this->depend = new QJsonArray();

	this->textModE = new LTextModEditor(l, textMod);
	this->scriptModE = new LScriptModEditor(l, scriptMod);

	this->lay = new QFormLayout;

	this->e_file = new QLineEdit;
	this->e_name = new QLineEdit;
	this->e_ver = new QLineEdit;
	this->e_dep = new QLineEdit;
	this->e_plg = new QLineEdit;
	this->e_devl = new QLineEdit;
	this->e_site = new QLineEdit;
	this->e_desc = new QTextEdit;

	this->b_textMod = new QPushButton(tr("Edit Items, Blocks, "));
	this->b_scriptMod = new QPushButton(tr("Edit Scripts"));
	this->b_plugin = new QPushButton(tr("Select plugin file"));

	this->b_create = new QPushButton("Create");
	this->b_clear = new QPushButton("Clear");
	this->b_other = new QPushButton(tr("Other"));
	this->b_dep = new QPushButton("Edit dependies");

	this->c_type = new QComboBox;

	this->w_oth = new LTableManager(*other, tr("Other"));
	this->w_dep = new LListManager(*depend, tr("Dependence"));

	this->c_type->addItem(tr("Mod"));
	this->c_type->addItem(tr("CoreMod"));
	this->c_type->addItem(tr("Resource pack"));

	connect(b_textMod,   SIGNAL(clicked()),      textModE,   SLOT(show()));
	connect(b_scriptMod, SIGNAL(clicked()),      scriptModE, SLOT(show()));
	connect(b_plugin,    SIGNAL(clicked()),      this,       SLOT(splugin()));
	connect(b_create,    SIGNAL(clicked()),      this,       SLOT(bcreate()));
	connect(b_clear,     SIGNAL(clicked()),      this,       SLOT(bclear()));
	connect(b_dep,       SIGNAL(clicked()),      this,       SLOT(bdep()));
	connect(b_other,     SIGNAL(clicked()),      this,       SLOT(bother()));
	connect(c_type,      SIGNAL(activated(int)), this,       SLOT(ctype(int)));

	this->lay->addRow("File name:", e_file);
	this->lay->addRow("Name:", e_name);
	this->lay->addRow("Developer:", e_devl);
	this->lay->addRow("Site:", e_site);
	this->lay->addRow("Description:", e_desc);
	this->lay->addRow("Type:", c_type);
	this->lay->addRow(b_textMod);
	this->lay->addRow(b_scriptMod);
	this->lay->addRow(b_plugin);
	this->lay->addRow("Version:", e_ver);
	this->lay->addRow(b_dep, b_other);
	this->lay->addRow(b_create, b_clear);

	this->setLayout(lay);
	this->setWindowTitle("Mod editor");
	this->log->addL(GLogLevel::FINE, "ModEditor", "Constructed");
}
void LModEditor::bcreate(){
	QJsonObject o;
	o["name"] = e_name->text();
	o["desc"] = e_desc->toPlainText();
	o["devl"] = e_devl->text();
	o["site"] = e_site->text();
	o["type"] = type;

	o["depend"] = *depend;
	o["version"] = e_ver->text();
	o["revision"] = this->REVISION;
			foreach(QString k, other->keys()){
			o[k] = (*other)[k];
		}

	QString tmp = "modEditor/tmp/";
	QString out = "modEditor/out/";
	QDir dir;
	QString mess = "Now you can copy mod resources to " + dir.absolutePath() + "/" + tmp + e_file->text() +
	               "/\n Press OK when you ready to compress";
	dir.mkpath(tmp);
	dir.mkpath(out);
	dir.cd(tmp);
	dir.mkdir(e_file->text());

	(*textMod)["name"] = e_name->text();

	saveJson(o, tmp + e_file->text() + "/pack.dat");
	saveJson(*textMod,   tmp + e_file->text() + "/text.dat");
	saveJson(*scriptMod, tmp + e_file->text() + "/scripts.dat");
	if(pluginFile != "") QFile(pluginFile).rename(tmp + e_file->text() + "/plugin.dll");

	QMessageBox::StandardButton reply;
	reply = QMessageBox::information(this, tr("QMessageBox::information()"), tr(qPrintable(mess)));
	if (reply == QMessageBox::Ok){
		QZipWriter zip(out + e_file->text() + ME_SAVE);
		zip.setCompressionPolicy(QZipWriter::AutoCompress);

		QString path = tmp + e_file->text() + "/";
		QDirIterator it(path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
		while(it.hasNext()){
			QString file_path = it.next();
			if (it.fileInfo().isDir()) {
				zip.setCreationPermissions(QFile::permissions(file_path));
				zip.addDirectory(file_path.remove(path));
			} else if (it.fileInfo().isFile()) {
				QFile file(file_path);
				if (!file.open(QIODevice::ReadOnly))
					continue;

				zip.setCreationPermissions(QFile::permissions(file_path));
				zip.addFile(file_path.remove(path), file.readAll());
			}
		}

		zip.close();
	}
}
void LModEditor::bclear(){
	e_file->clear();
	e_name->clear();
	e_desc->clear();
	e_devl->clear();
	e_site->clear();
	e_ver ->clear();
	e_dep ->clear();
}
void LModEditor::bdep(){
	w_dep->show();
}
void LModEditor::bother(){
	w_oth->show();
}
void LModEditor::ctype(int i){
	switch(i){
		case 0: type = "Mod"; break;
		case 1: type = "CoreMod"; break;
		case 2: type = "ResourcePack"; break;
		default: type = "Unknown";
	}
}
void LModEditor::splugin() {

}
