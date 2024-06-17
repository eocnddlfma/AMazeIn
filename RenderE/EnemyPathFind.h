#pragma once
#include "Core.h"

void SetMap(std::vector<Obj> GameObjs, int size, Vector2 minPos, Vector2 maxPos)//이차원 배열을 만들고 
Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos); //배열을 astar로 일일히 돌아서 길 찾아서 dir반환
bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos);
Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos);

