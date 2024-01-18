#include "pch.h"
#include "Triangle.h"

//Constructor
Triangle::Triangle(Point3D inP1, Point3D inP2, Point3D inP3, Point3D inNormal) :
    mP1(inP1), mP2(inP2), mP3(inP3),mNormal(inNormal)
{
}

//Destructor
Triangle::~Triangle()
{
}


//Getters
Point3D Triangle::p1() const
{
    return mP1;
}

Point3D Triangle::p2() const
{
    return mP2;
}

Point3D Triangle::p3() const
{
    return mP3;
}

Point3D Triangle::normal() const {
    return mNormal;
}

//Setters
void Triangle::setP1(Point3D inP1)
{
    mP1 = inP1;
}

void Triangle::setP2(Point3D inP2)
{
    mP2 = inP2;
}

void Triangle::setP3(Point3D inP3)
{
    mP3 = inP3;
}

void Triangle::setNormal(Point3D inNormal) {
    mNormal = inNormal;
}

