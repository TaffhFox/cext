//
//  CXTypes.h
//  CExt
//
//  Copyright (c) TaffhFox (https://github.com/taffhfox) 2021
//

#ifndef CExt_Header_CXTypes
#define CExt_Header_CXTypes

#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

typedef size_t cx_size_t;

#define CX_UNSIGNED(integer) ((integer >= 0) ? (integer) : 0)

typedef enum {
    CX_STRING_DEFAULT = 0,
    CX_STRING_UPPERCASE = 1,
    CX_STRING_LOWERCASE = 2,
    CX_STRING_REVERSE = 3
} cx_casetransformation_t;

typedef wchar_t cx_wchar_t;

// Unix ANSI color codes

typedef enum {
    CX_COLOR_DEFAULT = 0,
    CX_COLOR_RED = 91,
    CX_COLOR_GREEN = 92,
    CX_COLOR_YELLOW = 93,
    CX_COLOR_BLUE = 94,
    CX_COLOR_MAGENTA = 95,
    CX_COLOR_CYAN = 96,
    CX_COLOR_LGRAY = 37,
    CX_COLOR_DGRAY = 90,
    CX_COLOR_WHITE = 97,
    CX_COLOR_BLACK = 30,
    CX_COLOR_AUXC = 8
} cx_builtincolor_t;

#endif
