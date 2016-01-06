#ifndef GLOBALQT_MDEFINES_H
#define GLOBALQT_MDEFINES_H
#include <Engine/einterfaces.h>

// Render defines
#define MFPS_COUNT 200
// Render defines

#define mLogE(ms)  this->loader->log->log(ILogLevel::ERR,   Q_FUNC_INFO /*this->className*/, ms)
#define mLogW(ms)  this->loader->log->log(ILogLevel::WARN,  Q_FUNC_INFO /*this->className*/, ms)
#define mLogI(ms)  this->loader->log->log(ILogLevel::INFO,  Q_FUNC_INFO /*this->className*/, ms)
#define mLogD(ms)  this->loader->log->log(ILogLevel::DEBUG, Q_FUNC_INFO /*this->className*/, ms)
#define mLogF(ms)  this->loader->log->log(ILogLevel::FINE,  Q_FUNC_INFO /*this->className*/, ms)
#define mLogFF(ms) this->loader->log->log(ILogLevel::FFINE, Q_FUNC_INFO /*this->className*/, ms)
#define mLogA(ms)  this->loader->log->log(ILogLevel::ALL,   Q_FUNC_INFO /*this->className*/, ms)


#define mVarG(cl, s) reinterpret_cast<cl>(this->loader->vars->get(s))
#define mVarS(cl, s) this->loader->vars->set(cl, s)

class MMods;
class MCoreMods;

#endif //GLOBALQT_MDEFINES_H
