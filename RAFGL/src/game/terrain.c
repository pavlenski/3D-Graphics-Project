#include <galactic/terrain.h>
#include <galactic/texture.h>
#include <rafgl.h>

#define TERRAIN_VERTEX_COUNT       64
#define TERRAIN_SIZE               100
#define TERRAIN_ARRAY_COUNT        (TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT)
#define TERRAIN_QUAD_COUNT         (TERRAIN_VERTEX_COUNT - 1)
#define TERRAIN_VERTEX_TOTAL_COUNT ((TERRAIN_QUAD_COUNT * TERRAIN_QUAD_COUNT) * 2 * 3 )

#define TERRAIN_MAX_COLOUR_VAL     256
#define TERRAIN_MAX_HEIGHT         16

float get_vertex_height( rafgl_raster_t heightmap, int x, int z ) {

    if(x < 0 || x >= heightmap.height || z < 0 || z >= heightmap.height) return 0.0f;
    float height = pixel_at_m(heightmap, x, z).r;
    height -= TERRAIN_MAX_COLOUR_VAL / 2;
    height /= TERRAIN_MAX_COLOUR_VAL / 2;
    height *= TERRAIN_MAX_HEIGHT;

    return height;
}

vec3_t calculate_normal( rafgl_raster_t heightmap, int x, int z ) {

    float hl = get_vertex_height(heightmap, x - 1, z);
    float hr = get_vertex_height(heightmap, x + 1, z);
    float hd = get_vertex_height(heightmap, x, z + 1);
    float hu = get_vertex_height(heightmap, x, z - 1);
    vec3_t normal = vec3m( hl - hr, 2.0f , hd - hu);
    normal = v3_norm(normal);
    
    return normal;
}

terrain_t init_terrain( int grid_x , int grid_z, texture_pack_terrain_t texture_pack, char * blendmap_path ) {


    terrain_vertex_t vertices[TERRAIN_ARRAY_COUNT];
    terrain_vertex_t final_vertices[TERRAIN_VERTEX_TOTAL_COUNT];

    rafgl_raster_t heightmap;
    rafgl_raster_load_from_image(&heightmap, "res/images/heightmap64.png");
    // printf("ghae %lf\n", get_vertex_height(heightmap, 32, 32) );

    int i, j, vertex_pointer = 0;

    for(i = 0 ; i < TERRAIN_VERTEX_COUNT ; i++) {
        for(j = 0 ; j < TERRAIN_VERTEX_COUNT ; j++) {

            vertices[vertex_pointer].position = vec3m( (float)j / ((float)TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE,
                                           get_vertex_height(heightmap, j, i),
                                          (float)i / ((float)TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE);

            // vertices[vertex_pointer].normal = vec3m( 0.0f, 1.0f, 0.0f );
            vertices[vertex_pointer].normal = calculate_normal(heightmap, j, i);

            vertices[vertex_pointer].u = (float)j / ((float)TERRAIN_VERTEX_COUNT - 1);
            vertices[vertex_pointer].v = (float)i / ((float)TERRAIN_VERTEX_COUNT - 1);

            vertex_pointer++;

        }
    }

    // printf("\n\nVERTEX_COUNT = %d\n\n", TERRAIN_ARRAY_COUNT);

    vertex_pointer = 0;

    for(i = 0 ; i < TERRAIN_QUAD_COUNT ; i++) {
        for(j = 0 ; j < TERRAIN_QUAD_COUNT ; j++) {

            /* first triangle (top left) */
            int index = i * TERRAIN_VERTEX_COUNT + j + 1;
            final_vertices[vertex_pointer].position = vertices[index].position;     // top-right vertex
            final_vertices[vertex_pointer].normal   = vertices[index].normal;
            final_vertices[vertex_pointer].u        = vertices[index].u;
            final_vertices[vertex_pointer++].v      = vertices[index].v;

            index = i * TERRAIN_VERTEX_COUNT + j;
            final_vertices[vertex_pointer].position = vertices[index].position;     // bot-left vertex
            final_vertices[vertex_pointer].normal   = vertices[index].normal;
            final_vertices[vertex_pointer].u        = vertices[index].u;
            final_vertices[vertex_pointer++].v      = vertices[index].v;

            index = (i + 1) * TERRAIN_VERTEX_COUNT + j;
            final_vertices[vertex_pointer].position = vertices[index].position;     // bottm-left vertex
            final_vertices[vertex_pointer].normal   = vertices[index].normal;
            final_vertices[vertex_pointer].u        = vertices[index].u;
            final_vertices[vertex_pointer++].v      = vertices[index].v;

            /* second triangle (bottom right) */
            index = i * TERRAIN_VERTEX_COUNT + j + 1;
            final_vertices[vertex_pointer].position = vertices[index].position;     // top-right vertex
            final_vertices[vertex_pointer].normal   = vertices[index].normal;
            final_vertices[vertex_pointer].u        = vertices[index].u;
            final_vertices[vertex_pointer++].v      = vertices[index].v;

            index = (i + 1) * TERRAIN_VERTEX_COUNT + j;
            final_vertices[vertex_pointer].position = vertices[index].position;     // bot-left vertex
            final_vertices[vertex_pointer].normal   = vertices[index].normal;
            final_vertices[vertex_pointer].u        = vertices[index].u;
            final_vertices[vertex_pointer++].v      = vertices[index].v;

            index = (i + 1) * TERRAIN_VERTEX_COUNT + j + 1;
            final_vertices[vertex_pointer].position = vertices[index].position;   // bot-right vertex
            final_vertices[vertex_pointer].normal   = vertices[index].normal;
            final_vertices[vertex_pointer].u        = vertices[index].u;
            final_vertices[vertex_pointer++].v      = vertices[index].v;
            // printf("VERTEX (%d), x: %lf - y: %lf - z: %lf - u: %lf - v: %lf - normal( %lf, %lf, %lf)\n", vertex_pointer, final_vertices[vertex_pointer - 1].position.x,
            //                                                                   final_vertices[vertex_pointer - 1].position.y,
            //                                                                   final_vertices[vertex_pointer - 1].position.z,
            //                                                                   final_vertices[vertex_pointer - 1].u,
            //                                                                   final_vertices[vertex_pointer - 1].v,
            //                                                                   final_vertices[vertex_pointer - 1].normal.x,
            //                                                                   final_vertices[vertex_pointer - 1].normal.y,
            //                                                                   final_vertices[vertex_pointer - 1].normal.z);

        }
    }

    GLuint vao;
    GLuint data_buffer;
	glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

	glGenBuffers(1, &data_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, data_buffer);

    glBufferData(GL_ARRAY_BUFFER, TERRAIN_VERTEX_TOTAL_COUNT * sizeof(terrain_vertex_t), final_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(terrain_vertex_t), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(terrain_vertex_t), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(terrain_vertex_t), (void*)(5 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    terrain_t terrain;
        terrain.vao_id = vao;
        terrain.x = grid_x * TERRAIN_SIZE;
        terrain.z = grid_z * TERRAIN_SIZE;
        terrain.vertex_count = TERRAIN_VERTEX_TOTAL_COUNT;
        terrain.texture_pack = texture_pack;
        terrain.blendmap_id = init_terrain_blend_map(blendmap_path);

    return terrain;
}

mat4_t terrain_get_transformation_matrix( terrain_t terrain ) {

    mat4_t transf_mat = m4_identity();
    transf_mat        = m4_mul( transf_mat, m4_translation( vec3m(terrain.x, 0.0f, terrain.z) ) );

    return transf_mat;
}
