#ifndef GLOBALQT_IMAIN_H
#define GLOBALQT_IMAIN_H

class QString;
class QStringList;
class QFile;
class QDir;

class IMain{
public:
	virtual void setSplashLabel(QString) = 0;

	virtual void init()                  = 0;
	virtual void show()                  = 0;
	virtual void destroy()               = 0;
};


class ILogger{
public:
	virtual void log(ILogLevel lv, QString, QString) = 0;
	virtual void sendM(QString)                      = 0;
};


class IVars{
public:
	virtual bool  contains(QString)             = 0;
	virtual bool  contains(QStringList)         = 0;

	virtual void* get(QString)                  = 0;

	virtual void  set(void* o, QString)         = 0;
	virtual void  setOverwriteList(QStringList) = 0;
};


class IDirs{
public:
	virtual void    addDir(QString, QString)   = 0;

	virtual QDir*   getDir(QString)            = 0;
	virtual QFile*  getFile(QString, QString)  = 0;

	virtual QString getSDir(QString)           = 0;
	virtual QString getSFile(QString, QString) = 0;
};


#endif //GLOBALQT_IMAIN_H
