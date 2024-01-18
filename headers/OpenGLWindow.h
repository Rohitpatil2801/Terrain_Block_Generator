#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMainWindow>
#include <QQuaternion>
#include <QWheelEvent>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWindow(const QColor& background, QMainWindow* parent); //Constructor
    ~OpenGLWindow(); //Destructor

    //Member Functions
    void setVectorOfLines(QVector<GLfloat>& vectorOfLines);
    void setColorOfLines(QVector<GLfloat>& colorOfLines);
    void setNormal(QVector<GLfloat>& normal);
    void setZoomFactor(GLfloat& zoomFactor);

    void updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors, const QVector<GLfloat>& normal);

    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    QString readShaderSource(QString filePath);

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();

private:
    //Member Variables
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QMetaObject::Connection mContextWatchConnection;
    QOpenGLBuffer mVbo;
    QColor mBackground;

    GLint mPosAttr = 0;
    GLint mColAttr = 0;
    GLint mNormalAttr = 0;
    GLint mMatrixUniform_proj = 0;
    GLint mMatrixUniform_view = 0;
    GLint mMatrixUniform_model = 0;

    QQuaternion mRotationAngle;
    QPoint mLastPos;
    GLfloat mZoomFactor = 1.0f;

    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;
    QVector<GLfloat> mNormals;
};
