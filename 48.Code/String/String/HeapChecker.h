#pragma once
#include <fstream>
#include <windows.h>

class HeapChecker
{
public:
	enum class OutputType{CONSOLE, VSWINDOW, TXTFILE};
private:
	const char *m_pFunction ;
	const char *m_pFile ;
	inline static OutputType m_Output ;
	static std::ofstream m_OutStream ;
	inline static bool m_Initialized{false} ;
public:
	HeapChecker(const char *pFun, const char *pFile);
	~HeapChecker();
	static void Init(OutputType type) {
		m_Output = type ;
		if(m_Output == OutputType::TXTFILE) {
			char fileName[512]{} ;
			GetModuleFileNameA(GetModuleHandleA(nullptr), fileName, 512) ;
			strcat(fileName, ".log") ;
			m_OutStream.open(fileName) ;
		}
		m_Initialized = true ;
	}
};
#ifdef _DEBUG 
#define HEAPCHECK HeapChecker instance{__FUNCSIG__, __FILE__} ;
#else
#define HEAPCHECK
#endif