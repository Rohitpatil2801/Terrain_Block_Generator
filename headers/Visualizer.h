#pragma once
#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include <QVector>
#include "Triangle.h"
#include "Reader.h"
#include "Algorithm.h"

class OpenGLWindow;

class Visualizer : public QMainWindow {
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr); //Constructor
    ~Visualizer(); //Destructor

private:
    void setupUi();

private slots:
    void generateBlock();
    void readSTL();
    void screenClear();

private:
    //Member Variables
    OpenGLWindow* mRenderer;

    QPushButton* mPushButtonRead;
    QPushButton* mPushButtonGenerate;
    QPushButton* mPushButtonClear;

    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;
    QVector<GLfloat> mNormal;

    std::vector<float>mVerticeSTD;
    std::vector<float>mColorSTD;
    std::vector<float>mNormalSTD;

    std::vector<Triangle> mTriangles;
    std::string mFileName;
    Reader* mSTLReader;
    Algorithm* mTerrainBlock;
};

