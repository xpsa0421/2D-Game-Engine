#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#define EPSILON 0.001f

class Vector2
{
public:
	float x;
	float y;
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& v);
public:
	float	LengthSquared();
	float	Length();
	void	Normalise();
public:
	Vector2	operator +  (Vector2& v);
	Vector2	operator -  (Vector2& v);
	Vector2	operator *  (float scala);
	Vector2	operator /  (float scala);
	Vector2	operator += (Vector2 v);
	//Vector2	operator += (Vector2& v);
	Vector2	operator -= (Vector2& v);
	Vector2	operator *= (float scala);
	bool	operator == (Vector2& v);
	bool	operator <= (Vector2& v);
	bool	operator >= (Vector2& v);
};

class Vector3
{
public:
	float x;
	float y;
	float z;
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);
public:
	float	LengthSquared();
	float	Length();
	void	Normalise();
public:
	Vector3	operator +  (Vector3& v);
	Vector3	operator -  (Vector3& v);
	Vector3	operator *  (float scala);
	Vector3	operator /  (float scala);
	Vector3	operator *= (float scala);
	Vector3	operator += (Vector3& v);
	Vector3	operator -= (Vector3& v);
	bool	operator == (Vector3& v);
	bool	operator <= (Vector3& v);
	bool	operator >= (Vector3& v);
};

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& v);
public:
	float	LengthSquared();
	float	Length();
	void	Normalise();
public:
	Vector4	operator +  (Vector4& v);
	Vector4	operator -  (Vector4& v);
	Vector4	operator *  (float scala);
	Vector4	operator /  (float scala);
	Vector4	operator *= (float scala);
	Vector4	operator += (Vector4& v);
	Vector4	operator -= (Vector4& v);
	bool	operator == (Vector4& v);
	bool	operator <= (Vector4& v);
	bool	operator >= (Vector4& v);
};
