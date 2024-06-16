#include "MapInitializer.h"
#include <fstream>
#include <iostream>

void SetMap(std::vector<Objs>* map)
{
	int leftup, rightup, rightdown, leftdown, texture;
	std::ifstream file;
	file.open("mapData.txt");
	while (true)
	{
		file >> leftup >> rightup >> rightdown >> leftdown >> texture;
		map->push_back(Objs(
			{ Vector2(leftup, rightup),
			Vector2(rightup, rightdown),
			Vector2(rightdown, leftdown),
			Vector2(leftdown, leftup)
			}, texture
		));
		if (!file.eof())
			break;
	}
	file.close();

}
