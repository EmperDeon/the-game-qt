#include <cstdlib>

int main(int argc, char *argv[]) {
 system("copy ..\\GameTmp\\Launcher.exe Launcher.exe /Y");
 system("copy ..\\GameTmp\\Global.exe game.exe /Y");
 system("copy ..\\GameTmp\\libzlib.dll zlib.dll /Y");
 system("copy ..\\GameTmp\\libModLoader.dll modloaders\\base.dll /Y");
	if(argc == 1) system("Launcher.exe");
	return 0;
}