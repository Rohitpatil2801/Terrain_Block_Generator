#pragma once
#include <fstream>
#include "QVector"
#include "Triangle.h"

class Algorithm {
public:
    Algorithm(const std::string& fileName); //Constructor

    ~Algorithm(); //Destructor

    //Member Functions
    bool openFile();
    void generateTerrainBlock(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors,QVector<GLfloat>& mNormal);

private:
    //Member Variables
    std::string mFileName;
    std::ifstream mFile;
};


