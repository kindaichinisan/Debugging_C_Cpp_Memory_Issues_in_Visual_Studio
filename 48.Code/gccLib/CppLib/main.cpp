#include "utils.h"


int * ProcessData(int data) {
	int *ptr = new int[data] ;
	for(int i = 0 ; i < data ; ++i) {
		ptr[i] = i ;//Fill with dummy data ;
	}
	return ptr ;
}

