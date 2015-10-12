#ifndef GLOBALQT_IRENDER_H
#define GLOBALQT_IRENDER_H

class IRender{
public:
	virtual void init() = 0;
	virtual void render(QPaintDevice* dev) = 0;
	virtual ~IRender(){};
};

#endif //GLOBALQT_IRENDER_H
