#include "StaticObject.h"

void StaticObject::SetSize(Vector2 size)
{
	_sizeSet = true;
	_rectInit = { 0, 0, size.x, size.y };
}

void StaticObject::UpdateVertexBuffer()
{
	if (!_sizeSet)
		BaseObject::UpdateVertexBuffer();
	else
	{
		_vertices[0].p = { _drawPos.x, _drawPos.y, 0.0f };
		_vertices[1].p = { _drawPos.x + _drawSize.x, _drawPos.y, 0.0f };
		_vertices[2].p = { _drawPos.x, _drawPos.y - _drawSize.y, 0.0f };
		_vertices[3].p = { _drawPos.x + _drawSize.x, _drawPos.y - _drawSize.y, 0.0f };
		
		_vertices[0].t = { 0, 0 };
		_vertices[1].t = { 1, 0 };
		_vertices[2].t = { 0, 1 };
		_vertices[3].t = { 1, 1 };	

		_immediateContext->UpdateSubresource(
			_vertexBuffer, NULL, nullptr, &_vertices.at(0), 0, 0);
	}
}