#pragma once
#include<vector>
using std::vector;

enum class OBJ_TYPE {
	WALL, KEY, DOOR, ENEMY, FORRAYCASTING
};

std::string ObjectTypeToString(OBJ_TYPE type)
{
	switch (type)
	{
	case OBJ_TYPE::WALL:
		return "WALL";
		break;
	case OBJ_TYPE::KEY:
		return "KEY";
		break;
	case OBJ_TYPE::DOOR:
		return "DOOR";
		break;
	case OBJ_TYPE::ENEMY:
		return "ENEMY";
		break;
	case OBJ_TYPE::FORRAYCASTING:
		return "FORRAYCASTING";
		break;
	default:
		break;
	}
}
enum ObjLayer {
	Stru,
	Bill
};

struct Vector2 {
public:
	float x = 0; float y = 0;
	bool able;
	Vector2(float x1, float y1, bool able = false) {
		x = x1; y = y1; this->able = able;
	}

	Vector2() {
		x = 0; y = 0; able = false;
	}

	float Distance()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 operator+(const Vector2 v)
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(const Vector2 v)
	{
		float bigx, smallx;
		float bigy, smally;

		if (v.x > x) {
			bigx = v.x;
			smallx = x;
		}
		else {
			bigx = x;
			smallx = v.x;
		}
		if (v.y > y) {
			bigy = v.y;
			smally = y;
		}
		else {
			bigy = y;
			smally = v.y;
		}


		return Vector2(bigx - smallx, bigy - smally);
	}
};

struct Obj {
public:
	Vector2 start;
	Vector2 end;
	bool able;
	ObjLayer la;
	int textureNum;
	OBJ_TYPE ObjType;

	Obj(Vector2 start1, Vector2 end1, int textureNum=0, ObjLayer laa = ObjLayer::Stru, OBJ_TYPE type = OBJ_TYPE::FORRAYCASTING) {
		start = start1;
		end = end1;
		la = laa;
		this->textureNum = textureNum;
		ObjType = type;
	};
	Obj() {};

	Vector2 ConvertVector2() {
		return Vector2((start.x + end.x) / 2, (start.y + end.y) / 2);
	}
};

class Billboard {
public:
	Vector2 pos;
	float size;
	Vector2 dir;
	float speed;
	int textureNum;
	OBJ_TYPE ObjType;

	Billboard(Vector2 po, float si, Vector2 direction, float speed, OBJ_TYPE type, int texture = 2)
	{
		pos = po;
		size = si;
		dir = direction;
		this->speed = speed;
		ObjType = type;
		textureNum = texture;
	};
	Billboard() {};

	Obj ConvertObj(float rot) {
		return Obj(Vector2(pos.x + cos(rot + 1.7079) * size, pos.y + sin(rot + 1.7079) * size),
			Vector2(pos.x + cos(rot - 1.7079) * size, pos.y + sin(rot - 1.7079) * size),
			textureNum, ObjLayer::Bill,  ObjType);
	}

	void DeleteThis()
	{
		delete this;
	}
};

class Enemy {
public:
	Billboard render;
	int currentHp;
	int maxHp;
	float attackCooltime;
	float currentattacktime;

	Enemy(Billboard billboard, int maxhp, float attackcooltime)
	{
		render = billboard;
		maxHp = maxhp;
		currentHp = maxhp;
		attackCooltime = attackcooltime;
	}


};