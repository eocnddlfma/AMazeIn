#pragma once
#include "Core.h"

void SetMap(std::vector<Obj> GameObjs, int size, Vector2 minPos, Vector2 maxPos)//������ �迭�� ����� 
Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos); //�迭�� astar�� ������ ���Ƽ� �� ã�Ƽ� dir��ȯ
bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos);
Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos);

