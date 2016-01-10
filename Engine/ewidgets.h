#ifndef G_WIDGETS
#define G_WIDGETS
#include <Engine/edefines.h>

// EDeveloper
class EDeveloper : public QWidget{
	Q_OBJECT

	QVBoxLayout* lay;
	QPushButton* bsett;
	QPushButton* blevl;
	QPushButton* bmods;
	QPushButton* bmodl;
	QPushButton* bpack;
	QPushButton* bresm;

public:
	EDeveloper();
};
// EDeveloper

#endif
