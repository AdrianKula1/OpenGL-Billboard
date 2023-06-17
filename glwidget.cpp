#include "glwidget.h"
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>

#include "primitives.h"
#include "billboard.h"

Billboard* billboard;

GLWidget::GLWidget()
{
    frame = 0;
    de = 0;
    angle = 0.0f;
    ax=ay=dax=day=0;
}




void GLWidget::createShaders()
{
    GLSLProgram* prog = new GLSLProgram;
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\vshader.glsl", GL_VERTEX_SHADER);
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\fshader.glsl", GL_FRAGMENT_SHADER);
    if (prog->link())
        shaders["basic"] = prog;
    else
        delete prog;

    prog = new GLSLProgram;
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\v_background.glsl", GL_VERTEX_SHADER);
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\f_background.glsl", GL_FRAGMENT_SHADER);
    if (prog->link())
        shaders["background"] = prog;
    else
        delete prog;

    prog = new GLSLProgram;
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\v_ads.glsl", GL_VERTEX_SHADER);
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\f_ads.glsl", GL_FRAGMENT_SHADER);
    if (prog->link())
        shaders["ads"] = prog;
    else
        delete prog;



    prog = new GLSLProgram;
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\billboardv.glsl", GL_VERTEX_SHADER);
    prog->compileShaderFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\billboardf.glsl", GL_FRAGMENT_SHADER);
    if (prog->link())
        shaders["billboard"] = prog;
    else
        delete prog;
}

void GLWidget::createSomeGeometry()
{
    geometry["main_axes"] = createAxesGeometry();
    geometryMat["main_axes"] = identity();

    geometry["background"] = createPlaneGeometry({1,1}, {0.2, 0.2, 0.9});

    geometry["plane"] = createPlaneGeometry({1,1}, {1,1,1});
    vec3 normals[4] = {{0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}};
    vec2 uv[4] = {{0,1},{1,1},{0,0},{0,1}};
    geometry["plane"]->setAttribute(2, normals, 4);
    geometry["plane"]->setAttribute(3, uv, 4);


    QImage image("C:\\Programowanie\\Qt\\gl_terraing_ads\\clouds2.png");
    int w = 256;  //image.width();
    int h = 256;  //image.height();
    std::vector<float> data(w*h);
    for(int y=0; y<h; y++)
        for(int x=0; x<w; x++)
            data[x+y*w] = qBlue(image.pixel(y,x))/255.0f;
    geometry["terrain"] = createTerrainGeometry(w, h, data.data(), {0.1, 10, 0.1}, {0,-5,0});




    billboard = new Billboard({1, 1}, {0, 0, 0}, {5, 5, 3});
    geometry["billboard"] = billboard->getGeometry();

}

void GLWidget::createTextures()
{
    textures2d["grass"] = new Texture2D();
    textures2d["grass"]->loadFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\grass_2k.jpg");

    textures2d["hmap"] = new Texture2D();
    textures2d["hmap"]->loadFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\grass_2k.jpg");

    textures2d["billboard"] = new Texture2D();
    textures2d["billboard"]->loadFromFile("C:\\Programowanie\\Qt\\gl_terraing_ads\\lena.jpg");
}

void GLWidget::wheelEvent(QWheelEvent *event){
}

void GLWidget::processCamera()
{
    float dv = 0.1f;

    if(keys.find('W') != keys.end())
    {
        camera.pos = camera.pos + camera.forward*dv;
    }
    else if(keys.find('S') != keys.end())
    {
        camera.pos = camera.pos - camera.forward*dv;
    }

    if(keys.find('A') != keys.end())
    {
        camera.pos = camera.pos - camera.s()*dv;
    }
    else if(keys.find('D') != keys.end())
    {
        camera.pos = camera.pos + camera.s()*dv;
    }

    if(keys.find('Q') != keys.end())
    {
        camera.pos = camera.pos + camera.up*dv;
    }
    else if(keys.find('Z') != keys.end())
    {
        camera.pos = camera.pos - camera.up*dv;
    }

    camera.forward = normal(vec3{1,0,1});
    camera.forward = mul( rotation_mat(dax/400.0f, 0, 1, 0), camera.forward );
    vec3 cx = normal(camera.s());
    camera.forward = mul( rotation_mat(day/400.0f, cx.x, cx.y, cx.z), camera.forward );
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    createShaders();
    createSomeGeometry();
    createTextures();

    camera.pos = {0,1,0};

    connect(&frame_timer, SIGNAL(timeout()), this, SLOT(update()));
    frame_timer.setInterval(10);
    frame_timer.start();
    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    ProjMat = perspective(60, w/(float)h, 0.1f, 1500.0f);
    //ProjMat = ortho(-2, 2, -2, 2, -2, 2);
}

void GLWidget::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton){  // test czy klikniety zostal lewy przycisk mychy
        e->pos().x(); // pozycja X mychy na ekranie w chwili klikniecia
        ax = e->pos().x();
        ay = e->pos().y();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent * e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        dax += ax-e->pos().x();
        day += ay-e->pos().y();

        ax = e->pos().x();
        ay = e->pos().y();
    }
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W)
    {
        keys.insert('W');
    }
    if(e->key() == Qt::Key_S)
    {
        keys.insert('S');
    }
    if(e->key() == Qt::Key_A)
    {
        keys.insert('A');
    }
    if(e->key() == Qt::Key_D)
    {
        keys.insert('D');
    }
    if(e->key() == Qt::Key_Q)
    {
        keys.insert('Q');
    }
    if(e->key() == Qt::Key_Z)
    {
        keys.insert('Z');
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W)
    {
        keys.erase(keys.find('W'));
    }
    if(e->key() == Qt::Key_S)
    {
        keys.erase(keys.find('S'));
    }
    if(e->key() == Qt::Key_A)
    {
        keys.erase(keys.find('A'));
    }
    if(e->key() == Qt::Key_D)
    {
        keys.erase(keys.find('D'));
    }
    if(e->key() == Qt::Key_Q)
    {
        keys.erase(keys.find('Q'));
    }
    if(e->key() == Qt::Key_Z)
    {
        keys.erase(keys.find('Z'));
    }
}

void GLWidget::paintGL()
{
    processCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    mat4 MView = camera.matrix();

    float dt = frame/10.0f;

    if(shaders.contains("background"))
    {
        shaders["background"]->use();
        shaders["background"]->setUniform("Resolution", vec2{width(), height()});
        shaders["background"]->setUniform("Forward", camera.forward);
        glDisable(GL_DEPTH_TEST);
        geometry["background"]->render();
        glEnable(GL_DEPTH_TEST);

    }

    if(shaders.contains("ads"))
    {
        shaders["ads"]->use();
        shaders["ads"]->setUniform("MProj", ProjMat);
        shaders["ads"]->setUniform("MVMat", MView);
        vec3 lightPos = {0, 0, 0};
        vec3 lightColor = {1,1,1};
        //vec3 materialColor = {0.2, 0.7, 0.1};
        vec3 materialColor = {1.1, 1.8, 1.0};

        shaders["ads"]->setUniform("LightColor", lightColor);
        shaders["ads"]->setUniform("LightPosition", lightPos);
        shaders["ads"]->setUniform("MaterialColor", materialColor);

        textures2d["hmap"]->bind(0);
        shaders["ads"]->setUniform("HMap", 0);
        geometry["terrain"]->render();
        textures2d["hmap"]->unbind();

        textures2d["grass"]->bind(0);
        shaders["ads"]->setUniform("HMap", 0);
        geometry["plane"]->render();
        textures2d["grass"]->unbind();

    }

    if(shaders.contains("basic"))
    {
        shaders["basic"]->use();
        shaders["basic"]->setUniform("MProj", ProjMat);
        shaders["basic"]->setUniform("MVMat", MView);
        geometry["main_axes"]->render();


    }

    if(shaders.contains("billboard")){
        shaders["billboard"]->use();
        textures2d["billboard"]->bind(0);
        shaders["billboard"]->setUniform("MProj", ProjMat);
        shaders["billboard"]->setUniform("MVMat", MView);

        shaders["billboard"]->setUniform("Size", billboard->getSize());
        shaders["billboard"]->setUniform("Position", billboard->getPosition());

        shaders["billboard"]->setUniform("CameraRight_worldspace", camera.up);
        shaders["billboard"]->setUniform("CameraUp_worldspace", camera.s());

        geometry["billboard"]->render();
        textures2d["billboard"]->unbind();

    }

    frame++;
    PRINT_GL_ERRORS("Widget::paintGL(): ");
}

