#ifndef GLOBALQT_IDEFINES_H
#define GLOBALQT_IDEFINES_H

// Engine
class ILogger;
class IVars;
class IDirs;
class ISettings;
class ISettCont;

extern ILogger*   IV_LOGGER;
extern IVars*     IV_VARS;
extern IDirs*     IV_DIRS;
extern ISettings* IV_SETT;
extern ISettCont* IV_SETC;

#define logE(ms)  IV_LOGGER->log(ILogLevel::ERR,   Q_FUNC_INFO, ms)
#define logW(ms)  IV_LOGGER->log(ILogLevel::WARN,  Q_FUNC_INFO, ms)
#define logI(ms)  IV_LOGGER->log(ILogLevel::INFO,  Q_FUNC_INFO, ms)
#define logD(ms)  IV_LOGGER->log(ILogLevel::DEBUG, Q_FUNC_INFO, ms)
#define logF(ms)  IV_LOGGER->log(ILogLevel::FINE,  Q_FUNC_INFO, ms)
#define logFF(ms) IV_LOGGER->log(ILogLevel::FFINE, Q_FUNC_INFO, ms)
#define logA(ms)  IV_LOGGER->log(ILogLevel::ALL,   Q_FUNC_INFO, ms)

#define varG(cl, s) reinterpret_cast<cl>(IV_VARS->get(s))
#define varN(cl, s)    reinterpret_cast<cl>(IV_VARS->getN(s))
#define varNA(cl, x, y) reinterpret_cast<cl>(IV_VARS->getN(x, y))
#define varS(cl, s) IV_VARS->set(cl, s)
// Engine


// ModLoader
class MMods;
class MCoreMods;

extern MMods*     MV_MODS;
extern MCoreMods* MV_CORE_MODS;
// ModLoader

#include <iall.h>
#include <ivars.h>

#endif //GLOBALQT_IDEFINES_H
