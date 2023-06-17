QT += gui opengl widgets
CONFIG += debug c++11


equals(QT_MAJOR_VERSION, 6) {
    QT += openglwidgets
}

SOURCES += \
    billboard.cpp \
    geometry.cpp \
    main.cpp \
    glwidget.cpp \
    glslprogram.cpp \
    mathgl.cpp \
    primitives.cpp \
    stb_image.cpp \
    texture2d.cpp

HEADERS += \
    billboard.h \
    geometry.h \
    glwidget.h \
    glslprogram.h \
    mathgl.h \
    primitives.h \
    stb_image.h \
    texture2d.h

unix {
    LIBS += -lGLU
}

win32 {
    LIBS += -lglu32 -lopengl32
}

DISTFILES += \
    billboardf.glsl \
    billboardv.glsl \
    f_ads.glsl \
    f_background.glsl \
    fshader.glsl \
    v_ads.glsl \
    v_background.glsl \
    vshader.glsl
