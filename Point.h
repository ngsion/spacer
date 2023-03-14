#ifndef _INCLUDE_POINT_H_
#define _INCLUDE_POINT_H_

class Point
{
public:
   int x;
   int y;

public:
   Point();
   Point(int x, int y);
   Point(const Point &original);
   const Point &operator=(const Point &rightSide);
   Point UpRight();
   Point Up();
   Point Right();
};

Point::Point()
{
   this->x = 0;
   this->y = 0;
}

Point::Point(int xpos, int ypos)
{
   this->x = xpos;
   this->y = ypos;
}

Point::Point(const Point &original)
{
   x = original.x;
   y = original.y;
}

Point Point::UpRight()
{
   Point point;
   point.x = this->x + 1;
   point.y = this->y + 1;
   return point;
}

Point Point::Up()
{
   Point point;
   point.x = this->x;
   point.y = this->y + 1;
   return point;
}

Point Point::Right()
{
   Point point;
   point.x = this->x + 1;
   point.y = this->y;
   return point;
}

const Point &Point::operator=(const Point &rightSide)
{

   if (this != &rightSide)
   {
      this->x = rightSide.x;
      this->y = rightSide.y;
   }
}

#endif
