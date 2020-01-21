#include <galactic/fbo.h>
#include <game_constants.h>
#include <rafgl.h>

fbo_t init_water_fbo( int width, int height ) {

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    /* colour texture attachment */

    GLuint texture_colour;
    glGenTextures(1, &texture_colour);
    glBindTexture(GL_TEXTURE_2D, texture_colour);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_colour, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    /* depth texture attachment */

    GLuint texture_depth;
    glGenTextures(1, &texture_depth);
    glBindTexture(GL_TEXTURE_2D, texture_depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_depth, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    /* depth buffer attachment */

    GLuint depth_buffer;
    glGenRenderbuffers(1, &depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    /*  */

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    printf("WATER-LOG: Initializing water fbo with W: %d - H: %d...\n", width, height);

    fbo_t frame_buffer_object;
    frame_buffer_object.id = fbo;
    frame_buffer_object.height = height;
    frame_buffer_object.width = width;
    frame_buffer_object.colour_tex = texture_colour;
    frame_buffer_object.depth_tex = texture_depth;

    return frame_buffer_object;

}

void bind_frame_buffer(fbo_t fbo) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
    glViewport(0, 0, fbo.width, fbo.height);
}

void unbind_frame_buffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, RASTER_WIDTH, RASTER_HEIGHT);
}
