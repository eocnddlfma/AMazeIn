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
		map->push_back(Obj(Vector2(Startx*4, Starty*4), Vector2(Endx*4, Endy*4), texture, ObjLayer::Stru));
		if (file.eof())
			break;
	}
	file.close();

}
