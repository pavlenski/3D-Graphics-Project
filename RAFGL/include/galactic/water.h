#ifndef WATER_H_INCLUDED
#define WATER_H_INCLUDED

#include <rafgl.h>

typedef struct _water_t {

    float x, y, z;
    GLuint vao_id;
    int vertex_count;

} water_t;

typedef struct _water_vertex_t {

    vec2_t position;
    vec4_t indicators;

} water_vertex_t;

/* initializes water plane */
water_t init_water( int grid_x, int grid_z, float y_offset, int water_type );

mat4_t water_get_transformation_matrix( water_t water );

#endif // WATER_H_INCLUDED
