#include <Launcher/lmain.h>

// Main
int main(int argc, char *argv[]){
	qInstallMessageHandler(qtMessageHandler);
	QApplication a(argc, argv);
	
	LV_LOGGER = new LLogWidget;
	LV_LOGGER->showMaximized();

	LMainWindow w;
	w.show();
	
	return a.exec();
}
// Main


// LMainWindow
//  Construction
LMainWindow::LMainWindow(){
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");
	site = "";

	initNews();
	initLog();
	collectWidgets();

	check();

//	launch();
}

void LMainWindow::initNews(){

}

void LMainWindow::initLog(){
	modsMap = new LModsList(this);

	dev    = new LDevelop(this);
	proc   = new QProcess(this);
 parser = new LParser ();

	devvis = false;
	dev->setVisible(false);

	srv = new LLocalServer();

	bstart	= new QPushButton  ("Start");
	bdev	= new QPushButton    ("+");
	elog	= new QLineEdit      ("admin");
	epas	= new QLineEdit      ("admin");
	log  = new QCheckBox      ("Show log");
	list	= new QListView      ();
	prog    = new QProgressBar();

	bdev->setMaximumWidth(25);
	epas->setEchoMode(QLineEdit::Password);

	log->setChecked(true);

	list->setMaximumHeight(50);

	prog->setMinimumWidth(200);
	prog->setMaximum(100);
	prog->setValue(0);

	this->setWindowTitle("The game launcher");

	connect(bstart, SIGNAL(clicked()), this, SLOT(launch()));
	connect(bdev,   SIGNAL(clicked()), this, SLOT(showDev()));
}

void LMainWindow::collectWidgets(){
	QHBoxLayout* layout = new QHBoxLayout();
	QVBoxLayout* vlay   = new QVBoxLayout();
	QHBoxLayout* hlay   = new QHBoxLayout();
	QGridLayout* slay   = new QGridLayout();
	QGridLayout* llay   = new QGridLayout();

	llay->addWidget(new QLabel("Login:"), 0, 0);
	llay->addWidget(new QLabel("Password:"), 1, 0);
	llay->addWidget(elog, 0, 1);
	llay->addWidget(epas, 1, 1);

	slay->addWidget(bstart, 0, 0);
	slay->addWidget(bdev, 0, 1);
	slay->addWidget(log, 0, 2);
	slay->addWidget(prog, 1, 0, 1, 3);

	hlay->addLayout(llay);
	hlay->addStretch();
	hlay->addWidget(list);
	hlay->addSpacing(50);
	hlay->addLayout(slay);

	vlay->addLayout(hlay);

	layout->addLayout(vlay);
	layout->addWidget(dev);

	wgt = new QWidget();
	wgt->setLayout(layout);

	setCentralWidget(wgt);
	setUnifiedTitleAndToolBarOnMac(true);
}

void LMainWindow::check(){
	checkSettings();
	checkDir();
	parse();
}

void LMainWindow::checkSettings(){
	QSettings sett;
	if(sett.contains("working-dir")){
		this->dir = sett.value("working-dir").toString();
	}else{
		QString d = QFileDialog::getExistingDirectory(this,"Select dir for install");
		sett.setValue("working-dir", d);
		this->dir = d;
	}

	this->proc->setWorkingDirectory(dir);
	this->rfile = dir+"/game.exe";
}

void LMainWindow::checkDir(){
	QStringList list;

	bool needDownload = false;
	for(QString f : list){
		QFile file(f);
		needDownload = !file.exists();
	}

	if(needDownload){
		download();
	}else{
		this->prog->setValue(100);
	}
}

void LMainWindow::parse(){
	this->parser->parseZip();
}

void LMainWindow::download(){

}
//  Construction


//  Launch
void LMainWindow::launch(){
	this->hide();
	srv->clients->clear();
	proc->start(dir+"/game.exe");

	connect(proc, SIGNAL(finished(int)), this, SLOT(procF(int)));
}

void LMainWindow::procF(int e){
//	this->show();
	lLogI(QString(proc->readAll()));
	if(e)
		lLogE("The game crashed with code " + QString::number(e));
	disconnect(proc, SIGNAL(finished(int)), this, SLOT(procF(int)));
}
//  Launch

//  Other
void LMainWindow::showDev(){
	int resize = 160;
	if(devvis){
		dev->setVisible(false);
		bdev->setText("+");
		this->resize(this->width()-resize, this->height());
		devvis = false;
	}else{
		dev->setVisible(true);
		bdev->setText("-");
		this->resize(this->width()+resize, this->height());
		devvis = true;
	}
}

void LMainWindow::closeEvent(QCloseEvent *event){
	LV_LOGGER->close();
}
//  Other
// LMainWindow

void qtMessageHandler(QtMsgType type, const QMessageLogContext& cont, const QString& msg) {
	switch(type){
		case QtDebugMsg:break;
		case QtWarningMsg:
		case QtCriticalMsg:
		case QtFatalMsg:	LV_LOGGER->log(ILogLevel::QT, "Qt", msg); break;
	}
}