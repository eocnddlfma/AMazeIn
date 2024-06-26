#include "Render.h"
#include "Core.h"
void renderObjs(std::vector<Obj> GameObjs, float** horizontal, float** HorizontalTexture, Vector2 player, ObjLayer* objectLayer, float playerRotation)
{
	for (int i = 0; i < GameObjs.size(); i++)
	{
		for (int ii = -FOV; ii < FOV; ii++)
		{
			/*Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x+ ((float)ii + rot) * 990, player.y+ FOV * 990 )));*/
			Obj ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y),
				Vector2(player.x + (cosf((float)((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + FOV]),
					player.y + (sinf(((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + FOV]))));
			float dis = VDistace(ray1.ConvertVector2(), player);

			if (ray1.able)
			{
				if (dis < horizontal[0][ii + FOV]) {
					horizontal[0][ii + FOV] = dis;
					//std::cout << " distance:" << dis << " obj: " << ObjTypeToString(ray1.ObjType) << " gameobjpos: " << GameObjs[i].start.x << " " << GameObjs[i].start.y << " gameobjpos: " << GameObjs[i].end.x << " " << GameObjs[i].end.y << "\n";
					//std::cout <<  "distancex: " << distx << " distance:" << dis <<"\n";
					objectLayer[ii + FOV] = GameObjs[i].la;
					float distx = VDistace(ray1.ConvertVector2(), GameObjs[i].end) / (VDistace(GameObjs[i].start, GameObjs[i].end));
					if (distx < 0) {
						distx = 0;
					}
					if (distx > 1) {
						distx = 1;
					}
					HorizontalTexture[0][ii + FOV] = distx;
				}
			}

		}
	}
}

void renderBillBoards(std::vector<Billboard*> Billboards, float** horizontal, float** HorizontalTexture, Vector2 player, ObjLayer* las, float playerRotation)
{
	for (int i = 0; i < Billboards.size(); i++) {

		Obj Billbod = Billboards[i]->ConvertObj(playerRotation);
		for (int ii = -FOV; ii < FOV; ii++)
		{
			/*Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x+ ((float)ii + rot) * 990, player.y+ FOV * 990 )));*/
			Obj ray1 = Raycasting(Billbod, 
				Obj(Vector2(player.x, player.y), 
					Vector2(player.x + (cosf((float)((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + FOV]), 
						player.y + (sinf(((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + FOV]))
				,ObjLayer::Bill));
			float dis = VDistace(ray1.ConvertVector2(), player);

			bool able = ray1.able;
			if (able)
			{
				if (dis < horizontal[1][ii + FOV])
				{

					float distx = VDistace(ray1.ConvertVector2(), Billbod.end) / (VDistace(Billbod.start, Billbod.end));
					if (distx >= 0 && distx <= 1)
					{
						horizontal[1][ii + FOV] = dis;
						if (distx < 0) 
						{
							distx = 0;
						}
						if (distx > 1) 
						{
							distx = 1;
						}

						HorizontalTexture[1][ii + FOV] = distx;
					}
				}
			}
		}
	}
}

std::string renderMap(Vector2 playerPosition, int width, int height, OBJ_TYPE** map)
{
	std::string s;

	for (int y = playerPosition.y - height / 2; y < playerPosition.y + height/2; y++)
	{
		for (int x = playerPosition.x - width / 2; x < playerPosition.x + width / 2; x++)
		{
			char c;
			switch (map[y][x])
			{
			case OBJ_TYPE::WALL:
				c = '¡á';
				break;
			case OBJ_TYPE::KEY:
				c = '¡×';
				break;
			case OBJ_TYPE::DOOR:
				c = '¡Ø';
				break;
			case OBJ_TYPE::ENEMY:
				c = '¡ß';
				break;
			case OBJ_TYPE::PLAYER:
				c = '¡Ý';
				break;
			case OBJ_TYPE::FORRAYCASTING:
				c = ' ';
				break;
			default:
				break;
			}
			s += c;
		}
		s += "\n";
	}
	return s;
}

