#pragma once
#include "Core.h"

//Enemy의 이동을 처리하는 함수

Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos);
bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos);
Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos);
