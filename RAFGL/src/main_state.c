#include <main_state.h>
#include <glad/glad.h>
#include <math.h>
#include <game_constants.h>
#include <rafgl.h>

#include <galactic/renderer.h>
#include <galactic/terrain.h>
#include <galactic/texture.h>
#include <galactic/camera.h>
#include <galactic/cursor.h>
#include <galactic/entity.h>
#include <galactic/shader.h>
#include <galactic/light.h>
#include <galactic/water.h>
#include <galactic/fbo.h>

/* ALL ENTITY, SHADER, TERRAIN GLOBALS DERIVE FROM <game_constants.h> */

/* MAIN */

    camera_t camera;
    camera_t camera_reflection;
    cursor_t cursor;
    light_t sunlight;

/* TERRAIN */

    terrain_t terrains[TERRAIN_COUNT];
    shader_terrain_t shader_terrain;
    texture_pack_terrain_t tpack;

/* WATER */

    water_t waters_linear[WATER_COUNT];
    water_t waters_low_poly[WATER_COUNT];
    shader_water_t shader_water;

/* MONKEY */

    master_entity_t master_monkey;
    shader_t shader_monkey;
    rafgl_meshPUN_t model_monkey;
    entity_t monkeys[MONKEY_COUNT];

/* FBOS */

    fbo_t reflection_fbo;
    fbo_t refraction_fbo;

master_entity_t bigMONKEY;
entity_t bigMONKEYS[2];

GLuint uni_background_texture, uni_r_texture, uni_g_texture, uni_b_texture, uni_blend_map;

float posy1;
float posx2;

void main_state_init( GLFWwindow *window, void *args, int width, int height ) {

    /* MAIN */

        cursor = init_cursor();
        camera = init_camera( vec3m(50.0f, 20.0f, 80.0f) );
        // camera = init_camera( vec3m(0.0f, 10.0f, 0.0f) );
        camera_reflection = init_camera( vec3m(50.0f, 20.0f, 80.0f) );
        sunlight = init_light( vec3m(-0.5f, -0.2f, 0.0f), vec3m(1.0f, 0.9f, 0.7f), RAFGL_GRAYX(0.06f) );
        //sunlight = init_light_default();

    /* MONKEYS */

        shader_monkey = init_shader( "monkey_shaders" );
        rafgl_meshPUN_init( &model_monkey );
        rafgl_meshPUN_load_from_OBJ( &model_monkey, "res/models/monkey.obj" );

        int i;
        for(i = 0 ; i < MONKEY_COUNT ; i++) monkeys[i] = init_entity( vec3m( (randf() - 0.5f) * 70, 1.0f, ( randf() - 0.5f ) * 70 ), 0, 0, 0, 1 );
        master_monkey = init_master_entity( monkeys, shader_monkey, model_monkey, MONKEY_COUNT );

        bigMONKEYS[0] = init_entity( vec3m( -2.5f, 7.0f, 0.0f ), 0, 0, 0, 2 );
        bigMONKEYS[1] = init_entity( vec3m( 3.0f, 12.0f, 0.0f ), 0, 0, 0, 2 );
        bigMONKEY = init_master_entity( bigMONKEYS, shader_monkey, model_monkey, 2 );

    /* TERRAIN */

        shader_terrain = init_shader_terrain( "terrain_shaders" );

        tpack = init_terrain_texture_pack( "res/images/terrain_tex_1.jpg", "res/images/terrain_tex_5.jpg", "res/images/terrain_tex_4.jpg", "" );

        terrains[0] = init_terrain(  0,  0 , tpack, "res/images/blendmap.png" ); //"res/images/doge.png"
        // terrains[1] = init_terrain(  0, -1 , tpack, "res/images/blendmap.png" );
        // terrains[2] = init_terrain( -1,  0 , tpack, "res/images/blendmap.png" );
        // terrains[3] = init_terrain( -1, -1 , tpack, "res/images/blendmap.png" );

    /* WATER */

        shader_water = init_shader_water( "water_shaders" );
        waters_linear[0] = init_water( 0, 0, WATER_Y_OFFSET, WATER_LINEAR);
        waters_low_poly[0] = init_water( 0, 0, WATER_Y_OFFSET, WATER_LOW_POLY);

        reflection_fbo = init_water_fbo( RASTER_WIDTH, RASTER_HEIGHT );
        refraction_fbo = init_water_fbo( RASTER_WIDTH, RASTER_HEIGHT );

    //
    posy1 = bigMONKEYS[0].position.y;
    posx2 = bigMONKEYS[1].position.x;

    glClearColor(SKY_RED, SKY_GREEN, SKY_BLUE, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthMask(GL_TRUE);
}

float time;
float wave_time;
int f_pressed = 0;
int r_pressed = 0;

int render_type = 2;
double WAVE_TYPE = WAVE_SMOOTH;

void main_state_update( GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args ) {

    time += delta_time;
    wave_time += WATER_WAVE_SPEED * delta_time;

    camera_update( &camera, &cursor, game_data, window, delta_time );
    camera_update_reflection_camera( camera, &camera_reflection );

    int i;
    int spin = -1;
    for(i = 0 ; i < MONKEY_COUNT ; i++) {
        spin = spin == -1 ? 1 : -1;
        monkeys[i].ry = time * spin;
    }

    bigMONKEYS[0].position.y = sin(time) * 5 + posy1;
    bigMONKEYS[1].position.x = sin(time) * 5 + posx2;

    f_pressed = game_data->keys_down['F'];
    r_pressed = game_data->keys_down['R'];

    if(game_data->keys_pressed['1']) render_type = 1;
    if(game_data->keys_pressed['2']) render_type = 2;

    if(game_data->keys_pressed['T']) {
        WAVE_TYPE = WAVE_TYPE == WAVE_SMOOTH ? WAVE_CHAOS : WAVE_SMOOTH;
    }

}

void main_state_render( GLFWwindow *window, void *args ) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind_frame_buffer( reflection_fbo );
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render_set_type( RENDER_REFLECTION );
    // render_terrains( terrains, shader_terrain, sunlight, camera_reflection, cursor, TERRAIN_COUNT );
    // unbind_frame_buffer();

    // bind_frame_buffer( refraction_fbo );
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render_set_type( RENDER_REFRACTION );
    // render_terrains( terrains, shader_terrain, sunlight, camera, cursor, TERRAIN_COUNT );
    // unbind_frame_buffer();

    render_set_type( RENDER_DEFAULT );
    if(r_pressed) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(render_type == 1)
    {
        render_waters( waters_linear, shader_water, sunlight, camera, cursor, reflection_fbo.colour_tex, refraction_fbo.colour_tex, refraction_fbo.depth_tex, WATER_COUNT, wave_time, WAVE_TYPE );

    } else if(render_type == 2)
    {
        render_waters( waters_low_poly, shader_water, sunlight, camera, cursor, reflection_fbo.colour_tex, refraction_fbo.colour_tex, refraction_fbo.depth_tex, WATER_COUNT, wave_time, WAVE_TYPE );

    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // render_terrains( terrains, shader_terrain, sunlight, camera, cursor, TERRAIN_COUNT );

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render_entities( master_monkey, sunlight, camera, cursor );
    // render_entities( bigMONKEY, sunlight, camera, cursor );

    if(f_pressed) rafgl_texture_show( &reflection_fbo.colour_tex, 0 );

}

void main_state_cleanup( GLFWwindow *window, void *args ) {


}
