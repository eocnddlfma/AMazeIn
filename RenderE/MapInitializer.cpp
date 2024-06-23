#include "MapInitializer.h"
#include <fstream>
#include <iostream>

void SetMap(std::vector<Obj>* map)//맵 초기화 처리
{
	int leftup, rightup, rightdown, leftdown, texture;
	std::ifstream file;
	file.open("mapData.txt");
	while (true)
	{
		file >> leftup >> rightup >> rightdown >> leftdown >> texture;
		map->push_back(Obj(Vector2(leftup, rightup), Vector2(rightup, rightdown), ObjLayer::Stru, 1, OBJ_TYPE::WALL));
		map->push_back(Obj(Vector2(rightup, rightdown), Vector2(leftdown, leftup), ObjLayer::Stru, 1, OBJ_TYPE::WALL));
		map->push_back(Obj(Vector2(rightdown, leftdown), Vector2(leftup, rightup), ObjLayer::Stru, 1, OBJ_TYPE::WALL));
		map->push_back(Obj(Vector2(leftdown, leftup), Vector2(rightup, rightdown), ObjLayer::Stru, 1, OBJ_TYPE::WALL));
		if (!file.eof())
			break;
	}
	file.close();

}
