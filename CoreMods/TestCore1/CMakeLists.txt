# You need to set <ModName> + _S(.cpp) and <ModName> + _H(.h), and then use M_BUILD_MOD(ModName)

set(TESTCORE1_S main.cpp)
set(TESTCORE1_H main.h)


M_BUILD_MOD(TESTCORE1)
