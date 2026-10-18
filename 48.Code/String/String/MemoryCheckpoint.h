#pragma once
#include <any>
#include <iostream>

class MemoryCheckpoint {
	_CrtMemState m_Begin ;
	const char *m_pFile ;
	const char *m_pFunction ;
public:
	MemoryCheckpoint(const char  *pFile, const char *pFunction):
		m_pFile{pFile},
		m_pFunction{pFunction} {
		_CrtMemCheckpoint(&m_Begin) ;
	}
	~MemoryCheckpoint()
	{
		_CrtMemState end, diff ;
		_CrtMemCheckpoint(&end) ;
		if(_CrtMemDifference(&diff, &m_Begin, &end)==1) {
			std::cout << "LEAKS DETECTED" << std::endl
				<< "\nIn function ->" << m_pFunction
				<< "\n In file ->" << m_pFile
				<< std::endl; 
			_CrtMemDumpAllObjectsSince(&m_Begin) ;
			_CrtMemDumpStatistics(&diff) ;
		}
	}
};

#ifdef _DEBUG
#define MEMCHECKPOINT MemoryCheckpoint cp{__FILE__, __FUNCSIG__} ;
#else
#define MEMCHECKPOINT 
#endif
