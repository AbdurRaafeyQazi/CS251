#include "include/shape.h"

#include <sstream>
#include <string>

using namespace std;


Shape::Shape() : x(0) , y(0) {}


Shape::Shape(int x, int y) : x(x) , y(y) {}


Shape::~Shape() {

  
  // TODO_STUDENT
}



Shape* Shape::copy() {
  // TODO_STUDENT
  
  return new Shape(x , y);

  //return new Shape(this->x ,this->y);
}


int Shape::getX() const {
  return x;
}


int Shape::getY() const {
  return y;
}


void Shape::setX(int X) {
  x = X;
}


void Shape::setY(int Y) {
  y = Y;
}


string Shape::as_string() const {
  // TODO_STUDENT
  stringstream ss;
  ss << "It's a Shape at x: " << x << ", y: " << y;
  return ss.str();
}

//-----------------------------------------------------------------------------------------------------------

Circle::Circle() : Shape(0, 0), radius(0){}

Circle::Circle(int r) : Shape(0, 0), radius(r) {}

Circle::Circle(int x, int y, int r) : Shape(x , y), radius(r) {}

Circle::~Circle() {}

Circle* Circle::copy()
{
  return new Circle(getX(), getY(), radius);
}

int Circle::getRadius() const
{
  return radius;
}

void Circle::setRadius(int r)
{
  radius = r;
}

string Circle::as_string() const
{
  stringstream ss;
  ss << "It's a Circle at x: " << getX() << ", y: " << getY() << ", radius: " << radius;
  return ss.str();
} 


//-----------------------------------------------------------------------------------------------------------


Rect::Rect() : Shape(0, 0), width(0), height(0) {}

Rect::Rect(int w, int h) : Shape(0, 0), width(w), height(h) {}

Rect::Rect(int x, int y, int w, int h) : Shape(x, y), width(w), height(h) {}

Rect::~Rect() {}

Rect* Rect::copy()
{
  return new Rect(getX(), getY(), width, height);
}

int Rect::getWidth() const
{
  return width;
}

int Rect::getHeight() const
{
  return height;
}

void Rect::setHeight(int h)
{
  height = h;
}

void Rect::setWidth(int w)
{
  width = w;
}


string Rect::as_string() const
{
  stringstream ss;
  ss << "It's a Rectangle at x: " << getX() << ", y: " << getY() << " with width: " << width << " and height: " << height;
  return ss.str();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

RightTriangle::RightTriangle() : Shape(0, 0), base(0), height(0) {}

RightTriangle::RightTriangle(int b, int h) : Shape(0, 0), base(b), height(h) {}

RightTriangle::RightTriangle(int x, int y, int b, int h) : Shape(x, y), base(b), height(h) {}

RightTriangle::~RightTriangle() {}

RightTriangle* RightTriangle::copy()
{
  return new RightTriangle(getX(), getY(), base, height);
}

int RightTriangle::getBase() const 
{
  return base;
}

int RightTriangle::getHeight() const 
{
  return height;
}

void RightTriangle::setBase(int b)
{
  base = b;
}

void RightTriangle::setHeight(int h)
{
  height = h;
}

string RightTriangle::as_string() const
{
  stringstream ss;
  ss << "It's a Right Triangle at x: " << getX() << ", y: " << getY() << " with base: " << base << " and height: " << height;
  return ss.str();
}