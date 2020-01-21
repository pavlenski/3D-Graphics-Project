#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <galactic/terrain.h>
#include <galactic/camera.h>
#include <galactic/entity.h>
#include <galactic/shader.h>
#include <galactic/cursor.h>
#include <galactic/light.h>
#include <galactic/water.h>
#include <rafgl.h>

void render_entities( master_entity_t master_entity , light_t light , camera_t camera , cursor_t cursor );

void render_terrains( terrain_t * terrains , shader_terrain_t shader , light_t light , camera_t camera , cursor_t cursor , unsigned int count );

void render_waters( water_t * waters , shader_water_t shader , light_t light , camera_t camera , cursor_t cursor , GLuint reflection_tex , GLuint refraction_tex , GLuint refraction_depth_tex , unsigned int count , float wave_time, float wave_type);

void render_set_type(int render_type);

#endif // RENDERER_H_INCLUDED
