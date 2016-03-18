#include <cstdlib>

int main(int argc, char *argv[]) {
 system( "copy ..\\GameTmp\\E_LAUNCHER.exe Launcher.exe /Y");
 system( "copy ..\\GameTmp\\E_ENGINE.exe game.exe /Y");
 system( "copy ..\\GameTmp\\libE_MODLOADER.dll modLoader.dll /Y");
	system("xcopy ..\\GameTmp\\mods mods\\ /Y /E");

	if(argc == 1) system("Launcher.exe");
	return 0;
}
