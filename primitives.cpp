#include "primitives.h"


Geometry* createCircleGeometry(float radius, int n, vec3 color)
{
    Geometry* geometry = new Geometry();
    {
        geometry->primitiveMode = GL_TRIANGLE_FAN;
        std::vector<vec3> verts(n+2);
        std::vector<vec3> colors(n+2);
        verts[0] = {0,0,0};
        colors[0] = color;
        for(int i=0; i<n; i++)
        {
            verts[i+1] = {sin(i/(float)n*2*M_PI), cos(i/(float)n*2*M_PI), 0};
            colors[i+1] = color;
        }
        verts[n+1] = {0, 1, 0};
        colors[n+1] = color;
        geometry->setVertices(0, verts.data(), verts.size());
        geometry->setAttribute(1, colors.data(), verts.size());
    }
    return geometry;
}

Geometry *createAxesGeometry()
{
    Geometry* geometry = new Geometry();
    {
        geometry->primitiveMode = GL_LINES;
        vec3 verts[] = { {0,0,0}, {1.0,0,0}, {0,0,0}, {0,1.0,0}, {0,0,0}, {0,0,1.0} };
        vec3 colors[] = { 1,0,0, 1,0,0,   0,1,0, 0,1,0,   0,0,1, 0,0,1 };
        geometry->setVertices(0, verts, 6);
        geometry->setAttribute(1, colors, 6);
    }
    return geometry;
}

Geometry *createPlaneGeometry(vec2 size, vec3 color)
{
    Geometry* geometry = new Geometry();
    {
        geometry->primitiveMode = GL_TRIANGLES;
        vec3 verts[]  = { {-size.x,  size.y, 0},
                          { size.x,  size.y, 0},
                          {-size.x, -size.y, 0},
                          { size.x, -size.y, 0}
                        };
        vec3 colors[] = { color, color, color, color };
        uint indices[] = { 0,1,2, 2,3,1 };
        geometry->setIndices(indices, 6);
        geometry->setVertices(0, verts, 4);
        geometry->setAttribute(1, colors, 4);
    }
    return geometry;
}


Geometry* createBoxGeometry(vec3 size, vec3 color)
{
    Geometry* geometry = new Geometry();
    {
        int n = 24;
        vec3 origin = {0.0, 0.0, 0.0};
        float w = size.x;
        float h = size.y;
        float d = size.z;

        std::vector<vec3> pos(n);
        std::vector<vec3> colors(n);
        std::vector<uint> indices(36);

        int it=0;
        // sciana z = +1  //front
        pos[it++] = origin + vec3{-w,  h, d};
        pos[it++] = origin + vec3{-w, -h, d};
        pos[it++] = origin + vec3{ w, -h, d};
        pos[it++] = origin + vec3{ w,  h, d};

        // sciana x=+1   //right
        pos[it++] = origin + vec3{w,  h, d};
        pos[it++] = origin + vec3{w, -h, d};
        pos[it++] = origin + vec3{w, -h, -d};
        pos[it++] = origin + vec3{w,  h, -d};

        // sciana z=-1   //back
        pos[it++] = origin + vec3{-w,  h, -d};
        pos[it++] = origin + vec3{-w, -h, -d};
        pos[it++] = origin + vec3{ w, -h, -d};
        pos[it++] = origin + vec3{ w,  h, -d};

        // sciana x=-1   //left
        pos[it++] = origin + vec3{-w,  h, d};
        pos[it++] = origin + vec3{-w, -h, d};
        pos[it++] = origin + vec3{-w, -h, -d};
        pos[it++] = origin + vec3{-w,  h, -d};

        // sciana y=1  //top
        pos[it++] = origin + vec3{-w, h, -d};
        pos[it++] = origin + vec3{-w, h,  d};
        pos[it++] = origin + vec3{ w, h,  d};
        pos[it++] = origin + vec3{ w, h, -d};

        // sciana y=-1  //bottom
        pos[it++] = origin + vec3{-w, -h, -d};
        pos[it++] = origin + vec3{-w, -h,  d};
        pos[it++] = origin + vec3{ w, -h,  d};
        pos[it++] = origin + vec3{ w, -h, -d};

        for(int i=0; i<n; i++)
            colors[i] = color;
        geometry->setVertices(0, pos.data(), n);
        geometry->setAttribute(1, colors.data(), n);

        it=0;
        indices[it++] = 0;    indices[it++] = 1;    indices[it++] = 2;    indices[it++] = 0;    indices[it++] = 2;    indices[it++] = 3;
        indices[it++] = 4;    indices[it++] = 5;    indices[it++] = 6;    indices[it++] = 4;    indices[it++] = 6;    indices[it++] = 7;
        indices[it++] = 8;    indices[it++] = 11;   indices[it++] = 10;   indices[it++] = 8;    indices[it++] = 10;   indices[it++] = 9;
        indices[it++] = 12;   indices[it++] = 15;   indices[it++] = 14;   indices[it++] = 12;   indices[it++] = 14;   indices[it++] = 13;
        indices[it++] = 16;   indices[it++] = 17;   indices[it++] = 18;   indices[it++] = 16;   indices[it++] = 18;   indices[it++] = 19;
        indices[it++] = 20;   indices[it++] = 23;   indices[it++] = 22;   indices[it++] = 20;   indices[it++] = 22;   indices[it++] = 21;

        geometry->setIndices(indices.data(), indices.size());
    }
    return geometry;
}

Geometry* createSphereGeometry(float radius, int rings, int sectors, vec3 color)
{
    Geometry* geometry = new Geometry();
    geometry->primitiveMode = GL_TRIANGLES;

    int nv = (rings-1) * sectors + 2;
    vec3* verts = new vec3[nv];
    float dth =   M_PI / rings;
    float da  = 2*M_PI / sectors;
    float th = -M_PI/2.0 + dth;
    int i, j, iv=1;
    float a, ct, st, ca, sa;

    //pasy trojkatow od 1 do faces_h-1
    for(i=1; i<rings; i++)
    {
        ct = cos(th);
        st = sin(th);
        a = 0;
        for(j=0; j<sectors; j++)
        {
            ca = cos(a);
            sa = sin(a);
            verts[iv].x = radius * ct * ca;
            verts[iv].z = radius * ct * sa;
            verts[iv].y = radius * st;
            iv++;
            a += da;
        }
        th += dth;
    }

    // wierzcholek na samym dole
    verts[0] = vec3{0, -radius, 0};
    // wierzcholek na samej gorze
    verts[nv-1] = vec3{0,radius,0};

    geometry->setVertices(0, verts, nv);
    vec3* colors = new vec3[nv];
    for(int i=0; i<nv; i++) colors[i] = color;

    geometry->setAttribute(1, colors, nv);
    delete[] verts;
    delete[] colors;

    /////////////////////////////////////////
    //indeksacja

    uint *indices = new uint[6*nv];
    int idx=0;
    // trojkaty na samym dole
    for(i=0; i<sectors-1; i++)
    {
        indices[idx++] = 0;
        indices[idx++] = i+1;
        indices[idx++] = i+2;
    }
    indices[idx++] = 0;
    indices[idx++] = i+1;
    indices[idx++] = 1;


    // pasy indeksow w srodku
    for(j=0; j<rings-2; j++)
    {
        for(i=1; i<sectors; i++)
        {
            indices[idx++] = sectors*j + sectors+i;
            indices[idx++] = sectors*j + i+1;
            indices[idx++] = sectors*j + i;
            indices[idx++] = sectors*j + sectors+i+1;
            indices[idx++] = sectors*j + i+1;
            indices[idx++] = sectors*j + sectors+i;
        }
        indices[idx++] = sectors*j + sectors+i;
        indices[idx++] = sectors*j + 1;
        indices[idx++] = sectors*j + i;
        indices[idx++] = sectors*j + sectors+1;
        indices[idx++] = sectors*j + 1;
        indices[idx++] = sectors*j + sectors+i;
    }

    // trojkaty na samej gorze
    for(i=0; i<sectors-1; i++)
    {
        indices[idx++] = nv-1 - sectors + i+1;
        indices[idx++] = nv-1 - sectors + i;
        indices[idx++] = nv-1;
    }
    indices[idx++] = nv-1 - sectors;
    indices[idx++] = nv-1 - sectors + i;
    indices[idx++] = nv-1;

    geometry->setIndices(indices, idx);
    delete[] indices;

    return geometry;
}

Geometry *createTerrainGeometry(int w, int h, float *data, vec3 scales, vec3 shifts)
{
    Geometry* geom = new Geometry();
    geom->primitiveMode = GL_TRIANGLES;

    std::vector<vec3> vertices(w*h);
    std::vector<vec3> colors(w*h);
    std::vector<uint> indices(2*3*(w-1)*(h-1));

    for(int z=0; z<h; z++)
        for(int x=0; x<w; x++)
        {
            vertices[x+z*w] = vec3{x*scales.x + shifts.x,
                                   0, //data[x+z*w]*scales.y + shifts.y,
                                   z*scales.z + shifts.z};
            colors[x+z*w] = vec3{data[x+z*w],data[x+z*w],data[x+z*w]};
        }

    int idx = 0, i = 0;
    for(int z=0; z<h-1; z++)
    {
        for(int x=0; x<w-1; x++)
        {
            indices[idx]   = i;
            indices[idx+1] = i+w;
            indices[idx+2] = i+1;

            indices[idx+3] = i+1;
            indices[idx+4] = i+w;
            indices[idx+5] = i+w+1;

            idx += 6;
            i++;
        }
        i++;
    }

    std::vector<vec3> normals(w*h, vec3{0,0,0});
    idx = 0, i = 0;
    for(int z=0; z<h-1; z++)
    {
        for(int x=0; x<w-1; x++)
        {
            vec3 v1 = vertices[indices[idx]];
            vec3 v2 = vertices[indices[idx+1]];
            vec3 v3 = vertices[indices[idx+2]];
            vec3 n = calcNormal(v1, v2, v3);
            normals[indices[idx]]   += n;
            normals[indices[idx+1]] += n;
            normals[indices[idx+2]] += n;

            v1 = vertices[indices[idx+3]];
            v2 = vertices[indices[idx+4]];
            v3 = vertices[indices[idx+5]];
            n = calcNormal(v1, v2, v3);
            normals[indices[idx+3]] += n;
            normals[indices[idx+4]] += n;
            normals[indices[idx+5]] += n;
            idx += 6;
        }
    }

    for(int i=0; i<w*h; i++)
        normalize(normals[i]);

    geom->setVertices(0, vertices.data(), vertices.size());
    geom->setAttribute(1, colors.data(), colors.size());
    geom->setAttribute(2, normals.data(), normals.size());
    geom->setIndices(indices.data(), indices.size());

    std::vector<vec2> uv(w*h);

    for(int z=0; z<h; z++)
        for(int x=0; x<w; x++)
        {
            uv[x+z*w] = vec2{x/(float)w,z/(float)h};
        }

    geom->setAttribute(3, uv.data(), uv.size());
    return geom;
}





















