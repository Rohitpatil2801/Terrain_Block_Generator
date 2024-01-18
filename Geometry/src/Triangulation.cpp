#include "pch.h"
#include "Triangulation.h"

//Constructor
Triangulation::Triangulation(std::vector<Triangle> inTriangles) :
    mTriangles(inTriangles)
{
}

//Destructor
Triangulation::~Triangulation()
{
}

//Getter
std::vector<Triangle> Triangulation::getTriangles() const
{
    return mTriangles;
}
