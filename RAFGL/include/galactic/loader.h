#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

#include <rafgl.h>
#include <galactic/renderer.h>
#include <galactic/camera.h>
#include <galactic/entity.h>
#include <galactic/shader.h>
#include <galactic/cursor.h>
#include <galactic/light.h>
#include <galactic/water.h>

/* STATIC LOADER */

    /* loads the uniform for the view_projection matrix */
    void load_entity_view_projection_matrix( shader_t shader, camera_t camera );

    /* loads the uniform for the light (direction, colour, ambient) */
    void load_entity_light( shader_t shader, light_t light );

    /* loads the uniforms for the camera */
    void load_entity_camera( shader_t shader, camera_t camera );

    /* loads the uniform object colour */
    void load_entity_colour( shader_t shader, vec3_t object_colour );

    /* loads the uniform location for the model_transformation matrix */
    void load_entity_transformation_matrix( shader_t shader, entity_t ent );

/* TERRAIN LOADER */

    /* loads the uniform for the view_projection matrix for terrain */
    void load_terrain_view_projection_matrix( shader_terrain_t shader, camera_t camera );

    /* loads the uniform for the light (direction, colour, ambient) for terrain */
    void load_terrain_light( shader_terrain_t shader, light_t light );

    /* loads the uniforms for the camera for terrain */
    void load_terrain_camera( shader_terrain_t shader, camera_t camera );

    /* loads the uniform location for the model_transformation matrix for terrain */
    void load_terrain_transformation_matrix( shader_terrain_t shader, terrain_t terr );

    /* loads the uniform flags for reflection and refraction, 
    with these flags the shader will know wheather to
    discard certain fragments or include them into the rendering process */
    void load_terrain_render_type( shader_terrain_t shader, float reflection_flag, float refraction_flag );

/* WATER LOADER */

    /* loads the uniform for the view_projection matrix for terrain */
    void load_water_view_projection_matrix( shader_water_t shader, camera_t camera );

    /* loads the uniform for the light (direction, colour, ambient) for terrain */
    void load_water_light( shader_water_t shader, light_t light );

    /* loads the uniforms for the camera for terrain */
    void load_water_camera( shader_water_t shader, camera_t camera );

    /* loads the uniform for the model_transformation matrix for terrain */
    void load_water_transformation_matrix( shader_water_t shader, water_t water );  

    /* loads the uniform for the y offset of the water plane in the world */
    void load_water_y_offset( shader_water_t shader, water_t water ); 

    /* loads the uniform reflection and refraction textures */
    void load_water_rr_textures( shader_water_t shader, GLuint reflection_tex, GLuint refraction_tex, GLuint refraction_depth_tex );

/*  */

#endif // LOADER_H_INCLUDED
