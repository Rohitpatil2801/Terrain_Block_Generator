#include "pch.h"
#include "Reader.h"
#include "Triangulation.h"
#include <iostream>

//Constructor
Reader::Reader(const std::string& fileName)
    : mFileName(fileName)
{
}

//Destructor
Reader::~Reader()
{
}


//Fuction to check file is open or not
bool Reader::openFile() {
    mFile.open(mFileName, std::ios::binary);
    return mFile.is_open();
}

//ReadSTL function to read binary STL file and fill vertices, colors and normal in QVector
void Reader::readSTLFile(std::vector<float>& mVerticeSTD, std::vector<float>& mColorSTD, std::vector<float>& mNormalSTD)
{
    std::string filePath = mFileName;

    std::ifstream file(filePath, std::ios::binary);

    if (file.is_open())
    {
        char header[80];
        file.read(header, 80);

        uint32_t numTriangles;
        file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

        std::vector<Triangle> triangles;  // Temporary storage for triangles

        for (uint32_t i = 0; i < numTriangles; ++i)
        {
            // Read normal vector (12 bytes)
            float normal[3];
            file.read(reinterpret_cast<char*>(&normal), sizeof(normal));
            Point3D normalPoint(normal[0], normal[1], normal[2]);

            //Add normals to mNormal
            mNormalSTD.push_back(normalPoint.x());
            mNormalSTD.push_back(normalPoint.y());
            mNormalSTD.push_back(normalPoint.z());


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


        for (const auto& triangle : trianglesFromTriangulation)
        {
            // Add triangles to Vertices
            mVerticeSTD.push_back(triangle.p1().x());
            mVerticeSTD.push_back(triangle.p1().y());
            mVerticeSTD.push_back(triangle.p1().z());

            mVerticeSTD.push_back(triangle.p2().x());
            mVerticeSTD.push_back(triangle.p2().y());
            mVerticeSTD.push_back(triangle.p2().z());

            mVerticeSTD.push_back(triangle.p3().x());
            mVerticeSTD.push_back(triangle.p3().y());
            mVerticeSTD.push_back(triangle.p3().z());


            // Add colors to mColors
            mColorSTD.push_back(1.0f);
            mColorSTD.push_back(1.0f);
            mColorSTD.push_back(1.0f);

            mColorSTD.push_back(1.0f);
            mColorSTD.push_back(1.0f);
            mColorSTD.push_back(1.0f);

            mColorSTD.push_back(1.0f);
            mColorSTD.push_back(1.0f);
            mColorSTD.push_back(1.0f);

        }

    }
}