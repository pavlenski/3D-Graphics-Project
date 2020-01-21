#ifndef FBO_H_INCLUDED
#define FBO_H_INCLUDED

#include <rafgl.h>

typedef struct _fbo_t {

    int width, height;
    GLuint id, colour_tex, depth_tex;

} fbo_t;

/* initializes water frame buffer object */
fbo_t init_water_fbo( int width, int height );

/* binds a certain frame buffer object */
void bind_frame_buffer( fbo_t fbo );

/* unbinds the currently bound frame buffer object
(once unbound everything rendering is rendering 
directly to the screen) */
void unbind_frame_buffer();

#endif // FBO_H_INCLUDED
