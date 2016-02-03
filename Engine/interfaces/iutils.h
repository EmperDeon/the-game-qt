#ifndef GLOBALQT_IUTILS_H
#define GLOBALQT_IUTILS_H

#define CHUNK_SIZE 32
#define REGION_SIZE_X 8
#define REGION_SIZE_Y 8
#define REGION_SIZE_Z 8

#include <QtCore>
#include <QtWidgets>

// Id containers
class Imiks {// bytes - mod:10, item:10, kind:8, state:4
	quint32 d;

public:
	Imiks(){d = 0;}
	Imiks(quint32 c){this->d = c;}
	Imiks(int m, int i, int k, int s){
		d = 0;
		if((m < 1024)&&(i < 1024)&&(k < 256)&&(s < 16)){
			d |= m << 23;
			d |= i << 13;
			d |= k << 5;
			d |= s << 1;
		}else{
			//EV_LOGGER->log(ILogLevel::ERR, "Imiks", "One of parameters is greater then 1024");
		}
	}

	quint32 c()const { return d;}

	int     m()const {	return this->d >> 22 & 1023;}
	int     i()const {	return this->d >> 13 & 1023;}
	int     k()const {	return this->d >> 5 & 255;  }
	int     s()const {	return this->d >> 1 & 15;   }

	bool    operator< (Imiks o)const {return d < o.d;}
};
// Id containers


// Position containers
class IBlockPos {// bytes - x:5, y:5, z:5
	quint16 d;

public:
	IBlockPos(){d = 0;}
	IBlockPos(int x, int y, int z){
		d = 0;
		if((x < 32)&&(y < 32)&&(z < 32)){
			d |= x << 11;
			d |= y << 6;
			d |= z << 1;
		}else{
			//EV_LOGGER->log(ILogLevel::ERR, "Imiks", "One of parameters is greater then 1024");
		}
	}

	quint16 c()const { return d;}

	int     x()const {	return this->d >> 11 & 31;}
	int     y()const {	return this->d >> 6 & 31;}
	int     z()const {	return this->d >> 1 & 31;  }

	bool    operator< (IBlockPos o)const {return d < o.d;}
};

class IChunkPos {// bytes - x:5, y:5, z:5
	quint16 d;

public:
	IChunkPos(){d = 0;}
	IChunkPos(quint16 c): d(c){}
	IChunkPos(int x, int y, int z){
		d = 0;
		if((x < 32)||(y < 32)||(z < 32)){
			d |= x << 11;
			d |= y << 6;
			d |= z << 1;
		}else{
			//EV_LOGGER->log(ILogLevel::ERR, "Imiks", "One of parameters is greater then 1024");
		}
	}

	quint16 c()const { return d;}

	int     x()const {	return this->d >> 11 & 31;}
	int     y()const {	return this->d >> 6 & 31;}
	int     z()const {	return this->d >> 1 & 31;  }

	bool    operator< (IChunkPos o)const {return d < o.d;}
};

class IRegionPos{
	qint32 px;
	qint32 py;
	qint32 pz;
public:
	IRegionPos(){ px = 0; py = 0; pz = 0; }
	IRegionPos(qint32 x, qint32 y, qint32 z){ this->px = x; this->pz = z; }

	qint32 x(){ return px; }
	qint32 y(){ return py; }
	qint32 z(){ return pz; }
};

class IAChunkPos {// bytes - x:5, y:5, z:5
	quint16 d;

	qint32 rgX;
	qint32 rgY;
	qint32 rgZ;
 qint32 ps(qint32 x){return byte(x >= 0 ? x : -x);}
 bool  ips(qint32 x){return x >= 0;}
public:
	IAChunkPos(){d = 0;}
	IAChunkPos(quint16 c, qint32 rX, qint32 rY, qint32 rZ): d(c), rgX(rX), rgY(rY), rgZ(rZ){}
	IAChunkPos(IRegionPos p, qint32 x, qint32 y, qint32 z){
		d = 0;
		d  |= x << 11;
		d  |= y << 6;
		d  |= z << 1;
		rgX = p.x();
		rgY = p.y();
		rgZ = p.z();
	}
	IAChunkPos(qint32 x, qint32 y, qint32 z){
		d = 0;
		d |= (x >= 0) << 15;		d |= (ps(x) % REGION_SIZE_X) << 12;
		d |= (y >= 0) << 11;		d |= (ps(y) % REGION_SIZE_Y) << 8;
		d |= (z >= 0) << 7; 		d |= (ps(z) % REGION_SIZE_Z) << 4;

	 rgX = x / REGION_SIZE_X;
		rgY = y / REGION_SIZE_Y;
		rgZ = z / REGION_SIZE_Z;
	}

	quint16 c()const { return d;}

	qint32  x() const{	return (rgX * REGION_SIZE_X) + (this->d >> 12& 7) * (d>>15 & 1 ? 1 : -1); }
	qint32  y() const{	return (rgY * REGION_SIZE_Y) + (this->d >> 8 & 7) * (d>>11 & 1 ? 1 : -1); }
	qint32  z() const{	return (rgZ * REGION_SIZE_Z) + (this->d >> 4 & 7) * (d>>7  & 1 ? 1 : -1); }

	qint32 rX() const{ return rgX; }
	qint32 rY() const{ return rgY; }
	qint32 rZ() const{ return rgZ; }

	bool    operator< (IAChunkPos o)const {
		if(rgX != o.rgX)
			return rgX < o.rgX;

		else if(rgY != o.rgY)
			return rgY < o.rgY;

		else if(rgZ != o.rgZ)
			return rgZ < o.rgZ;

		return d < o.d;
	}

	bool    operator> (IAChunkPos o)const {
		if(rgX != o.rgX)
			return rgX > o.rgX;

		else if(rgY != o.rgY)
			return rgY > o.rgY;

		else if(rgZ != o.rgZ)
			return rgZ > o.rgZ;

		return d > o.d;
	}
};
// Position containers


// Vectors
struct IVec2 {
	float x, y;

	IVec2(float X, float Y):	x(X),	y(Y){ }
	IVec2():	x(0.0f),	y(0.0f) { }
	IVec2(const IVec2 &v):	x(v.x),	y(v.y) { }

	IVec2 operator*(const float s) const {	return IVec2(x * s, y * s);	}

	IVec2 &operator=(const IVec2 &v) {
		if (this == &v) {
			return *this;
		}

		x = v.x;
		y = v.y;

		return *this;
	}

	IVec2 &operator+=(const IVec2 &v) {
		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	const IVec2 operator-(const IVec2 &v) const {
		IVec2 result;
		result.x = x - v.x;
		result.y = y - v.y;

		return result;
	}

	float length() const {	return sqrtf(x * x + y * y);	}

	void normalize() {
		float l = 1.0f / length();
		x *= l;
		y *= l;
	}
};

struct IVec3 {
	float x, y, z;

	IVec3(float X, float Y, float Z) :
		x(X),
		y(Y),
		z(Z) { }

	IVec3() :
		x(0.0f),
		y(0.0f),
		z(0.0f) { }

	IVec3(const IVec3 &v) :
		x(v.x),
		y(v.y),
		z(v.z) { }

	IVec3 operator*(const float s) const {
		return IVec3(x * s, y * s, z * s);
	}

	IVec3 &operator=(const IVec3 &v) {
		if (this == &v) {
			return *this;
		}

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	IVec3 &operator+=(const IVec3 &v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}

	const IVec3 operator-(const IVec3 &v) const {
		IVec3 result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;

		return result;
	}

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	void normalize() {
		float l = 1.0f / length();
		x *= l;
		y *= l;
		z *= l;
	}
};

struct IRect {
	float x1, y1, x2, y2;

	IRect(float X, float Y, float X1, float Y2): x1(X), y1(Y), x2(X1), y2(Y2) { }
	IRect(): x1(0.0f), y1(0.0f), x2(0.0f), y2(0.0f) { }

	IRect(const IRect &v) :
		x1(v.x1),
		y1(v.y1),
		x2(v.x2), y2(v.y2) { }
};

struct IVec3i {
	int x, y, z;

	IVec3i(int X, int Y, int Z) :
		x(X),
		y(Y),
		z(Z) { }

	IVec3i() :
		x(0),
		y(0),
		z(0) { }

	IVec3i(const IVec3i &v) :
		x(v.x),
		y(v.y),
		z(v.z) { }

	IVec3i(const IVec3 &v) :
		x((int)v.x),
		y((int)v.y),
		z((int)v.z) { }

	IVec3i operator*(const int s) const {
		return IVec3i(x * s, y * s, z * s);
	}

	IVec3i &operator=(const IVec3i &v) {
		if (this == &v) {
			return *this;
		}

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	IVec3i &operator+=(const IVec3i &v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}

	const IVec3i operator-(const IVec3i &v) const {
		IVec3 result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;

		return result;
	}

	bool operator==(const IVec3i v) const{
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator!=(const IVec3i v) const{
		return (x != v.x) || (y != v.y) || (z != v.z);
	}

	IBlockPos toBlockPos(){
		return IBlockPos(
			x % CHUNK_SIZE,
			y % CHUNK_SIZE,
			z % CHUNK_SIZE
		);
	}
};
// Vectors

// Standalone: Render
template<typename Base, typename T> inline bool instanceOf(const T *ptr) {
	return reinterpret_cast<const Base*>(ptr) != nullptr;
}

// Render
inline float degreesToRadians(const float degrees) {
	const float PIOver180 = 3.14159f / 180.0f;
	return degrees * PIOver180;
}

namespace IBSides{
 enum Sides{	Top = 1, Bottom = 2, Left = 4, Right = 8, Front = 16, Back = 32};
}

static bool isTopSide    (byte c){ return (c & 1 ) == 1;  }
static bool isBottomSide (byte c){ return (c & 2 ) == 2;  }
static bool isLeftSide   (byte c){ return (c & 4 ) == 4;  }
static bool isRightSide  (byte c){ return (c & 8 ) == 8;  }
static bool isFrontSide  (byte c){ return (c & 16) == 16; }
static bool isBackSide   (byte c){ return (c & 32) == 32; }
// Standalone: Render

#endif //GLOBALQT_IUTILS_H
