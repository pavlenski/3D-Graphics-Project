#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <rafgl.h>

typedef struct _texture_pack_terrain_t {

    GLuint tex0_id, tex1_id, tex2_id, tex3_id;

} texture_pack_terrain_t;

/* initializes the desired texture pack for terrain */
texture_pack_terrain_t init_terrain_texture_pack( char * tex_path_1 , char * tex_path_2 , char * tex_path_3 , char * tex_path_4 );

GLuint init_terrain_blend_map( char * blend_map_path );

#endif // TEXTURE_H_INCLUDED
