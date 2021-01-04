//
//  CXDebug.h
//  CExt
//
//  Copyright (c) TaffhFox (https://github.com/taffhfox) 2021
//

#ifndef CExt_Header_CXDebug
#define CExt_Header_CXDebug

#include <stdarg.h>
#include "CXTypes.h"

void CXConsoleSetColor(const cx_builtincolor_t clr);
void CXConsoleClear(void);

void CXLog(const char* format, ...);
void CXDebug(const char* format, ...);
void CXWarning(const char* format, ...);

#endif
