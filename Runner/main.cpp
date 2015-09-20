#include <cstdlib>

int main() {
	system("copy ..\\GameTmp\\Launcher.exe Launcher.exe /Y");
	system("copy ..\\GameTmp\\Global.exe game.exe /Y");
	system("copy ..\\GameTmp\\libzlib.dll zlib.dll /Y");
	system("copy ..\\GameTmp\\libModLoader.dll modloaders\\base.dll /Y");
	system("Launcher.exe");
	return 0;
}