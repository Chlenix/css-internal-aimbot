// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "main.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&main, nullptr, 0, 0))
		{
			return TRUE;
		}
		break;

	case DLL_PROCESS_DETACH:
		return TRUE;
    }
    return FALSE;
}

