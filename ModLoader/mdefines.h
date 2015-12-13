#ifndef GLOBALQT_MDEFINES_H
#define GLOBALQT_MDEFINES_H
#include <Engine/einterfaces.h>

#define mLogE(ms)  this->loader->log->log(GLogLevel::ERR,   this->className, ms)
#define mLogW(ms)  this->loader->log->log(GLogLevel::WARN,  this->className, ms)
#define mLogI(ms)  this->loader->log->log(GLogLevel::INFO,  this->className, ms)
#define mLogD(ms)  this->loader->log->log(GLogLevel::DEBUG, this->className, ms)
#define mLogF(ms)  this->loader->log->log(GLogLevel::FINE,  this->className, ms)
#define mLogFF(ms) this->loader->log->log(GLogLevel::FFINE, this->className, ms)
#define mLogA(ms)  this->loader->log->log(GLogLevel::ALL,   this->className, ms)


#define mVarG(cl, s) reinterpret_cast<cl>(this->loader->vars->get(s))
#define mVarS(cl, s) this->loader->vars->set(cl, s)

class MMods;
class MCoreMods;

#endif //GLOBALQT_MDEFINES_H
