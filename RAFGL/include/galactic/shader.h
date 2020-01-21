#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

#include <rafgl.h>
#include <galactic/camera.h>
#include <galactic/light.h>

typedef struct _shader_t {

    GLuint shader_program_id , uni_M , uni_light_direction , uni_object_colour ,
           uni_light_colour , uni_shine_damper , uni_reflectivity , uni_V , uni_P ,
           uni_ambient_light , uni_camera_position, uni_sky_colour;

} shader_t;

typedef struct _shader_terrain_t {

    GLuint shader_program_id,
           uni_sky_colour,
           uni_light_colour,
           uni_ambient_light,
           uni_light_direction,
           uni_camera_position,
           uni_background_texture,
           uni_r_texture,
           uni_g_texture,
           uni_b_texture,
           uni_blend_map,
           uni_reflection_flag,
           uni_refraction_flag,
           uni_M,
           uni_V,
           uni_P;

} shader_terrain_t;

typedef struct _shader_water_t {

    GLuint shader_program_id,
           uni_sky_colour,
           uni_light_colour,
           uni_ambient_light,
           uni_light_direction,
           uni_camera_position,
           uni_reflectivity,
           uni_shine_damper,
           uni_y_offset,
           uni_reflection_tex,
           uni_refraction_tex,
           uni_depth_tex,
           uni_wave_time,
           uni_wave_type,
           uni_M,
           uni_V,
           uni_P;

} shader_water_t;

    /* initializes the desired shader */
    shader_t init_shader( char * shaders_folder_path );

    /* initializes the desired terrain shader */
    shader_terrain_t init_shader_terrain( char * shaders_folder_path );

    /* initializes the desierd water shader */
    shader_water_t init_shader_water( char * shaders_folder_path );

#endif // SHADERS_H_INCLUDED
