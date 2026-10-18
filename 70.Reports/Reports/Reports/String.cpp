#include "String.h"


#ifdef _DEBUG
#define DEBUG_NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif
String::String()
{
	
	m_Length = 0 ;
	m_pBuffer = DEBUG_NEW char[1]{'\0'} ;
}



String::String(const char* pstr) {
	Allocate(pstr);
}

void String::Allocate(const char * pstr)
{
		

	m_Length = strlen(pstr);
	m_pBuffer = DEBUG_NEW char[m_Length + 1];
	strcpy(m_pBuffer, pstr);
}

String::String(const String& other) {
	Allocate(other.GetString()) ;
}

String& String::operator=(const String& other) {
	if(this != &other) {
		Allocate(other.GetString()) ;
	}
	return *this ;
}

String String::operator+(const String& other) const {
	String temp{*this} ;
	temp += other ;
	return temp ;
}

String::~String(){
	//delete []m_pBuffer ;
}
String& String::operator+=(const String& other) {
	Append(other.GetString()) ;
	return *this; 
}

void String::Insert(const char* pStr, size_t position) {
		

	if(position > m_Length) {
		throw std::runtime_error{"Index out of bounds"} ;
	}
	size_t totalLength = strlen(pStr) + m_Length ;
	char *pTemp = DEBUG_NEW char[totalLength]{} ;
	if(position == 0) {
		strcpy(pTemp, pStr) ;
		strcat(pTemp, m_pBuffer) ;
	}else if(position < m_Length) {
		strncpy(pTemp, m_pBuffer, position) ;
		strcat(pTemp, pStr) ;
		strcat(pTemp, &m_pBuffer[position]) ;
	}else if(position == m_Length) {
		strcpy(pTemp, m_pBuffer) ;
		strcat(pTemp, pStr) ;
	}
	m_pBuffer = pTemp ;
	m_Length = totalLength ;
}
/*
 * String ->Hello
 * Raw Str->Bye
 */

void String::Append(const char* pStr) {
	Insert(pStr, m_Length) ;
}

void String::Assign(const char* pStr) {
	Allocate(pStr) ;
}
