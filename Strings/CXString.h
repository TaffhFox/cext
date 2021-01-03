//
//  CXString.h
//  CExt
//
//  Copyright (c) TaffhFox (https://github.com/taffhfox) 2021
//

#ifndef CExt_Header_CXString
#define CExt_Header_CXString

//
// Unicode string type implementation
//

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "CXTypes.h"

#define CX_STRING_ALLOCSTEP 64

typedef struct CXString* CXStringRef;
typedef wchar_t cx_wchar_t;

typedef enum { CX_STRING_DEFAULT = 0, CX_STRING_UPPERCASE = 1, CX_STRING_LOWERCASE = 2 } cx_casetransformation_t;

/// Creates an empty Unicode string
CXStringRef CXStringCreateEmpty(void);

/// Creates a Unicode string with contents borrowed from the specified
/// C string
CXStringRef CXStringCreateFromCString(const char* cstring);

/// Creates a Unicode string with contents borrowed from the specified
/// W string
CXStringRef CXStringCreateFromWString(const cx_wchar_t* wstring);

/// Returns the Unicode string length
cx_size_t CXStringGetLength(const CXStringRef string);

/// Returns the C string representation
const char* CXStringGetCString(const CXStringRef string);

/// Returns the W string representation
const cx_wchar_t* CXStringGetWString(const CXStringRef string);

/// Finds the first occurence of the specified substring and returns
/// its index
cx_size_t CXStringGetIndexOf(const CXStringRef string, const CXStringRef substring);
cx_size_t CXStringGetIndexOfC(const CXStringRef string, const char* substring);
cx_size_t CXStringGetIndexOfW(const CXStringRef string, const cx_wchar_t* substring);

/// Replaces all of the occurences of the specified substring
void CXStringReplaceAll(CXStringRef string, const CXStringRef substring, const CXStringRef substitute);
void CXStringReplaceAllC(CXStringRef string, const char* substring, const char* substitute);
void CXStringReplaceAllW(CXStringRef string, const cx_wchar_t* substring, const cx_wchar_t* substitute);

/// Gets the W character located at the specified position in the Unicode
/// string
cx_wchar_t CXStringGetCharacterAt(const CXStringRef string, const cx_size_t index);

/// Reverses the Unicode string
void CXStringReverse(CXStringRef string);

/// Appends the specified string
void CXStringAppend(CXStringRef string, const CXStringRef ending);
void CXStringAppendC(CXStringRef string, const char* ending);
void CXStringAppendW(CXStringRef string, const cx_wchar_t* ending);

/// Prepends the specified string
void CXStringPrepend(CXStringRef string, const CXStringRef ending);
void CXStringPrependC(CXStringRef string, const char* ending);
void CXStringPrependW(CXStringRef string, const cx_wchar_t* ending);

/// Transforms the Unicode string using the specified format
void CXStringTransform(CXStringRef string, const cx_casetransformation_t tcase);

/// Returns the numeric value encoded in the string
int CXStringGetInteger(const CXStringRef string);
unsigned CXStringGetUnsigned(const CXStringRef string);

/// Releases the Unicode string
void CXStringRelease(CXStringRef string);

#endif
