#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define RAFGL_IMPLEMENTATION
#include <rafgl.h>

#include <game_constants.h>
#include <main_state.h>

int main(int argc, char *argv[])
{

    rafgl_game_t game;

    rafgl_game_init(&game, "main", 1280, 720, 0);
    rafgl_game_add_named_game_state(&game, main_state);
    rafgl_game_start(&game, NULL);

    return 0;
}
