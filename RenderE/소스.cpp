#include<iostream>
#include "Windows.h"
#include"conio.h"
#include<vector>
#include<string>
#include<algorithm>

#include "DataStructure.h"

using namespace std;



const std::string reset = "\033[0m";
const std::string bold = "\033[1m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string yellow = "\033[33m";
const std::string purple = "\033[35m";
const std::string cyan = "\033[36m";
const std::string green = "\033[32m";
const std::string black = "\033[30m";
const std::string white = "\033[37m";
const std::string underline = "\033[4m";
const std::string g = "\033[32m";

void SetColor(int _textcolor, int _bgcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
		, (_bgcolor << 4) | _textcolor);
}

void Gotoxy(int x, int y)
{
	// ÄÜ¼Ö Ä¿¼­ À§Ä¡¸¦ µü ¼¼ÆÃ
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		Cur);
}

float VDistace(Vector2 a, Vector2 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<Obj> GameObjs;
vector<Obj>BillBoards;
char Pixels[8] = { '@','#','X','x','+','*','^',' ' };
char PixelsGround[15] = { '~','-','-','-',',',',',',','.','.','.','.','.','.',' ',' ' };
string colors[5] = { "\033[1;33m","\033[1;31m","\033[1;42m","\033[1;32m","\033[1;92m" };

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

Vector2 Raycasting(Obj gm, Obj ray)
{
	float lean1, lean2, start1, start2;
	lean1 = (gm.start.y - gm.end.y) / (gm.start.x - gm.end.x);
	start1 = gm.start.y - lean1 * gm.start.x;

	lean2 = (ray.start.y - ray.end.y) / (ray.start.x - ray.end.x);
	start2 = ray.start.y - lean2 * ray.start.x;


	Vector2 ming{ 1, 1 };
	ming.able = false;
	if (lean1 == lean2)
	{
		return ming;
	}

	ming.x = -(start1 - start2) / (lean1 - lean2);
	ming.y = ming.x * lean1 + start1;

	/*ming.x = ((gm.start.x * gm.end.y - gm.start.y * gm.end.x) * (ray.start.x - ray.end.x) - (ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (gm.start.x - gm.end.x))
		/ ((gm.start.x - gm.end.x) * (ray.start.y - ray.end.y) - (ray.start.x - ray.end.x) * (gm.start.y - gm.end.y));
	ming.y = ((gm.start.x * gm.end.y - gm.start.y * gm.end.x) * (ray.start.y - ray.end.y) - (ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (gm.start.y - gm.end.y))
		/ ((gm.start.x - gm.end.x) * (ray.start.y - ray.end.y) - (ray.start.x - ray.end.x) * (gm.start.y - gm.end.y));*/

	if (ming.x <= (ray.start.x >= ray.end.x ? ray.start.x : ray.end.x) && ming.x >= (ray.start.x <= ray.end.x ? ray.start.x : ray.end.x) &&
		ming.y <= (ray.start.y >= ray.end.y ? ray.start.y : ray.end.y) && ming.y >= (ray.start.y <= ray.end.y ? ray.start.y : ray.end.y))
	{
		ming.able = true;
	}

	return ming;
}
//COORD GetConsoleResolution()
//{
//
//	
//	short width = info.srWindow.Right - info.srWindow.Left + 1;
//	short height =  - + 1;
//	return COORD{ width,height };
//}

vector<string> ViewModelArt1 = { {bold},
								{"    #############"},
								{" 000=##############"},
								{"0000==###############"},
								{" 000====##############"},
								{"  00=====##############"},
								{"    ======##############"},
								{"    =======##############"},
								{"    ========##############"},
								{"    =========##############"},
								{"     ===========###########"},
								{"      ===========############"},
								{"       ===========#############"},
								{"       ============#############"},
								{"      ----==========##############"},
								{"      ----============#############"},
								{"      ------===========#############"},
								{"      ------===========#############"},
								{"      ------+===========#############"},
								{"       ----------===========############"},
								{"        --------- ==========#############"},
								{"         --------   =========#############"},
								{"                     ========#############"},
								{"                      ========#############"},
								{"                       =======#############"},
								{"                  ============#############"},
								{"                 =============#############"},
								{"                 =============#############"},
								{reset}
};
vector<string> ViewModelArt12 = { {bold},
								{"            :            "},
								{"      .    ::              "},
								{"   .  ..  ::::             "},
								{"   . . :::::#############"},
								{"     :::000=##############"},
								{" ::::::0000==###############"},
								{"  .  :::000====##############"},
								{"       ::00=====##############"},
								{"         ::======##############"},
								{"         ::=======##############"},
								{"           ========##############"},
								{"           =========##############"},
								{"            ===========###########"},
								{"             ===========############"},
								{"              ===========#############"},
								{"              ============#############"},
								{"             ----==========##############"},
								{"             ----============#############"},
								{"             ------===========#############"},
								{"             ------===========#############"},
								{"             ------+===========#############"},
								{"              ----------===========############"},
								{"               --------- ==========#############"},
								{"                --------   =========#############"},
								{"                            ========#############"},
								{"                             ========#############"},
								{"                              =======#############"},

								{reset}
};

void Renderer(const int fov, Vector2 player, float rot, int resol)
{
	float** horizontal = new float*[3];
	float* horizontal2 = new float[fov * 2] { 999, };
	float* horizontaltx = new float[fov * 2] { 0, };
	ObjLayer* las = new ObjLayer[fov * 2];
	
	for (int i = 0; i < 3; i++) {
		horizontal[i] = new float[fov * 2]{999, };
		
		for (int j = 0; j < fov * 2; j++)
		{
			horizontal[i][j] = 999;
		}
	}
	//CONSOLE_SCREEN_BUFFER_INFO info;
	//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		//, &info);

	string output = "";
	string output2 = "";

	for (int i = 0; i < GameObjs.size(); i++)
	{
		if (true)
		{
			for (int ii = -fov; ii < fov; ii++)
			{
				/*Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x+ ((float)ii + rot) * 990, player.y+ fov * 990 )));*/
				Vector2 ray1 = Raycasting(GameObjs[i], Obj(Vector2(player.x, player.y), Vector2(player.x + (cosf((float)((float)ii) * 3.14159f / resol + rot) * horizontal[0][ii + fov]), player.y + (sinf(((float)ii) * 3.14159f / resol + rot) * horizontal[0][ii + fov]))));
				float dis = VDistace(ray1, player);

				bool able = ray1.able;
				if (able)
				{
					if (dis < horizontal[0][ii + fov])
					horizontal[0][ii + fov] = dis;
					las[ii + fov] = GameObjs[i].la;
					float distx = VDistace(ray1, GameObjs[i].end) / (VDistace(GameObjs[i].start, GameObjs[i].end));
					if (distx < 0) {
						distx = 0;
					}
					if (distx > 1) {
						distx = 1;
					}
					horizontaltx[ii + fov] = distx;
				}

			}
		}
	}

	Gotoxy(2, 2);
	for (int j = 0; j < 75; j++)
	{
		for (int ii = 0; ii < fov * 2; ii++)
		{

			//output[j].push_back(' ');
			//output[j][ii + fov]='#';
			//output[ii,48 - j] = '0' + ((int)horizontal[ii] < 9 ? (int)horizontal[ii] : 9);

			if (j >= horizontal[0][ii]/2 && j <= 75 - horizontal[0][ii]/2)
			{
				//if (las[ii] == ObjLayer::Bill)
				//{
				//	output += red;
				//}

				float size = ((int)horizontal[ii]/2 - (75 - (int)horizontal[ii]/2));

				if (75 - horizontal[0][ii]/2 * 2 > 0)
					output.append(colors[ming[(int)(horizontaltx[ii] * 14)][(int)fabs((j - horizontal[0][ii]/2) / ((75 - horizontal[0][ii]/2 * 2)) * 14)]]);//(int)((55 - j)/15*horizontaltx[ii])

				if ((int)(horizontal[0][ii]/5/2) < 7) {

					output += Pixels[(int)(horizontal[0][ii]/2 / 5)];
				}
				else
				{
					output += Pixels[6];
				}
				output += reset;
				//if (las[ii] == ObjLayer::Bill)
				//{
				//	output += reset;
				//}
			}
			else
			{
				output += PixelsGround[j/5];
			}
		}
		output += '\n';
	}
	{
		cout << output;
		output.clear();
		//output[i] = string(200, ' ');
	}


	for (int i = 0; i < 3; i++) {
		delete[] horizontal[i];
	}
	delete horizontal;
}


int main()
{


	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 10;                   // Width of each character in the font
	cfi.dwFontSize.Y = 10;                  // Height
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ShowWindow(GetConsoleWindow(),
		SW_MAXIMIZE);
	system("mode con: cols=960 lines=540");
	//HWND console = GetConsoleWindow();
	//LONG style = GetWindowLong(console, GWL_STYLE);

	//style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;// &~WS_HSCROLL;// &~WS_CAPTION;
	//SetWindowLong(console, GWL_STYLE, style);

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15<<4)|0);

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = FALSE; //Ä¿¼­ Visible TRUE(º¸ÀÓ) FALSE(¼û±è)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	vector<Objs> GameObjss;
	GameObjss.push_back(Objs({Vector2(-15*2,-15*2), Vector2(15*2,-15*2), Vector2(15*2,15*2), Vector2(-15*2,15*2)}));
	/*GameObjss.push_back(Objs({ Vector2(-12*2,-6 * 2), Vector2(12 * 2,-6 * 2), Vector2(12 * 2,12 * 2), Vector2(6 * 2,12 * 2),Vector2(6 * 2,12 * 2) ,Vector2(6 * 2,24 * 2) ,Vector2(18 * 2,24 * 2)
		,Vector2(18 * 2,42 * 2),Vector2(-36 * 2,42 * 2) ,Vector2(-36 * 2,24 * 2),Vector2(-2,24 * 2) ,Vector2(-2,12 * 2) ,Vector2(-12 * 2,12 * 2)}));*/
	//GameObjss.push_back(Objs({ Vector2(3,3), Vector2(3,6), Vector2(6,6), Vector2(6,3) },ObjLayer::Bill));

//GameObjs[0] =(Obj(Vector2(2, 8), Vector2(-2, 8)));
//GameObjs.push_back(Obj(Vector2(8, 8), Vector2(-15, 8)));
//GameObjs.push_back(Obj(Vector2(-8, -8), Vector2(-8, 8)));
//GameObjs.push_back(Obj(Vector2(-8, -8), Vector2(8, -8)));

	//vector<Obj4> GameObject4(1);
//	GameObject4[0] = Obj4(Vector2(-10,10), Vector2(10,10), Vector2(10,-10), Vector2(-10,-10));
//
//for (int i = 0; i < GameObject4.size(); i++)
//{
//	for (int j = 0; j < 4; j++)
//	{
//		GameObjs.push_back(GameObject4[i].lines[j]);
//	}
//}

	for (int i = 0; i < GameObjss.size(); i++)
	{
		for (int j = 0; j < GameObjss[i].lines.size(); j++)
		{
			GameObjs.push_back(GameObjss[i].lines[j]);
		}
	}
	//GameObjs.push_back(Obj(Vector2(7, 30), Vector2(-7,30)));
	//GameObjs.push_back(Obj(Vector2(-2, 1), Vector2(2, 1)));
	//GameObjs.push_back(Obj(Vector2(5, 15), Vector2(2, 1)));
	float speedOrigin = 15;
	int fov = 140;
	int resol = 660;
	float rot = 0, speed = 0;
	Vector2 Playerpos = Vector2(0, 0);
	POINT TMPMousePos = { 0,0 };
	float deltaTime = 0;
	LARGE_INTEGER Current, last, MING;
	QueryPerformanceCounter(&Current);
	QueryPerformanceFrequency(&MING);
	last = Current;
	while (true)
	{
		QueryPerformanceCounter(&Current);
		deltaTime = (float)(Current.QuadPart - last.QuadPart) / static_cast<float>(MING.QuadPart);
		last = Current;

		Gotoxy(0, 0);


		speed = speedOrigin * deltaTime;
		cout << speed;
		Vector2 poss = Vector2(0, 0);
		if (rot > 2 * 3.141592) {
			rot = 0;
		}
		else
			if (rot < 0) {
				rot = 2 * 3.141591;
			}

		Renderer(fov, Playerpos, rot, resol);
		if (GetAsyncKeyState('W') & 0x8000)
		{
			poss.x += cosf(rot) * speed;
			poss.y += sinf(rot) * speed;
		}
		if (GetAsyncKeyState('S') & 0x8000) {
			poss.x += cosf(rot) * -speed;
			poss.y += sinf(rot) * -speed;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			poss.x += cosf(rot + 1.7079) * speed;
			poss.y += sinf(rot + 1.7079) * speed;
		}
		if (GetAsyncKeyState('A') & 0x8000) {
			poss.x += cosf(rot + 1.7079) * -speed;
			poss.y += sinf(rot + 1.7079) * -speed;
		}


		if (poss.x != 0 || poss.y != 0)
		{
			bool able = true;
			for (int i = 0; i < GameObjs.size(); i++)
			{
				if (Raycasting(GameObjs[i], Obj(Playerpos, Vector2(Playerpos.x + poss.x * 2, Playerpos.y + poss.y * 2))).able)
				{
					able = false;
					break;
				}
			}
			if (able)
			{
				Playerpos.x += poss.x;
				Playerpos.y += poss.y;
			}
			else
			{

			}
		}
		//if (GetAsyncKeyState('Q') & 0x8000) {
		//	rot -= 0.01f;
		//}
		//if (GetAsyncKeyState('E') & 0x8000) {
		//	rot += 0.01f;
		//}

		//Sleep(10);
		POINT p;
		if (GetCursorPos(&p))
		{
			rot += (p.x - 500.0) / 1000.0;

			TMPMousePos = p;

			SetCursorPos(500, 500);
			//p.y - TMPMousePos.y;
		}


		/*if (_kbhit())
		{
			char a = _getch();
			if (a =='w')
			{
			poss.x += cos(rot) * 0.01f;
			poss.y += sin(rot)*0.01f;
			}
			if((a=='s'))
			{
				poss.x += cos(rot) * -0.01f;
				poss.y += sin(rot) * -0.01f;
			}
			if (a == 'a')
			{
				poss.x += cos(rot+1.7079) * -0.01f;
				poss.y += sin(rot+1.7079) * -0.01f;
			}
			if ((a == 'd'))
			{
				poss.x += cos(rot+ 1.7079) * 0.01f;
				poss.y += sin(rot+ 1.7079) * 0.01f;
			}
			if (a == 'q')
			{

			}
			if (a == 'e')
			{

			}
		}*/

	}
	return 0;
}