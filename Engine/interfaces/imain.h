#ifndef GLOBALQT_IMAIN_H
#define GLOBALQT_IMAIN_H

class IMain{
public:
	virtual void setSplashLabel(QString s) = 0;
	virtual void init() = 0;
	virtual void show() = 0;
	virtual void destroy() = 0;
	virtual ~IMain(){};
};

class ILogger{
public:
	virtual void log(ILogLevel lv, QString cl, QString ms) = 0;
	virtual void sendM(QString s) = 0;
	virtual ~ILogger(){};
};

class IVars{
public:
	virtual bool contains(QString name) = 0;
	virtual bool contains(QStringList l) = 0;
	virtual void* get(QString name) = 0;
	virtual void set(void* o, QString n) = 0;
	virtual void setOverwriteList(QStringList l) = 0;
	virtual ~IVars(){};
};

#endif //GLOBALQT_IMAIN_H
