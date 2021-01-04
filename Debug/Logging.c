//
//  Colors.c
//  CExt
//
//  Copyright (c) TaffhFox (https://github.com/taffhfox) 2021
//

#include <stdio.h>
#include <stdlib.h>
#include "CXDebug.h"

// private

void CXLogM(FILE* place, const char* trigger, const char* label, const cx_builtincolor_t color, const char* format, va_list vl) {
    // logging facilities
    
    if (!place)
        place = stderr; // by default it's stderr
    
    if (trigger) {
        // trigger variables
        
        if (getenv(trigger))
            return;
    }
    
    // whenever when need to enable coloring or not
    
    bool colorFriendly = true;
    
    if (place != stderr && place != stdout)
        colorFriendly = false;
    
    if (colorFriendly)
        CXConsoleSetColor(color);
    
    fprintf(place, "[%s] ", label);
    vfprintf(place, format, vl);
    
    fprintf(place, "%c", '\n');
    
    if (colorFriendly)
        CXConsoleSetColor(CX_COLOR_DEFAULT);
}

// from CXDebug.h

#define CXLogN(trigger, label, color)   { \
                                            va_list vl; \
                                            va_start(vl, format); \
                                            \
                                            CXLogM(stderr, trigger, label, color, format, vl); \
                                            \
                                            va_end(vl); \
                                        }

void CXLog(const char* format, ...) {
    // TODO: add support for other types of logs
    
    CXLogN("CX_ALLOW_LOGGING", "Information", CX_COLOR_CYAN);
}

void CXDebug(const char* format, ...) {
    CXLogN("CX_ALLOW_DEBUGGING", "Debug", CX_COLOR_GREEN);
}

void CXWarning(const char* format, ...) {
    CXLogN("CX_ALLOW_WARNINGS", "Warning", CX_COLOR_ORANGE);
}
