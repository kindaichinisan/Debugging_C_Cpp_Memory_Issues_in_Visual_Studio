#define _CRTDBG_MAP_ALLOC
#include "String.h"
#include <iostream>
#include <cassert>
#include "HeapChecker.h"
#include "MemoryCheckpoint.h"
#ifdef _DEBUG
#define DEBUG_NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

void Print(const String &txt) {
	std::cout << txt.GetLength() << ":" << txt.GetString() << std::endl; 
}
std::string Create(const char *p) {
	//MEMCHECKPOINT
	std::string s{p} ;
	s.append("New string") ;
	return s ;
}
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ;
	HeapChecker::Init(HeapChecker::OutputType::VSWINDOW) ;
	String text{"Hello"} ;
	Print(text) ;
	text.Insert("Bye", 1) ;
	Print(text) ;
	text.Append("Object Oriented Language") ;
	Print(text) ; 
	text.Assign("Goodbye") ;
	Print(text) ;
	std::string str = Create("Hello world") ;

}


/*
 * Creating checkpoints
 * 
 * 
 */

/*
 	_CrtMemState beg, end, diff ;
	_CrtMemCheckpoint(&beg) ;
	std::string str{"Hello"} ;

	void *p = malloc(100) ;
	char *p2 = DEBUG_NEW char[512]{} ;
	free(p) ;
	delete []p2 ;
	_CrtMemCheckpoint(&end) ;
	if(_CrtMemDifference(&diff, &beg, &end) == 1) {
		std::cout << "Memory leaks detected" << std::endl;
		_CrtMemDumpStatistics(&diff) ;
		_CrtMemDumpAllObjectsSince(&beg) ;
	}
 */