#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>

// Constructor
OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}

// Destructor
OpenGLWindow::~OpenGLWindow()
{
    reset();
}

// Setters
void OpenGLWindow::setVectorOfLines(QVector<GLfloat>& inVectors)
{
    mVertices = inVectors;
}

void OpenGLWindow::setColorOfLines(QVector<GLfloat>& inColors)
{
    mColors = inColors;
}

void OpenGLWindow::setNormal(QVector<GLfloat>& inNormals)
{
    mNormals = inNormals;
}

void OpenGLWindow::setZoomFactor(GLfloat& inZoomFactor)
{
    mZoomFactor = inZoomFactor;
    update();
}


// Functions

// Update the data and trigger a repaint
void OpenGLWindow::updateData(const QVector<GLfloat>& inVertices, const QVector<GLfloat>& inColors, const QVector<GLfloat>& inNormals)
{
    mVertices = inVertices;
    mColors = inColors;
    mNormals = inNormals;
    update();
}


// Reset the OpenGL resources
void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}


// OpenGL painting function
void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProgram->bind();

    QMatrix4x4 matrix_proj;
    QMatrix4x4 matrix_view;
    QMatrix4x4 matrix_model;

    matrix_model.setToIdentity();
    matrix_model.rotate(mRotationAngle);

    matrix_proj.setToIdentity();
    matrix_proj.ortho(-30.0f * mZoomFactor, 30.0f * mZoomFactor, -30.0f * mZoomFactor, 30.0f * mZoomFactor, 0.1f, 100.0f);
    matrix_proj.translate(0, 0, -20);

    mProgram->setUniformValue(mMatrixUniform_proj, matrix_proj);
    mProgram->setUniformValue(mMatrixUniform_view, matrix_view);
    mProgram->setUniformValue(mMatrixUniform_model, matrix_model);

    GLfloat* verticesData = mVertices.data();
    GLfloat* colorsData = mColors.data();
    GLfloat* normalsData = mNormals.data();

    glVertexAttribPointer(mPosAttr, 3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(mColAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);
    glVertexAttribPointer(mNormalAttr, 1, GL_FLOAT, GL_FALSE, 0, normalsData);

    glEnableVertexAttribArray(mPosAttr);
    glEnableVertexAttribArray(mColAttr);
    glEnableVertexAttribArray(mNormalAttr);

    glDrawArrays(GL_LINE_LOOP, 0, mVertices.size() / 3);
}


// Mouse move event function for rotation
void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - mLastPos.x();
    int dy = event->y() - mLastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);
        mRotationAngle = rotX * rotY * mRotationAngle;
        update();
    }
    mLastPos = event->pos();
}


// Mouse wheel event function for zoom in and zoom out
void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    int delta = event->angleDelta().y();
    if (delta > 0)
    {
        mZoomFactor *= 1.1f;
    }
    else
    {
        mZoomFactor /= 1.1f;
    }
    update();
}


// Read shader source from file
QString OpenGLWindow::readShaderSource(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open file: " << filePath;
        return "";
    }
    QTextStream stream(&file);
    return stream.readAll();
}

// Initialize OpenGL resources and set up shader program
void OpenGLWindow::initializeGL()
{
    QString vertexShaderSource = readShaderSource("Shaders/vertexShader.glsl");
    QString fragmentShaderSource = readShaderSource("Shaders/fragmentShader.glsl");

    initializeOpenGLFunctions();
    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();

    mPosAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(mPosAttr != -1);

    mColAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(mColAttr != -1);

    mNormalAttr = mProgram->attributeLocation("normalAttr");
    Q_ASSERT(mNormalAttr != -1);

    mMatrixUniform_proj = mProgram->uniformLocation("matrix_proj");
    Q_ASSERT(mMatrixUniform_proj != -1);

    mMatrixUniform_view = mProgram->uniformLocation("matrix_view");
    Q_ASSERT(mMatrixUniform_view != -1);

    mMatrixUniform_model = mProgram->uniformLocation("matrix_model");
    Q_ASSERT(mMatrixUniform_model != -1);
}

