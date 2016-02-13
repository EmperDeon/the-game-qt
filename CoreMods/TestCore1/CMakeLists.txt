set(TESTCORE1_S main.cpp)
set(TESTCORE1_H main.h)


add_library(TESTCORE1 SHARED ${TESTCORE1_S} ${TESTCORE1_H})

qt5_use_modules(TESTCORE1 Core Widgets OpenGL)

target_compile_features(TESTCORE1 PRIVATE cxx_range_for)

target_link_libraries(TESTCORE1 ${OPENGL_LIBRARY} ${Qt5Core_QTMAIN_LIBRARIES})
