#include "billboard.h"



Billboard::Billboard(vec2 size, vec3 color, vec3 position){
    this->size=size;
    this->color=color;
    this->position=position;

    this->geometry = createGeometry();
}


Geometry* Billboard::createGeometry(){
    Geometry* geometry = new Geometry();
    {
        vec2 uv[4] = {{1, 0}, {0, 0}, {1, 1}, {0, 1}};
        geometry->primitiveMode = GL_TRIANGLES;
        vec3 verts[]  = { {-size.x,  size.y, 0},
                          { size.x,  size.y, 0},
                          {-size.x, -size.y, 0},
                          { size.x, -size.y, 0}
                        };

        uint indices[] = { 0,1,2, 2,3,1 };

        geometry->setIndices(indices, 6);
        geometry->setVertices(0, verts, 4);
        geometry->setAttribute(1, uv, 4);
    }
    return geometry;
}

void Billboard::render(){
    geometry->render();
}

vec3 Billboard::getPosition(){
    return position;
}

vec2 Billboard::getSize(){
    return size;
}

Geometry* Billboard::getGeometry(){
    return geometry;
}
