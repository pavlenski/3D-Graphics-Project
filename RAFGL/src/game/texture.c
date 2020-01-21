#include <galactic/texture.h>

#define TEXTURE_LOD_FACTOR -0.5

texture_pack_terrain_t init_terrain_texture_pack( char * tex_path_1 , char * tex_path_2 , char * tex_path_3 , char * tex_path_4 ) {

    rafgl_raster_t raster0;
    rafgl_texture_t texture0;

    rafgl_raster_load_from_image(&raster0, tex_path_1);
    rafgl_texture_init(&texture0);
    rafgl_texture_load_from_raster(&texture0, &raster0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0.tex_id);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, TEXTURE_LOD_FACTOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    rafgl_raster_t raster1;
    rafgl_texture_t texture1;

    rafgl_raster_load_from_image(&raster1, tex_path_2);
    rafgl_texture_init(&texture1);
    rafgl_texture_load_from_raster(&texture1, &raster1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1.tex_id);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, TEXTURE_LOD_FACTOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    rafgl_raster_t raster2;
    rafgl_texture_t texture2;

    rafgl_raster_load_from_image(&raster2, tex_path_3);
    rafgl_texture_init(&texture2);
    rafgl_texture_load_from_raster(&texture2, &raster2);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture2.tex_id);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, TEXTURE_LOD_FACTOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    printf("TEXTURE-LOG: currently loading GL_TEXTURE0, GL_TEXTURE1 and GL_TEXTURE2 slots for regular textures!\n");

    texture_pack_terrain_t tpack;
    tpack.tex0_id = texture0.tex_id;
    tpack.tex1_id = texture1.tex_id;
    tpack.tex2_id = texture2.tex_id;

    return tpack;
}

GLuint init_terrain_blend_map( char * blend_map_path ) {

    rafgl_raster_t raster;
    rafgl_texture_t blendmap_tex;

    rafgl_raster_load_from_image(&raster, blend_map_path);
    rafgl_texture_init(&blendmap_tex);
    rafgl_texture_load_from_raster(&blendmap_tex, &raster);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, blendmap_tex.tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    printf("TEXTURE-BLENDMAP-LOG: currently loading GL_TEXTURE3 slot for blendmap texture!\n");

    return blendmap_tex.tex_id;
}
