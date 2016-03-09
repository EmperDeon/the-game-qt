#ifndef GLOBALQT_EDEFINES_H
#define GLOBALQT_EDEFINES_H

class ILogger;
class IVars;
class IDirs;
class ISettings;
class ISettCont;

extern ILogger*   EV_LOGGER;
extern IVars*     EV_VARS;
extern IDirs*     EV_DIRS;
extern ISettings* EV_SETT;
extern ISettCont* EV_SETC;

#define logE(ms)  EV_LOGGER->log(ILogLevel::ERR,   Q_FUNC_INFO, ms)
#define logW(ms)  EV_LOGGER->log(ILogLevel::WARN,  Q_FUNC_INFO, ms)
#define logI(ms)  EV_LOGGER->log(ILogLevel::INFO,  Q_FUNC_INFO, ms)
#define logD(ms)  EV_LOGGER->log(ILogLevel::DEBUG, Q_FUNC_INFO, ms)
#define logF(ms)  EV_LOGGER->log(ILogLevel::FINE,  Q_FUNC_INFO, ms)
#define logFF(ms) EV_LOGGER->log(ILogLevel::FFINE, Q_FUNC_INFO, ms)
#define logA(ms)  EV_LOGGER->log(ILogLevel::ALL,   Q_FUNC_INFO, ms)


#define varG(cl, s) reinterpret_cast<cl>(EV_VARS->get(s))
#define varS(cl, s) EV_VARS->set(cl, s)

#include <Engine/edvars.h>
#include <iall.h>

#endif //GLOBALQT_EDEFINES_H
