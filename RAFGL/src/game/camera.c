#include <galactic/camera.h>
#include <game_constants.h>
#include <stdio.h>
#include <stdlib.h>
#include <rafgl.h>
#include <math.h>

#define DEFAULT_MOVEMENT_SPEED   15.5f
#define DEFAULT_ANGLE_SPEED      M_PIf * 0.4f
#define DEFAULT_ANGLE           -M_PIf * 0.5f
#define DEFAULT_H_OFFSET         0
#define DEFAULT_FOV              60.0f
#define NEAR_PLANE               0.1f
#define FAR_PLANE                1000.0f

#define DEFAULT_CAMERA_POSITION  vec3m( 0.0f, 0.0f, 4.0f )

#define CURSOR_SHOW 1
#define CURSOR_HIDE 0

camera_t init_camera( vec3_t position ) {

    camera_t camera;
    camera.position = position;
    camera.aim_dir  = vec3m( 0.0f, 0.0f, -1.0f );
    camera.target   = vec3m( 0.0f, 0.0f,  0.0f );
    camera.up       = vec3m( 0.0f, 1.0f,  0.0f );

    camera.h_offset     =  DEFAULT_H_OFFSET;
    camera.angle        =  DEFAULT_ANGLE;
    camera.angle_speed  =  DEFAULT_ANGLE_SPEED;
    camera.move_speed   =  DEFAULT_MOVEMENT_SPEED;

    camera.FOV    = DEFAULT_FOV;
    camera.aspect = 0.0f;

    return camera;

}
// TODO keep camera in check

void camera_update( camera_t* camera, cursor_t* cursor, rafgl_game_data_t* game_data, GLFWwindow *window, float delta_time ) {
    
    if(game_data->is_lmb_down) {

        if(cursor->reshow_cursor == CURSOR_HIDE) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        float ydelta = game_data->mouse_pos_y - game_data->raster_height / 2;
        float xdelta = game_data->mouse_pos_x - game_data->raster_width / 2;

        if(!cursor->last_lmb) {
            ydelta = 0;
            xdelta = 0;
        }

        camera->h_offset -= ydelta / game_data->raster_height;
        camera->angle += (xdelta / game_data->raster_width) * camera->angle_speed;

        glfwSetCursorPos(window, game_data->raster_width / 2, game_data->raster_height / 2);
        cursor->reshow_cursor = CURSOR_SHOW;
    } else if(cursor->reshow_cursor) {
        cursor->reshow_cursor = CURSOR_HIDE;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    cursor->last_lmb = game_data->is_lmb_down;

    camera->aim_dir = vec3(cosf(camera->angle), camera->h_offset * camera->angle_speed, sinf(camera->angle));

    if(game_data->keys_down['W']) camera->position = v3_add(camera->position, v3_muls(camera->aim_dir, camera->move_speed * delta_time));
    if(game_data->keys_down['S']) camera->position = v3_add(camera->position, v3_muls(camera->aim_dir, -camera->move_speed * delta_time));

    vec3_t right = v3_cross(camera->aim_dir, vec3(0.0f, 1.0f, 0.0f));
    if(game_data->keys_down['D']) camera->position = v3_add(camera->position, v3_muls(right,  camera->move_speed * delta_time));
    if(game_data->keys_down['A']) camera->position = v3_add(camera->position, v3_muls(right, -camera->move_speed * delta_time));

    if(game_data->keys_down[RAFGL_KEY_SPACE]) camera->position.y += camera->move_speed * delta_time;
    if(game_data->keys_down[RAFGL_KEY_LEFT_SHIFT]) camera->position.y -= camera->move_speed * delta_time;

    float aspect = ((float)(game_data->raster_width)) / game_data->raster_height;
    camera->projection_mat = m4_perspective(camera->FOV, aspect, NEAR_PLANE, FAR_PLANE);
    camera->view_mat = m4_look_at(camera->position, v3_add(camera->position, v3_add(camera->aim_dir, vec3(0.0f, camera->h_offset, 0.0f))), camera->up);
}

void camera_update_reflection_camera( camera_t camera, camera_t* reflection_camera ) {

    reflection_camera->position = camera.position;
    reflection_camera->target = camera.target;
    reflection_camera->up = camera.up;
    reflection_camera->aim_dir = camera.aim_dir;
    reflection_camera->angle = camera.angle;
    reflection_camera->angle_speed = camera.angle_speed;
    reflection_camera->move_speed = camera.move_speed;
    reflection_camera->FOV = camera.FOV;
    reflection_camera->aspect = camera.aspect;
    reflection_camera->projection_mat = camera.projection_mat;

    reflection_camera->h_offset = camera.h_offset * -1;
    float distance = ( camera.position.y - WATER_Y_OFFSET + 1 ) * 2;
    reflection_camera->position.y -= distance;
    reflection_camera->aim_dir.y  *= -1;

    reflection_camera->view_mat = m4_look_at(reflection_camera->position, 
                                  v3_add(reflection_camera->position, 
                                         v3_add(reflection_camera->aim_dir, 
                                         vec3(0.0f, reflection_camera->h_offset, 0.0f))),
                                  reflection_camera->up);

}

mat4_t get_view_projection_mat( camera_t camera ) {

    return m4_mul( camera.projection_mat, camera.view_mat );
    
}
