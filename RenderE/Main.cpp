#include<iostream>
#include "Windows.h"
#include"conio.h"
#include<vector>
#include<string>
#include<algorithm>

#include "DataStructure.h"
#include "Render.h"
#include "mapinitializer.h"
#include "EnemyGenerator.h"

using namespace std;

#
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
vector<Obj> MapObjs;
vector<Billboard*>BillBoardss;
vector<Billboard*>MovingBillboards;
vector<Enemy*>EnemyList;
char Pixels[8] = { '@','#','X','x','+','*','^',' ' };
char PixelsGround[15] = { '~','-','-','-',',',',',',','.','.','.','.','.','.',' ',' ' };
string colors[9] = { bold,red,blue,yellow,purple, cyan ,green,black,white};

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

void Input(Vector2* poss, Vector2* Playerpos, float rot, float speed)
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		poss->x += cosf(rot) * speed;
		poss->y += sinf(rot) * speed;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		poss->x += cosf(rot) * -speed;
		poss->y += sinf(rot) * -speed;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		poss->x += cosf(rot + 1.7079) * speed;
		poss->y += sinf(rot + 1.7079) * speed;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		poss->x += cosf(rot + 1.7079) * -speed;
		poss->y += sinf(rot + 1.7079) * -speed;
	}

	if (_kbhit())
	{
		char a = _getch();
		if (a == 'f')
		{
			Billboard* ming = new Billboard(*Playerpos, 0.4f, Vector2(cosf(rot), sinf(rot)), 2, OBJ_TYPE::ENEMY);
			BillBoardss.push_back(ming);
			MovingBillboards.push_back(ming);
		}
		if (a == 'g')
		{
			//GenerateEnemy(MapObjs[0], MapObjs[0].start, 1, EnemyList);
			/*Enemy enemy(Billboard(Playerpos, 0.4f, Vector2(cosf(rot), sinf(rot)), 0.4, 3), 5, 1);
			BillBoardss.push_back(enemy.render);
			EnemyList.push_back(&enemy);*/
		}
	}
}

void Render(const int fov, Vector2 player, float rot, int resol)
{
	float** horizontal = new float*[3];
	float* horizontal2 = new float[fov * 2] { 999, };
	float** horizontaltx = new float* [3];
	ObjLayer* las = new ObjLayer[fov * 2];
	
	for (int i = 0; i < 3; i++) {
		horizontal[i] = new float[fov * 2]{999, };
		horizontaltx[i] = new float[fov * 2] {0, };
		//
		for (int j = 0; j < fov * 2; j++)
		{
			horizontal[i][j] = 999;
			horizontaltx[i][j] = 0-i;
		}
	}
	//CONSOLE_SCREEN_BUFFER_INFO info;
	//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		//, &info);


	string output2[ScreenHeight];
	int **outputColor = new int*[ScreenHeight];
	for (int j = 0; j < 75; j++)
	{
		outputColor[j] = new int[fov*2];
		for (int i = 0; i < fov * 2; i++)
		{
			outputColor[j][i] = 0;
			output2[j] += " ";
		}
		//output += "/n";
	}

	renderObjs(FOV, GameObjs, horizontal, horizontaltx, player, las, rot);
	
	renderBillBoards(FOV, BillBoardss, horizontal, horizontaltx, player, las, rot);

	for (int ii = 0; ii < 75; ii++)
	{
		for (int z = 0; z < fov * 2; z++)
		{

			//output[j].push_back(' ');
			//output[j][ii + fov]='#';
			//output[ii,48 - j] = '0' + ((int)horizontal[ii] < 9 ? (int)horizontal[ii] : 9);
			if (output2[ii][z] == ' ')//비어있는지
			{
				if (ii >= horizontal[1][z] / 2 && ii <= 75 - horizontal[1][z] / 2)//하늘이랑 땅 제한
				{
					//float size = ((int)horizontal[1][z] / 2 - (75 - (int)horizontal[1][z] / 2));


						if (horizontaltx[1][z] < 0)//0보다 작으면 0으로
						{
							outputColor[ii][z] = 0;
						}
						else if (75 > horizontal[1][z] / 2)//0보다 크면 인트로 바꿔서 해당 텍스쳐 가져오기
						{
							outputColor[ii][z] = GetTextureByNumber(3)[(int)(horizontaltx[1][z] * 14)][(int)(((ii-horizontal[1][z]/2) / (75 - horizontal[1][z] / 2)) * 14)];

						}

						if (outputColor[ii][z] == 0)//0이면 비어있게 놔두기
						{
							output2[ii][z] = ' ';
							continue;
						}

						if ((int)(horizontal[1][z] / 5 / 2) < 7) {// 거리 계산

							output2[ii][z] = Pixels[(int)(horizontal[1][z] / 2 / 10)];//7보다 가까우면 가까움 표시
						}
						else
						{
							output2[ii][z] = Pixels[6];//그보다 멀면 빈 표시
						}
						//output2[ii].insert(ii, reset);
				//if (las[ii] == ObjLayer::Bill)
				//{
				//	output += reset;
				//}

				}
				//output += '\n';
			}
		}
	}
	//여기까지 승현이가 방금짬
	
	for (int j = 0; j < 75; j++)
	{
		for (int z = 0; z < fov * 2; z++)
		{

			//output[j].push_back(' ');
			//output[j][ii + fov]='#';
			//output[ii,48 - j] = '0' + ((int)horizontal[ii] < 9 ? (int)horizontal[ii] : 9);
			if (output2[j][z] == ' ')
			{
				if (j >= horizontal[0][z] / 2 && j <= 75 - horizontal[0][z] / 2)
				{
					//if (las[ii] == ObjLayer::Bill)
					//{
					//	output += red;
					//}

					//float size = ((int)horizontal[z] / 2 - (75 - (int)horizontal[z] / 2));

					if (75 - horizontal[0][j] / 2 > 0)
						outputColor[j][z] = GetTextureByNumber(1)[(int)(horizontaltx[0][z] * 14)][(int)fabs((j - horizontal[0][z] / 2) / ((75 - horizontal[0][z])) * 14)];
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

	Gotoxy(0, 0);
	string output = "";
	for(int i =0; i<75; i++)
	{
		for (int j = 0; j < fov * 2; j++)
		{
			output += colors[outputColor[i][j]];
			output +=output2[i][j];
			output += reset;
		}
		output += '\n';
	}
	//cout << output;
	//cout << "\n" << player.x << " " << player.y;
	//output.clear();
	
	for (int i = 0; i < 3; i++) {
		delete[] horizontal[i];
	}
	delete horizontal;
}

void Update(Vector2* Playerpos, Vector2* poss, float rot) {
	for (int i = 0; i < MovingBillboards.size(); i++) {
		MovingBillboards[i]->pos.x += MovingBillboards[i]->dir.x * MovingBillboards[i]->speed;
		MovingBillboards[i]->pos.y += MovingBillboards[i]->dir.y * MovingBillboards[i]->speed;
	}
	//적 이동 방향 확인후 이동하는 스크립트
	for (int i = 0; i < EnemyList.size(); i++) {
		Vector2 direction = (*Playerpos - EnemyList[i]->render.pos);
		int distance = direction.Distance();
		direction = Vector2(direction.x / direction.Distance(), direction.y / direction.Distance());
		EnemyList[i]->render.dir = Vector2(direction.x, direction.y);
		Obj ray1 = Raycasting(Obj(EnemyList[i]->render.pos, EnemyList[i]->render.pos + EnemyList[i]->render.dir),
			Obj(Vector2(Playerpos->x, Playerpos->y), Vector2(Playerpos->x + rot, Playerpos->y + rot)));
		if (ray1.able) {
			EnemyList[i]->render.pos.x += EnemyList[i]->render.dir.x * EnemyList[i]->render.speed;
			EnemyList[i]->render.pos.y += EnemyList[i]->render.dir.y * EnemyList[i]->render.speed;
		}
		else {
			//적과 닿음.
		}
	}

	if (poss->x != 0 || poss->y != 0)
	{
		bool able = true;
		for (int i = 0; i < GameObjs.size(); i++)
		{
			if (Raycasting(GameObjs[i], Obj(*Playerpos, Vector2(Playerpos->x + poss->x * 2, Playerpos->y + poss->y * 2))).able)
			{
				able = false;
				break;
			}
		}
		for (int i = 0; i < BillBoardss.size(); i++)
		{
			Obj Billbod = BillBoardss[i]->ConvertObj(rot);
			if (Raycasting(Billbod, Obj(*Playerpos,
				Vector2(Playerpos->x + poss->x * 2, Playerpos->y + poss->y * 2),
				ObjLayer::Bill)).able)
			{
				able = false;
				break;
			}
		}
		if (able)
		{
			Playerpos->x += poss->x;
			Playerpos->y += poss->y;
		}
	}
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
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	SetMap(&MapObjs);
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

	for (int i = 0; i < MapObjs.size(); i++)
	{
		GameObjs.push_back(MapObjs[i]);
	}

	//BillBoardss.push_back(Billboard(Vector2(3,3),2));
	//BillBoardss.push_back(Billboard(Vector2(7, 7), 2));
	//BillBoardss.push_back(Billboard(Vector2(-3, -3), 1));
	float speedOrigin = 15;
	int fov = FOV;
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

		POINT p;
		if (GetCursorPos(&p))
		{
			rot += (p.x - 500.0) / 1000.0;
			TMPMousePos = p;
			SetCursorPos(500, 500);
		}


		Input(&poss, &Playerpos, rot, speed);
		Update(&Playerpos, &poss, rot);
		Render(fov, Playerpos, rot, resol);



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