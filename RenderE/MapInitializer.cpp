#include "MapInitializer.h"
#include <fstream>
#include <iostream>

void SetMap(std::vector<Obj>* map)//맵 초기화 처리
{
	int Startx, Starty, Endx, Endy, texture;
	std::ifstream file;
	file.open("mapData.txt");
	while (true)
	{
		file >> Startx >> Starty >> Endx >> Endy >> texture;
		map->push_back(Obj(Vector2(Endx, Starty), Vector2(Startx, Starty), 1, ObjLayer::Stru, OBJ_TYPE::WALL));
		map->push_back(Obj(Vector2(Startx, Starty), Vector2(Startx, Endy), 1, ObjLayer::Stru, OBJ_TYPE::WALL));
		map->push_back(Obj(Vector2(Endx, Starty), Vector2(Endx, Endy), 1, ObjLayer::Stru, OBJ_TYPE::WALL));
		map->push_back(Obj(Vector2(Endx, Endy), Vector2(Startx, Endy), 1, ObjLayer::Stru, OBJ_TYPE::WALL));
		if (!file.eof())
			break;
	}
	file.close();

}
