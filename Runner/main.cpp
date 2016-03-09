#include <cstdlib>

int main(int argc, char *argv[]) {
 system( "copy ..\\GameTmp\\Launcher.exe Launcher.exe /Y");
 system( "copy ..\\GameTmp\\Engine.exe game.exe /Y");
 system( "copy ..\\GameTmp\\libModLoader.dll modLoader.dll /Y");
	system("xcopy ..\\GameTmp\\mods mods\\ /Y /E");

	if(argc == 1) system("Launcher.exe");
	return 0;
}
