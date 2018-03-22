#include "stdafx.h"
#include "main.h"
#include "PlayerEntity.h"
#include "BaseEntity.h"
#include "VevoSDK.h"
#include "Offsets.h"
#include "Aimbot.h"

#include <iostream>

VevoSDK vevoSDK;
cBaseEntity *pPlayerEntity;
DWORD *dwCommandTable;

FILE *pCout;

BOOL __stdcall main(LPVOID)
{
	SummonConsole();

	Aimbot aimbot;

	// Player
	DWORD dwClientImageBase = (DWORD)GetModuleHandle("client.dll");
	//pLocalPlayerEntity = *(cPlayerEntity **)(dwClientImageBase + PLAYER_BASE_OFFSET);

	DWORD dwEngineImageBase;
	while (!(dwEngineImageBase = (DWORD)GetModuleHandle("engine.dll")))
	{
		fprintf_s(stdout, "Can't find the engine dll dude...\r\n");
	}

	dwCommandTable = *(DWORD **)(dwClientImageBase + COMMAND_TABLE_OFFSET);

	LPDWORD pBaseEntityList = (LPDWORD)(dwClientImageBase + ENTITY_LIST_OFFSET);
	pPlayerEntity = *(cBaseEntity **)pBaseEntityList;

	aimbot.SetPlayerEntity(pPlayerEntity);

	fprintf_s(stdout, "EntityList: 0x%X\r\n", pBaseEntityList);
	fprintf_s(stdout, "Entity Player: 0x%X\r\n", pPlayerEntity);
	fprintf_s(stdout, "Entity Player HP: %lu\r\n", pPlayerEntity->dwHealth);

	while (!GetAsyncKeyState(VK_DELETE))
	{

		Sleep(10);

		if (GetAsyncKeyState(VK_MBUTTON) & 1)
		{
			aimbot.HeadshotNearest((DWORD)pBaseEntityList);
			Sleep(50);
			vevoSDK.DoThisCall((DWORD)dwCommandTable, dwClientImageBase + ATTACK_START_OFFSET);
			Sleep(10);
			vevoSDK.DoThisCall((DWORD)dwCommandTable, dwClientImageBase + ATTACK_STOP_OFFSET);
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			vevoSDK.DoThisCall((DWORD)dwCommandTable, dwClientImageBase + ATTACK_START_OFFSET);
			Sleep(100);
			vevoSDK.DoThisCall((DWORD)dwCommandTable, dwClientImageBase + ATTACK_STOP_OFFSET);
		}

		if (GetAsyncKeyState(VK_END) & 1)
		{
			vevoSDK.DoThisCall((DWORD)dwCommandTable, dwClientImageBase + ATTACK_STOP_OFFSET);
		}

		fflush(stdout);
	}

	ConsoleClose();
	return TRUE;
}

void SummonConsole()
{
	AllocConsole();
	freopen_s(&pCout, "CONOUT$", "w", stdout);
}

void ConsoleClose()
{
	fclose(pCout);
	FreeConsole();
}