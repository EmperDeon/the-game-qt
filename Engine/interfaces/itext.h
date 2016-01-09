#ifndef GLOBALQT_ITEXT_H
#define GLOBALQT_ITEXT_H
#include <Engine/einterfaces.h>

class IModsIds {
public:
	virtual Imiks get(QString m, QString i, QString k, int s) = 0;
};

class IItem{
public:
	virtual float getStackSize() = 0;
	virtual int getStackType() = 0;

	virtual QString getTexture() = 0;
};
class IItemsContainer{
public:
	virtual IItem* get(Imiks id) = 0;
	virtual Imiks get(IItem* it) = 0;
};

class ITool{
public:
	virtual QString getType() = 0;
	virtual int getDurability() = 0;

	virtual QString getTexture() = 0;
};
class IToolsContainer{
public:
	virtual ITool* get(Imiks id) = 0;
	virtual Imiks get(ITool* id) = 0;
};

class IBlock{
public:
	virtual float getWeight() = 0;

	virtual QString getTexture() = 0;
};

class IBlocksContainer{
public:
	virtual IBlock* get(Imiks id) = 0;
	virtual Imiks get(IBlock* id) = 0;
};

#endif //GLOBALQT_ITEXT_H
