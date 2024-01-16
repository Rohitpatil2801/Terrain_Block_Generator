#pragma once
#include "pch.h"
#include <fstream>
#include "vector"

class STLREADER_API Reader {
public:
    Reader(const std::string& fileName); //Constructor

    ~Reader(); //Destructor

    //Member Function
    bool openFile();
    void readSTLFile(std::vector<float>& mVerticeSTD, std::vector<float>& mColorSTD, std::vector<float>& mNormalSTD);

private:
    //Member Variable
    std::string mFileName;
    std::ifstream mFile;
};
