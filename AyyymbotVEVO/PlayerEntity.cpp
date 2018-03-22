#include "stdafx.h"
#include "PlayerEntity.h"
#include <stdio.h>

void PrintLocalPlayer(cPlayerEntity *player)
{
	fprintf_s(stdout, "%s", "------------------+ Local Player Info +-----------------\r\n\r\n");
	fprintf_s(stdout, "Stats:\t\t%s HP: %lu [0x%X]\r\n", player->szName, player->dwHealth, player);
	fprintf_s(stdout, "Coordinates:\t(X: %.1f, Y: %.1f, Z: %.1f)\r\n",
		player->vfOrigin.X,
		player->vfOrigin.Y,
		player->vfOrigin.Z);
	fprintf_s(stdout, "Euler Angles:\t(Pitch: %.1f, Yaw: %.1f)\r\n", player->vfEuler.Pitch, player->vfEuler.Yaw);
	fprintf_s(stdout, "%s", "\r\n------------------+ Local Player Info #End +------------\r\n");
}