#pragma once
#include "Core.h"

void renderObjs(std::vector<Obj> GameObjs,
	float** horizontal, float** HorizontalTexture,
	Vector2 player, ObjLayer* las, float playerRotation);

void renderBillBoards(std::vector<Billboard*> Billboards,
	float** horizontal, float** HorizontalTexture,
	Vector2 player, ObjLayer* las, float playerRotation);

std::string renderMap(Vector2 playerPosition, int width, int height, int** map);
