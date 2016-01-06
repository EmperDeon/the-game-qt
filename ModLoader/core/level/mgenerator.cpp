#include "ModLoader/core/level/mgenerator.h"
#include <ModLoader/core/level/mblock.h>

MWorldGenerator::MWorldGenerator() {}
void MWorldGenerator::generateChunk(IChunk *ch) {
 IChunkPos pos = ch->getId();
	Imiks block(1,1,1,1);

	for ( int x = 0; x < IChunk::size; x++ )
		for ( int y = 0; y < IChunk::size; y++ )
			for ( int z = 0; z < IChunk::size; z++ )
				if((pos.y() == 0) && (y >= 0) && (y < 4)){
					ch->setBlock(IBlockPos(x, y, z), new MWorldBlock(block, IBlockPos(x, y, z)));
				}else{
					ch->setBlock(IBlockPos(x, y, z), nullptr);
				}
}


