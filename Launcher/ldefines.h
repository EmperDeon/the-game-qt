#ifndef GLOBALQT_LDEFINES_H
#define GLOBALQT_LDEFINES_H

enum class ILogLevel {ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7, QT = 8};

class LLogWidget;

extern LLogWidget* LV_LOGGER;

#define ME_SAVE QString(".zip")
#define NO_DEBUG true

#define lLogE(ms)  LV_LOGGER->log(ILogLevel::ERR,   Q_FUNC_INFO, ms)
#define lLogW(ms)  LV_LOGGER->log(ILogLevel::WARN,  Q_FUNC_INFO, ms)
#define lLogI(ms)  LV_LOGGER->log(ILogLevel::INFO,  Q_FUNC_INFO, ms)
#define lLogD(ms)  LV_LOGGER->log(ILogLevel::DEBUG, Q_FUNC_INFO, ms)
#define lLogF(ms)  LV_LOGGER->log(ILogLevel::FINE,  Q_FUNC_INFO, ms)
#define lLogFF(ms) LV_LOGGER->log(ILogLevel::FFINE, Q_FUNC_INFO, ms)
#define lLogA(ms)  LV_LOGGER->log(ILogLevel::ALL,   Q_FUNC_INFO, ms)


#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <lutils.h>


#endif //GLOBALQT_LDEFINES_H
