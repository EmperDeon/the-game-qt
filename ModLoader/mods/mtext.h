#ifndef GLOBALQT_MTEXT_H
#define GLOBALQT_MTEXT_H
#include <ModLoader/mdefines.h>
#include <ModLoader/mods/mcontainers.h>
#include <ModLoader/core/render/texture/mtexturemanager.h>

class MIIds;
class MBIds;
class MTIds;
class MItemsContainer;
class MBlocksContainer;
class MToolsContainer;
class MTextureManager;


class MTextContainer {
public:
	MIIds *mIids;
	MBIds *mBids;
	MTIds *mTids;
	MItemsContainer *mIic;
	MBlocksContainer *mBic;
	MToolsContainer *mTic;
	MTextureManager *mItex, *mBtex, *mTtex;

	MTextContainer();

	void preInit();
	void init();
	void postInit();
};

#endif //GLOBALQT_MTEXT_H
