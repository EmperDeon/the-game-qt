#ifndef GLOBALQT_IUTILS_H
#define GLOBALQT_IUTILS_H


class Imiks {
	//bytes - mod:10, item:10, kind:8, state:4
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
		if((x < 32)&&(y < 32)&&(z < 32)){
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
	bool operator< (IBlockPos o)const {return d < o.d;}
};
class IChunkPos {
	// bytes - x:5, y:5, z:5
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

struct Vector3 {
	float x, y, z;

	Vector3(float X, float Y, float Z) :
		x(X),
		y(Y),
		z(Z) { }

	Vector3() :
		x(0.0f),
		y(0.0f),
		z(0.0f) { }

	Vector3(const Vector3 &v) :
		x(v.x),
		y(v.y),
		z(v.z) { }

	Vector3 operator*(const float s) const {
		return Vector3(x * s, y * s, z * s);
	}

	Vector3 &operator=(const Vector3 &v) {
		if (this == &v) {
			return *this;
		}

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	Vector3 &operator+=(const Vector3 &v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}

	const Vector3 operator-(const Vector3 &v) const {
		Vector3 result;
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

template<typename Base, typename T> inline bool instanceOf(const T *ptr) {
	return reinterpret_cast<const Base*>(ptr) != nullptr;
}

inline float degreesToRadians(const float degrees) {
	const float PIOver180 = 3.14159f / 180.0f;
	return degrees * PIOver180;
}

#endif //GLOBALQT_IUTILS_H
