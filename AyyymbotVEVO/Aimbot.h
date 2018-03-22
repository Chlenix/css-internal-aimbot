#pragma once
#include "BaseEntity.h"
#include "Offsets.h"
#include "VevoSDK.h"
#include "PlayerEntity.h"

#include <iostream>
#include <DirectXMath.h>
#include <vector>

#define ENGINE_DLL "engine.dll"

class Aimbot
{
private:
	cBaseEntity * pPlayer;
	cPlayerEntity *pLocalPlayer;
	DWORD* pPlayersAlive;
	std::vector<cBaseEntity*> aliveEnemies;
public:
	DWORD dwServerImageBase;
	DWORD dwEngineImageBase;
	DWORD dwClientImageBase;

	Aimbot();
	~Aimbot();

	void SetPlayerEntity(cBaseEntity *pLocalPlayer);

	void HeadshotNearest(DWORD const& dwBaseEntityList);
	void SetViewAngle(Vector2 const& vfNewAngle, bool clamp = false);
	void CalcAngle(DirectX::XMFLOAT3& vfSrc, DirectX::XMFLOAT3& vfDest, Vector2& angles);
	void GetHeadboneVertex(DWORD const& dwTargetBoneMatrix, unsigned int const& uiBoneID, DirectX::XMFLOAT3& vfHeadPosition);
	DWORD const ScanForEnemies(DWORD const& dwBaseEntityList);
};

