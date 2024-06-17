#pragma once
#include "Core.h"

void SetMap(std::vector<Obj> GameObjs, int size, Vector2 minPos, Vector2 maxPos);
Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos);
bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos);
Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos);
