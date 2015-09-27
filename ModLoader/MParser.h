#ifndef GLOBALQT_MPARSER_H
#define GLOBALQT_MPARSER_H

#include <ModLoader/mmodloader.h>

class ModLoader;

class MParser {
 ModLoader* loader;

public:
	MParser(ModLoader* m);
	void parse();
	void parse(QString s);
};


#endif //GLOBALQT_MPARSER_H
