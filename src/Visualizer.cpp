#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

//Constructor
Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mPushButtonRead, &QPushButton::clicked, this, &Visualizer::readSTL);
    connect(mPushButtonGenerate, &QPushButton::clicked, this, &Visualizer::generateBlock);
    connect(mPushButtonClear, &QPushButton::clicked, this, &Visualizer::screenClear);
}

//Destructor
Visualizer::~Visualizer()
{
}


//User Interface Code
void Visualizer::setupUi()
{
    QWidget* mCentralWidget = new QWidget(this);
    mCentralWidget->setStyleSheet("background-color:#F0F0F0; color: white;");

    QVBoxLayout* mainVerticalLayout = new QVBoxLayout(mCentralWidget);

    mRenderer = new OpenGLWindow(QColor(1.0, 1.0, 0.0), this);
    mainVerticalLayout->addWidget(mRenderer, 3);

    QFrame* buttonsFrame = new QFrame(this);
    buttonsFrame->setFrameStyle(QFrame::Box | QFrame::Raised);
    buttonsFrame->setLineWidth(2);
    buttonsFrame->setMidLineWidth(2);

    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttonsFrame);
    QMargins marginsHorizontalLayout(1, 20, 1, 20);
    buttonsLayout->setContentsMargins(marginsHorizontalLayout);

    mPushButtonRead = new QPushButton(this);
    mPushButtonRead->setText("Read STL");
    mPushButtonRead->setFixedSize(150, 50);
    mPushButtonRead->setStyleSheet("QPushButton {"
        "background-color: #008CBA;"
        "color: white;"
        "border: 0.5px solid #1f1f1f;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}");

    mPushButtonGenerate = new QPushButton(this);
    mPushButtonGenerate->setText("Generate Block");
    mPushButtonGenerate->setFixedSize(150, 50);
    mPushButtonGenerate->setStyleSheet("QPushButton {"
        "background-color: #f44336;"
        "color: white;"
        "border: 0.5px solid #1f1f1f;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}");

    mPushButtonClear = new QPushButton(this);
    mPushButtonClear->setText("Clear Screen");
    mPushButtonClear->setFixedSize(150, 50);
    mPushButtonClear->setStyleSheet("QPushButton {"
        "background-color:  #555555;"
        "color: white;"
        "border: 0.5px solid #1f1f1f;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}");

    buttonsLayout->addWidget(mPushButtonRead);
    buttonsLayout->addWidget(mPushButtonGenerate);
    buttonsLayout->addWidget(mPushButtonClear);

    buttonsFrame->setFixedHeight(100);

    mainVerticalLayout->addWidget(buttonsFrame, 1);
    setCentralWidget(mCentralWidget);
    setWindowTitle(QCoreApplication::translate("Terrain Block Generator", "Terrain Block Generator", nullptr));
    showMaximized();
}


//Read STL File Slot
void Visualizer::readSTL()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files(*.stl);; All Files(*)"));
    if (!fileName.isEmpty())
    {
        mFileName = fileName.toStdString();
        mSTLReader = new Reader(mFileName);

        if (mSTLReader->openFile())
        {
            mSTLReader->readSTLFile(mVerticeSTD, mColorSTD, mNormalSTD);

            mRenderer->setVectorOfLines(mVertices);
            mRenderer->setColorOfLines(mColors);
            mRenderer->setNormal(mNormal);

            for (int i = 0; i < mVerticeSTD.size(); i++)
            {
                mVertices << mVerticeSTD.at(i);
            }

            for (int i = 0; i < mColorSTD.size(); i++)
            {
                mColors << mColorSTD.at(i);
            }

            for (int i = 0; i < mNormalSTD.size(); i++)
            {
                mNormal << mNormalSTD.at(i);
            }

            mRenderer->updateData(mVertices, mColors, mNormal);
            mVertices.clear();
            mColors.clear();
        }
    }
}

//Generate Terrain Block Slot 
void Visualizer::generateBlock()
{
    mTerrainBlock = new Algorithm(mFileName);
    if (mTerrainBlock->openFile())
    {
        mTerrainBlock->generateTerrainBlock(mVertices, mColors, mNormal);

        mRenderer->setVectorOfLines(mVertices);
        mRenderer->setColorOfLines(mColors);
        mRenderer->setNormal(mNormal);

        mRenderer->updateData(mVertices, mColors, mNormal);
        mVertices.clear();
        mColors.clear();
    }
}


//Clear Screen Slot
void Visualizer::screenClear()
{
    mVertices.clear();
    mColors.clear();
    mRenderer->updateData(mVertices, mColors, mNormal);
}