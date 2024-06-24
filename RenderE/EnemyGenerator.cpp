#include "EnemyGenerator.h"

void GenerateEnemy(Vector2 lefttop, Vector2 rightbottom, int speed, vector<Enemy*> enemyList)
{
	srand((unsigned int)time(NULL));

	int spawnPointX = (rand() % (int)(rightbottom.x-lefttop.x)) + lefttop.x;
	int spawnPointY = (rand() % (int)(rightbottom.y-lefttop.y)) + lefttop.y;

	Enemy enemy(Billboard(Vector2(spawnPointX, spawnPointY), 0.4f, Vector2(0, 0), 0.4, OBJ_TYPE::ENEMY, 3), 5, 1);
	enemyList.push_back(&enemy);
}
