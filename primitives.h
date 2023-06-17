#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"

Geometry* createCircleGeometry(float radius, int n, vec3 color);

Geometry *createAxesGeometry();

Geometry *createPlaneGeometry(vec2 size, vec3 color);

Geometry* createBoxGeometry(vec3 size, vec3 color);

Geometry* createSphereGeometry(float radius, int rings, int sectors, vec3 color);

Geometry* createTerrainGeometry(int w, int h, float* data, vec3 scales, vec3 shifts);

#endif // PRIMITIVES_H
