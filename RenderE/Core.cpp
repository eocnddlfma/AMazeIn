#include "Core.h"
void SetColor(int _textcolor, int _bgcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
		, (_bgcolor << 4) | _textcolor);
}

void Gotoxy(int x, int y)
{
	// 콘솔 커서 위치를 딱 세팅
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		Cur);
}

float VDistace(Vector2 a, Vector2 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Obj Raycasting(Obj gm, Obj ray)
{
	float lean1, lean2, start1, start2;
	lean1 = (gm.start.y - gm.end.y) / (gm.start.x - gm.end.x);
	start1 = gm.start.y - lean1 * gm.start.x;

	lean2 = (ray.start.y - ray.end.y) / (ray.start.x - ray.end.x);
	start2 = ray.start.y - lean2 * ray.start.x;


	Obj ming;
	ming.able = false;
	ming.textureNum = 0;
	if (lean1 == lean2)
	{
		return ming;
	}

	//ming.x = -(start1 - start2) / (lean1 - lean2);
	//ming.y = ming.x * lean1 + start1;

	ming.start.x = ((gm.start.x * gm.end.y - gm.start.y * gm.end.x) * (ray.start.x - ray.end.x) - (ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (gm.start.x - gm.end.x))
		/ ((gm.start.x - gm.end.x) * (ray.start.y - ray.end.y) - (ray.start.x - ray.end.x) * (gm.start.y - gm.end.y));
	ming.start.y = ((gm.start.x * gm.end.y - gm.start.y * gm.end.x) * (ray.start.y - ray.end.y) - (ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (gm.start.y - gm.end.y))
		/ ((gm.start.x - gm.end.x) * (ray.start.y - ray.end.y) - (ray.start.x - ray.end.x) * (gm.start.y - gm.end.y));

	if(VDistace(Vector2((gm.start.x + gm.end.x) / 2, (gm.start.y + gm.end.y) / 2), ming.start) <= VDistace(gm.start, gm.end)/2 && (ming.start.x <= (ray.start.x >= ray.end.x ? ray.start.x : ray.end.x) && ming.start.x >= (ray.start.x <= ray.end.x ? ray.start.x : ray.end.x)
		&& ming.start.y <= (ray.start.y >= ray.end.y ? ray.start.y : ray.end.y) && ming.start.y >= (ray.start.y <= ray.end.y ? ray.start.y : ray.end.y)))
		//(ming.x <= (ray.start.x >= ray.end.x ? ray.start.x : ray.end.x) && ming.x >= (ray.start.x <= ray.end.x ? ray.start.x : ray.end.x) &&
		//ming.y <= (ray.start.y >= ray.end.y ? ray.start.y : ray.end.y) && ming.y >= (ray.start.y <= ray.end.y ? ray.start.y : ray.end.y)
		//&& (ming.x-0.1 <= (gm.start.x >= gm.end.x ? gm.start.x : gm.end.x) && ming.x+0.1 >= (gm.start.x <= gm.end.x ? gm.start.x : gm.end.x) &&
		//ming.y-0.1 <= (gm.start.y >= gm.end.y ? gm.start.y : gm.end.y) && ming.y+0.1 >= (gm.start.y <= gm.end.y ? gm.start.y : gm.end.y))))
	{
		ming.able = true;
		if (gm.ObjType != OBJ_TYPE::FORRAYCASTING) {
			ming.ObjType = gm.ObjType;
			ming.textureNum = gm.textureNum;
		}
		else {
			ming.ObjType = ray.ObjType;
			ming.textureNum = ray.textureNum;
		}
	}

	return ming;
}

#define TextureNum 4

int BaseTexture[15][15] =
{
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}
};

int ming[15][15] =
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,3,3,3,3,3,3,0,0,3,0,0,0},
{0,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
{0,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
{0,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
{0,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
{0,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
{0,0,0,3,3,3,3,3,3,0,0,3,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
{0,0,0,0,0,3,3,3,0,0,0,3,0,0,0},
{0,0,0,0,3,0,0,0,3,0,0,3,0,0,0},
{0,0,0,3,0,0,0,0,3,0,0,0,0,0,0},
{0,0,0,3,0,0,0,3,0,0,0,0,0,0,0},
{0,0,0,0,3,3,3,0,0,0,0,0,0,0,0}
};

int EnemyTexture[15][15] =
{
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,1,1,0,0},
{0,0,0,0,0,0,1,1,0,0,1,1,1,1,0},
{1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,0,0,0,1,1,0,0},
{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

//{
//	{3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4},
//	{ 3,3,4,3,3,3,3,3,1,2,3,1,3,3,3 },
//	{ 3,1,2,1,3,3,3,1,2,2,2,1,1,1,1 },
//	{ 1,1,2,1,1,2,1,2,2,1,0,1,1,2,1 },
//	{ 1,2,0,2,1,1,2,1,1,1,0,2,2,0,2 },
//	{ 1,1,1,1,1,1,1,1,1,1,1,1,0,1,1 },
//	{ 1,1,1,1,1,1,1,1,1,1,1,0,1,1,1 },
//	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
//	{ 1,1,1,1,1,1,1,1,1,1,1,2,1,1,1 },
//	{ 1,1,1,1,2,2,1,1,1,1,1,1,2,1,1 },
//	{ 0,1,1,0,1,1,1,1,1,0,0,0,0,2,1 },
//	{ 0,1,1,0,1,0,0,1,1,0,0,2,0,0,0 },
//	{ 1,1,1,0,1,1,1,1,1,2,2,2,1,1,1 },
//	{ 0,2,1,1,1,1,1,1,1,1,2,1,1,2,1 },
//	{ 1,2,1,1,1,1,1,1,1,1,2,2,0,1,1 }
//};
int BulletTexture[15][15] =
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


int(*GetTextureByNumber(int num))[15]
{
	switch (num)
	{
	case 0:
		return BaseTexture;
		break;
	case 1:
		return ming;
		break;
	case 2:
		return EnemyTexture;
		break;
	case 3:
		return BulletTexture;
		break;
	default:
		break;
	}
}
	//COORD GetConsoleResolution()
	//{
	//
	//	
	//	short width = info.srWindow.Right - info.srWindow.Left + 1;
	//	short height =  - + 1;
	//	return COORD{ width,height };
	//}

int** LineToMap(Vector2 playerPos, vector<Obj> Objs, int width, int height)
{
	int** map = new int*[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for(Obj v : Objs)
			{

			}
		}
	}

	return map;
}
