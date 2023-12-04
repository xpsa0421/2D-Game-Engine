#include "ScrollObject.h"

void ScrollObject::SetScrollSpeed(float speed)
{
	_scrollSpeed = speed;
}

void ScrollObject::SetScrollDirection(float direction)
{
	_scrollDirection = direction;
}

bool ScrollObject::Frame()
{
	float step = g_secondPerFrame * _scrollSpeed * _scrollDirection;
	_scrollStep += step;

	if (_scrollStep + 1.0f > 2.0f)
		_scrollStep = 0.0f;

	_vertices[0].t = { 0.0f + _scrollStep, 0.0f };
	_vertices[1].t = { 1.0f + _scrollStep, 0.0f };
	_vertices[2].t = { 0.0f + _scrollStep, 1.0f };
	_vertices[3].t = { 1.0f + _scrollStep, 1.0f };

	_immediateContext->UpdateSubresource(
		_vertexBuffer, 0, nullptr, &_vertices.at(0), 0, 0);

	return true;
}

void ScrollObject::UpdateVertexBuffer()
{
	_vertices[0].p = { _drawPos.x, _drawPos.y, 0.0f };
	_vertices[1].p = { _drawPos.x + _drawSize.x, _drawPos.y,  0.0f };
	_vertices[2].p = { _drawPos.x, _drawPos.y - _drawSize.y, 0.0f };
	_vertices[3].p = { _drawPos.x + _drawSize.x, _drawPos.y - _drawSize.y, 0.0f };
	
	_immediateContext->UpdateSubresource(
		_vertexBuffer, 0, nullptr, &_vertices.at(0), 0, 0);
}