#include "Launcher/lmain.h"

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	LMainWindow w;
	//w.show();

	return a.exec();
}

LMainWindow::LMainWindow(){
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");
	site = "";

	initWebKit();
	initLog();
	collectWidgets();

	check();

	//	createJson();
	launch();
}
GModLoaderInterface *LMainWindow::getModLoader(){
	return this->modloader;
}

void LMainWindow::showDev(){
	int resize = 150;
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

void LMainWindow::procF(int e){
	this->show();
	if(e)
		w_log->addL(GLogLevel::ERR, "L-Main", "The game crashed with code "+QString::number(e));
	disconnect(proc, SIGNAL(finished(int)),this, SLOT(procF(int)));
}

void LMainWindow::initWebKit(){
	progress = 0;

	QFile file;
	file.setFileName(":/jquery.min.js");
	file.open(QIODevice::ReadOnly);
	jQuery = file.readAll();
	jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
	file.close();

	QNetworkProxyFactory::setUseSystemConfiguration(true);

	view = new QWebView(this);

	connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
	connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
	connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
	connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

	locationEdit = new QLineEdit(this);
	locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
	connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

	QToolBar *toolBar = addToolBar(tr("Navigation"));
	toolBar->addAction(view->pageAction(QWebPage::Back));
	toolBar->addAction(view->pageAction(QWebPage::Forward));
	toolBar->addAction(view->pageAction(QWebPage::Reload));
	toolBar->addAction(view->pageAction(QWebPage::Stop));
	toolBar->addWidget(locationEdit);

	if(site != ""){
		view->load(QUrl(site));
	}
}
void LMainWindow::initLog(){
	dev    = new GDevelop    (this);
	proc   = new QProcess    (this);

	devvis = false;
	dev->setVisible(false);

	modloaderlist = new QMap<QString, QString>;
	selectmodv = new QTableView;
	selectmodl = new GModLoaderSelect(*modloaderlist);

	w_log = new LLogWidget;
	srv = new MLocalServer(w_log);

	bstart	= new QPushButton  ("Start");
	bdev	= new QPushButton    ("+");
	elog	= new QLineEdit      ("admin");
	epas	= new QLineEdit      ("admin");
	log     = new QCheckBox   ("Show log");
	list	= new QListView      ();
	prog    = new QProgressBar();

	selectmodv->setModel(selectmodl);

	w_log->showMaximized();
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
	layout = new QHBoxLayout();
	vlay = new QVBoxLayout();
	hlay = new QHBoxLayout();
	slay = new QGridLayout();
	llay = new QGridLayout();

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

	vlay->addWidget(view);
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
	dev->reloadModLoader();
	checkDir();
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
	foreach(QString f, list){
		QFile file(f);
		needDownload = !file.exists();
	}

	if(needDownload){
		download();
	}else{
		this->prog->setValue(100);
	}
}

void LMainWindow::initModLoaders(){
	QSettings sett;
	initModLoaderList();
	if(sett.contains("modloader")){
		loadModLoader(sett.value("modloader").toString());
	}else{
		selectModLoader();
	}
}
void LMainWindow::initModLoaderList(){
	modloaderlist->clear();
	w_log->addL(GLogLevel::DEBUG, "L-Main", "ModLoaderList: ");
	QDir dir("modloaders");
	foreach(QString f, dir.entryList(getPluginFilter())){
		QPluginLoader pluginLoader(dir.absoluteFilePath(f));
		QObject *plugin = pluginLoader.instance();
		if (plugin) {
			GModLoaderInterface* t = qobject_cast<GModLoaderInterface *>(plugin);
			if (t){
				w_log->addL(GLogLevel::DEBUG, "L-Main", t->getName() + " : " + f);
				modloaderlist->insert(t->getName(), f);
			}
		}
	}
}
void LMainWindow::loadModLoader(QString s){
	if(modloaderlist->contains(s)){
		QDir modloaderdir("modloaders");
		pluginLoader = new QPluginLoader(modloaderdir.absoluteFilePath(modloaderlist->value(s)));
		QObject *plugin = pluginLoader->instance();
		if (plugin) {
			GModLoaderInterface* t = qobject_cast<GModLoaderInterface *>(plugin);
			if (t){
				modloader = t;
				modloader->setLogger(w_log);
				w_log->addL(GLogLevel::INFO, "L-Main", modloader->getName() + " modloader loaded");
			}
		}
	}else{
		w_log->addL(GLogLevel::INFO, "L-Main", s + " modloader don't loaded");
	}
}
void LMainWindow::selectModLoader(){
	//selectmodv->show();
	QSettings sett;
	sett.setValue("modloader","BaseModLoader");
}
void LMainWindow::parse(){
	this->modloader->parseZips();
}

void LMainWindow::download(){

}
void LMainWindow::launch(){
	pluginLoader->unload();
	this->hide();
	srv->clients->clear();
	proc->start(dir+"/game.exe");

	connect(proc, SIGNAL(finished(int)), this, SLOT(procF(int)));
}
void LMainWindow::adjustLocation(){
	locationEdit->setText(view->url().toString());
}
void LMainWindow::changeLocation(){
	QUrl url = QUrl::fromUserInput(locationEdit->text());
	view->load(url);
	view->setFocus();
}
void LMainWindow::adjustTitle(){
	if (progress <= 0 || progress >= 100)
		setWindowTitle(view->title());
	else
		setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}
void LMainWindow::setProgress(int p){
	progress = p;
	adjustTitle();
}
void LMainWindow::finishLoading(bool){
	progress = 100;
	adjustTitle();
	view->page()->mainFrame()->evaluateJavaScript(jQuery);
}
void LMainWindow::closeEvent(QCloseEvent *event){
	w_log->close();
	event->accept();
}
