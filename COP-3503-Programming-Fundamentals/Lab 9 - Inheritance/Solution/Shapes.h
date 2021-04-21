#pragma once

#include <math.h>
#include<iostream>
#include <string>
#include <vector>

using namespace std;

#define PI 3.14159f

class Shape
{
public:
	float s, w, h, r, a, b, theta;
	virtual void Scale(float scaleFactor) = 0;
	virtual void Display() const = 0;

	virtual ~Shape();

};

class Shape2D : virtual public Shape
{
public:
	virtual float Area() const = 0;
	void ShowArea() const;
	virtual string GetName2D() const = 0;
	bool operator>(const Shape2D &rhs) const;
	bool operator<(const Shape2D &rhs) const;
	bool operator==(const Shape2D &rhs) const;

	~Shape2D();
};

class Shape3D : virtual public Shape
{
public:
	virtual float Volume() const = 0;
	void ShowVolume() const;
	virtual string GetName3D() const = 0;
	bool operator>(const Shape3D &rhs) const;
	bool operator<(const Shape3D &rhs) const;
	bool operator==(const Shape3D &rhs) const;

	~Shape3D();
};

/* 2D */
class Square : virtual public Shape2D
{
public:
	Square();
	Square(float side);
	~Square();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Rectangle : virtual public Shape2D
{
public:
	Rectangle();
	Rectangle(float width, float height);
	~Rectangle();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Triangle : virtual public Shape2D
{
public:
	Triangle();
	Triangle(float base, float height);
	~Triangle();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};


class Circle : virtual public Shape2D
{
public:
	Circle();
	Circle(float radius);
	~Circle();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Ellipse : virtual public Shape2D
{
public:
	Ellipse();
	Ellipse(float majorAxis, float minorAxis);
	~Ellipse();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Trapezoid : virtual public Shape2D
{
public:
	Trapezoid();
	Trapezoid(float firstParallel, float secondParallel, float height);
	~Trapezoid();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Sector : virtual public Shape2D
{
public:
	Sector();
	Sector(float radius, float theta);
	~Sector();

	virtual float Area() const;
	virtual void ShowArea() const;
	virtual string GetName2D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};


/*  3D  */

class TriangularPyramid : virtual public Shape3D
{
public:
	TriangularPyramid();
	TriangularPyramid(float height, float base, float height2);
	~TriangularPyramid();

	virtual float Volume() const;
	virtual void ShowVolume() const;
	virtual string GetName3D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class RectangularPyramid : virtual public Shape3D
{
public:
	RectangularPyramid();
	RectangularPyramid(float height, float base, float height2);
	~RectangularPyramid();

	virtual float Volume() const;
	virtual void ShowVolume() const;
	virtual string GetName3D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Cylinder : virtual public Shape3D
{
public:
	Cylinder();
	Cylinder(float height, float radius);
	~Cylinder();

	virtual float Volume() const;
	virtual void ShowVolume() const;
	virtual string GetName3D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Sphere : virtual public Shape3D
{
public:
	Sphere();
	Sphere(float radius);
	~Sphere();

	virtual float Volume() const;
	virtual void ShowVolume() const;
	virtual string GetName3D() const;
	virtual void Scale(float scaleFactor);
	virtual void Display() const;
};

class Temp
{
public:
	int count;
	Temp();
};