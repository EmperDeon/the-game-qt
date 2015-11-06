#ifndef GLOBALQT_MLEVEL_H
#define GLOBALQT_MLEVEL_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mregion.h>

class MLevel : public ILevel{
	QString name;
	MRegion* reg;

public:
	MLevel(QString name);
	virtual QString getName();
	virtual void load();
	virtual void save();
};

#endif //GLOBALQT_MLEVEL_H
