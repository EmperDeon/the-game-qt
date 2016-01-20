#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
 system("copy ..\\GameTmp\\Launcher.exe Launcher.exe /Y");
 system("copy ..\\GameTmp\\Engine.exe game.exe /Y");
 system("copy ..\\GameTmp\\libModLoader.dll modLoader.dll /Y");

	if(argc == 1) system("Launcher.exe");
	return 0;
}

//#include <time.h>
//#include <stdio.h>
//int main(){
//	long i;
//	struct tm *time_s;
//
//	time(&i);
//	time_s = localtime(&i);
//	time_s->tm_year += 1900;
//	time_s->tm_mon += 1;
//
//	printf("date:  %02d.%02d.%02d \n time:  %02d:%02d:%02d \n",
//
//	       time_s->tm_year,
//	       time_s->tm_mon,
//	       time_s->tm_mday,
//
//	       time_s->tm_hour,
//	       time_s->tm_min,
//	       time_s->tm_sec
//	);
// return 0;
//}