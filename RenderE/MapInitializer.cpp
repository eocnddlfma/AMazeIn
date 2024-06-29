#include "MapInitializer.h"
#include <fstream>
#include <iostream>

void SetMap(std::vector<Obj>* map)//�� �ʱ�ȭ ó��
{
	int Startx, Starty, Endx, Endy, texture;
	std::ifstream file;
	file.open("mapData.txt");
	while (true)
	{
		file >> Startx >> Starty >> Endx >> Endy >> texture;
		map->push_back(Obj(Vector2(Startx, Starty), Vector2(Endx, Endy), texture, ObjLayer::Stru));
		if (file.eof())
			break;
	}
	file.close();

}
