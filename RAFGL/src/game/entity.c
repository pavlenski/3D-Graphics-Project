#include <galactic/entity.h>
#include <math_3d.h>
#include <rafgl.h>

#define ENTITY_DEFAULT_ROTATION 0
#define ENTITY_DEFAULT_SCALE    1

master_entity_t init_master_entity( entity_t * entities, shader_t shader, rafgl_meshPUN_t model, unsigned int count ) {

    master_entity_t mentity;

        mentity.vertex_count = model.vertex_count;
        mentity.entities     = entities;
        mentity.vao_id       = model.vao_id;
        mentity.shader       = shader;
        mentity.entity_count = count;

    return mentity;
}

entity_t init_entity( vec3_t position, float rx, float ry, float rz, float scale ) {

    entity_t entity;

        entity.position     = position;
        entity.scale        = scale;
        entity.rx           = rx;
        entity.ry           = ry;
        entity.rz           = rz;

    return entity;
}

entity_t init_entity_default( vec3_t position ) {

    entity_t entity;

        entity.position     = position;
        entity.scale        = ENTITY_DEFAULT_SCALE;
        entity.rx           = ENTITY_DEFAULT_ROTATION;
        entity.ry           = ENTITY_DEFAULT_ROTATION;
        entity.rz           = ENTITY_DEFAULT_ROTATION;

    return entity;

}

mat4_t entity_get_transformation_matrix( entity_t ent ) {

    mat4_t transf_mat = m4_identity();
    transf_mat        = m4_mul( transf_mat, m4_translation( ent.position ) );
    transf_mat        = m4_mul( transf_mat, m4_rotation_y( ent.ry ) );
    transf_mat        = m4_mul( transf_mat, m4_rotation_x( ent.rx ) );
    transf_mat        = m4_mul( transf_mat, m4_rotation_z( ent.rz ) );
    transf_mat        = m4_mul( transf_mat, m4_scaling( vec3m( ent.scale, ent.scale, ent.scale ) ) );

    return transf_mat;
}

void entity_log( entity_t * ent ) {
    printf(" posx: %lf, posy: %lf, posz: %lf, vao_id: %d, v-count: %d \n", ent->position.x, ent->position.y, ent->position.z, ent->vao_id, ent->vertex_count);
}