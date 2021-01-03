//
//  CXString.c
//  CExt
//
//  Created by Tim K on 01.01.2021.
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

cx_size_t CXStringGetIndexOf(const CXStringRef string, const CXStringRef substring) {
    // well, this is just going to be using W string backend basically
    
    if (!string || !substring)
        return 0;
    
    return CXStringGetIndexOfW(string, substring->wstring);
}

cx_size_t CXStringGetIndexOfC(const CXStringRef string, const char* substring) {
    // TODO: implement the C version
    
    (void)(string);
    (void)(substring);
    
    return 0;
}

cx_size_t CXStringGetIndexOfW(const CXStringRef string, const cx_wchar_t* substring) {
    if (!string || !substring)
        return 0;
    
    cx_wchar_t* wstring = string->wstring;
    
    cx_size_t offset = 0;
    
    while (wstring[0] != L'\0') {
        if (wcsncmp(wstring, substring, wcslen(substring)) == 0)
            return offset;
        
        offset += 1;
        wstring += 1;
    }
    
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
    (void)(string);
    (void)(substring);
    (void)(substitute);
    
    return;
}

void CXStringReplaceAllC(CXStringRef string, const char* substring, const char* substitute) {
    (void)(string);
    (void)(substring);
    (void)(substitute);
    
    return;
}

void CXStringReplaceAllW(CXStringRef string, const cx_wchar_t* substring, const cx_wchar_t* substitute) {
    (void)(string);
    (void)(substring);
    (void)(substitute);
    
    return;
}

cx_wchar_t CXStringGetCharacterAt(const CXStringRef string, const cx_size_t index) {
    (void)(string);
    (void)(index);
    
    return L'\0';
}

void CXStringReverse(CXStringRef string) {
    (void)(string);
}

void CXStringAppend(CXStringRef string, const CXStringRef ending) {
    (void)(string);
    (void)(ending);
    
    return;
}

void CXStringAppendC(CXStringRef string, const char* ending) {
    (void)(string);
    (void)(ending);
    
    return;
}

void CXStringAppendW(CXStringRef string, const cx_wchar_t* ending) {
    (void)(string);
    (void)(ending);
    
    return;
}

void CXStringPrepend(CXStringRef string, const CXStringRef ending) {
    (void)(string);
    (void)(ending);
    
    return;
}

void CXStringPrependC(CXStringRef string, const char* ending) {
    (void)(string);
    (void)(ending);
    
    return;
}

void CXStringPrependW(CXStringRef string, const cx_wchar_t* ending) {
    (void)(string);
    (void)(ending);
    
    return;
}

void CXStringTransform(CXStringRef string, const cx_casetransformation_t tcase) {
    (void)(string);
    (void)(tcase);
    
    return;
}


int CXStringGetInteger(const CXStringRef string) {
    (void)(string);
    
    return -1;
}

unsigned CXStringGetUnsigned(const CXStringRef string) {
    (void)(string);
    
    return 0;
}
