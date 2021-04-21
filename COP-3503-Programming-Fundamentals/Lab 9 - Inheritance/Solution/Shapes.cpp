#include "Shapes.h"
int count = 0;
Shape::~Shape()
{

}

Square::Square()
{
	this->s = 0;
}

Square::Square(float side)
{
	this->s = side;
}

Square::~Square()
{
}

float Square::Area() const
{
	return s * s;
}

void Square::Scale(float scaleFactor)
{
	this->s *= scaleFactor;
}

void Square::ShowArea() const
{
	cout << "The area of the "+ GetName2D() +" is : " << Area() << endl;
}

string Square::GetName2D() const
{
	return "Square";
}

void Square::Display() const
{
	ShowArea();
	cout << "Length of a side: " << this->s << endl;
}



Rectangle::Rectangle()
{
	this->w = 0;
	this->h = 0;
}

Rectangle::Rectangle(float width, float height)
{
	this->w = width;
	this->h = height;
}

Rectangle::~Rectangle()
{
}

float Rectangle::Area() const
{
	return w * h;
}

void Rectangle::Scale(float scaleFactor)
{
	this->w *= scaleFactor;
	this->h *= scaleFactor;
}

void Rectangle::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Rectangle::GetName2D() const
{
	return "Rectangle";
}

void Rectangle::Display() const
{
	ShowArea();
	cout << "Length: " << this->w << endl;
	cout << "Width: " << this->h << endl;
}




Triangle::Triangle()
{
	this->b = 0;
	this->h = 0;
}
Triangle::Triangle(float base, float height)
{
	this->b = base;
	this->h = height;
}

Triangle::~Triangle()
{
}

float Triangle::Area() const
{
	return 0.5 * b * h;
}

void Triangle::Scale(float scaleFactor)
{
	this->b *= scaleFactor;
	this->h *= scaleFactor;
}

void Triangle::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Triangle::GetName2D() const
{
	return "Triangle";
}

void Triangle::Display() const
{
	ShowArea();
	cout << "Base: " << this->b << endl;
	cout << "Height: " << this->h << endl;
}







Circle::Circle()
{
	this->r = 0;
}

Circle::Circle(float radius)
{
	this->r = radius;
}

Circle::~Circle()
{
}

float Circle::Area() const
{
	return PI * r * r;
}

void Circle::Scale(float scaleFactor)
{
	this->r *= scaleFactor;
}

void Circle::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Circle::GetName2D() const
{
	return "Circle";
}

void Circle::Display() const
{
	ShowArea();
	cout << "Radius: " << this->r << endl;
}




Ellipse::Ellipse()
{
	this->b = 0;
	this->a = 0;
}

Ellipse::Ellipse(float majorAxis, float minorAxis)
{
	this->b = majorAxis;
	this->a = minorAxis;
}

Ellipse::~Ellipse()
{
}

float Ellipse::Area() const
{
	return PI * a * b;
}

void Ellipse::Scale(float scaleFactor)
{
	this->a *= scaleFactor;
	this->b *= scaleFactor;
}

void Ellipse::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Ellipse::GetName2D() const
{
	return "Ellipse";
}

void Ellipse::Display() const
{
	ShowArea();
	cout << "Length of semi-major axis: " << this->b << endl;
	cout << "Length of semi-minor axis: " << this->a << endl;
}




Trapezoid::Trapezoid()
{
	this->b = 0;
	this->a = 0;
	this->h = 0;
}

Trapezoid::Trapezoid(float firstParallel, float secondParallel, float height)
{
	this->a = firstParallel;
	this->b = secondParallel;
	this->h = height;
}

Trapezoid::~Trapezoid()
{
}

float Trapezoid::Area() const
{
	return 0.5 * (a + b) * h;
}

void Trapezoid::Scale(float scaleFactor)
{
	this->a *= scaleFactor;
	this->b *= scaleFactor;
	this->h *= scaleFactor;
}

void Trapezoid::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Trapezoid::GetName2D() const
{
	return "Trapezoid";
}

void Trapezoid::Display() const
{
	ShowArea();
	cout << "Length of side A: " << this->a << endl;
	cout << "Length of side B: " << this->b << endl;
	cout << "Height: " << this->h << endl;
}




Sector::Sector()
{
	this->r = 0;
	this->theta = 0;
}

Sector::Sector(float radius, float theta)
{
	this->r = radius;
	this->theta = theta;
}

Sector::~Sector()
{
}

float Sector::Area() const
{
	return 0.5 * this->r * this->r * ((this->theta * PI) / 180);
}

void Sector::Scale(float scaleFactor)
{
	this->r *= scaleFactor;
	this->theta *= scaleFactor;
}

void Sector::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Sector::GetName2D() const
{
	return "Sector";
}

void Sector::Display() const
{
	ShowArea();
	cout << "Radius: " << this->r << endl;
	cout << "Angle in radians: " << (this->theta * PI) / 180 << endl;
	cout << "Angle in degrees: " << this->theta << endl;
}



/*  3D  */

TriangularPyramid::TriangularPyramid()
{
	s = 0;
	b = 0;
	h = 0;
}

TriangularPyramid::TriangularPyramid(float height, float base, float height2)
{
	this->s = height;
	this->b = base;
	this->h = height2;
}

TriangularPyramid::~TriangularPyramid()
{
}


float TriangularPyramid::Volume() const
{	
	return ((float)1 / (float)3) * (float)(0.5 * this->b * this->h) * (float)s;
}



string TriangularPyramid::GetName3D() const
{
	return "Triangular Pyramid";
}

void TriangularPyramid::ShowVolume() const
{
	cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void TriangularPyramid::Scale(float scaleFactor)
{
	s *= scaleFactor;
	b *= scaleFactor;
	h *= scaleFactor;
}

void TriangularPyramid::Display() const
{
	ShowVolume();
	cout << "The height is: " << this->s << endl;
	cout << "The area of the Triangle is: " << (float)(0.5 * this->b * this->h) << endl;
	cout << "Base: " << this->b << endl;
	cout << "Height: " << this->h << endl;
}








RectangularPyramid::RectangularPyramid()
{
	h = 0;
	b = 0;
	w = 0;
}

RectangularPyramid::RectangularPyramid(float height, float base, float width)
{
	this->h = height;
	this->b = base;
	this->w = width;
}

RectangularPyramid::~RectangularPyramid()
{
}


float RectangularPyramid::Volume() const
{
	return ((float)1 / (float)3) * (float)(this->h * this->b) * (float)w;
}



string RectangularPyramid::GetName3D() const
{
	return "Rectangular Pyramid";
}

void RectangularPyramid::ShowVolume() const
{
	cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void RectangularPyramid::Scale(float scaleFactor)
{
	h *= scaleFactor;
	b *= scaleFactor;
	w *= scaleFactor;
}

void RectangularPyramid::Display() const
{
	ShowVolume();
	cout << "The height is: " << this->h << endl;
	cout << "The area of the Rectangle is: " << (float)(this->b * this->w) << endl;
	cout << "Length: " << this->b << endl;
	cout << "Width: " << this->w << endl;
}







Cylinder::Cylinder()
{
	this->r = 0;
	this->h = 0;
}

Cylinder::Cylinder(float height, float radius)
{
	this->h = height;
	this->r = radius;
}

Cylinder::~Cylinder()
{
}


float Cylinder::Volume() const
{
	return PI * r * r * h;
}



string Cylinder::GetName3D() const
{
	return "Cylinder";
}

void Cylinder::ShowVolume() const
{
	cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void Cylinder::Scale(float scaleFactor)
{
	h *= scaleFactor;
	r *= scaleFactor;
}

void Cylinder::Display() const
{
	ShowVolume();
	cout << "The height is: " << this->h << endl;
	cout << "The area of the Circle is: " << PI * r * r << endl;
	cout << "Radius: " << this->r << endl;
}









Sphere::Sphere()
{
	r = 0;
}

Sphere::Sphere(float radius)
{
	this->r = radius;
}

Sphere::~Sphere()
{
}


float Sphere::Volume() const
{
	return ((float)4 / (float)3) * (float)(PI * this->r * this->r * this->r);
}



string Sphere::GetName3D() const
{
	return "Sphere";
}

void Sphere::ShowVolume() const
{
	cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void Sphere::Scale(float scaleFactor)
{
	r *= scaleFactor;
}

void Sphere::Display() const
{
	ShowVolume();
	cout << "The area of the Circle is: " << (float)(PI * this->r * this->r) << endl;
	cout << "Radius: " << this->r << endl;
}

void Shape2D::ShowArea() const
{
}

bool Shape2D::operator>(const Shape2D & rhs) const
{
		cout << "The area of the " << this->GetName2D() << " is : " << this->Area() << endl;
		
	if (this->Area() > rhs.Area())
	{

		return true;
	}
	return false;
}

bool Shape2D::operator<(const Shape2D & rhs) const
{
	if (this->Area() < rhs.Area())
	{

		return true;
	}
	return false;
}

bool Shape2D::operator==(const Shape2D & rhs) const
{
	
	if (this->Area() == rhs.Area())
	{
		/*cout << "The area of the " << this->GetName2D() << " is : " << this->Area() << endl;
		cout << "The area of the " << rhs.GetName2D() << " is : " << rhs.Area() << endl;*/

		return true;
	}
	return false;
}

Shape2D::~Shape2D()
{
}

void Shape3D::ShowVolume() const
{
}

Temp::Temp()
{
	count = 0;
}

bool Shape3D::operator>(const Shape3D & rhs) const
{			
	if (this->Volume() > rhs.Volume())
	{

		return true;
	}
	
	return false;
}

bool Shape3D::operator<(const Shape3D & rhs) const
{
	
	if (this->Volume() < rhs.Volume())
	{

		return true;
	}
	return false;
}

bool Shape3D::operator==(const Shape3D & rhs) const
{
		/*cout << "The volume of the " << this->GetName3D() << " is : " << this->Volume() << endl;
		cout << "The volume of the " << rhs.GetName3D() << " is : " << rhs.Volume() << endl;*/
	if (this->Volume() == rhs.Volume())
	{

		return true;
	}
	return false;
}

Shape3D::~Shape3D()
{
}
