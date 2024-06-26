#include "EnemyPathFind.h"

static int map[100][100];


Vector2 FindAndGetDir(Vector2 playerPos, Vector2 EnemyPos)
{
	return Vector2();
}

bool IsStraightAble(std::vector<Obj> GameObjs, Vector2 playerPos, Vector2 EnemyPos)
{
	bool hasObstacle = false;

	for (int i = 0; i < GameObjs.size(); i++)
	{
		Obj ray1 = Raycasting(GameObjs[i], Obj(playerPos, EnemyPos));
		if (ray1.able)
			hasObstacle = true;
	}
	return hasObstacle;
}

Vector2 GetStraightDir(Vector2 playerPos, Vector2 EnemyPos)
{
	return Vector2(playerPos.x - EnemyPos.x, playerPos.y - EnemyPos.y);
}