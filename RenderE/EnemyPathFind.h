#pragma once
#include "Core.h"

//Enemy의 이동을 처리하는 함수

void SetMap(std::vector<Obj> GameObjs, int size, Vector2 minPos, Vector2 maxPos);
Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos);
bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos);
Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos);
