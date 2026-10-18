#include <crtdbg.h>
#include "String.h"
#include <iostream>
#include <windows.h>

void Print(const String &txt) {
	std::cout << txt.GetLength() << ":" << txt.GetString() << std::endl;
}

int main() {
	//MessageBoxA(nullptr, "Workaround", "", MB_OK) ;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ;
	_CrtSetReportMode(_CRT_WARN,_CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG) ;
	freopen("leaks.log", "w", stderr) ;
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR) ;
	char *p = new char[5] ;

}
