#pragma once
#include "BaseObject.h"

class StaticObject : public BaseObject
{
public:
	bool	_sizeSet	= false;
public:
	void			SetSize(Vector2 size);
	virtual void	UpdateVertexBuffer()	override;
};

