#include "Render.h"
#include "Core.h"
#include <iostream>
void renderObjs(int fov, std::vector<Obj> GameObjs, float** horizontal, float** HorizontalTexture, Vector2 player, ObjLayer* objectLayer, float playerRotation)
{
	for (int i = 0; i < GameObjs.size(); i++)
	{
		for (int ii = -fov; ii < fov; ii++)
		{
			/*Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x+ ((float)ii + rot) * 990, player.y+ fov * 990 )));*/
			Obj ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y),
				Vector2(player.x + (cosf((float)((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + fov]),
					player.y + (sinf(((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + fov]))
			, 1, ObjLayer::Stru, OBJ_TYPE::FORRAYCASTING));
			float dis = VDistace(ray1.ConvertVector2(), player);
			//Gotoxy(2, 2);
			bool able = ray1.able;
			if (able)
			{
				if (dis < horizontal[0][ii + fov]) {
					horizontal[0][ii + fov] = dis;
					std::cout << " distance:" << dis << "\n";
					//std::cout <<  "distancex: " << distx << " distance:" << dis <<"\n";
					objectLayer[ii + fov] = GameObjs[i].la;
					float distx = VDistace(ray1.ConvertVector2(), GameObjs[i].end) / (VDistace(GameObjs[i].start, GameObjs[i].end));
					if (distx < 0) {
						distx = 0;
					}
					if (distx > 1) {
						distx = 1;
					}
					HorizontalTexture[0][ii + fov] = distx;
				}
			}

		}
	}
}

void renderBillBoards(int fov, std::vector<Billboard*> Billboards, float** horizontal, float** HorizontalTexture, Vector2 player, ObjLayer* las, float playerRotation)
{
	for (int i = 0; i < Billboards.size(); i++) {

		Obj Billbod = Billboards[i]->ConvertObj(playerRotation);
		for (int ii = -fov; ii < fov; ii++)
		{
			/*Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x+ ((float)ii + rot) * 990, player.y+ fov * 990 )));*/
			Obj ray1 = Raycasting(Billbod, 
				Obj(Vector2(player.x, player.y), 
					Vector2(player.x + (cosf((float)((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + fov]), 
						player.y + (sinf(((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + fov]))
				,ObjLayer::Bill));
			float dis = VDistace(ray1.ConvertVector2(), player);

			bool able = ray1.able;
			if (able)
			{
				if (dis < horizontal[1][ii + fov])
				{

					float distx = VDistace(ray1.ConvertVector2(), Billbod.end) / (VDistace(Billbod.start, Billbod.end));
					if (distx >= 0 && distx <= 1)
					{
						horizontal[1][ii + fov] = dis;
						if (distx < 0) 
						{
							distx = 0;
						}
						if (distx > 1) 
						{
							distx = 1;
						}

						HorizontalTexture[1][ii + fov] = distx;
					}
				}
				//las[ii + fov] = BillBoards[i].la;

			}
		}
	}
}

void renderMap(int width, int height, int** map)
{

}

