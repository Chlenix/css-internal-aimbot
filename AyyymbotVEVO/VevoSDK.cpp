#include "stdafx.h"
#include "VevoSDK.h"

VevoSDK::VevoSDK()
{
}

BOOL VevoSDK::IsGameRunning(LPCSTR szModuleName)
{
	return (GetModuleHandle("kernel32.dll") && GetModuleHandle(szModuleName));
}

void VevoSDK::DoThisCall(DWORD _this, DWORD dwFuncAddress)
{
	__asm {
		pushad

		mov ecx, _this
		call dword ptr[dwFuncAddress]

		popad
	}
}

double VevoSDK::VectorLength(DirectX::XMFLOAT3 const& xmfVec)
{
	return sqrt((xmfVec.x * xmfVec.x) + (xmfVec.y * xmfVec.y) + (xmfVec.z * xmfVec.z));
}

VevoSDK::~VevoSDK()
{
}
