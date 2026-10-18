#pragma once
#include <stdexcept>

class String
{
	char *m_pBuffer ;
	size_t m_Length ;
	void Allocate(const char * pstr);
public:
	String();
	~String();
	String(const char *pstr) ;
	String(const String &other) ;
	String & operator = (const String &other) ;
	size_t GetLength()const {
		return m_Length ;
	}
	const char *GetString()const {
		return m_pBuffer ;
	}
	String operator+(const String &other)const ;
	String & operator +=(const String &other) ;
	char operator [](int index)const {
		if(index > m_Length)
			throw std::runtime_error{"Invalid index"} ;
		return m_pBuffer[index] ;
	}
	char & operator [](int index) {
		if(index > m_Length)
			throw std::runtime_error{"Invalid index"} ;
		return m_pBuffer[index] ;
	}
	void Insert(const char *pStr, size_t position) ;
	void Append(const char *pStr) ;
	void Assign(const char *pStr) ;
};

