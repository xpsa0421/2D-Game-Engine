#include "Camera.h"

void Camera::SetPosition(Vector2 pos)
{
	_pos = pos;
}

void Camera::SetSize(Vector2 size)
{
	_size = size;
}

void Camera::SetLimit(float minX, float maxX, float minY, float maxY)
{
	_minX = minX;
	_maxX = maxX;
	_minY = minY;
	_maxY = maxY;
}

void Camera::AdjustPos(Vector2 playerPos)
{
	// adjust x position
	if ((playerPos.x > _maxX))
		_pos.x = _maxX;
	else if (playerPos.x < _minX)
		_pos.x = _minX;
	else
		_pos.x = playerPos.x;

	// adjust y position
	if ((playerPos.y > _maxY))
		_pos.y = _maxY;
	else if (playerPos.y < _minY)
		_pos.y = _minY;
	else
		_pos.y = playerPos.y;
}
