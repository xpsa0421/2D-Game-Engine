#pragma once
#include "Std.h"

class Camera
{
public:
	Vector2 _pos = { 0,0 };
	Vector2 _size;
	float	_minX = 0.0f;
	float	_maxX = 0.0f; //  ÀüÃ¼ world width - screen width
	float	_minY = 0.0f;
	float	_maxY = 0.0f;
public:
	void	SetPosition(Vector2 pos);
	void	SetSize(Vector2 size);
	void	SetLimit(float minX, float maxX, float minY, float maxY);
	void	AdjustPos(Vector2 playerPos);
};
