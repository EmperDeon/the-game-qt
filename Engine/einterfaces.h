#ifndef G_MODINTERFACES
#define G_MODINTERFACES

#include <QString>
#include <QtWidgets>

#include "Engine/edefines.h"
#include "Engine/interfaces/imain.h"

class Imiks {
	//bytes - mod:10, item:10, kind:8, state:4
	quint32 d;
public:
	Imiks(){d = 0;}
	Imiks(quint32 c){this->d = c;}
	Imiks(int m, int i, int k, int s){
		d = 0;
		if((m < 1024)||(i < 1024)||(k < 256)||(s < 16)){
			d |= m << 23;
			d |= i << 13;
			d |= k << 5;
			d |= s << 1;
		}else{
			//GV_LOGGER->log(GLogLevel::ERR, "Imiks", "One of parameters is greater then 1024");
		}
	}
	quint32 c()const { return d;}
	int m()const {	return this->d >> 22 & 1023;}
	int i()const {	return this->d >> 13 & 1023;}
	int k()const {	return this->d >> 5 & 255;  }
	int s()const {	return this->d >> 1 & 15;   }
	bool operator< (Imiks o)const {return d < o.d;}
};
class IBlockPos {
	// bytes - x:5, y:5, z:5
	quint16 d;
public:
	IBlockPos(){d = 0;}
	IBlockPos(int x, int y, int z){
		d = 0;
		if((x < 32)||(y < 32)||(z < 32)){
			d |= x << 11;
			d |= y << 6;
			d |= z << 1;
		}else{
			//GV_LOGGER->log(GLogLevel::ERR, "Imiks", "One of parameters is greater then 1024");
		}
	}
	quint16 c()const { return d;}
	int x()const {	return this->d >> 11 & 32;}
	int y()const {	return this->d >> 6 & 32;}
	int z()const {	return this->d >> 1 & 32;  }
	bool operator< (IBlockPos o)const {return d < o.d;}
};
class IChunkPos {
	// bytes - x:5, y:5, z:5
	quint16 d;
public:
	IChunkPos(){d = 0;}
	IChunkPos(int x, int y, int z){
		d = 0;
		if((x < 32)||(y < 32)||(z < 32)){
			d |= x << 11;
			d |= y << 6;
			d |= z << 1;
		}else{
			//GV_LOGGER->log(GLogLevel::ERR, "Imiks", "One of parameters is greater then 1024");
		}
	}
	quint16 c()const { return d;}
	int x()const {	return this->d >> 11 & 31;}
	int y()const {	return this->d >> 6 & 31;}
	int z()const {	return this->d >> 1 & 31;  }
	bool operator< (IChunkPos o)const {return d < o.d;}
};
class IRegionPos{
	long int px;
	long int py;
public:
	IRegionPos(){ px = 0; py = 0; }
	IRegionPos(long int x, long int y){ this->px = x; this->py = y; }
	long int x(){ return px; }
	long int y(){ return py; }
};

template<typename Base, typename T> inline bool instanceOf(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

#include "Engine/interfaces/iinventory.h"
#include "Engine/interfaces/ilevel.h"
#include "Engine/interfaces/imods.h"
#include "Engine/interfaces/irender.h"
#include "Engine/interfaces/itext.h"



QT_BEGIN_NAMESPACE
// ModLoader
Q_DECLARE_INTERFACE(IModLoader, "org.ilzcorp.IModLoader")
Q_DECLARE_INTERFACE(IModsIds, "org.ilzcorp.IModsIds")

Q_DECLARE_INTERFACE(IItemsContainer, "org.ilzcorp.IItemsContainer")
Q_DECLARE_INTERFACE(IItem, "org.ilzcorp.IItem")

Q_DECLARE_INTERFACE(IBlocksContainer, "org.ilzcorp.IBlocksContainer")
Q_DECLARE_INTERFACE(IBlock, "org.ilzcorp.IBlock")

//!ModLoader
//CoreMod

Q_DECLARE_INTERFACE(ICoreMod, "org.ilzcorp.ICoreMod")
Q_DECLARE_INTERFACE(IRender,  "org.ilzcorp.GRenderInterface")

//!CoreMod
//Mod

Q_DECLARE_INTERFACE(IMod,     "org.ilzcorp.IMod")

//!Mod
//Engine

Q_DECLARE_INTERFACE(IMain,    "org.ilzcorp.IMain")
Q_DECLARE_INTERFACE(ILogger,  "org.ilzcorp.ILogger")
Q_DECLARE_INTERFACE(IVars,    "org.ilzcorp.IVars")

//!Engine
// Q_DECLARE_INTERFACE(, "org.ilzcorp.")
QT_END_NAMESPACE
#endif