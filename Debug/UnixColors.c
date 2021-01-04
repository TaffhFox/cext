//
//  UnixColors.c
//  CExt
//
//  Copyright (c) TaffhFox (https://github.com/taffhfox) 2021
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CXDebug.h"

#define CX_COLOR_CLEAN "\033[1;1H\033[2J"

void CXConsoleSetColor(const cx_builtincolor_t clr) {
    if (clr == CX_COLOR_AUXC)
        return; // auxillary color
    
    char* fmtStr = calloc(24, sizeof(char));
    sprintf(fmtStr, "\033[%um", (unsigned)(clr));
    
    fprintf(stderr, "\033[1m%s", fmtStr);
    fprintf(stdout, "\033[1m%s", fmtStr);
}

void CXConsoleClear() {
    fprintf(stdout, "%s", CX_COLOR_CLEAN);
}
