#ifndef GLOBALQT_MDEFINES_H
#define GLOBALQT_MDEFINES_H
#include <Engine/einterfaces.h>

// Render defines
#define MFPS_COUNT 200
// Render defines

#define mLogE(ms)  this->loader->log->log(GLogLevel::ERR,   Q_FUNC_INFO /*this->className*/, ms)
#define mLogW(ms)  this->loader->log->log(GLogLevel::WARN,  Q_FUNC_INFO /*this->className*/, ms)
#define mLogI(ms)  this->loader->log->log(GLogLevel::INFO,  Q_FUNC_INFO /*this->className*/, ms)
#define mLogD(ms)  this->loader->log->log(GLogLevel::DEBUG, Q_FUNC_INFO /*this->className*/, ms)
#define mLogF(ms)  this->loader->log->log(GLogLevel::FINE,  Q_FUNC_INFO /*this->className*/, ms)
#define mLogFF(ms) this->loader->log->log(GLogLevel::FFINE, Q_FUNC_INFO /*this->className*/, ms)
#define mLogA(ms)  this->loader->log->log(GLogLevel::ALL,   Q_FUNC_INFO /*this->className*/, ms)


#define mVarG(cl, s) reinterpret_cast<cl>(this->loader->vars->get(s))
#define mVarS(cl, s) this->loader->vars->set(cl, s)

class MMods;
class MCoreMods;

#endif //GLOBALQT_MDEFINES_H
