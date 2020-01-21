#include <galactic/light.h>
#include <rafgl.h>

#define SUNLIGHT vec3m(1.0f, 0.9f, 0.7f);

light_t init_light( vec3_t direction, vec3_t colour, vec3_t ambient ){

    light_t light;
        light.direction = direction;
        light.colour    = colour;
        light.ambient   = ambient;

    return light;
}

light_t init_light_default() {
    
    light_t light;
        light.direction = vec3m( -1000.0f, -1000.0f, -1000.0f );
        light.colour    = SUNLIGHT;
        light.ambient   = RAFGL_GRAYX(0.13f);

    return light;
}