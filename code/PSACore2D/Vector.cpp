#include "Vector.h"

//-------------------------------------------------
// member functions of Vector2
Vector2::Vector2()
{
	x = y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
}

float Vector2::LengthSquared()
{
	return (x * x + y * y);
}

float Vector2::Length()
{
	return sqrt(LengthSquared());
}

void Vector2::Normalise()
{
	float inverseLength = 1.0f / Length();
	x = x * inverseLength;
	y = y * inverseLength;
}

Vector2 Vector2::operator + (Vector2& v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (Vector2& v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator * (float scala)
{
	return Vector2(x * scala, y * scala);
}

Vector2 Vector2::operator / (float scala)
{
	return Vector2(x / scala, y / scala);
}

Vector2 Vector2::operator += (Vector2 v)
{
	x += v.x;
	y += v.y;
	return *this;
}

//Vector2 Vector2::operator += (Vector2& v)
//{
//	x += v.x;
//	y += v.y;
//	return *this;
//}


Vector2 Vector2::operator -= (Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	return *this;
}

bool Vector2::operator == (Vector2& v)
{
	if ((fabs(x - v.x) < EPSILON)
		&& (fabs(y - v.y) < EPSILON))
	{
		return true;
	}
	return false;
}

bool Vector2::operator <= (Vector2& v)
{
	if ((x <= v.x) && (y <= v.y)) return true;
	return false;
}

bool Vector2::operator >= (Vector2& v)
{
	if ((x >= v.x) && (y >= v.y)) return true;
	return false;
}


//-------------------------------------------------
// member functions of Vector3
Vector3::Vector3()
{
	x = y = z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

float Vector3::LengthSquared()
{
	return (x * x + y * y + z * z);
}

float Vector3::Length()
{
	return sqrt(LengthSquared());
}

void Vector3::Normalise()
{
	float inverseLength = 1.0f / Length();
	x = x * inverseLength;
	y = y * inverseLength;
	z = z * inverseLength;
}

Vector3 Vector3::operator + (Vector3& v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator - (Vector3& v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator * (float scala)
{
	return Vector3(x * scala, y * scala, z * scala);
}

Vector3 Vector3::operator / (float scala)
{
	return Vector3(x / scala, y / scala, z / scala);
}

Vector3 Vector3::operator += (Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator -= (Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	return *this;
}

bool Vector3::operator == (Vector3& v)
{
	if ((fabs(x - v.x) < EPSILON)
		&& (fabs(y - v.y) < EPSILON)
		&& (fabs(z - v.z) < EPSILON))
	{
		return true;
	}
	return false;
}

bool Vector3::operator <= (Vector3& v)
{
	if ((x <= v.x) && (y <= v.y) && (z <= v.z)) return true;
	return false;
}

bool Vector3::operator >= (Vector3& v)
{
	if ((x >= v.x) && (y >= v.y) && (z >= v.z)) return true;
	return false;
}


//-------------------------------------------------
// member functions of Vector4
Vector4::Vector4()
{
	x = y = z = w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(const Vector4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

float Vector4::LengthSquared()
{
	return (x * x + y * y + z * z + w * w);
}

float Vector4::Length()
{
	return sqrt(LengthSquared());
}

void Vector4::Normalise()
{
	float inverseLength = 1.0f / Length();
	x = x * inverseLength;
	y = y * inverseLength;
	z = z * inverseLength;
	w = w * inverseLength;
}

Vector4 Vector4::operator + (Vector4& v)
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator - (Vector4& v)
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator * (float scala)
{
	return Vector4(x * scala, y * scala, z * scala, w * scala);
}

Vector4 Vector4::operator / (float scala)
{
	return Vector4(x / scala, y / scala, z / scala, w / scala);
}

Vector4 Vector4::operator += (Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4 Vector4::operator -= (Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4 Vector4::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	w *= scala;
	return *this;
}

bool Vector4::operator == (Vector4& v)
{
	if ((fabs(x - v.x) < EPSILON)
		&& (fabs(y - v.y) < EPSILON)
		&& (fabs(z - v.z) < EPSILON)
		&& (fabs(w - v.w) < EPSILON))
	{
		return true;
	}
	return false;
}

bool Vector4::operator <= (Vector4& v)
{
	if ((x <= v.x) && (y <= v.y) && (z <= v.z) && (w <= v.w)) return true;
	return false;
}

bool Vector4::operator >= (Vector4& v)
{
	if ((x >= v.x) && (y >= v.y) && (z >= v.z) && (w >= v.w)) return true;
	return false;
}