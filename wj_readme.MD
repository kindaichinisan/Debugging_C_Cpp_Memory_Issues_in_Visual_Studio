# Udemy Course Debugging C/C++ Memory Issues in Visual Studio
- By Umar Lone

# Section 8: Custom Leak Detector
## 75 Leak Detection Internals
- Debug Heap library is only available in C runtime in Visual Studio in Windows. Cannot use that library on any other compiler, or platform (Mac or Linux).
- Create our own library using C\ C++ features.
- How visual Studio implements the features of leak detection and heap corruption.
    - When user requests memory through malloc or new, heap manager will allocate a memory block larger than size of requested memory.
    - Extra portion of memory block is used to store information about the allocation.
    - Block header
        - line #
        - file name
        - type of block (5 types)
        - function name
        - size of requested memory
        - pointer to prev block (2-way linked list)
        - pointer to next block (2-way linked list)
    - guard bytes (for heap corruption detection)
    - actual memory requested by user
    - leaks are detected if there is memory block in the list. Leaks happen when user forget to free pointer created by new.

## 76 Memory Block Header & ptmalloc() Function
- Our custom leak detection library
- Implementation is in C so that it can be used by both C and C++ program.
- pragma once is platform dependent (not so much. Can use). Pragma once is not standard C++ but it is widely supported (by GCC, Clang, MSVC). It is used to prevent same header from being included multiple times within a single translation unit. If cannot work, use traditional include guards (#ifndef, #define, #endif)
- ptHeader.h: holds the structure of the memory block header
- size_t needs to #include <stddef.h>
- C does not allow function overloading. need to create ptmalloc and ptfree in ptld_c.c.
- if malloc did not succeed, it will return NULL.

## 77 Implementation of ptfree() Function
- user_mem = pCurrentBlock + 1 (dont have guard byte). pCurrentBlock is of type ptMemoryBlockHeader*
- ptIsValidBlock checks if the query block is inside the double linked list

## 78 Implementation of PtDumpLeaks() Function
- check the blocks in the linked list and dump their information
- ptDumpBlock()
- ptmain.h is header file of ptld_c.c. Later to be changed.
- ptmain.h #define malloc and free to use ptmalloc() and ptfree()
- test malloc() and free() and ptDumpLeaks() in main.c

## 79 Adding C++ Support - I
- ptld_cpp.cpp
- operation new and new[], delete and delete[]
- function cannot call c function due to C function name mangling.
- c++ compiler encodes name of all symbols when it compiles the code.
- any c function used in c++ files have to be protected from being mangled => use external c preprocessor directive.
- cannot directly use extern c on these functions because extern c is available only to C++ and not to C.
- Extract C code into ptld_c.h
- protect ptmalloc() and ptfree() functions from being name-mangled in C++ files.
- extern c should be applied only for those headers which are included in c++ files
- check __cplusplus macro is defined to check if header file has been included in a .cpp file.
- user only needs to #include "ptmain.h"

## 80 Adding C++ Support - II
- #define new but no need for delete.
- test use new() and malloc()
- 2 main in VS project. To exclude from build in General > Excluded from build.
- what happens if we compile our code in Release? We dont want overhead of leak checking in release build. => #ifdef _DEBUG to define the macros in ptmain.h.
- need to include <malloc.h> so that code can be compiled successfully in release mode.
- ensure delete is not defined in _DEBUG. Use the standard overloaded operator delete functions from C++ library.

## 81 Compiling on Linux
- gcc does not define _DEBUG (specific to Visual Studio) => gcc -D_DEBUG
- __FUNCSIG__ specific to Visual Studio.
    - #ifdef _WIN32
    - #define PT_FUNCTION_NAME __FUNCSIG__
    - #elif define __GNUC__
    - #define PT_FUNCTION_NAME __PRETTY_FUNCTION__
    - #else
    - #define PT_FUNCTION_NAME "Unknown function"
- gcc -D_DEBUG -c ptld_c.c
- g++ -D_DEBUG main.cpp ptld_cpp.cpp ptld_c.o
- use it on c code, dont need cpp file
- use it on c++ code, need both c and cpp file.
- operator new and delete internally invoke the c functions malloc and free.