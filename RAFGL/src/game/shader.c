#include <galactic/shader.h>
#include <galactic/camera.h>
#include <galactic/entity.h>
#include <galactic/light.h>
#include <game_constants.h>
#include <rafgl.h>

shader_t init_shader( char * shaders_folder_path ) {

    shader_t shader;

        shader.shader_program_id          = rafgl_program_create_from_name( shaders_folder_path );
        shader.uni_camera_position        = glGetUniformLocation(shader.shader_program_id, "uni_camera_position");
        shader.uni_light_direction        = glGetUniformLocation(shader.shader_program_id, "uni_light_direction");
        shader.uni_ambient_light          = glGetUniformLocation(shader.shader_program_id, "uni_ambient_light");
        shader.uni_object_colour          = glGetUniformLocation(shader.shader_program_id, "uni_object_colour");
        shader.uni_light_colour           = glGetUniformLocation(shader.shader_program_id, "uni_light_colour");
        shader.uni_shine_damper           = glGetUniformLocation(shader.shader_program_id, "uni_shine_damper");
        shader.uni_reflectivity           = glGetUniformLocation(shader.shader_program_id, "uni_reflectivity");
        shader.uni_sky_colour             = glGetUniformLocation(shader.shader_program_id, "uni_sky_colour");
        shader.uni_M                      = glGetUniformLocation(shader.shader_program_id, "uni_M");
        shader.uni_V                      = glGetUniformLocation(shader.shader_program_id, "uni_V");
        shader.uni_P                      = glGetUniformLocation(shader.shader_program_id, "uni_P");

    return shader;
}

shader_terrain_t init_shader_terrain( char * shaders_folder_path ) {

    shader_terrain_t shader;

        shader.shader_program_id          = rafgl_program_create_from_name( shaders_folder_path );
        shader.uni_camera_position        = glGetUniformLocation(shader.shader_program_id, "uni_camera_position");
        shader.uni_light_direction        = glGetUniformLocation(shader.shader_program_id, "uni_light_direction");
        shader.uni_ambient_light          = glGetUniformLocation(shader.shader_program_id, "uni_ambient_light");
        shader.uni_light_colour           = glGetUniformLocation(shader.shader_program_id, "uni_light_colour");
        shader.uni_sky_colour             = glGetUniformLocation(shader.shader_program_id, "uni_sky_colour");
        shader.uni_M                      = glGetUniformLocation(shader.shader_program_id, "uni_M");
        shader.uni_V                      = glGetUniformLocation(shader.shader_program_id, "uni_V");
        shader.uni_P                      = glGetUniformLocation(shader.shader_program_id, "uni_P");
        shader.uni_background_texture     = glGetUniformLocation(shader.shader_program_id, "uni_background_texture");
        shader.uni_r_texture              = glGetUniformLocation(shader.shader_program_id, "uni_r_texture");
        shader.uni_g_texture              = glGetUniformLocation(shader.shader_program_id, "uni_g_texture");
        shader.uni_b_texture              = glGetUniformLocation(shader.shader_program_id, "uni_b_texture");
        shader.uni_blend_map              = glGetUniformLocation(shader.shader_program_id, "uni_blend_map");
        shader.uni_reflection_flag        = glGetUniformLocation(shader.shader_program_id, "uni_reflection_flag");
        shader.uni_refraction_flag        = glGetUniformLocation(shader.shader_program_id, "uni_refraction_flag");

    return shader;
}

shader_water_t init_shader_water( char * shaders_folder_path ) {

    shader_water_t shader;

        shader.shader_program_id          = rafgl_program_create_from_name( shaders_folder_path );
        shader.uni_camera_position        = glGetUniformLocation(shader.shader_program_id, "uni_camera_position");
        shader.uni_light_direction        = glGetUniformLocation(shader.shader_program_id, "uni_light_direction");
        shader.uni_ambient_light          = glGetUniformLocation(shader.shader_program_id, "uni_ambient_light");
        shader.uni_light_colour           = glGetUniformLocation(shader.shader_program_id, "uni_light_colour");
        shader.uni_shine_damper           = glGetUniformLocation(shader.shader_program_id, "uni_shine_damper");
        shader.uni_reflectivity           = glGetUniformLocation(shader.shader_program_id, "uni_reflectivity");
        shader.uni_sky_colour             = glGetUniformLocation(shader.shader_program_id, "uni_sky_colour");
        shader.uni_y_offset               = glGetUniformLocation(shader.shader_program_id, "uni_y_offset");
        shader.uni_reflection_tex         = glGetUniformLocation(shader.shader_program_id, "uni_reflection_tex");
        shader.uni_refraction_tex         = glGetUniformLocation(shader.shader_program_id, "uni_refraction_tex");
        shader.uni_depth_tex              = glGetUniformLocation(shader.shader_program_id, "uni_depth_tex");
        shader.uni_wave_time              = glGetUniformLocation(shader.shader_program_id, "uni_wave_time");
        shader.uni_wave_type              = glGetUniformLocation(shader.shader_program_id, "uni_wave_type");
        shader.uni_M                      = glGetUniformLocation(shader.shader_program_id, "uni_M");
        shader.uni_V                      = glGetUniformLocation(shader.shader_program_id, "uni_V");
        shader.uni_P                      = glGetUniformLocation(shader.shader_program_id, "uni_P");

    return shader;

}
