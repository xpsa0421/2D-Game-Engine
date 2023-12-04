#include "Collision2D.h"

CollisionType2D Collision2D::RectToRect(Rect& a, Rect& b)
{
    float minX = a.x1 < b.x1 ? a.x1 : b.x1;
    float minY = a.y1 < b.y1 ? a.y1 : b.y1;
    float maxX = a.x2 > b.x2 ? a.x2 : b.x2;
    float maxY = a.y2 > b.y2 ? a.y2 : b.y2;

    if ((a.w + b.w) >= (maxX - minX))
    {
        if ((a.h + b.h) >= (maxY - minY))
        {
            float x, y, x2, y2;
            Rect intersectRegion;
            x = a.x1 > b.x1 ? a.x1 : b.x1;
            y = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;
            intersectRegion.Set(x, y, x2 - x, y2 - y);
            if (intersectRegion == a || intersectRegion == b)
            {
                return CollisionType2D::RECT_IN;
            }
            return CollisionType2D::RECT_OVERLAP;
        }
    }
    return CollisionType2D::RECT_OUT;
}

bool Collision2D::RectToInRect(Rect& a, Rect& b)
{
    if ((a.x1 <= b.x1)
        && ((a.x1 + a.w) >= b.x1 + b.w)
        && (a.y1 <= b.y1)
        && ((a.y1 + a.h) >= b.y1 + b.h))
    {
        return true;
    }
    return false;
}

bool Collision2D::CircleToCircle(Circle& a, Circle& b)
{
    float x = a.cx - b.cx;
    float y = a.cy - b.cy;
    float distance = sqrt(x * x + y * y);
    if (distance <= (a.r + b.r))
    {
        return true;
    }
    return false;
}

bool  Collision2D::RectToPoint(Rect& a, POINT& p)
{
    if (a.x1 <= p.x && a.x2 >= p.x)
    {
        if (a.y1 <= p.y && a.y2 >= p.y)
        {
            return true;
        }
    }
    return false;
}