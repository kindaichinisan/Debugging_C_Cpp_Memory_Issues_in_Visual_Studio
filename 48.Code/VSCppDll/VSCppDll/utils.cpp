#include "utils.h"

#include <iostream>
// a sample exported function

int **  Create(int row, int column) {
    std::cout << "[Dll] Creating matrix of" << row << "x" << column << std::endl ;

	int **ptr = NULL ;
	int i = 0 ;
	try{
        ptr = new int*[row] ;
        for( ; i < row ; ++i) {
            ptr[i] = new int[column] ;
        }
	}catch(std::exception &ex){
	    std::cout << "[Dll] Exception caught at row # " << i << " with reason -> " << ex.what() << std::endl;
	    throw ;
	}
	return ptr ;
}

void  Destroy(int **ptr, int row, int column){
    for(int i = 0 ; i < row ; ++i) {
        delete[] ptr[i] ;
	}
	delete [] ptr ;
}
