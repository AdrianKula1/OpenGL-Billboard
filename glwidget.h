#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <set>
#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif

#include <QOpenGLFunctions_4_5_Core>
#include <QMap>
#include <QTimer>

#include "glslprogram.h"
#include "geometry.h"
#include "mathgl.h"
#include "texture2d.h"
#include "billboard.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    QMap<QString, GLSLProgram*> shaders;
    QMap<QString, Geometry*> geometry;
    QMap<QString, mat4> geometryMat;
    QMap<QString, Texture2D*> textures2d;
    QMap<QString, Billboard*> billboards;

    mat4 ProjMat;

    QTimer frame_timer;
    int frame;
    int de;     // pomiar kroku czasowego
    float angle;
    float ax,ay,dax,day;    // obroty myszka

    void createShaders();
    void createSomeGeometry();
    void createTextures();
    void createBillboards();

    Camera camera;
    std::set<char> keys; // do przechowywania aktualnie wcisnietych klawiszy
    void processCamera();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
    GLWidget();
};


#endif // GLWIDGET_H
