#include "stdafx.h"
#include "Algorithm.h"
#include "Triangulation.h"
#include <iostream>

//Constructor
Algorithm::Algorithm(const std::string& fileName) 
    : mFileName(fileName)
{
}

//Destructor
Algorithm::~Algorithm()
{
}

//Function to check is file open or not
bool Algorithm::openFile() {
    mFile.open(mFileName, std::ios::binary);
    return mFile.is_open();
}

//Function generate terrain block 
void Algorithm::generateTerrainBlock(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, QVector<GLfloat>& mNormals)
{
    std::string filePath = mFileName;

    std::ifstream file(filePath, std::ios::binary);

    // Read the header (80 bytes, usually skipped)
    char header[80];
    file.read(header, 80);

    // Read the number of triangles (4 bytes)
    uint32_t numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

    std::vector<Triangle> triangles;  // Temporary storage for triangles

    // Read each triangle
    for (uint32_t i = 0; i < numTriangles; ++i)
    {
        // Read normal vector (12 bytes)
        float normal[3];
        file.read(reinterpret_cast<char*>(&normal), sizeof(normal));
        Point3D normalPoint(normal[0], normal[1], normal[2]);

        mNormals << normalPoint.x() << normalPoint.y() << normalPoint.z();

        // Read vertices (36 bytes)
        float vertex1[3], vertex2[3], vertex3[3];
        file.read(reinterpret_cast<char*>(&vertex1), sizeof(vertex1));
        file.read(reinterpret_cast<char*>(&vertex2), sizeof(vertex2));
        file.read(reinterpret_cast<char*>(&vertex3), sizeof(vertex3));

        // Skip attributeByteCount (2 bytes)
        file.seekg(2, std::ios::cur);

        // Create Triangle object
        Point3D point1(vertex1[0], vertex1[1], vertex1[2]);
        Point3D point2(vertex2[0], vertex2[1], vertex2[2]);
        Point3D point3(vertex3[0], vertex3[1], vertex3[2]);

        Triangle newTriangle(point1, point2, point3, normalPoint);

        triangles.push_back(newTriangle);
    }

    // Create Triangulation object
    Triangulation triangulationObject(triangles);

    // Access the triangles
    std::vector<Triangle> trianglesFromTriangulation = triangulationObject.getTriangles();

   
    for (const auto& triangle : trianglesFromTriangulation) {
        //Add these triangles in mVertices
        mVertices << triangle.p1().x()<< triangle.p1().y()<< triangle.p1().z();
        mVertices << triangle.p2().x()<< triangle.p2().y()<< triangle.p2().z();
        mVertices << triangle.p3().x()<< triangle.p3().y()<< triangle.p3().z();

        // Add colors in mColors
        mColors << 1.0f << 0.0f << 1.0f;
        mColors << 1.0f << 0.0f << 1.0f;
        mColors << 1.0f << 0.0f << 1.0f;

        double yOffset = -10;

        // Add additional vertices to mVertices
        mVertices << triangle.p1().x()<< yOffset << triangle.p1().z();
        mVertices << triangle.p2().x()<< yOffset << triangle.p2().z();
        mVertices << triangle.p3().x()<< yOffset << triangle.p3().z();

        // Add colors in mColors
        mColors << 1.0f << 0.0f << 1.0f;
        mColors << 1.0f << 0.0f << 1.0f;
        mColors << 1.0f << 0.0f << 1.0f;
    }

}
