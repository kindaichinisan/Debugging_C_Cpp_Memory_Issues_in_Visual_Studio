#include <stdio.h>
//#include "..\..\CppLib/CppLib/utils.h"
//#include "e:/Work/Playground/CppDll/main.h"
#include <limits.h>
#include <windows.h>
#include <exception>
#include <iostream>

int main() {
	HINSTANCE hDll = LoadLibraryA("E:\\Work\\Playground\\CppDll\\bin\\Debug\\Cppdll.dll");
	//HINSTANCE hDll = LoadLibraryA(R"(..\..\VSCppDll\Debug\VSCppdll.dll)");
	if (hDll == NULL) {
		puts("Could not load dll");
		return -1;
	}
	int ** (*pfn)(int, int);
	pfn = (int ** (*)(int, int))GetProcAddress(hDll, (LPCSTR)1);
	if (pfn == NULL) {
		puts("Could not locate function");
		goto EXIT;
	}
	try {
		int rows = 1000;
		int columns = 1000000;
		int **pData = pfn(rows, columns);
		if (pData == NULL) {
			printf("Data could not be retrieved\n");
			goto EXIT;
		}
		puts("Processing data") ;
	}
	catch (std::exception &ex) {
		std::cout << "[main] Caught exception:" << ex.what() << std::endl;
	}

EXIT:
	FreeLibrary(hDll);
}
