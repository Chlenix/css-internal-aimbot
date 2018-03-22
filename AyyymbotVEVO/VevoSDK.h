#pragma once

#include <TlHelp32.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <DirectXMath.h>

struct Vector2
{
	float Pitch;
	float Yaw;
};

struct Vector3
{
	float X;
	float Y;
	float Z;
};

class VevoSDK
{
private:
public:
	VevoSDK();
	~VevoSDK();

	BOOL IsGameRunning(LPCSTR szModuleName);
	void DoThisCall(DWORD _this, DWORD dwFuncAddress);
	static double VectorLength(DirectX::XMFLOAT3 const& xmfVec);
};

