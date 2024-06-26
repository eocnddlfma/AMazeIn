#pragma once
#define FOV 140
#define RESOLUTION 660
#define ScreenHeight 75

#include "DataStructure.h"

void SetColor(int _textcolor, int _bgcolor);
void Gotoxy(int x, int y);
float VDistace(Vector2 a, Vector2 b);
std::string ObjTypeToString(OBJ_TYPE type);
Obj Raycasting(Obj gm, Obj ray);
int(*GetTextureByNumber(int num))[15];
int** LineToMap(Vector2 playerPos, vector<Obj> Objs, int width, int height);