#include "HeapChecker.h"
#include <crtdbg.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fstream>
std::ofstream HeapChecker::m_OutStream ;
HeapChecker::HeapChecker(const char* pFun, const char* pFile):
m_pFunction{pFun}, m_pFile{pFile} {
	if(!m_Initialized) {
		throw std::runtime_error{"HeapChecker needs to be initialized first"} ;
	}
}

HeapChecker::~HeapChecker()
{
	if(_CrtCheckMemory() == 0) {
		std::ostringstream output ;
		output << "### HEAP CORRUPTION DETECTED ###" << std::endl;
		output << "\tFunction->" << m_pFunction << std::endl ;
		output << "\tFile->" << m_pFile << std::endl;
		switch (m_Output) {
		case OutputType::CONSOLE:
			std::cout << output.str() ;
			break ;
		case OutputType::VSWINDOW:
			OutputDebugStringA(output.str().c_str()) ;
			break ;
		case OutputType::TXTFILE:
			m_OutStream << output.str() ;
			break ;
		}
	}
}
