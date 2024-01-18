#include "stdafx.h"
#include "Visualizer.h"
#include <QtWidgets/QApplication>

// Main entry point for the application
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Visualizer w;
    w.show();
    return a.exec();
}

