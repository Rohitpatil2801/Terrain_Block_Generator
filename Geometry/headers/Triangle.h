#pragma once
#include "Point3D.h"

class GEOMETRY_API Triangle
{
public:
    Triangle(Point3D inP1, Point3D inP2, Point3D inP3, Point3D inNormal); //Constructor
    ~Triangle(); //Destructor

    //Getters
    Point3D p1() const;
    Point3D p2() const;
    Point3D p3() const;
    Point3D normal() const;

    //Setters
    void setP1(Point3D inP1);
    void setP2(Point3D inP2);
    void setP3(Point3D inP3);
    void setNormal(Point3D inNormal);

private:
    //Member Variables
    Point3D mP1;
    Point3D mP2;
    Point3D mP3;
    Point3D mNormal;
};
