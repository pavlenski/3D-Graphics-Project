#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <rafgl.h>
#include <galactic/cursor.h>

typedef struct _camera_t {

    vec3_t position, target, up, aim_dir;

    float angle, angle_speed, move_speed, h_offset, FOV, aspect;

    mat4_t view_mat, projection_mat;

} camera_t;

/* initializes the camera */
camera_t init_camera( vec3_t position );

/* updates the state of the camera */
void camera_update( camera_t* camera, cursor_t* cursor, rafgl_game_data_t* game_data, GLFWwindow* window, float delta_time );

/* updates the state of the reflection camera */
void camera_update_reflection_camera( camera_t camera, camera_t* reflection_camera );

/* returns the view_projection matrix */
mat4_t get_view_projection_mat( camera_t camera );



#endif // CAMERA_H_INCLUDED
