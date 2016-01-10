#ifndef GLOBALQT_LDEFINES_H
#define GLOBALQT_LDEFINES_H

enum class ILogLevel {ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7};

class LLogWidget;

extern LLogWidget* LV_LOGGER;

#define ME_SAVE QString(".zip")
#define NO_DEBUG true

#define lLogE(ms)  LV_LOGGER->addL(ILogLevel::ERR,   Q_FUNC_INFO, ms)
#define lLogW(ms)  LV_LOGGER->addL(ILogLevel::WARN,  Q_FUNC_INFO, ms)
#define lLogI(ms)  LV_LOGGER->addL(ILogLevel::INFO,  Q_FUNC_INFO, ms)
#define lLogD(ms)  LV_LOGGER->addL(ILogLevel::DEBUG, Q_FUNC_INFO, ms)
#define lLogF(ms)  LV_LOGGER->addL(ILogLevel::FINE,  Q_FUNC_INFO, ms)
#define lLogFF(ms) LV_LOGGER->addL(ILogLevel::FFINE, Q_FUNC_INFO, ms)
#define lLogA(ms)  LV_LOGGER->addL(ILogLevel::ALL,   Q_FUNC_INFO, ms)


#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <Launcher/lutils.h>


#endif //GLOBALQT_LDEFINES_H
