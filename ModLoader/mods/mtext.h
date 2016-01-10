#ifndef GLOBALQT_MTEXT_H
#define GLOBALQT_MTEXT_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>
#include <ModLoader/mods/mcontainers.h>
#include <ModLoader/core/render/texture/mtexturemanager.h>

class MMods;
class ILogger;
class IVars;

class MIIds;
class MBIds;
class MTIds;
class MItemsContainer;
class MBlocksContainer;
class MToolsContainer;
class MTextureManager;
class MTextureManager;
class MTextureManager;

class MTextContainer {
 MMods* loader;
	ILogger* log;
	IVars* vars;

public:
	MIIds *mIids;
	MBIds *mBids;
	MTIds *mTids;
	MItemsContainer *mIic;
	MBlocksContainer *mBic;
	MToolsContainer *mTic;
	MTextureManager *mItex;
	MTextureManager *mBtex;
	MTextureManager *mTtex;

	MTextContainer(MMods* l);

	void preInit();
	void init();
	void postInit();
};

#endif //GLOBALQT_MTEXT_H
