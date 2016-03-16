#ifndef GLOBALQT_MTEXT_H
#define GLOBALQT_MTEXT_H
#include <idefines.h>
#include <mods/mcontainers.h>

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
	ITextureManager *mItex, *mBtex, *mTtex;

	MTextContainer();

	void preInit();
	void init();
	void postInit();
};

#endif //GLOBALQT_MTEXT_H
