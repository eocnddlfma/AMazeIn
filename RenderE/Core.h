#pragma once
//#define FOV 200
//#define RESOLUTION 1080
//#define SCREEN_HEIGHT 75

static int FOV = 200, RESOLUTION = 1080, SCREEN_HEIGHT = 100;
static float PLUSHEIGHT = 0;

#include<iostream>
#include "Windows.h"
#include"conio.h"
#include<vector>
#include<string>
#include<algorithm>
#include "DataStructure.h"

void SetColor(int _textcolor, int _bgcolor);
void Gotoxy(int x, int y);
float VDistace(Vector2 a, Vector2 b);
Vector2 Raycasting(Obj gm, Obj ray);