#pragma once
#include "Core.h"

//Enemy�� �̵��� ó���ϴ� �Լ�

Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos);
bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos);
Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos);
