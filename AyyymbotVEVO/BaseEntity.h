#pragma once
#include "VevoSDK.h"

class cBaseEntity
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //

	char pad_0x0010[0x28]; //0x0010
	float flTimer; //0x002C 
	char pad_0x0030[0x34]; //0x0030
	float flTimer_2; //0x0064 
	float flTimer_3; //0x0068 
	float flTimer_4; //0x006C 
	float flTimer_5; //0x0070 
	char pad_0x0074[0x20]; //0x0074
	DWORD dwHealth; //0x0094 
	char pad_0x0098[0x4]; //0x0098
	DWORD dwTeam; //0x009C 
	char pad_0x00A0[0x54]; //0x00A0
	Vector3 vfVelocity; //0x00F4 
	char pad_0x0100[0x30]; //0x0100
	Vector3 vfVelocity_2; //0x0130 
	char pad_0x013C[0x18]; //0x013C
	float flTimer_6; //0x0154 
	char pad_0x0158[0x108]; //0x0158
	Vector3 vfOrigin; //0x0260 
	Vector3 vfEulerAngles; //0x026C 
	Vector3 vfOrigin_2; //0x0278 
	Vector3 vfEulerAngles_2; //0x0284 
	Vector3 vfOrigin_3; //0x0290 
	char pad_0x029C[0x2DC]; //0x029C
	DWORD dwBoneMatrix; //0x0578 
	char pad_0x057C[0x8BC]; //0x057C
	DWORD dwKeyDown; //0x0E38 
	char pad_0x0E3C[0xC]; //0x0E3C
	Vector2 vfRecoil; //0x0E48 
	char pad_0x0E50[0x648]; //0x0E50
	DWORD dwArmor; //0x1498 
	char pad_0x149C[0x388]; //0x149C

}; //Size=0x1824