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

typedef enum {
    CX_COLOR_DEFAULT,
    CX_COLOR_RED,
    CX_COLOR_GREEN,
    CX_COLOR_YELLOW,
    CX_COLOR_ORANGE,
    CX_COLOR_BLUE,
    CX_COLOR_MAGENTA,
    CX_COLOR_CYAN,
    CX_COLOR_LGRAY,
    CX_COLOR_DGRAY,
    CX_COLOR_WHITE,
    CX_COLOR_BLACK,
    CX_COLOR_AUXC
} cx_builtincolor_t;

#endif
