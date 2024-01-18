#pragma once
#include "Triangle.h"
#include <vector>

class GEOMETRY_API Triangulation
{
public:
    Triangulation(std::vector<Triangle> triangles); //Constructor
    ~Triangulation(); //Destructor

    //Getter
    std::vector<Triangle> getTriangles() const;

private:
    //Member Variable
    std::vector<Triangle> mTriangles;
};
