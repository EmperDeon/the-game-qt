#ifndef GLOGALQT_EWIDGETS_H
#define GLOGALQT_EWIDGETS_H
#include <idefines.h>

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

#endif //GLOGALQT_EWIDGETS_H
