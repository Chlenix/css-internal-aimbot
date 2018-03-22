#include "stdafx.h"
#include "Aimbot.h"

#define _USE_MATH_DEFINES
#include <math.h>

Aimbot::Aimbot()
{
	HMODULE hModEngine = GetModuleHandle("engine.dll");
	if (hModEngine)
	{
		this->dwEngineImageBase = (DWORD)hModEngine;
	}

	HMODULE hModServer = GetModuleHandle("server.dll");
	if (hModServer)
	{
		this->dwServerImageBase = (DWORD)hModServer;
		this->pPlayersAlive = (DWORD *)(this->dwServerImageBase + PLAYERS_ALIVE_OFFSET);
	}

	HMODULE hModClient = GetModuleHandle("client.dll");
	if (hModClient)
	{
		this->dwClientImageBase = (DWORD)hModClient;
		this->pLocalPlayer = *(cPlayerEntity**)(this->dwClientImageBase + PLAYER_BASE_OFFSET);
	}
}

Aimbot::~Aimbot()
{
}

void Aimbot::SetPlayerEntity(cBaseEntity *pLocalPlayer)
{
	this->pPlayer = pLocalPlayer;
}

void Aimbot::SetViewAngle(Vector2 const& vfNewAngle, bool clamp)
{	
	if (this->dwEngineImageBase)
	{
		float *fpPlayerViewAngles = (float *)(this->dwEngineImageBase + PLAYER_PITCH_OFFSET);
		//fprintf_s(stdout, "EngineDLL Image Base: 0x%X\r\n", this->dwEngineImageBase);
		//fprintf_s(stdout, "ViewAnglePitch Pointer: 0x%X\r\n", (UINT_PTR)fpPlayerViewAngles);

		//fprintf_s(stdout, "ViewAnglePitch Value: %.1f\r\n", *fpPlayerViewAngles);

		*(fpPlayerViewAngles) = vfNewAngle.Pitch;
		*(fpPlayerViewAngles + 1) = vfNewAngle.Yaw;
	}
}

void Aimbot::GetHeadboneVertex(DWORD const& dwTargetBoneMatrix, unsigned int const& uiBoneID, DirectX::XMFLOAT3& vfHeadPosition)
{
	// 14 for head
	vfHeadPosition.x = *(float *)(dwTargetBoneMatrix + (0x30 * uiBoneID) + 0x0C);
	vfHeadPosition.y = *(float *)(dwTargetBoneMatrix + (0x30 * uiBoneID) + 0x1C);
	vfHeadPosition.z = *(float *)(dwTargetBoneMatrix + (0x30 * uiBoneID) + 0x2C);
}

void Aimbot::CalcAngle(DirectX::XMFLOAT3& vfSrc, DirectX::XMFLOAT3& vfDest, Vector2& angles)
{
	
}

void Aimbot::HeadshotNearest(DWORD const& dwBaseEntityList)
{
	system("cls");
	ScanForEnemies(dwBaseEntityList);
	size_t enemyCount = this->aliveEnemies.size();

	if (enemyCount <= 0)
	{
		Sleep(10);
		return;
	}

	void* pBoneMatrix = *(void **)(DWORD(this->aliveEnemies[enemyCount - 1]) + BONEMATRIX_OFFSET);
	
	DirectX::XMFLOAT3 xmfEnemyHead{ 0 };
	DirectX::XMFLOAT3 xmfPlayerHead{ 0 };
	DirectX::XMFLOAT3 xmfDelta{ 0 };
	DirectX::XMFLOAT3 xmfLength{ 0 };;

	GetHeadboneVertex((DWORD)pBoneMatrix, 14, xmfEnemyHead);

	xmfPlayerHead.x = this->pLocalPlayer->vfOrigin.X;
	xmfPlayerHead.y = this->pLocalPlayer->vfOrigin.Y;
	xmfPlayerHead.z = this->pLocalPlayer->vfOrigin.Z + 0.25f;

	fprintf_s(stdout, "(ENEMY ------ X: %.1f, Y: %.1f, Z: %.1f)\r\n", xmfEnemyHead.x, xmfEnemyHead.y, xmfEnemyHead.z);
	fprintf_s(stdout, "(PLAYER ----- X: %.1f, Y: %.1f, Z: %.1f)\r\n", 
		this->pLocalPlayer->vfOrigin.X, 
		this->pLocalPlayer->vfOrigin.Y, 
		this->pLocalPlayer->vfOrigin.Z);
	
	auto fxmfPlayerHead = DirectX::XMLoadFloat3(&xmfPlayerHead);
	auto fxmfEnemyHead = DirectX::XMLoadFloat3(&xmfEnemyHead);

	// Subtract Enemy.HeadPos from P.HeadPos 
	auto fxmfResult = DirectX::XMVectorSubtract(fxmfPlayerHead, fxmfEnemyHead);

	auto fxmfMagnitude = DirectX::XMVector3Length(fxmfResult);

	DirectX::XMStoreFloat3(&xmfDelta, fxmfResult);
	DirectX::XMStoreFloat3(&xmfLength, fxmfMagnitude);

	fprintf_s(stdout, "(DISTANCE ------ X: %.1f, Y: %.1f, Z: %.1f)\r\n", xmfDelta.x, xmfDelta.y, xmfDelta.z);
	fprintf_s(stdout, "(LENGTH ------ %.3f\r\n", xmfLength.x);

	Vector2 vfNewAngles{ 0 };
	vfNewAngles.Yaw = (atanf(xmfDelta.y / xmfDelta.x) * (180.0f / M_PI));
	vfNewAngles.Pitch = (acosf(xmfDelta.z / xmfLength.x) * (180.0f / M_PI)) - 90.0f;

	vfNewAngles.Pitch *= -1.0f;

	fprintf_s(stdout, "Raw YAW: %.2f\r\n", vfNewAngles.Yaw);

	if (xmfDelta.x > 0.0f)
	{
		vfNewAngles.Yaw += (vfNewAngles.Yaw > 0.0f) ? -180.000f : 180.000f;
	}

	fprintf_s(stdout, "Calculated YAW: %.2f\r\n", vfNewAngles.Yaw);

	fprintf_s(stdout, "Player Pitch: %.2f| Yaw: %.2f\r\n", this->pLocalPlayer->vfEuler.Pitch, this->pLocalPlayer->vfEuler.Yaw);
	SetViewAngle(vfNewAngles);
}

DWORD const Aimbot::ScanForEnemies(DWORD const& dwBaseEntityList)
{
	cBaseEntity *currentEntity;

	DWORD const playersAlive = *(this->pPlayersAlive);

	this->aliveEnemies.clear();

	size_t i = 0;
	while (i++ < MAX_PLAYERS && this->aliveEnemies.size() < playersAlive)
	{
		currentEntity = *(cBaseEntity **)((DWORD)dwBaseEntityList + (NEXT_BASE_ENTITY_OFFSET * i));

		if ((DWORD *)(currentEntity) == nullptr || currentEntity->dwTeam == this->pPlayer->dwTeam || currentEntity->dwHealth <= 1)
		{
			continue;
		}

		fprintf_s(stdout, "[0x%X] Pushed! At i = %Iu\r\n", currentEntity, i);

		// enemy player
		this->aliveEnemies.push_back(currentEntity);
	}

	fprintf_s(stdout, "Players alive: %lu\r\n", playersAlive);

	return playersAlive;
}