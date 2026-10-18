#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef _USRDLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT int **  Create(int row, int column) ;
DLL_EXPORT void  Destroy(int **ptr) ;
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
