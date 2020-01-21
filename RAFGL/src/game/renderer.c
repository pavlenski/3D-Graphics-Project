#include <galactic/renderer.h>
#include <galactic/camera.h>
#include <galactic/entity.h>
#include <galactic/shader.h>
#include <galactic/cursor.h>
#include <galactic/loader.h>
#include <galactic/light.h>
#include <game_constants.h>
#include <rafgl.h>

static int RENDER_TYPE = RENDER_DEFAULT;

/* sets the two flags that are loaded into the shader depending on the render type */
void set_render_flags( float* reflection_flag, float* refraction_flag ) {

    switch (RENDER_TYPE) {

        case RENDER_DEFAULT:
            *reflection_flag = 0.0f;
            *refraction_flag = 0.0f;
            break;

        case RENDER_REFLECTION:
            *reflection_flag = 1.0f;
            *refraction_flag = 0.0f;
            break;

        case RENDER_REFRACTION:
            *reflection_flag = 0.0f;
            *refraction_flag = 1.0f;
            break;

        default:
            *reflection_flag = 0.0f;
            *refraction_flag = 0.0f;
            break;
    }
}

void render_entities( master_entity_t master_entity , light_t light , camera_t camera , cursor_t cursor ) {

    glUseProgram(master_entity.shader.shader_program_id);

    glBindVertexArray(master_entity.vao_id);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    load_entity_view_projection_matrix(master_entity.shader, camera);
    load_entity_light(master_entity.shader, light);
    load_entity_camera(master_entity.shader, camera);
    load_entity_colour(master_entity.shader, RAFGL_YELOW);

    int i;
    for(i = 0 ; i < master_entity.entity_count ; i++) {
        load_entity_transformation_matrix(master_entity.shader, master_entity.entities[i]);
        glDrawArrays(GL_TRIANGLES, 0, master_entity.vertex_count);
    }

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

// TOASK - should 'glBindVertexArray(0)' be called inside the loop or outside ?

void render_terrains( terrain_t* terrains , shader_terrain_t shader , light_t light , camera_t camera , cursor_t cursor , unsigned int count ) {

    float reflection_flag = 0.0f;
    float refraction_flag = 0.0f;

    set_render_flags(&reflection_flag, &refraction_flag);

    glEnable(GL_TEXTURE_2D);

    glUseProgram(shader.shader_program_id);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // shader_load_view_projection_matrix(
    load_terrain_view_projection_matrix(shader, camera);
    load_terrain_light(shader, light);
    load_terrain_camera(shader, camera);
    load_terrain_render_type(shader, reflection_flag, refraction_flag);

    glUniform1i(shader.uni_background_texture, 0);
    glUniform1i(shader.uni_r_texture, 1);
    glUniform1i(shader.uni_g_texture, 2);
    // glUniform1i(shader.uni_b_texture, 0);
    glUniform1i(shader.uni_blend_map, 3);

    int i;
    for(i = 0 ; i < count ; i++) {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, terrains[i].texture_pack.tex0_id);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, terrains[i].texture_pack.tex1_id);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, terrains[i].texture_pack.tex2_id);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, terrains[i].blendmap_id);

        glBindVertexArray(terrains[i].vao_id);

        load_terrain_transformation_matrix(shader, terrains[i]);
        glDrawArrays(GL_TRIANGLES, 0, terrains[i].vertex_count);
        // glBindVertexArray(0);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void render_waters( water_t * waters , shader_water_t shader , light_t light , camera_t camera , cursor_t cursor ,
                    GLuint reflection_tex , GLuint refraction_tex , GLuint refraction_depth_tex , unsigned int count, float wave_time, float wave_type ) {

    glUseProgram(shader.shader_program_id);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    load_water_view_projection_matrix(shader, camera);
    load_water_light(shader, light);
    load_water_camera(shader, camera);
    load_water_rr_textures(shader, reflection_tex, refraction_tex, refraction_depth_tex);
    glUniform1f(shader.uni_wave_time, wave_time);
    glUniform1f(shader.uni_wave_type, wave_type);

    int i;
    for(i = 0 ; i < count ; i++) {
        load_water_y_offset(shader, waters[i]);
        load_water_transformation_matrix(shader, waters[i]);

        glBindVertexArray(waters[i].vao_id);
        glDrawArrays(GL_TRIANGLES, 0, waters[i].vertex_count);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

void render_set_type( int render_type ) {
    RENDER_TYPE = render_type;
}
