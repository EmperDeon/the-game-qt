#ifndef G_MODINTERFACES
#define G_MODINTERFACES
#include <QString>

class CoreModInterface
{
public:
	virtual ~CoreModInterface() {}
	// Launcher
	virtual void parseZips() = 0;

	// Engine
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;

};

QT_BEGIN_NAMESPACE

#define EchoInterface_iid "org.ilzcorp.CoreModInterface"

Q_DECLARE_INTERFACE(CoreModInterface, EchoInterface_iid)
QT_END_NAMESPACE

#endif

