#include "EnemyPathFind.h"

static int map[100][100];

void SetMap(std::vector<Obj> GameObjs, int size, Vector2 minPos, Vector2 maxPos)
{
}

Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos)
{
	return Vector2();
}

bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos)
{
	bool hasObstacle = false;

	for (int i = 0; i < GameObjs.size(); i++)
	{
		Vector2 ray1 = Raycasting(GameObjs[i], Obj(playerPos, EnemyPos));
		if (ray1.able)
			hasObstacle = true;
	}
	return hasObstacle;
}

Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos)
{
	return Vector2(playerPos.x - EnemyPos.x, playerPos.y - EnemyPos.y);
}