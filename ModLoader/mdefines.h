#ifndef GLOBALQT_MDEFINES_H
#define GLOBALQT_MDEFINES_H

class MMods;
class MCoreMods;
class ILogger;
class IVars;
class ISettings;
class ISettCont;

extern MMods*     MV_MODS;
extern MCoreMods* MV_CORE_MODS;

extern ILogger*   MV_LOGGER;
extern IVars*     MV_VARS;
extern ISettings* MV_SETT;
extern ISettCont* MV_SETC;

// Render defines
#define MFPS_COUNT 60
// Render defines

#define mLogE(ms)  MV_LOGGER->log(ILogLevel::ERR,   Q_FUNC_INFO, ms)
#define mLogW(ms)  MV_LOGGER->log(ILogLevel::WARN,  Q_FUNC_INFO, ms)
#define mLogI(ms)  MV_LOGGER->log(ILogLevel::INFO,  Q_FUNC_INFO, ms)
#define mLogD(ms)  MV_LOGGER->log(ILogLevel::DEBUG, Q_FUNC_INFO, ms)
#define mLogF(ms)  MV_LOGGER->log(ILogLevel::FINE,  Q_FUNC_INFO, ms)
#define mLogFF(ms) MV_LOGGER->log(ILogLevel::FFINE, Q_FUNC_INFO, ms)
#define mLogA(ms)  MV_LOGGER->log(ILogLevel::ALL,   Q_FUNC_INFO, ms)


#define mVarG(cl, s) reinterpret_cast<cl>(MV_VARS->get(s))
#define mVarS(cl, s) MV_VARS->set(cl, s)


#include <iall.h>

#endif //GLOBALQT_MDEFINES_H
