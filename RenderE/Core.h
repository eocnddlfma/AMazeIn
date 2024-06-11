#pragma once
#define FOV 140
#define RESOLUTION 660

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