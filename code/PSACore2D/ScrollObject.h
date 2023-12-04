#pragma once
#include "StaticObject.h"

class ScrollObject : public StaticObject
{
private:
	float	_scrollSpeed		= 0.05f;
	float	_scrollStep			= 0.0f;
	float	_scrollDirection	= 1.0f;
public:
	void	SetScrollSpeed(float speed);
	void	SetScrollDirection(float direction);
	bool	Frame()					override;
	void	UpdateVertexBuffer()	override;
};

