#include <core/mcoremods.h>

#define upd(a) main->setSplashLabel(a)

inline bool MCoreMods::contains(QStringList a, QStringList b){
	for(QString s : b){
		if(!a.contains(s)) return false;
	}
	return true;
}

MCoreMods::MCoreMods(){
 this->modList = new QList<ICoreMod*>;
//	this->t_ren = varG(QThread*, "eRenderThread");
//	this->queue = varG(QThreadPool*, "eThreadQueue");
	parseOverwrites();
	loadPlugins();

	main = varG(IMain*, "eMain");
	this->vSelect = new MVarSelect(this);
	logF("CoreMods constructed");
}

// PreInit
void MCoreMods::parseOverwrites(){
	QDir dir("mods/coremods");
	QStringList owr;

	// TODO: Rewrite plugin as an array in pack.dat
	QPluginLoader pluginLoader;

	for(QFileInfo i : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
	for(QFileInfo f : QDir(i.filePath()).entryInfoList({"*.dll"}, QDir::Files, QDir::Name)){
		pluginLoader.setFileName(f.filePath());
		QObject* plugin = pluginLoader.instance();
		if (plugin) {
			ICoreMod* t = qobject_cast<ICoreMod*>(plugin);
			if (t){
				t->setVars(IV_VARS);
				modList->append(t);
				logI(t->getName() + " coremod loaded");
			}
		}
	}

	owr << "mRender";
 owr << "mLevel";

	IV_VARS->setOverwriteList(owr);
}

void MCoreMods::loadPlugins() {
	QList<ICoreMod*> tlist(*modList), elist;
// Check all mods
	{
		QStringList names, dep, err;
		QString name;

		for(auto m : tlist){
			names.append(m->getName());
			dep.append(m->getDpList());
		}

		for(QString s : dep)	if(!names.contains(s)) err << s;

		for(auto m : tlist){
			if(err.contains(m->getName())){
				name += m->getName() + ", ";
				elist << m;
				tlist.removeAll(m);
			}
		}
		name.remove(name.length() - 2, 2);

		if(!err.isEmpty())
			logE("Not found CoreMods: " + name),
				qDebug() << "note - Name and Dependency lists: ",
				qDebug() << " " << names,
				qDebug() << " " << dep;
	}

	// Sort mods by dependencies
	{
		QStringList loaded;
		bool changed = true;

		while(changed){
			changed = false;

			for(auto m : tlist)		if (contains(loaded, m->getDpList())){
					modList->append(m);
					tlist.removeAll(m);
					changed = true;
				}
		}

		if(!tlist.isEmpty()){
			QString t;
			for(auto m : tlist) t += m->getName() + ", ";
			t.remove(t.length()-2, 2);

			logE("Deadlock: " + t);
			for(auto m : tlist)
				qDebug() << " Name: " << m->getName() << ", Dependencies: " << m->getDpList();
		}
	}

	main = varG(IMain*, "eMain");
}

void MCoreMods::preInit() {
	logF("preCoreInit started");
 IV_VARS->setVarsLoader(vSelect);

 upd("Started preCoreInit");

	varG(IEvents*, "mEvents");
	upd("Event system constructed");

	varG(ILevelManager*, "mLevel");
	upd("Level constructed");

	varG(QOpenGLWidget*, "mRender");
	upd("Render constructed");


	for(ICoreMod* p : *modList ){
	 p->preInit();
	}
	upd("CoreMods preInit finished");

	logF("preCoreInit finished");
}
// PreInit


void MCoreMods::init() {
	logF("init started");

	for(ICoreMod* p : *modList ){
		p->init();
	}
	upd("Coremods init finished");

	logF("init finished");
}

void MCoreMods::postInit() {
	logF("postInit started");

	for(ICoreMod* p : *modList ){
 	p->postInit();
	}
	upd("Coremods postInit finished");

//	events = varG(IEvents*, "mEvents");
//	level = varG(ILevelManager*, "mLevel");
//	render = varG(MGlWidget*, "mRender");

	logF("postInit finished");
}

IVarsLoader *MCoreMods::findMod(QString n) {
	for(ICoreMod* i : *modList)
		if(i->getName() == n)
			return i;

	return nullptr;
}

MCoreMods* MV_CORE_MODS;
// MCoreMods


// MVarSelect
MVarSelect::MVarSelect(MCoreMods *core) {
 QJsonObject s = IV_SETT->get("VarOverride");

//	if(s.size() == 1){
  MVarSelectWidget* wgt = new MVarSelectWidget(core);
  core->main->getSplashSceen()->finish(wgt);
	 wgt->show();
//	}else{
//		QTimer::singleShot(10, [=](){continueLoad();});
//	}
}

void MVarSelect::continueLoad(){
	QJsonObject& s = IV_SETT->get("VarOverride");
 IV_SETT->save();

	map = new QMap<QString, IVarsLoader*>;
	// Fill map with mods
	for(QString k : s.keys()){
		if(s.value(k).toString() != "ModLoader" && k != "name")
		map->insert(k, MV_CORE_MODS->findMod(s.value(k).toString()));
	}

	MV_CORE_MODS->main->init();
}

void* MVarSelect::get(QString name) {
 if(map->contains(name)){
	 logFF("Getting " + name + " from mod " + (reinterpret_cast<ICoreMod*>(map->value(name)))->getName());
	 return map->value(name)->get(name);
 }else{
	 logW("No such var "+name);
	 return nullptr;
 }
}

void *MVarSelect::getN(QString name) {
	if(map->contains(name)){
		logFF("Getting new " + name + " from mod");
		return map->value(name)->getN(name);
	}else{
		logW("No such var "+name);
		return nullptr;
	}
}

void *MVarSelect::getN(QString name, QJsonObject arg) {
	if(map->contains(name)){
		logFF("Getting new " + name + " from mod with arguments");
		qDebug() << "note: " << arg;
		return map->value(name)->getN(name, arg);
	}else{
		logW("No such var "+name);
		return nullptr;
	}
}

void *MVarSelect::get(QString mod, QString name) {
	IVarsLoader* l = MV_CORE_MODS->findMod(mod);
	return l ? l->get(name) : nullptr;
}

void *MVarSelect::getN(QString mod, QString name) {
	IVarsLoader* l = MV_CORE_MODS->findMod(mod);
	return l ? l->getN(name) : nullptr;
}

void *MVarSelect::getN(QString mod, QString name, QJsonObject arg) {
	IVarsLoader* l = MV_CORE_MODS->findMod(mod);
	return l ? l->getN(name, arg) : nullptr;
}
// MVarSelect


// MVarSelectWidget
void MVarSelectWidget::cellClicked(int row, int column) {
 if(row != px && column != 0){
	 if(px != -1) {
		 QComboBox* b = reinterpret_cast<QComboBox*>(table->cellWidget(px, 1));
		 int curr = b->currentIndex();// == -1 ? 0 : b->currentIndex();

		 QString v = map->values(map->uniqueKeys()[px])[curr];

		 smap->insert(map->uniqueKeys()[px], v);

		 table->removeCellWidget(px, 1);
		 table->setItem(px , 1, new QTableWidgetItem(v));
	 }

	 QComboBox *box = new QComboBox;
	 box->addItems(map->values(map->uniqueKeys()[row]));
	 box->setCurrentIndex(0);

	 table->setCellWidget(row, 1, box);

	 px = row;
 }
}

void MVarSelectWidget::save() {
	QJsonObject& obj =	IV_SETT->get("VarOverride");

	if(smap->size() != map->uniqueKeys().size()) {
		QMessageBox::information(this, "Warning", "You need to click on all variables [Debug]");
	}else{
  for(QString k : smap->keys()){
		 obj.insert(k, smap->value(k));
  }

		close();
	}
}

MVarSelectWidget::MVarSelectWidget(MCoreMods *core) {
	map = new QMultiMap<QString, QString>;
	smap = new QMap<QString, QString>;

	for(ICoreMod* m : *core->modList)
		for(QString s : m->getOwList())
			if(!map->contains(s, m->getName()))
			 map->insert(s, m->getName());

	QVBoxLayout* l = new QVBoxLayout;
	table = new QTableWidget(map->size(), 2);
	QPushButton* bs = new QPushButton(tr("Save and close"));

	table->setHorizontalHeaderLabels({"Variable", "Mod"});
	for(int i = 0 ; i <  map->uniqueKeys().size() ; i++){
		table->setItem(i, 0, new QTableWidgetItem(map->uniqueKeys()[i]));
		table->setItem(i, 1, new QTableWidgetItem(map->values(map->uniqueKeys()[i])[0]));
	}

	l->addWidget(table);
	l->addWidget(bs);
	this->setLayout(l);

	connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(cellClicked(int, int)));
	connect(bs, SIGNAL(clicked()), this, SLOT(save()));
}

void MVarSelectWidget::closeEvent(QCloseEvent *event) {
	Q_UNUSED(event)

	MV_CORE_MODS->vSelect->continueLoad();
}
// MVarSelectWidget

