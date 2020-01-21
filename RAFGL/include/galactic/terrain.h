#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <rafgl.h>
#include <galactic/texture.h>

typedef struct _terrain_t {

    float x, z;
    GLuint vao_id, blendmap_id;
    int vertex_count;
    texture_pack_terrain_t texture_pack;

} terrain_t;

typedef struct _terrain_vertex_t {

    vec3_t position;
    float u, v;
    vec3_t normal;

} terrain_vertex_t;

/* initializes terrain */
terrain_t init_terrain( int grid_x , int grid_z, texture_pack_terrain_t texture_pack, char * blendmap_path );

/* returns the 4x4 transformation matrix of the desired terrain */
mat4_t terrain_get_transformation_matrix( terrain_t terrain );

#endif // TERRAIN_H_INCLUDED
