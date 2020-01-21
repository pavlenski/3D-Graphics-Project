
#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include <rafgl.h>

typedef struct _light_t {

    vec3_t direction , colour, ambient;

} light_t;

/* initializes the desired light */
light_t init_light( vec3_t direction, vec3_t colour, vec3_t ambient );

/* initializes the light to the default position */
light_t init_light_default();

#endif // LIGHT_H_INCLUDED
