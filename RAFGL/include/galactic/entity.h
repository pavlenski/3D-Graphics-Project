#ifndef ENTETIES_H_INCLUDED
#define ENTETIES_H_INCLUDED

#include <rafgl.h>
#include <galactic/shader.h>

typedef struct _entity_t {

    unsigned int vertex_count;
    GLuint       vao_id;
    vec3_t       position;
    float        rx, ry, rz, scale;

} entity_t;

typedef struct _master_entity_t {

    GLuint vao_id;
    unsigned int vertex_count, entity_count;
    shader_t shader;
    entity_t * entities;

} master_entity_t;

/* initializes desired entity */
entity_t init_entity( vec3_t position, float rx, float ry, float rz, float scale );

/* initializes entity on desired position and on default rotation and scale variables */
entity_t init_entity_default( vec3_t position );

/* returns transformation matrix of an entity ( the matrix data depends on the entity data )*/
mat4_t entity_get_transformation_matrix( entity_t ent );

/* initializes master entity */
master_entity_t init_master_entity( entity_t * entities, shader_t shader, rafgl_meshPUN_t model, unsigned int count );

#endif // ENTETIES_H_INCLUDED
