#include <lutils.h>
#include <cmath>

// Logger
QString getLevelName(ILogLevel lv){
	switch(lv){
	case ILogLevel::ERR  : return "[E]";
	case ILogLevel::WARN : return "[W]";
	case ILogLevel::INFO : return "[I]";
	case ILogLevel::DEBUG: return "[D]";
	case ILogLevel::FINE : return "[F]";
	case ILogLevel::FFINE: return "[FF]";
	case ILogLevel::ALL  : return "[A]" ;
	case ILogLevel::QT   : return "[QT]";
	}
}

LLogE::LLogE(ILogLevel lvl, QDateTime dt, QString cls, QString mss): lv(lvl), d(dt), cl(parseQtFunc(cls)), ms(mss), engine(false){}

LLogE::LLogE(QString s){
	QStringList lst = s.split("^");
	t = lst.takeFirst();
	QString level = lst.takeFirst();
	if (level == "[E]"){ lv = ILogLevel::ERR  ;
	}else if (level == "[W]"){ lv = ILogLevel::WARN ;
	}else if (level == "[I]"){ lv = ILogLevel::INFO ;
	}else if (level == "[D]"){ lv = ILogLevel::DEBUG;
	}else if (level == "[F]"){ lv = ILogLevel::FINE ;
	}else if (level == "[FF]"){lv = ILogLevel::FFINE ;
	}else if (level == "[A]"){ lv = ILogLevel::ALL ;
	}else if (level == "[QT]"){lv = ILogLevel::QT;
	}else{

	}
 cl = parseQtFunc(lst.takeFirst());
	ms = lst.takeFirst();
	engine = true;
}

QString LLogE::parseQtFunc(QString s) {
	if(s.indexOf("Qt") != -1){
		return s;
	}
	QString	r = s;
	r = r.replace("virtual ", "");
	int f = r.indexOf(' ');

	if(f != -1) r = QStringRef(&r, f + 1, r.length() - f).toString();
	r = r.insert(1, '-');
	if(NO_DEBUG)	r = QStringRef(&r, 0, r.indexOf(':')).toString();

	return r;
}

QString LLogE::toString(){
	QString r = "<div ";

	switch(lv){
		case ILogLevel::ERR  : r += "style=\"color:red";    break;
		case ILogLevel::WARN : r += "style=\"color:#ff9c00"; break;
		case ILogLevel::INFO : r += "style=\"color:blue";   break;
		case ILogLevel::DEBUG: r += "style=\"color:black";  break;
		case ILogLevel::FINE : r += "style=\"color:gray";   break;
		case ILogLevel::FFINE: r += "style=\"color:gray";   break;
		case ILogLevel::ALL  : r += "style=\"color:gray";   break;
		case ILogLevel::QT   : r += "style=\"color:#5CAA15";break;
	}

	r.append("\">[");
	r.append(engine ? t : d.toString(ELOG_DATE_FORMAT));
	//r.append(engine ? t : d.toString("HH:mm:ss dd.MM.yyyy"));
	r.append("]" + getLevelName(lv));
	r.append("["+cl+"]");
	r.append(": "+ms);

	r.append("</div>");
	return r;
}

LLogWidget::LLogWidget() :QWidget(){
	list = new QList<LLogE>;
	last = "";

	QVBoxLayout* vlay = new QVBoxLayout();
	QHBoxLayout* hlay = new QHBoxLayout();

	w_edit = new QTextEdit();
 c_qt = new QCheckBox("Qt");

	QLabel* w_l = new QLabel(tr("Show log level:"));
	QPushButton* be = new QPushButton(tr("Errors"));
	QPushButton* bw = new QPushButton(tr("Warnings"));
	QPushButton* bi = new QPushButton(tr("Info"));
	QPushButton* bd = new QPushButton(tr("Debug"));
	QPushButton* bf = new QPushButton(tr("Fine"));
	QPushButton* bff= new QPushButton(tr("FFine"));
	QPushButton* ba = new QPushButton(tr("All"));
	QPushButton* br = new QPushButton(tr("Refresh"));
	QLabel* w_l1 = new QLabel(tr("Current collect value:"));
	w_c = new QLabel("-- ms");
 c_qt->setChecked(true);

	connect(be, SIGNAL(clicked()), this, SLOT(switchE()));
	connect(bw, SIGNAL(clicked()), this, SLOT(switchW()));
	connect(bi, SIGNAL(clicked()), this, SLOT(switchI()));
	connect(bd, SIGNAL(clicked()), this, SLOT(switchD()));
	connect(bf, SIGNAL(clicked()), this, SLOT(switchF()));
	connect(bff,SIGNAL(clicked()), this, SLOT(switchFF()));
	connect(ba, SIGNAL(clicked()), this, SLOT(switchA()));
	connect(br, SIGNAL(clicked()), this, SLOT(refresh()));

	hlay->addWidget(w_l);
	hlay->addWidget(be);
	hlay->addWidget(bw);
	hlay->addWidget(bi);
	hlay->addWidget(bd);
	hlay->addWidget(bf);
	hlay->addWidget(bff);
	hlay->addWidget(ba);
	hlay->addWidget(c_qt);
	hlay->addSpacing(20);
	hlay->addWidget(w_l1);
	hlay->addWidget(w_c);
	hlay->addWidget(br);

	vlay->addLayout(hlay);
	vlay->addWidget(w_edit);

	w_edit->setStyleSheet("font: 10pt \"Fantasque Sans Mono\";");
	this->setLayout(vlay);

	switchL(ILogLevel::FINE);
}

void LLogWidget::addL(LLogE e){
	if(curr >= e.lv || (c_qt->isChecked() && e.lv == ILogLevel::QT)){
		last += e.toString();
		w_edit->setHtml(last);
		QTextCursor c = w_edit->textCursor();
		c.movePosition(QTextCursor::End);
		w_edit->setTextCursor(c);
	}
	list->append(e);
//	qDebug() << e.toString();
}

void LLogWidget::switchL(ILogLevel lv){
	curr = lv;
	refresh();
}

void LLogWidget::refresh(){
	last = "";

	QTime st;
	st.start();
		for(LLogE e : *list) {
			if(curr >= e.lv || (c_qt->isChecked() && e.lv == ILogLevel::QT)){
				last += e.toString();
			}
		}
	w_c->setText(QString::number(st.elapsed()) + " ms " + QString::number(list->size()) + " total");

	w_edit->setHtml(last);
	QTextCursor c = w_edit->textCursor();
	c.movePosition(QTextCursor::End);
	w_edit->setTextCursor(c);
}

LLogWidget* LV_LOGGER;
// Logger


// LLocalServer
LLocalServer::LLocalServer(){
	clients = new QVector<QLocalSocket*>();
	blockSize = 0;

	server = new QLocalServer(this);
	if (!server->listen(ESERVER_NAME)) {
		qDebug() << "Construction failed "+server->errorString();
		return;
	}

	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(readyRead()));
	timer->start(10);
}

void LLocalServer::addLog(QString s){
	if(s.indexOf("#Launcher") == 0){
		if(s.indexOf("#Launcher#Disconnect") == 0){
			clients->clear();
		}
	}else{
		LV_LOGGER->addL(LLogE(s));
	}
}

void LLocalServer::newConnection(){
	QLocalSocket* client = server->nextPendingConnection();
//	connect(client, SIGNAL(disconnected()),	client, SLOT(deleteLater()));
	connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
	clients->append(client);
	lLogD("Engine connected");
}

void LLocalServer::readyRead(){
	for(QLocalSocket* client : *clients){
		if(client->isOpen()){
			QDataStream in(client);
			in.setVersion(QDataStream::Qt_5_4);

			if (in.atEnd())
				return;

			if (blockSize == 0) {
				if (client->bytesAvailable() < (int)sizeof(quint16))
					return;
				in >> blockSize;
			}

			QString curr;
			in >> curr;

			if (curr != lastMsg) {
				addLog(curr);
				blockSize = 0;
			}
		}
	}
}
// LLocalServer


//LModsList
LModsList::LModsList(LMainWindow *l): loader(l){
	this->list = new QJsonArray;
	this->lst = QJsonArray();
}
void LModsList::update(){
	QDir mods("mods/mods");
		for(QFileInfo f : mods.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			if(f.fileName() != "." && f.fileName() != ".."){
				lLogD("parsing " + f.filePath());
				addToList(loadJson(QDir("mods/mods/"+f.fileName()).filePath("pack.dat")));
			}
		}

}
void LModsList::fillList(){
	lst = QJsonArray();
		for(QJsonValue o : *list){
			if(o.toObject()["enabled"].toBool() && !lst.contains(o.toObject()["name"].toString())){
				lst << o.toObject()["name"].toString();
			}
		}
}
void LModsList::addToList(QJsonObject o){
	if(contains(o["name"].toString())){
		lLogD(o["name"].toString() + " has already added, ignoring ");
	}else{
		lLogD("found new mod, adding " + o["name"].toString());
		QJsonObject t;
		t["name"] = o["name"];
		t["desc"] = o["desc"];
		t["enabled"] = true;
		*list << t;
		this->lst << o["name"].toString();
	}
}
bool LModsList::contains(QString s){
		for(QJsonValue v : *list){
			if( (v.toObject())["name"] == s ) return true;
		}
	return false;
}
void LModsList::disable(QString n){
		for(QJsonValue v : *list){
			if(v.toObject()["name"] == n){
				v.toObject()["enabled"] = false;
			}
		}
}
void LModsList::addNew(){
	QString file = QFileDialog::getOpenFileName(loader->dev->w_mod, "Open File","/home",qPrintable("Mod (*"+ME_SAVE+")"));
	QString ffile = QStringRef(&file, file.lastIndexOf("/")+1, file.indexOf(".zip")).toString();
	QZipReader z(file);
	lLogD("unzipping " + file + " to " + ffile);
	//z.extractAll("mods/");
}
void LModsList::load(){
	QFile f("mods/mods.dat");
	if(f.exists()){
		list = new QJsonArray(loadJsonA(f.fileName()));
	}else{
		lLogD("file mods/mods.dat not exist");
		list = new QJsonArray();
	}
	update();
	fillList();
}
void LModsList::save(){
		for(QJsonValue e : *list){
			QJsonObject o = e.toObject();
			o["enabled"] = lst.contains(o["name"].toString());
		}
	saveJsonA(*list, "mods/mods.dat");
}
void LModsList::reload(){
	this->list = new QJsonArray();
	update();
}
//!LModsList


// Standalone functions
QJsonObject loadJson(QString file){
	QFile loadFile(file);
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.object();
}

QJsonArray loadJsonA(QString file){
	QFile loadFile(file);
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.array();
}

void saveJson(QJsonObject o, QString file){
	QFile f(file);
	if (!f.open(QIODevice::WriteOnly)) {return;}

	QJsonDocument doc(o);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}

void saveJsonA(QJsonArray o, QString file){
	QFile f(file);
	if (!f.open(QIODevice::WriteOnly)) {return;}

	QJsonDocument doc(o);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}
// Standalone functions

