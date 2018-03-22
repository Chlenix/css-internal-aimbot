#pragma once

// Pitch: *engine.dll+47F1B4
// yaw: *(engine.dll+47F1B4)+4

// UMP45 "server.dll"+004F438C

// +4B0 for ammo

// How to get Async:
/*
"client.dll"+004C6708
"client.dll"+004D3904
"client.dll"+0050228C
"client.dll"+00503128

And offset: 1018
*/

#define MAX_PLAYERS 64

/* CLIENT.dll */
#define PLAYER_BASE_OFFSET 0x50C150
#define FIRST_BOT_ENTITY_OFFSET 0x168
#define NEXT_BASE_ENTITY_OFFSET 0x10
#define GAME_WORLD_OFFSET_NEGATIVE 0x158

#define BONEMATRIX_OFFSET 0x578

// client + 004D3904
// entity = *(list **)
// (DWORD)entity + (0x10 * i) for next
#define BASE_ENTITY_OFFSET 0x4C6708
#define ENTITY_LIST_OFFSET 0x4D3904

#define COMMAND_TABLE_OFFSET 0x4F3520

#define ATTACK_START_OFFSET 0x1472D0
#define ATTACK_STOP_OFFSET 0x147310

/* ENGINE.dll */
#define PLAYER_PITCH_OFFSET 0x47F1B4
#define TERRORISTS_ALIVE_OFFSET 0x65843C

/* SERVER.dll */

#define PLAYERS_ALIVE_OFFSET 0x4EFFC0
