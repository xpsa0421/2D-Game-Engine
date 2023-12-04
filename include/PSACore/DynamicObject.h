#pragma once
#include "BaseObject.h"

class DynamicObject : public BaseObject
{
public:
	Vector2		_dir		= { 0,0 };
	float		_speed		= 100.0f;
	float		_gravity	= 1.0f;
public:
	virtual void	SetSpeed(float speed);
	virtual void	SetDirection(Vector2 dir);
};

