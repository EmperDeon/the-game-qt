#include <ModLoader/core/mcoremods.h>

#define upd(a) main->setSplashLabel(a)

bool contains(QStringList a, QStringList b){
	for(QString s : b){
		if(!a.contains(s)) return false;
	}
	return true;
}

MCoreMods::MCoreMods(){
 this->modList = new QList<ICoreMod*>;
	this->t_ren = mVarG(QThread*, "eRenderThread");
	this->queue = mVarG(QThreadPool*, "eThreadQueue");
	parseOwerwrites();
	loadPlugins();

	main = mVarG(IMain*, "eMain");
	this->vselect = new MVarSelect(this);
}

// PreInit
void MCoreMods::parseOwerwrites(){
	QDir dir("mods/coremods");
	QStringList owr;

	// TODO: Rewrite plugin is an array in pack.dat
	QPluginLoader pluginLoader;

	for(QFileInfo i : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
	for(QFileInfo f : QDir(i.filePath()).entryInfoList({"*.dll"}, QDir::Files, QDir::Name)){
		pluginLoader.setFileName(f.filePath());
		QObject* plugin = pluginLoader.instance();
		if (plugin) {
			ICoreMod* t = qobject_cast<ICoreMod*>(plugin);
			if (t){
				t->setVars(MV_VARS);
				modList->append(t);
				mLogI(t->getName() + " coremod loaded");
			}
		}
	}

	owr << "mRender";
 owr << "mLevel";

	MV_VARS->setOverwriteList(owr);
}

void MCoreMods::loadPlugins() {
	QList<ICoreMod*> tlist(*modList), elist;
// Check all mods
	{
		QStringList names, dep, err;
		bool b = false; QString name;

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
			mLogE("Not found CoreMods: " + name),
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

			mLogE("Deadlock: " + t);
			for(auto m : tlist)
				qDebug() << " Name: " << m->getName() << ", Dependencies: " << m->getDpList();
		}
	}

	main = mVarG(IMain*, "eMain");
}

void MCoreMods::preInit() {
	mLogFF("preInit started");
 MV_VARS->setVarsLoader(this);

 upd("Started preCoreInit");

	events = mVarG(IEvents*, "mEvents");
	upd("Event system constructed");

	level = mVarG(ILevelManager*, "mLevel");
	upd("Level constructed");

	render = mVarG(MGlWidget*, "mRender");
	upd("Render constructed");

	this->perf = new MPerformanceWidget();
	upd("Performance Widget constructed");
	//this->perf->show();

	for(ICoreMod* p : *modList ){
	 p->preInit();
	}
	upd("CoreMods preInit finished");

	mLogFF("preInit finished");
}
// PreInit


void MCoreMods::init() {
	mLogFF("init started");

	for(ICoreMod* p : *modList ){
		p->init();
	}
	upd("Coremods init finished");

	mLogFF("init finished");
}

void MCoreMods::postInit() {
	mLogFF("postInit started");

	for(ICoreMod* p : *modList ){
 	p->postInit();
	}
	upd("Coremods postInit finished");

	events = mVarG(IEvents*, "mEvents");
	level = mVarG(ILevelManager*, "mLevel");
	render = mVarG(MGlWidget*, "mRender");

	mLogFF("postInit finished");
}

void* MCoreMods::get(QString name){
	return vselect->getVar(name);
}

void* MCoreMods::getO(QString name) {
	if(name == "mEvents"){
		if(oEvents == nullptr) oEvents = new MEvents();
		return oEvents;

	}else if(name == "mRender"){
		if(oRender == nullptr) oRender = new MGlWidget();
		return oRender;

	}else if(name == "mLevel"){
		if(oLevel == nullptr) oLevel = new MLevelManager();
		return oLevel;

	}else{
		mLogE("No such variable");
		return nullptr;
	}
}

IVarsLoader *MCoreMods::findMod(QString n) {
	if(n == "ModLoader"){
		return this;
	}
	for(ICoreMod* i : *modList)
		if(i->getName() == n)
			return i;

	return nullptr;
}

QStringList MCoreMods::getVarsList() {
	return {"mEvents", "mRender", "mLevel"};
}

MCoreMods* MV_CORE_MODS;
// MCoreMods


// MVarSelect
MVarSelect::MVarSelect(MCoreMods *core) {
 QJsonObject s = MV_SETT->get("VarOverrideMap");

	if(s.size() == 1){
  MVarSelectWidget* wgt = new MVarSelectWidget(core);
  core->main->getSplashSceen()->finish(wgt);
	 wgt->show();
	}else{
		continueLoad();
	}
}

void MVarSelect::continueLoad(){
	QJsonObject& s = MV_SETT->get("VarOverride");
	s.remove("Map");
	MV_SETT->save();

	map = new QMap<QString, IVarsLoader*>;
	// Fill map with mods
	for(QString k : s.keys()){
		if(s.value(k).toString() != "ModLoader" && k != "name")
		map->insert(k, MV_CORE_MODS->findMod(s.value(k).toString()));
	}

	MV_CORE_MODS->main->init();
}

void* MVarSelect::getVar(QString name) {
 if(map->contains(name)){
	 mLogI("Getting " + name + " from mod");
	 return map->value(name)->get(name);
 }else{
	 mLogI("Getting " + name + " from modloader");
	 return getOVar(name);
 }
}

void* MVarSelect::getOVar(QString name) {
 return MV_CORE_MODS->getO(name);
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
	QJsonObject& obj =	MV_SETT->get("VarOverride");

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
	for(QString s : core->getVarsList())
		map->insert(s, "ModLoader");

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
	MV_CORE_MODS->vselect->continueLoad();
}
// MVarSelectWidget

