#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "mathgl.h"
#include "geometry.h"

class Billboard{
private:
    vec2 size;
    vec3 color;
    vec3 position;

    Geometry* geometry;

    Geometry* createGeometry();
public:
    Billboard(vec2 size, vec3 color, vec3 position);
    ~Billboard();


    void movePosition();
    void render();
    vec3 getPosition();
    vec2 getSize();
    Geometry* getGeometry();
};

#endif //BILLBOARD_H


































