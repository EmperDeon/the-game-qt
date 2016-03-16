#include <widgets/lmodeditor.h>

LTextModWidgetEditor::LTextModWidgetEditor(QStringList keys, QStringList vals, QJsonArray* a) {
	this->ob = a;
	this->nameKeys = keys;
	this->nameVals = vals;

	QVBoxLayout* l = new QVBoxLayout;
	QHBoxLayout* l_h = new QHBoxLayout;
	QFormLayout* f_r = new QFormLayout;
	QFormLayout* f_c = new QFormLayout;
	QVBoxLayout* f_l = new QVBoxLayout;

	this->table = new QTableView;
	this->model = new LTextModWidgetModel(this);

	b_add    = new QPushButton(tr("Add"));
	b_del    = new QPushButton(tr("Delete"));

	this->list = new QList<QLineEdit*>;

	for(int i = 0 ; i < keys.size() ; i++)
		(*list) << new QLineEdit;

	int k = keys.size();

	for(int i = 0 ; i < k/2 + (k%2==0 ? 0 : 1); i++)
		f_r->addRow(keys.value(i), list->value(i));

	for(int i = k/2 + (k%2==0 ? 0 : 1); i < k ; i++)
		f_c->addRow(keys.value(i), list->value(i));

	f_l->addWidget(b_add);
	f_l->addWidget(b_del);

	l_h->addLayout(f_r);
	l_h->addSpacing(10);
	l_h->addLayout(f_c);
	l_h->addSpacing(10);
	l_h->addLayout(f_l);

	l->addLayout(l_h);
	l->addWidget(table);

	connect(b_add, SIGNAL(clicked()), this, SLOT(sadd()));
	connect(b_del, SIGNAL(clicked()), this, SLOT(sdel()));

	this->setLayout(l);
}
void LTextModWidgetEditor::sadd() {
	model->add();
	model = new LTextModWidgetModel(this);
	this->table->setModel(model);
}
void LTextModWidgetEditor::sdel() {
	model->del();
	model = new LTextModWidgetModel(this);
	this->table->setModel(model);
}

LTextModEditor::LTextModEditor(QJsonObject* o) {
	QVBoxLayout* l = new QVBoxLayout;
	tabs = new QTabWidget;

	obj = o;

	jItems = new QJsonArray();
	jBlocks = new QJsonArray();
	jTools = new QJsonArray();

	QStringList k;
	QStringList v;
	k << "Item" ;      v << "ii"       ;
	k << "Kind" ;      v << "ik"       ;
	k << "State";      v << "is"       ;
	k << "Texture";    v << "tex"      ;
	k << "Stack size"; v << "stackSize";
	k << "Stack Type"; v << "stackType";
	w_items = new LTextModWidgetEditor(k, v, jItems);

	k.clear(); v.clear();
	k << "Block";  v << "ii"    ;
	k << "Kind";   v << "ik"    ;
	k << "State";  v << "is"    ;
	k << "Texture";v << "tex"   ;
	k << "Weight"; v << "weight";
	w_blocks = new LTextModWidgetEditor(k, v, jBlocks);

	k.clear(); v.clear();
	k << "Tool";       v <<  "ii"  ;
	k << "Kind";       v <<  "ik"  ;
	k << "State";      v <<  "is"  ;
	k << "Texture";    v << "tex"  ;
	k << "Type";       v <<  "type";
	k << "Durability"; v <<  "drb" ;
	w_tools = new LTextModWidgetEditor(k, v, jTools);

	QPushButton* bsave = new QPushButton(tr("Save"));
	QPushButton* bfill = new QPushButton(tr("Fill"));

	tabs->addTab(w_items, "Items");
	tabs->addTab(w_blocks, "Blocks");
	tabs->addTab(w_tools, "Tools");

	l->addWidget(tabs);
	l->addWidget(bsave);
	l->addWidget(bfill);

	connect(bsave, SIGNAL(clicked()), this, SLOT(ssave()));
	connect(bfill, SIGNAL(clicked()), this, SLOT(sfill()));

	this->setLayout(l);
}
void LTextModEditor::ssave() {
	obj->insert("items", *jItems);
	obj->insert("blocks", *jBlocks);
	obj->insert("tools", *jTools);
}
void LTextModEditor::sfill() {
	for(int i = 0 ; i < 256 ; i++) {
		for(int k = 0 ; k < 256 ; k++) {
			QJsonObject o;
			o["ii"       ] = "Item" + QString::number(i);
			o["ik"       ] = "Kind" + QString::number(k);
			o["is"       ] = "State0";
			o["stackSize"] = 10;
			o["stackType"] = 0;
			(*jItems) << o;
		}
	}
	for(int i = 0 ; i < 256 ; i++) {
		for(int k = 0 ; k < 256 ; k++) {
			QJsonObject o;
			o["ii"    ] = "Block" + QString::number(i);
			o["ik"    ] = "Kind" + QString::number(k);
			o["is"    ] = "State0";
			o["weight"] = 1.0;
			(*jBlocks) << o;
		}
	}
	for(int i = 0 ; i < 256 ; i++) {
		for(int k = 0 ; k < 256 ; k++) {
			QJsonObject o;
			o["ii"  ] = "Tool" + QString::number(i);
			o["ik"  ] = "Kind" + QString::number(k);
			o["is"  ] = "State0";
			o["type"] = "Type0";
			o["drb" ] = 10;
			(*jTools) << o;
		}
	}
}

LScriptModEditor::LScriptModEditor(QJsonObject *o) {
	this->obj = o;
}

LModEditor::LModEditor(){
	this->REVISION = QString("0.1");
	this->pluginFile = "";

	this->other = new QJsonObject();
	this->textMod = new QJsonObject();
	this->scriptMod = new QJsonObject();
	this->depend = new QJsonArray();

	this->textModE = new LTextModEditor(textMod);
	this->scriptModE = new LScriptModEditor(scriptMod);

	QFormLayout* lay = new QFormLayout;

	this->e_file = new QLineEdit;
	this->e_name = new QLineEdit;
	this->e_ver = new QLineEdit;
	this->e_dep = new QLineEdit;
	this->e_plg = new QLineEdit;
	this->e_devl = new QLineEdit;
	this->e_site = new QLineEdit;
	this->e_desc = new QTextEdit;

	QPushButton* b_textMod = new QPushButton(tr("Edit Items, Blocks, "));
	QPushButton* b_scriptMod = new QPushButton(tr("Edit Scripts"));
	QPushButton* b_plugin = new QPushButton(tr("Select plugin file"));

	QPushButton* b_create = new QPushButton("Create");
	QPushButton* b_clear = new QPushButton("Clear");
	QPushButton* b_other = new QPushButton(tr("Other"));
	QPushButton* b_dep = new QPushButton("Edit dependencies");

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

	lay->addRow("File name:", e_file);
	lay->addRow("Name:", e_name);
	lay->addRow("Developer:", e_devl);
	lay->addRow("Site:", e_site);
	lay->addRow("Description:", e_desc);
	lay->addRow("Type:", c_type);
	lay->addRow(b_textMod);
	lay->addRow(b_scriptMod);
	lay->addRow(b_plugin);
	lay->addRow("Version:", e_ver);
	lay->addRow(b_dep, b_other);
	lay->addRow(b_create, b_clear);

	this->setLayout(lay);
	this->setWindowTitle("Mod editor");
	lLogD("Constructed");
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
		for(QString k : other->keys()){
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
	reply = QMessageBox::information(this, tr("QMessageBox::information()"), mess);
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
	this->pluginFile = QFileDialog::getOpenFileName(
		this,
		"Select plugin file",
		"modEditor/tmp/" + e_file->text() + "/",
		"*.dll *.so"
	);
}



void LModFixer::bcreate() {
	int f = pluginFile.lastIndexOf('/');
	QString dir = QStringRef(&pluginFile, 0, f).toString();
	lLogI(dir + " " + pluginFile);

	QJsonObject o;
	o["name"] = e_name->text();
	o["desc"] = e_desc->toPlainText();
	o["devl"] = e_devl->text();
	o["site"] = e_site->text();
	o["type"] = type;

	o["depend"] = *depend;
	o["version"] = e_ver->text();
	o["revision"] = this->REVISION;
	for(QString k : other->keys()){
		o[k] = (*other)[k];
	}
	o["pluginFile"] = QStringRef(&pluginFile, f + 1, pluginFile.size() - f).toString();
	(*textMod)["name"] = e_name->text();

	saveJson(o, dir + "/pack.dat");
	saveJson(*textMod,   dir + "/text.dat");
	saveJson(*scriptMod, dir + "/scripts.dat");
	

	this->close();
}

LModFixer::LModFixer(QString pluginFile) {
	this->REVISION = QString("0.1");
	this->pluginFile = pluginFile;

	this->other = new QJsonObject();
	this->textMod = new QJsonObject();
	this->scriptMod = new QJsonObject();
	this->depend = new QJsonArray();

	this->textModE = new LTextModEditor(textMod);
	this->scriptModE = new LScriptModEditor(scriptMod);

	QFormLayout* lay = new QFormLayout;

	this->e_file = new QLineEdit;
	this->e_name = new QLineEdit;
	this->e_ver = new QLineEdit;
	this->e_dep = new QLineEdit;
	this->e_plg = new QLineEdit;
	this->e_devl = new QLineEdit;
	this->e_site = new QLineEdit;
	this->e_desc = new QTextEdit;

	QPushButton* b_textMod = new QPushButton(tr("Edit Items, Blocks, "));
	QPushButton* b_scriptMod = new QPushButton(tr("Edit Scripts"));
	QPushButton* b_plugin = new QPushButton(tr("Select plugin file"));

	QPushButton* b_create = new QPushButton("Create");
	QPushButton* b_clear = new QPushButton("Clear");
	QPushButton* b_other = new QPushButton(tr("Other"));
	QPushButton* b_dep = new QPushButton("Edit dependencies");

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

	lay->addRow("File name:", e_file);
	lay->addRow("Name:", e_name);
	lay->addRow("Developer:", e_devl);
	lay->addRow("Site:", e_site);
	lay->addRow("Description:", e_desc);
	lay->addRow("Type:", c_type);
	lay->addRow(b_textMod);
	lay->addRow(b_scriptMod);
	lay->addRow(b_plugin);
	lay->addRow("Version:", e_ver);
	lay->addRow(b_dep, b_other);
	lay->addRow(b_create, b_clear);

	this->setLayout(lay);
	this->setWindowTitle("Mod editor");
	lLogD("Constructed");
}
