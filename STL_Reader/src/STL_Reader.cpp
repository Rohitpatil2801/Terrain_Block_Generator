// STL_Reader.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "STL_Reader.h"


// This is an example of an exported variable
STLREADER_API int nSTLReader=0;

// This is an example of an exported function.
STLREADER_API int fnSTLReader(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
STLReader::STLReader()
{
    return;
}
