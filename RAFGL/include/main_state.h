#ifndef MAIN_STATE_H_INCLUDED
#define MAIN_STATE_H_INCLUDED

#include <GLFW/glfw3.h>
#include <rafgl.h>

void main_state_init(GLFWwindow *window, void *args, int width, int height);
void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args);
void main_state_render(GLFWwindow *window, void *args);
void main_state_cleanup(GLFWwindow *window, void *args);

#endif // MAIN_STATE_H_INCLUDED
