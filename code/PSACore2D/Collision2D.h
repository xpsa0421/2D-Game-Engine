#pragma once
#include <vector>
#include "Vector.h"

enum CollisionType2D
{
	RECT_OUT,
	RECT_IN,
	RECT_OVERLAP,
};

struct Circle
{
	float cx, cy;
	float r;
	Circle() 
	{
		cx = cy = r = 0.0f;
	};
	Circle(float x, float y, float r)
	{
		cx = x;
		cy = y;
		this->r  = r;
	}

	void Set(float cx, float cy, float w, float h)
	{
		this->cx = cx;
		this->cy = cy;
		float x = w / 2.0f;
		float y = h / 2.0f;
		this->r = sqrt(x * x + y * y);
	}

	void Set(Vector2 pos, Vector2 size)
	{
		Set(pos.x, pos.y, size.x, size.y);
	}
};

struct Rect
{
	float x1, x2, y1, y2;
	float w, h;
	float cx, cy;

	bool operator == (Rect& rect)
	{
		if ((fabs(x1 - rect.x1) < EPSILON)
			&& (fabs(y1 - rect.y1) < EPSILON)
			&& (fabs(w - rect.w) < EPSILON)
			&& (fabs(h - rect.h) < EPSILON))
		{
			return true;
		}
		return false;
	}

	Rect()
	{
		x1 = x2 = y1 = y2 = w = h = cx = cy = 0.0f;
	}

	Rect(float x, float y, float w, float h)
	{
		Set(x, y, w, h);
	}

	void Set(float x, float y, float w, float h)
	{
		x1 = x;
		x2 = x + w;
		y1 = y;
		y2 = y + h;
		this->w = w;
		this->h = h;
		cx = (x + x2) / 2.0f;
		cy = (y + y2) / 2.0f;
	}

	void SetFromBottomCentre(float bc_x, float bc_y, float w, float h)
	{
		x1 = bc_x - w / 2.0f;
		x2 = x1 + w;
		y1 = bc_y - h;
		y2 = bc_y;
		this->w = w;
		this->h = h;
		cx = (x1 + x2) / 2.0f;
		cy = (x2 + y2) / 2.0f;
	}

	void Set(Vector2 pos, Vector2 size)
	{
		Set(pos.x, pos.y, size.x, size.y);
	}
};

class Collision2D
{
public:
	static CollisionType2D  RectToRect(Rect& a, Rect& b);
	static bool             RectToInRect(Rect& a, Rect& b);
	static bool             CircleToCircle(Circle& a, Circle& b);
	static bool				RectToPoint(Rect& a, POINT& p);
};

static Rect ConvertRect(RECT rt)
{
	Rect tRt;
	tRt.x1 = rt.left;
	tRt.y1 = rt.top;
	tRt.w = rt.right;
	tRt.h = rt.bottom;
	return tRt;
}