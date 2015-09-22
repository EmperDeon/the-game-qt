#include <Global/gmods.h>

#undef CLASS_NAME
#define CLASS_NAME "Modloader"
GMods::GMods(){
 initModLoaders();
}

void GMods::coreInit(){
	if(modloader){
		this->modloader->corePreInit();
		this->modloader->coreInit();
		this->modloader->corePostInit();
	}
}

void GMods::init(){
	if(modloader){
		this->modloader->preInit();
		this->modloader->init();
		this->modloader->postInit();
	}
}

void GMods::initModLoaders() {
	QSettings sett;
	modloaderlist = new QMap<QString, QString>();
	initModLoaderList();
	if(sett.contains("modloader")){
		loadModLoader(sett.value("modloader").toString());
	}else{
	}
}
void GMods::initModLoaderList() {
	modloaderlist->clear();
	logF("ModLoaderList: ");
	QDir dir("modloaders");
			foreach(QString f, dir.entryList(getPluginFilter())){
			QPluginLoader pluginLoader(dir.absoluteFilePath(f));
			QObject *plugin = pluginLoader.instance();
			if (plugin) {
				GModLoaderInterface* t = qobject_cast<GModLoaderInterface *>(plugin);
				if (t){
					logF(t->getName() + " : " + f);
					modloaderlist->insert(t->getName(), f);
				}
			}
		}
}
void GMods::loadModLoader(QString s) {
	if(modloaderlist->contains(s)){
		QDir modloaderdir("modloaders");
		QPluginLoader pluginLoader(modloaderdir.absoluteFilePath(modloaderlist->value(s)));
		QObject *plugin = pluginLoader.instance();
		if (plugin) {
			GModLoaderInterface* t = qobject_cast<GModLoaderInterface *>(plugin);
			if (t){
				modloader = t;
				modloader->setVars(&GV_VARS);
				logI(modloader->getName() + " modloader loaded");
			}
		}
	}else{
		logI(s + " modloader don't loaded");
	}
}

QStringList GMods::getPluginFilter() {
		QStringList r;
		//#ifdef Q_OS_WIN
		r << "*.dll";
		//#endif

		return r;
}
