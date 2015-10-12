#ifndef GLOBALQT_GDEFINES_H
#define GLOBALQT_GDEFINES_H

class ILogger;
class IVars;
enum class GLogLevel{ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7};

extern ILogger* GV_LOGGER;
extern IVars* GV_VARS;

#define logE(ms) GV_LOGGER->log(GLogLevel::ERR,   this->className, ms)
#define logW(ms) GV_LOGGER->log(GLogLevel::WARN,  this->className, ms)
#define logI(ms) GV_LOGGER->log(GLogLevel::INFO,  this->className, ms)
#define logD(ms) GV_LOGGER->log(GLogLevel::DEBUG, this->className, ms)
#define logF(ms) GV_LOGGER->log(GLogLevel::FINE,  this->className, ms)
#define logFF(ms) GV_LOGGER->log(GLogLevel::FFINE,this->className, ms)
#define logA(ms) GV_LOGGER->log(GLogLevel::ALL,   this->className, ms)


#define varG(cl, s) reinterpret_cast<cl>(GV_VARS->get(s))
#define varS(cl, s) GV_VARS->set(cl, s)

#include "einterfaces.h"

#endif //GLOBALQT_GDEFINES_H
