#ifndef GLOBALQT_IMODS_H
#define GLOBALQT_IMODS_H

class IVars;

class IModLoader {
public:
	virtual QString getName() = 0;
	virtual ~IModLoader() {}
	// Engine
	virtual void setVars(IVars* v) = 0;
	virtual void corePreInit() = 0;
	virtual void coreInit() = 0;
	virtual void corePostInit() = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;

};

class ICoreMod{
public:
	virtual QStringList getOwList() = 0;
	virtual QStringList getDpList() = 0;

	virtual void setVars(IVars* v) = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;
};

class IMod{
public:
	virtual QStringList getOwList() = 0;
	virtual QStringList getDpList() = 0;

	virtual void setVars(IVars* v) = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;
};

#endif //GLOBALQT_IMODS_H
