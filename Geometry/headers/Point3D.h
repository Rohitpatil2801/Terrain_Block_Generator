#pragma once
#include "pch.h"

class GEOMETRY_API Point3D
{
public:
    Point3D(double inX, double inY, double inZ); //Constructor
    ~Point3D(); //Destructor

    //Getters
    double x() const;
    double y() const;
    double z() const;

    //Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);

private:
    //Member Variables
    double mX;
    double mY;
    double mZ;
};

