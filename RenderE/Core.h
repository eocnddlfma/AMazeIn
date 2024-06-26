#pragma once
#define FOV 150
#define RESOLUTION 1080
#define SCREEN_HEIGHT 50

#include "DataStructure.h"

void SetColor(int _textcolor, int _bgcolor);
void Gotoxy(int x, int y);
float VDistace(Vector2 a, Vector2 b);
std::string ObjTypeToString(OBJ_TYPE type);
Obj Raycasting(Obj gm, Obj ray);
int(*GetTextureByNumber(int num))[15];
int GetAllCollisions(vector<Obj> Objs, Obj Line, vector<Obj>* collidedObjList);
void LineToMap(Vector2 playerPos, vector<Obj> Objs, int startX, int startY, int width, int height, OBJ_TYPE** targetMap);
