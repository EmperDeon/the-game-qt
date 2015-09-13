#include "mmodswidget.h"

MModsWidget::MModsWidget(ModLoader *l){
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
	model = new MListModel(loader->modsMap->lst);
	list->setModel(model);
	this->setLayout(layout);
	log->addL(GLogLevel::DEBUG, "ModsList", "Constructed");
}

void MModsWidget::closeEvent(QCloseEvent *event){
	loader->modsMap->save();
	event->accept();
}

void MModsWidget::reload(){
	loader->modsMap->reload();
}
void MModsWidget::add(){
	loader->modsMap->addNew();
}
void MModsWidget::del(){
	model->del(list);
}



MModEditor::MModEditor(ModLoader *l){
	REVISION = QString("0.1");
	loader = l;
	log = loader->w_log;

	other = new QJsonObject();
	depend = new QJsonArray();

	lay = new QFormLayout;

	e_file = new QLineEdit;
	e_name = new QLineEdit;
	e_ver = new QLineEdit;
	e_dep = new QLineEdit;
	e_scr = new QLineEdit;
	e_plg = new QLineEdit;
	e_devl = new QLineEdit;
	e_site = new QLineEdit;
	e_desc = new QTextEdit;

	b_create = new QPushButton("Create");
	b_clear = new QPushButton("Clear");
	b_other = new QPushButton(tr("Other"));
	b_dep = new QPushButton("Edit dependies");

	c_type = new QComboBox;

	w_oth = new MTableManager(*other, tr("Other"));
	w_dep = new MListManager(*depend, tr("Dependence"));

	c_type->addItem(tr("Mod"));
	c_type->addItem(tr("CoreMod"));
	c_type->addItem(tr("Resource pack"));

	connect(b_create, SIGNAL(clicked()), this, SLOT(bcreate()));
	connect(b_clear, SIGNAL(clicked()), this, SLOT(bclear()));
	connect(b_dep, SIGNAL(clicked()), this, SLOT(bdep()));
	connect(b_other, SIGNAL(clicked()), this, SLOT(bother()));
	connect(c_type, SIGNAL(activated(int)), this, SLOT(ctype(int)));

	lay->addRow("File name:", e_file);
	lay->addRow("Name:", e_name);
	lay->addRow("Developer:", e_devl);
	lay->addRow("Site:", e_site);
	lay->addRow("Description:", e_desc);
	lay->addRow("Type:", c_type);
	lay->addRow("Script file:", e_scr);
	lay->addRow("Plugin file:", e_plg);
	lay->addRow("Version:", e_ver);
	lay->addRow(b_dep, b_other);
	lay->addRow(b_create, b_clear);

	setLayout(lay);
	setWindowTitle("Mod editor");
	log->addL(GLogLevel::DEBUG, "ModEditor", "Constructed");
}
void MModEditor::bcreate(){
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
	QString mess = "Now you can copy mod resources to " + dir.absolutePath() + "/" + tmp + "\n Press OK when you ready to comress";
	dir.mkpath(tmp);
	dir.mkpath(out);
	dir.cd(tmp);
	dir.mkdir(e_file->text());

	saveJson(o, tmp + e_file->text() + "/pack.dat");

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
void MModEditor::bclear(){
	e_file->clear();
	e_name->clear();
	e_desc->clear();
	e_devl->clear();
	e_site->clear();
	e_ver ->clear();
	e_dep ->clear();
	e_scr ->clear();
}
void MModEditor::bdep(){
	w_dep->show();
}
void MModEditor::bother(){
	w_oth->show();
}
void MModEditor::ctype(int i){
	switch(i){
	case 0: type = "Mod"; break;
	case 1: type = "CoreMod"; break;
	case 2: type = "ResourcePack"; break;
	default: type = "Unknown";
	}
}

MPacker::MPacker(ModLoader *l){
	loader = l;
	log = loader->w_log;
}


//Redefine
void saveJsonA(QJsonArray o, QString file){
	QFile f(file);
	if (!f.open(QIODevice::WriteOnly)) {return;}

	QJsonDocument doc(o);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}
QJsonArray loadJsonA(QString file){
	QFile loadFile(file);
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.array();
}

