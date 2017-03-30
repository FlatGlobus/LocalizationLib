// part of MS VC++ sample 
// Copyright (c) Microsoft Corporation.  All rights reserved.

#include "stdafx.h"
#define MAX_LOADSTRING	100	
#define MAX_LANGNAME	255		// Maximum native language name length

// Type definitions
typedef struct LANGINFO_DEF {
	int		Count;
	LANGID	LangID;
} LANGINFO;
typedef LANGINFO *PLANGINFO;

LANGID UILanguage;								// The UI language chosen by the user
// Forward declarations of functions included in this code module:
LRESULT CALLBACK	Language(HWND, UINT, WPARAM, LPARAM);
LANGID				DetectLanguage(void);

// The following functions contain code to
// detect the language in which the initial
// user interface should be displayed

BOOL CALLBACK EnumLangProc(HANDLE, LPCTSTR, LPCTSTR,
						   WORD wIDLanguage, LONG_PTR lParam)
{
    PLANGINFO LangInfo;

    LangInfo = (PLANGINFO) lParam;
    LangInfo->Count++;
    LangInfo->LangID  = wIDLanguage;

    return (TRUE);        // continue enumeration
}

// Detects the language of ntdll.dll with some specific processing for 
// the Hongkong SAR version
LANGID GetNTDLLNativeLangID()
{

    LANGINFO LangInfo;
	LPCTSTR Type = (LPCTSTR) ((LPVOID)((WORD)16));
    LPCTSTR Name = (LPCTSTR) 1;

    ZeroMemory(&LangInfo,sizeof(LangInfo));
    
    // Get the HModule for ntdll.
    HMODULE hMod = GetModuleHandle(_T("ntdll.dll"));
    if (hMod==NULL) {
        return(0);
    }

    BOOL result = EnumResourceLanguages(hMod, Type, Name, (ENUMRESLANGPROC)EnumLangProc, (LONG_PTR) &LangInfo);
    
    if (!result || (LangInfo.Count > 2) || (LangInfo.Count < 1) ) {
        return (0);
    }
    
    return (LangInfo.LangID);
}

// Checks if NT4 system is Hongkong SAR version
BOOL IsHongKongVersion()
{
    HMODULE hMod;
    BOOL bRet=FALSE;
	typedef BOOL (WINAPI *IMMRELEASECONTEXT)(HWND,HIMC);
    IMMRELEASECONTEXT pImmReleaseContext;

    hMod = LoadLibrary(_T("imm32.dll"));
    if (hMod) {
        pImmReleaseContext = (IMMRELEASECONTEXT)GetProcAddress(hMod,"ImmReleaseContext");
        if (pImmReleaseContext) {
            bRet = pImmReleaseContext(NULL,NULL);
        }
        FreeLibrary(hMod);
    }
    return (bRet);
}

// This function detects a correct initial UI language for all
// platforms (Win9x, ME, NT4, Windows 2000, Windows XP)
LANGID DetectLanguage() {

#define MAX_KEY_BUFFER	80

	OSVERSIONINFO		VersionInfo;
	LANGID				uiLangID = 0;
	HKEY				hKey;
	DWORD				Type, BuffLen = MAX_KEY_BUFFER;
	TCHAR				LangKeyValue[MAX_KEY_BUFFER];


	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if( !GetVersionEx(&VersionInfo) )
		return(0);

	switch( VersionInfo.dwPlatformId ) {
		// On Windows NT, Windows 2000 or higher
		case VER_PLATFORM_WIN32_NT:
			if( VersionInfo.dwMajorVersion >= 5)   // Windows 2000 or higher
				uiLangID = GetUserDefaultUILanguage();
			else {   // for NT4 check the language of ntdll.dll
				uiLangID = GetNTDLLNativeLangID();   
				if (uiLangID == 1033) {		// special processing for Honkong SAR version of NT4
					if (IsHongKongVersion()) {
						uiLangID = 3076;
					}
				}
			}
			break;
		// On Windows 98 or Windows ME
		case VER_PLATFORM_WIN32_WINDOWS:
			// Open the registry key for the UI language
			if( RegOpenKeyEx(HKEY_CURRENT_USER,_T("Default\\Control Panel\\Desktop\\ResourceLocale"), 0,
				KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS ) {
				// Get the type of the default key
				if( RegQueryValueEx(hKey, NULL, NULL, &Type, NULL, NULL) == ERROR_SUCCESS 
					&& Type == REG_SZ ) {
					// Read the key value
					if( RegQueryValueEx(hKey, NULL, NULL, &Type, (LPBYTE)LangKeyValue, &BuffLen) 
						== ERROR_SUCCESS ) {
						uiLangID = (LANGID)_ttoi(LangKeyValue);
					}
				}
				RegCloseKey(hKey);
			}				
			break;
	}

    if (uiLangID == 0) {
        uiLangID = GetUserDefaultLangID();
    }
    // Return the found language ID.
    return (uiLangID);
}