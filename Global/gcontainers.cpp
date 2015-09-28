#include <Global/gcontainers.h>

#undef CLASS_NAME
#define CLASS_NAME "Emiks"
//bytes: mod - 10, item -  10, kind - 8, state - 4

Emiks::Emiks(int m, int i, int k, int s) {
	c = 0;
 if((m < 1024)||(i < 1024)||(k < 256)||(s < 16)){
	 c |= m << 23;
	 c |= i << 13;
	 c |= k << 5;
	 c |= s << 1;
 }else{
	 logE("One of parameters is greater then 1024");
 }
}

quint32 Emiks::m() {	return c >> 22 & 1023;}
quint32 Emiks::i() {	return c >> 13 & 1023;}
quint32 Emiks::k() {	return c >> 5 & 255;  }
quint32 Emiks::s() {	return c >> 1 & 15;   }