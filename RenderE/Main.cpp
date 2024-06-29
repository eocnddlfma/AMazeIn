#include<iostream>
#include "Windows.h"
#include"conio.h"
#include<vector>
#include<string>
#include<algorithm>

#include "DataStructure.h"
#include "Render.h"
#include "Core.h"
#include "mapinitializer.h"
#include "ConsoleDoubleBuffer.h"
#include "TitleScene.h"

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


vector<Obj> GameObjs;
vector<Billboard*>BillBoardss;
vector<Billboard*>MovingBillboards;
vector<Billboard*>EnemyBillboards;
char Pixels[8] = { '@','#','X','x','+','*','^',' ' };
char PixelsGround[15] = { '~','~','-','-',',',',','.',' ','.',',',',','-','-','~','~' };
string colors[9] = { bold,red,blue,yellow,purple, cyan ,green,black,white};

#define TextureNum 3

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

int Enemy[15][15]=
{ 
{0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,0,1,0,0,0,0,0,0,0,0},
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
{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0}
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
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
};

int BillTXS[3][15][15] =
{
{
{0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,0,1,0,0,0,0,0,0,0,0},
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
{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0}
},
{
{0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
{0,0,0,1,1,0,1,0,0,0,0,0,0,0,0},
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
{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0}
},
{
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,3,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,3,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,3,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,3,1,1,0,0,0,0,0},
{0,0,0,0,1,3,3,3,1,3,1,0,0,0,0},
{0,0,0,0,1,3,3,3,1,3,1,3,0,0,0},
{0,0,0,0,1,3,3,3,1,3,1,0,3,0,0},
{0,0,0,0,1,3,3,3,3,3,1,0,0,0,0},
{0,0,0,0,0,3,3,3,3,1,0,0,0,0,0},
{0,0,3,0,0,1,3,3,3,1,0,0,3,0,0},
{0,0,0,0,0,1,3,3,3,1,0,0,0,0,0},
{0,0,3,0,0,1,1,3,1,1,0,3,0,0,0},
{0,0,0,0,0,0,1,3,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
}
};
int(*GetTextureByNumber(int num))[15]
	{
		switch (num)
		{
		case 1:
			return ming;
			break;
		case 2:
			return Enemy;
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

void Renderer(const int fov, Vector2 player, float rot, int resol, int playerhp)
{
	float** horizontal = new float*[3];
	float* horizontal2 = new float[fov * 2] { 999, };
	float** horizontaltx = new float* [3];
	int* horizontaltxType = new int [fov * 2] {0};
	float** horizontalTextureNum = new float* [TextureNum + 1];
	ObjLayer* las = new ObjLayer[fov * 2];
	
	for (int i = 0; i < 3; i++) {
		horizontal[i] = new float[fov * 2]{999, };
		horizontaltx[i] = new float[fov * 2] {0, };
		//
		for (int j = 0; j < fov * 2; j++)
		{
			horizontal[i][j] = 999;
			horizontaltx[i][j] = 0-i;
			horizontalTextureNum = 0;
		}
	}
	//CONSOLE_SCREEN_BUFFER_INFO info;
	//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		//, &info);


	vector<string> output2(SCREEN_HEIGHT);
	int **outputColor = new int*[SCREEN_HEIGHT];
	for (int j = 0; j < SCREEN_HEIGHT; j++)
	{
		outputColor[j] = new int[fov*2];
		for (int i = 0; i < fov * 2; i++)
		{
			outputColor[j][i] = 0;
			output2[j] += " ";
		}
	}
	//output2 =

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < playerhp * 10; j++) {
			output2[i + 8][j + 8] = 'H';
		}
	}


	renderObjs(FOV, GameObjs, horizontal, horizontaltx, player, las, rot);

	renderBillBoards(FOV, BillBoardss, horizontal, horizontaltx, player, las, rot,horizontaltxType);

	for (int ii = 0; ii < SCREEN_HEIGHT; ii++)
	{
		for (int z = 0; z < fov * 2; z++)
		{

			//output[j].push_back(' ');
			//output[j][ii + fov]='#';
			//output[ii,48 - j] = '0' + ((int)horizontal[ii] < 9 ? (int)horizontal[ii] : 9);
			if (output2[ii][z] == ' ')
			{
				if (ii >= horizontal[1][z] / 2 && ii <= SCREEN_HEIGHT - horizontal[1][z] / 2)
				{
					//float size = ((int)horizontal[1][z] / 2 - (75 - (int)horizontal[1][z] / 2));

					if (ii >= horizontal[1][z] / 2 && ii <= SCREEN_HEIGHT - horizontal[1][z] / 2)
					{
						//float size = ((int)horizontal[1][z] / 2 - (75 - (int)horizontal[1][z] / 2));



						if (horizontaltx[1][z] < 0)
						{
							outputColor[ii][z] = 0;
						}
						else if (SCREEN_HEIGHT > horizontal[1][z] / 2)
						{
							
							outputColor[ii][z] = BillTXS[horizontaltxType[z]][(int)(horizontaltx[1][z] * 14)][(int)(((ii-horizontal[1][z]/2) / (SCREEN_HEIGHT - horizontal[1][z] / 2)) * 14)];

						}

						if (outputColor[ii][z] == 0)
						{
							output2[ii][z] = ' ';
							continue;
						}

						if ((int)(horizontal[1][z] / 5 / 2) < 7) {

							output2[ii][z] = Pixels[(int)(horizontal[1][z] / 2 / 10)];
						}
						else
						{
							output2[ii][z] = Pixels[6];
						}
						//output2[ii].insert(ii, reset);
				//if (las[ii] == ObjLayer::Bill)
				//{
				//	output += reset;
				//}
					}


				}
				//output += '\n';
			}
		}
	}
	//여기까지 승현이가 방금짬
	Gotoxy(0, 0);
	for (int j = 0; j < SCREEN_HEIGHT; j++)
	{
		for (int z = 0; z < fov * 2; z++)
		{

			//output[j].push_back(' ');
			//output[j][ii + fov]='#';
			//output[ii,48 - j] = '0' + ((int)horizontal[ii] < 9 ? (int)horizontal[ii] : 9);
			if (output2[j][z] == ' ')
			{
				if (j >= horizontal[0][z] / 2 && j <= SCREEN_HEIGHT - horizontal[0][z] / 2)
				{
					//if (las[ii] == ObjLayer::Bill)
					//{
					//	output += red;
					//}

					//float size = ((int)horizontal[z] / 2 - (75 - (int)horizontal[z] / 2));

					if (SCREEN_HEIGHT - horizontal[0][j] / 2 > 0)
						outputColor[j][z] = ming[(int)(horizontaltx[0][z] * 14)][(int)fabs((j - horizontal[0][z] / 2) / ((SCREEN_HEIGHT - horizontal[0][z])) * 14)];
					else
						outputColor[j][z] = 0;
					//output2[ii].insert(ii,colors[ming[(int)(horizontaltx[0][ii] * 14)][(int)fabs((j - horizontal[0][ii]/2) / ((75 - horizontal[0][ii]/2 * 2)) * 14)]]);//(int)((55 - j)/15*horizontaltx[ii])

					if ((int)(horizontal[0][z] / 10) < 7) {

						output2[j][z] = Pixels[(int)(horizontal[0][z] /10)];
					}
					else
					{
						output2[j][z] = Pixels[6];
					}
					//output += reset;
					//if (las[ii] == ObjLayer::Bill)
					//{
					//	output += reset;
					//}
				}
				else
				{
					output2[j][z] = PixelsGround[j / 5];
				}
			}
		}
	}

	string output = "";
	for(int i =PLUSHEIGHT; i< SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < fov * 2; j++)
		{
			output += colors[outputColor[i][j]];
			output +=output2[i][j];
			output += reset;
		}
		output += '\n';
	}
	//RenderConsole(output);
	//cout << output;
	//output.clear();
	PrintConsoleBuffer(0, 0, output);
	FlipConsoleBuffer();
	for (int i = 0; i < 3; i++) {
		delete[] horizontal[i];
	}
	delete horizontal;
}

void Update() {

}

int main()
{
	StartTitle();

	system("mode con: cols=960 lines=540");

		ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 4;                   // Width of each character in the font
	cfi.dwFontSize.Y = 4;                  // Height
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	InitConsoleBuffer();
	//HWND console = GetConsoleWindow();
	//LONG style = GetWindowLong(console, GWL_STYLE);

	//style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;// &~WS_HSCROLL;// &~WS_CAPTION;
	//SetWindowLong(console, GWL_STYLE, style);

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15<<4)|0);

	//CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	//cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	//SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);



	vector<Obj> GameObjss;
	SetMap(&GameObjss);

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
		GameObjs.push_back(GameObjss[i]);
	}

	float speedOrigin = 15;
	int fov = FOV,playerHP=5;
	int resol = 660;
	float rot = 0, speed = 0;
	Vector2 Playerpos = Vector2(0, 0);
	POINT TMPMousePos = { 0,0 };
	float deltaTime = 0;
	LARGE_INTEGER Current, last, MING;
	QueryPerformanceCounter(&Current);
	QueryPerformanceFrequency(&MING);
	last = Current;
	InitConsoleBuffer();
	while (true)
	{
		QueryPerformanceCounter(&Current);
		deltaTime = (float)(Current.QuadPart - last.QuadPart) / static_cast<float>(MING.QuadPart);
		last = Current;
		speed = speedOrigin * deltaTime;
		Vector2 poss = Vector2(0, 0);
		if (rot > 2 * 3.141592) {
			rot = 0;
		}
		else
		if (rot < 0) 
		{
			rot = 2 * 3.141591;
		}

		Renderer(fov, Playerpos, rot, resol,playerHP);
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

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			poss.x += cosf(rot) * speed / 2;
			poss.y += sinf(rot) * speed / 2;
			poss.x *= 4;
			poss.y *= 4;
			if (PLUSHEIGHT < 13)
				PLUSHEIGHT += 8;
		}
		else
		{
			if (PLUSHEIGHT > 0.01f)
			{
				PLUSHEIGHT -= 2;
				if (PLUSHEIGHT < 0) {
					PLUSHEIGHT = 0;
				}
			}

			if (poss.Distance() > 0) {
				if (PLUSHEIGHT < 3)
					PLUSHEIGHT += 1;
			}
		}
		if (_kbhit())
		{
			char a = _getch();
			if (a == 'f')
			{
				Billboard* ming = new Billboard(Playerpos, 0.4, Vector2(cosf(rot), sinf(rot)), 10,2);
				BillBoardss.push_back(ming);
				MovingBillboards.push_back(ming);

				for (int i = 0; i < EnemyBillboards.size(); i++) {
					if (Raycasting(EnemyBillboards[i]->ConvertObj(rot), Obj(Vector2(Playerpos.x, Playerpos.y), Vector2(Playerpos.x + cosf(rot) * 300, Playerpos.y + sinf(rot) * 300))).able) 
					{
						BillBoardss.erase(find(BillBoardss.begin(), BillBoardss.end(), EnemyBillboards[i]));
						MovingBillboards.erase(find(MovingBillboards.begin(), MovingBillboards.end(), EnemyBillboards[i]));
						Billboard* ming = EnemyBillboards[i];
						EnemyBillboards.erase(EnemyBillboards.begin() + i);
						delete ming;
					}
				}

			}
			if (a == 'g')
			{
				Billboard* enemy = new Billboard(Vector2(Playerpos.x + 10,Playerpos.y+10), 2, Vector2(),0.6, 1);
				BillBoardss.push_back(enemy);
				MovingBillboards.push_back(enemy);
				EnemyBillboards.push_back(enemy);
			}
		}

		for (int i = 0; i < MovingBillboards.size(); i++) {
			MovingBillboards[i]->pos.x += MovingBillboards[i]->dir.x * MovingBillboards[i]->speed;
			MovingBillboards[i]->pos.y += MovingBillboards[i]->dir.y * MovingBillboards[i]->speed;

		}

		for (int i = 0; i < EnemyBillboards.size(); i++) {
			EnemyBillboards[i]->dir = Vector2(Playerpos.x - EnemyBillboards[i]->pos.x, Playerpos.y - EnemyBillboards[i]->pos.y).Normalized();
			if (VDistace(EnemyBillboards[i]->pos, Playerpos) < 0.8)
			{
				playerHP--;
				
				BillBoardss.erase(find(BillBoardss.begin(), BillBoardss.end(), EnemyBillboards[i]));
				MovingBillboards.erase(find(MovingBillboards.begin(), MovingBillboards.end(), EnemyBillboards[i]));
				Billboard* ming = EnemyBillboards[i];
				EnemyBillboards.erase(EnemyBillboards.begin() + i);
				delete ming;
			}
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
			for (int i = 0; i < BillBoardss.size(); i++)
			{
				Obj Billbod = BillBoardss[i]->ConvertObj(rot);
				if (Raycasting(Billbod, Obj(Playerpos, Vector2(Playerpos.x + poss.x * 2, Playerpos.y + poss.y * 2))).able)
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
		POINT p;
		if (GetCursorPos(&p))
		{
			rot += (p.x - 500.0) / 1000.0;
			TMPMousePos = p;
			SetCursorPos(500, 500);
		}
	}
	return 0;
}