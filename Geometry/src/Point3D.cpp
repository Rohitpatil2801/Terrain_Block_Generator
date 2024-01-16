#include "pch.h"
#include "Point3D.h"

//Constructor
Point3D::Point3D(double inX, double inY, double inZ)
    : mX(inX),
    mY(inY),
    mZ(inZ)
{
}

//Destructor
Point3D::~Point3D()
{
}

//Getters
double Point3D::x() const
{
    return mX;
}

double Point3D::y() const
{
    return mY;
}

double Point3D::z() const
{
    return mZ;
}


//Setters
void Point3D::setX(double x)
{
    mX = x;
}

void Point3D::setY(double y)
{
    mY = y;
}

void Point3D::setZ(double z)
{
    mZ = z;
}
