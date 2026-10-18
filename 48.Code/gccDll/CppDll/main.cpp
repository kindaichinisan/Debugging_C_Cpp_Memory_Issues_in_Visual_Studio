#include "main.h"
#include <iostream>
#include <new>
// a sample exported function

int ** DLL_EXPORT Create(int row, int column) {
    std::cout << "[Dll] Creating matrix of" << row << "x" << column << std::endl ;

	int **ptr = NULL ;
	int i = 0 ;
	try{
        ptr = new(std::nothrow) int*[row] ;
        if(ptr == NULL)
            return NULL ;
        for( ; i < row ; ++i) {
            ptr[i] = new(std::nothrow) int[column] ;
            if(ptr[i] == NULL){
                return NULL ;
            }
        }
	}catch(std::exception &ex){
	    std::cout << "[Dll] Exception caught at row # " << i << " with reason -> " << ex.what() << std::endl;
       // throw ;
       //return NULL ;
	}
	return ptr ;
}

void DLL_EXPORT Destroy(int **ptr, int row, int column){
    for(int i = 0 ; i < row ; ++i) {
        delete[] ptr[i] ;
	}
	delete [] ptr ;
}
