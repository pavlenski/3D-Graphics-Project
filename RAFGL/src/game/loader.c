#include <galactic/loader.h>
#include <game_constants.h>

/* STATIC LOADER */

    void load_entity_view_projection_matrix( shader_t shader, camera_t camera ) {
        glUniformMatrix4fv(shader.uni_V, 1, GL_FALSE, (void*) camera.view_mat.m );
        glUniformMatrix4fv(shader.uni_P, 1, GL_FALSE, (void*) camera.projection_mat.m );
    }

    void load_entity_light( shader_t shader, light_t light ) {
        glUniform3f(shader.uni_light_colour, light.colour.x, light.colour.y, light.colour.z);
        glUniform3f(shader.uni_light_direction, light.direction.x, light.direction.y, light.direction.z);
        glUniform3f(shader.uni_ambient_light, light.ambient.x, light.ambient.y, light.ambient.z);
        glUniform3f(shader.uni_sky_colour, SKY_RED, SKY_GREEN, SKY_BLUE);
    }

    void load_entity_camera( shader_t shader, camera_t camera ) {
        glUniform3f(shader.uni_camera_position, camera.position.x, camera.position.y, camera.position.z);
    }

    void load_entity_colour( shader_t shader, vec3_t object_colour ) {
        glUniform3f(shader.uni_object_colour, object_colour.x, object_colour.y, object_colour.z);
    }

    void load_entity_transformation_matrix( shader_t shader, entity_t ent ) {
        glUniformMatrix4fv(shader.uni_M, 1, GL_FALSE, (void *) entity_get_transformation_matrix( ent ).m);
    }

/* TERRAIN LOADER */

    void load_terrain_view_projection_matrix( shader_terrain_t shader, camera_t camera ) {
        glUniformMatrix4fv(shader.uni_V, 1, GL_FALSE, (void*) camera.view_mat.m );
        glUniformMatrix4fv(shader.uni_P, 1, GL_FALSE, (void*) camera.projection_mat.m );
    }

    void load_terrain_light( shader_terrain_t shader, light_t light ) {
        glUniform3f(shader.uni_light_colour, light.colour.x, light.colour.y, light.colour.z);
        glUniform3f(shader.uni_light_direction, light.direction.x, light.direction.y, light.direction.z);
        glUniform3f(shader.uni_ambient_light, light.ambient.x, light.ambient.y, light.ambient.z);
        glUniform3f(shader.uni_sky_colour, SKY_RED, SKY_GREEN, SKY_BLUE);
    }

    void load_terrain_camera( shader_terrain_t shader, camera_t camera ) {
        glUniform3f(shader.uni_camera_position, camera.position.x, camera.position.y, camera.position.z);
    }

    void load_terrain_transformation_matrix( shader_terrain_t shader, terrain_t terr ) {
        glUniformMatrix4fv(shader.uni_M, 1, GL_FALSE, (void *) terrain_get_transformation_matrix( terr ).m);
    }

    void load_terrain_render_type( shader_terrain_t shader, float reflection_flag, float refraction_flag ) {
        glUniform1f(shader.uni_reflection_flag, reflection_flag);
        glUniform1f(shader.uni_refraction_flag, refraction_flag);
    }

/* WATER LOADER */

    void load_water_view_projection_matrix( shader_water_t shader, camera_t camera ) {
        glUniformMatrix4fv(shader.uni_V, 1, GL_FALSE, (void*) camera.view_mat.m );
        glUniformMatrix4fv(shader.uni_P, 1, GL_FALSE, (void*) camera.projection_mat.m );
    }

    void load_water_light( shader_water_t shader, light_t light ) {
        glUniform3f(shader.uni_light_colour, light.colour.x, light.colour.y, light.colour.z);
        glUniform3f(shader.uni_light_direction, light.direction.x, light.direction.y, light.direction.z);
        glUniform3f(shader.uni_ambient_light, light.ambient.x, light.ambient.y, light.ambient.z);
        glUniform3f(shader.uni_sky_colour, SKY_RED, SKY_GREEN, SKY_BLUE);
    }

    void load_water_camera( shader_water_t shader, camera_t camera ) {
        glUniform3f(shader.uni_camera_position, camera.position.x, camera.position.y, camera.position.z);
    }

    void load_water_transformation_matrix( shader_water_t shader, water_t water ) {
        glUniformMatrix4fv(shader.uni_M, 1, GL_FALSE, (void *) water_get_transformation_matrix( water ).m);
    }

    void load_water_y_offset( shader_water_t shader, water_t water ) {
        glUniform1f(shader.uni_y_offset, water.y);
    }

    void load_water_rr_textures( shader_water_t shader, GLuint reflection_tex, GLuint refraction_tex, GLuint refraction_depth_tex ) {

        glUniform1i(shader.uni_reflection_tex, 0);
        glUniform1i(shader.uni_refraction_tex, 1);
        glUniform1i(shader.uni_depth_tex, 2);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, reflection_tex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, refraction_tex);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, refraction_depth_tex);
    }

/*  */