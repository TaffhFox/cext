//
//  Strings.c
//  CExt
//
//  Copyright (c) TaffhFox (https://github.com/taffhfox) 2021
//

#include "CXString.h"

struct CXString {
    // backend buffers
    char* cstring;
    cx_wchar_t* wstring;
    
    // allocated bytes
    cx_size_t csalloc;
    cx_size_t wsalloc;
};

// private

void CXWStringTransformationWrapper(cx_wchar_t* text, cx_wchar_t (*tfunc)(cx_wchar_t param)) {
    if (!tfunc || !text)
        return;
    
    for (cx_size_t index = 0; index < wcslen(text); index++)
        text[index] = tfunc(text[index]);
}

cx_wchar_t* CXCStringConvertToWString(const char* text, cx_size_t* allocSizePtr) {
    // your typical mbstowcs wrapper
    
    if (!text)
        return NULL;
    
    cx_size_t finalSize = strlen(text) + 2;
    
    cx_wchar_t* result = calloc(finalSize, sizeof(cx_wchar_t));
    
    if (mbstowcs(result, text, finalSize) < 1) {
        free(result);
        return NULL;
    }
    
    if (allocSizePtr)
        (*allocSizePtr) = finalSize;
    
    return result;
}

char* CXWStringConvertToCString(const cx_wchar_t* text, cx_size_t* allocSizePtr) {
    if (!text)
        return NULL;
    
    cx_size_t finalSize = wcslen(text) * 2 + 4;
    
    char* result = calloc(finalSize, sizeof(char));
    
    if (wcstombs(result, text, finalSize) < 1) {
        free(result);
        return NULL;
    }
    
    if (allocSizePtr)
        (*allocSizePtr) = finalSize;
    
    return result;
}

void CXStringAdaptByReallocation(CXStringRef string, const cx_size_t increment) {
    if (!string || increment < 1)
        return;
    
    cx_size_t length = string->wsalloc;
    
    while (length > (length + increment))
        length += CX_STRING_ALLOCSTEP;
    
    string->wstring = realloc(string->wstring, sizeof(cx_wchar_t) * length);
    string->wsalloc = length;
    
    string->csalloc = length;
    string->cstring = realloc(string->cstring, sizeof(char) * string->csalloc);
}

bool CXStringReplaceFirstW(CXStringRef string, const cx_wchar_t* occurence, const cx_wchar_t* replacement) {
    if (!string || !occurence || !replacement)
        return false;
    
    bool found = false;
    
    cx_size_t index = CXStringGetIndexOfW(string, occurence, &found);
    
    if (!found)
        return false;
    
    CXStringRef firstHalf = CXStringCreateSubstring(string, index, wcslen(occurence));
    
    CXStringRef secondHalf = CXStringCreateSubstring(string, index + wcslen(occurence), CXStringGetLength(string));
    
    free(string->cstring);
    free(string->wstring);
    
    string->wstring = firstHalf->wstring;
    string->cstring = firstHalf->cstring;
    
    string->wsalloc = firstHalf->wsalloc;
    string->csalloc = firstHalf->csalloc;
    
    free(firstHalf);
    
    CXStringAppendW(string, replacement);
    CXStringAppend(string, secondHalf);
    
    return true;
}

void CXWStringReverse(cx_wchar_t* original) {
    // TODO: performance efficiency
    
    cx_wchar_t* clone = wcsdup(original);
    
    for (cx_size_t index = 0; index < wcslen(clone); index++)
        original[index] = clone[wcslen(clone) - 1 - index];
    
    free(clone);
}

// from CXString.h

CXStringRef CXStringCreateEmpty() {
    // standard allocation stuff
    
    CXStringRef string = malloc(sizeof(struct CXString));
    
    string->cstring = calloc(CX_STRING_ALLOCSTEP, sizeof(char));
    string->csalloc = CX_STRING_ALLOCSTEP;
    
    string->wstring = calloc(CX_STRING_ALLOCSTEP, sizeof(cx_wchar_t));
    string->wsalloc = CX_STRING_ALLOCSTEP;
    
    return string;
}

CXStringRef CXStringCreateFromInteger(const int inv) {
    // conversion wrapper with temporary arrays and stuff
    
    char* tmp = calloc(CX_STRING_ALLOCSTEP, sizeof(char));
    sprintf(tmp, "%d", inv);
    
    CXStringRef result = CXStringCreateFromCString(tmp);
    
    free(tmp);
    
    return result;
}

CXStringRef CXStringCreateFromUnsigned(const unsigned inv) {
    char* tmp = calloc(CX_STRING_ALLOCSTEP, sizeof(char));
    sprintf(tmp, "%u", inv);
    
    CXStringRef result = CXStringCreateFromCString(tmp);
    
    free(tmp);
    
    return result;
}

CXStringRef CXStringCreateFromFloat(const float inv) {
    char* tmp = calloc(CX_STRING_ALLOCSTEP, sizeof(char));
    sprintf(tmp, "%f", inv);
    
    CXStringRef result = CXStringCreateFromCString(tmp);
    
    free(tmp);
    
    return result;
}

CXStringRef CXStringCreateFromCString(const char* cstring) {
    if (!cstring) {
        // No string - no result
        
        return NULL;
    }
    
    CXStringRef string = malloc(sizeof(struct CXString));
    
    string->cstring = strdup(cstring);
    string->csalloc = strlen(cstring);
    
    string->wstring = CXCStringConvertToWString(cstring, &string->wsalloc);
    
    return string;
}

CXStringRef CXStringCreateFromWString(const cx_wchar_t* wstring) {
    if (!wstring)
        return NULL;
    
    CXStringRef string = malloc(sizeof(struct CXString));
    
    string->wstring = wcsdup(wstring);
    string->wsalloc = wcslen(wstring);
    
    string->cstring = CXWStringConvertToCString(wstring, &string->csalloc);
    
    return string;
}
    
CXStringRef CXStringCreateSubstring(const CXStringRef string, const cx_size_t startIndex, const cx_size_t endIndex) {
    if (!string)
        return NULL;
    
    if (startIndex > endIndex)
        return CXStringCreateSubstring(string, endIndex, startIndex); // govnocode™️
    
    CXStringRef result = malloc(sizeof(struct CXString));
    
    result->wsalloc = endIndex - startIndex;
    result->wstring = calloc(result->wsalloc, sizeof(cx_wchar_t));
    
    wcsncpy(result->wstring, string->wstring + startIndex, endIndex);
    
    result->cstring = CXWStringConvertToCString(result->wstring, &result->wsalloc);
    
    return result;
}

cx_size_t CXStringGetLength(const CXStringRef string) {
    // W string length is more high priority than the C string
    // one
    
    if (!string)
        return 0;
    
    return wcslen(string->wstring);
}

const char* CXStringGetCString(const CXStringRef string) {
    if (!string)
        return NULL;
    
    return string->cstring;
}

const cx_wchar_t* CXStringGetWString(const CXStringRef string) {
    if (!string)
        return NULL;
    
    return string->wstring;
}

cx_size_t CXStringGetIndexOf(const CXStringRef string, const CXStringRef substring, bool* actuallyFoundPtr) {
    // well, this is just going to be using W string backend basically
    
    if (!string || !substring)
        return 0;
    
    return CXStringGetIndexOfW(string, substring->wstring, actuallyFoundPtr);
}

cx_size_t CXStringGetIndexOfC(const CXStringRef string, const char* substring, bool* actuallyFoundPtr) {
    // TODO: implement the C version
    
    (void)(string);
    (void)(substring);
    
    return 0;
}

#define __setIf(ptr, vl) if (ptr) \
                            (*ptr) = vl;

cx_size_t CXStringGetIndexOfW(const CXStringRef string, const cx_wchar_t* substring, bool* actuallyFoundPtr) {
    if (!string || !substring)
        return 0;
    
    cx_wchar_t* wstring = string->wstring;
    
    cx_size_t offset = 0;
    
    while (wstring[0] != L'\0') {
        if (wcsncmp(wstring, substring, wcslen(substring)) == 0) {
            __setIf(actuallyFoundPtr, true);
            
            return offset;
        }
        
        offset += 1;
        wstring += 1;
    }
    
    __setIf(actuallyFoundPtr, false);
    return 0;
}

void CXStringRelease(CXStringRef string) {
    if (!string)
        return;
    
    free(string->wstring);
    free(string->cstring);
    
    free(string);
}

// TODO: implement these

void CXStringReplaceAll(CXStringRef string, const CXStringRef substring, const CXStringRef substitute) {
    if (!string || !substring || !substitute)
        return;
    
    CXStringReplaceAllW(string, substring->wstring, substitute->wstring);
}

#define looped(args) while (true) { \
                          if (! args) \
                            break; \
                     }

void CXStringReplaceAllC(CXStringRef string, const char* substring, const char* substitute) {
    if (!string || !substring || !substitute)
        return;
    
    CXStringRef substringS = CXStringCreateFromCString(substring);
    CXStringRef substituteS = CXStringCreateFromCString(substitute);
    
    CXStringReplaceAll(string, substringS, substituteS);
    
    CXStringRelease(substringS);
    CXStringRelease(substituteS);
}

void CXStringReplaceAllW(CXStringRef string, const cx_wchar_t* substring, const cx_wchar_t* substitute) {
    if (!string || !substring || !substitute)
        return;
    
    looped(CXStringReplaceFirstW(string, substring, substitute));
}

cx_wchar_t CXStringGetCharacterAt(const CXStringRef string, const cx_size_t index) {
    if (!string || index >= wcslen(string->wstring)) {
        // NULL W character in case of invalid data
        
        return L'\0';
    }
    
    return string->wstring[index];
}

void CXStringAppend(CXStringRef string, const CXStringRef ending) {
    if (!ending)
        return;
    
    CXStringAppendW(string, string->wstring);
}

void CXStringAppendC(CXStringRef string, const char* ending) {
    if (!string)
        return;
    
    CXStringAdaptByReallocation(string, strlen(ending));
    
    cx_wchar_t* endingW = CXCStringConvertToWString(ending, NULL);
    
    strcat(string->cstring, ending);
    wcscat(string->wstring, endingW);
    
    free(endingW);
}

void CXStringAppendW(CXStringRef string, const cx_wchar_t* ending) {
    if (!string || !ending)
        return;
    
    CXStringAdaptByReallocation(string, wcslen(ending));
    
    char* endingC = CXWStringConvertToCString(ending, NULL);
    
    wcscat(string->wstring, ending);
    strcat(string->cstring, endingC);
    
    free(endingC);
}

void CXStringTransform(CXStringRef string, const cx_casetransformation_t tcase) {
    if (!string || tcase == CX_STRING_DEFAULT)
        return;
    
    switch (tcase) {
        case CX_STRING_REVERSE: {
            CXWStringReverse(string->wstring);
            break;
        }
        case CX_STRING_LOWERCASE: {
            CXWStringTransformationWrapper(string->wstring, towlower);
            break;
        }
        case CX_STRING_UPPERCASE: {
            CXWStringTransformationWrapper(string->wstring, towupper);
            break;
        }
        default:
            break;
    }
    
    free(string->cstring);
    string->cstring = CXWStringConvertToCString(string->wstring, &string->csalloc);
}


int CXStringGetInteger(const CXStringRef string) {
    if (!string)
        return -1;
    
    return ((int)(wcstod(string->wstring, NULL)));
}

unsigned CXStringGetUnsigned(const CXStringRef string) {
    return CX_UNSIGNED(CXStringGetInteger(string));
}

float CXStringGetFloat(const CXStringRef string) {
    if (!string)
        return 0.0;
    
    return wcstof(string->wstring, NULL);
}
