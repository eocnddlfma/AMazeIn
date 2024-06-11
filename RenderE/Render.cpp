#include "Render.h"
#include "Core.h"

void renderObjs(int fov, std::vector<Obj> GameObjs, float** horizontal, float** HorizontalTexture, Vector2 player, ObjLayer* objectLayer, float playerRotation)
{
	for (int i = 0; i < GameObjs.size(); i++)
	{
		for (int ii = -fov; ii < fov; ii++)
		{
			/*Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x+ ((float)ii + rot) * 990, player.y+ fov * 990 )));*/
			Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y),
				Vector2(player.x + (cosf((float)((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + fov]),
					player.y + (sinf(((float)ii) * 3.14159f / RESOLUTION + playerRotation) * horizontal[0][ii + fov]))));
			float dis = VDistace(ray1, player);

			bool able = ray1.able;
			if (able)
			{
				if (dis < horizontal[0][ii + fov])
					horizontal[0][ii + fov] = dis;
				objectLayer[ii + fov] = GameObjs[i].la;
				float distx = VDistace(ray1, GameObjs[i].end) / (VDistace(GameObjs[i].start, GameObjs[i].end));
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
