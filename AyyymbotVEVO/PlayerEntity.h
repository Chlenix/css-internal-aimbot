#pragma once

#include "VevoSDK.h"

class cPlayerEntity;
class cBotEntity;

class cPlayerEntity
{
public:
	virtual DWORD Function0(); //
	virtual void Function1(); //
	virtual void Function2(); // 
	virtual float* UpdatePlayerDisplayPosition(DWORD dwEntityID, float fpPosition[3], float fpViewAngles[3]);
	//virtual void Function4(); //
	//virtual void Function5(); //
	//virtual void Function6(); //
	//virtual void Function7(); //
	//virtual void Function8(); //
	//virtual void Function9(); //
	//virtual void Function10(); //
	//virtual void Function11(); //
	//virtual void Function12(); //
	//virtual void Function13(); //

	//char pad_0x0000[0x4];
	DWORD dwID; //0x0004 
	DWORD dwState; //0x0008 
	char pad_0x000C[0x20]; //0x000C
	DWORD na_Always2; //0x002C 
	char pad_0x0030[0x8]; //0x0030
	char szName[32]; //0x1026888 
	DWORD dwTeamID; //0x0058 
	DWORD dwHealth; //0x005C 
	Vector3 vfOrigin; //0x0060 
	Vector2 vfEuler; //0x006C 
	char pad_0x0074[0x44C]; //0x0074
}; //Size=0x04C0

class cBotEntity
{
public:
	DWORD dwID; //0x0000 
	DWORD dwJoinedID; //0x0004 
	DWORD na_Num1; //0x008 
	char pad_0x000C[0x4]; //0x00C
	char szName[32]; //0x010 
	DWORD dwTeamID; //0x0030 
	DWORD dwHealth; //0x0034 
	Vector3 vfOrigin; //0x0038 
	Vector2 vfEuler; //0x0050 
	char pad_0x0074[0x44C]; //0x0058
}; //Size=0x04C0

void PrintLocalPlayer(cPlayerEntity *player);

