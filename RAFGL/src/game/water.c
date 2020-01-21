#include <galactic/water.h>
#include <game_constants.h>
#include <rafgl.h>

#define WATER_VERTEX_COUNT       100
#define WATER_SIZE               100
#define WATER_ARRAY_COUNT        (WATER_VERTEX_COUNT * WATER_VERTEX_COUNT)
#define WATER_QUAD_COUNT         (WATER_VERTEX_COUNT - 1)
#define WATER_VERTEX_TOTAL_COUNT ((WATER_QUAD_COUNT * WATER_QUAD_COUNT) * 2 * 3 )

vec2_t vec2_sub( vec2_t a, vec2_t b ) {

    return vec2m( a.x - b.x , a.y - b.y );
}

water_t init_water( int grid_x, int grid_z, float y_offset, int water_type ) {

    water_vertex_t vertices[WATER_ARRAY_COUNT];
    water_vertex_t final_vertices[WATER_VERTEX_TOTAL_COUNT];

    int i, j, vertex_pointer = 0;

    for(i = 0 ; i < WATER_VERTEX_COUNT ; i++) {
        for(j = 0 ; j < WATER_VERTEX_COUNT ; j++) {

            vertices[vertex_pointer].position = vec2m( (float)j / ((float) WATER_VERTEX_COUNT - 1) * WATER_SIZE ,
                                                       (float)i / ((float) WATER_VERTEX_COUNT - 1) * WATER_SIZE);
            vertex_pointer++;
        }
    }

    vertex_pointer = 0;

    for(i = 0 ; i < WATER_QUAD_COUNT ; i++) {
        for(j = 0 ; j < WATER_QUAD_COUNT ; j++) {

            int TOP_RIGHT =  i * WATER_VERTEX_COUNT + j + 1;
            int TOP_LEFT  =  i * WATER_VERTEX_COUNT + j;
            int BOT_LEFT  = (i + 1) * WATER_VERTEX_COUNT + j;
            int BOT_RIGHT = (i + 1) * WATER_VERTEX_COUNT + j + 1;

            int BOT_BOT_LEFT = (i + 2) * WATER_VERTEX_COUNT + j;
            int BOT_BOT_RIGHT = (i + 2) * WATER_VERTEX_COUNT + j + 1;
            int BOT_RIGHT_RIGHT = (i + 1) * WATER_VERTEX_COUNT + j + 2;
            int TOP_RIGHT_RIGHT = i * WATER_VERTEX_COUNT + j + 2;

            // TODO take care when u are on the edges of the grid
            if( i == WATER_QUAD_COUNT - 1 || j == WATER_QUAD_COUNT - 1 ) {
                BOT_BOT_LEFT = BOT_LEFT;
                BOT_BOT_RIGHT = BOT_RIGHT;
                BOT_RIGHT_RIGHT = BOT_RIGHT;;
                TOP_RIGHT_RIGHT = TOP_RIGHT;
            }

            /* first triangle (top left) */

            vec2_t p1, p2;

            if( water_type == WATER_LINEAR)
            {
                final_vertices[vertex_pointer].position = vertices[TOP_RIGHT].position;     // top-right vertex
                p1 = vertices[BOT_RIGHT].position;
                p2 = vertices[TOP_RIGHT_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );


                final_vertices[vertex_pointer].position = vertices[TOP_LEFT].position;     // top-left vertex
                p1 = vertices[BOT_LEFT].position;
                p2 = vertices[TOP_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                final_vertices[vertex_pointer].position = vertices[BOT_LEFT].position;     // bot-left vertex
                p1 = vertices[BOT_BOT_LEFT].position;
                p2 = vertices[BOT_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                /* second triangle (bottom right) */

                final_vertices[vertex_pointer].position = vertices[TOP_RIGHT].position;     // top-right vertex
                p1 = vertices[BOT_RIGHT].position;
                p2 = vertices[TOP_RIGHT_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                final_vertices[vertex_pointer].position = vertices[BOT_LEFT].position;     // bot-left vertex
                p1 = vertices[BOT_BOT_LEFT].position;
                p2 = vertices[BOT_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                final_vertices[vertex_pointer].position = vertices[BOT_RIGHT].position;   // bot-right vertex
                p1 = vertices[BOT_BOT_RIGHT].position;
                p2 = vertices[BOT_RIGHT_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );
            }
            else if( water_type == WATER_LOW_POLY )
            {
                final_vertices[vertex_pointer].position = vertices[TOP_RIGHT].position;     // top-right vertex
                p1 = vertices[TOP_LEFT].position;
                p2 = vertices[BOT_LEFT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );


                final_vertices[vertex_pointer].position = vertices[TOP_LEFT].position;     // top-left vertex
                p1 = vertices[BOT_LEFT].position;
                p2 = vertices[TOP_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                final_vertices[vertex_pointer].position = vertices[BOT_LEFT].position;     // bot-left vertex
                p1 = vertices[TOP_RIGHT].position;
                p2 = vertices[TOP_LEFT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                /* second triangle (bottom right) */

                final_vertices[vertex_pointer].position = vertices[TOP_RIGHT].position;     // top-right vertex
                p1 = vertices[BOT_LEFT].position;
                p2 = vertices[BOT_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                final_vertices[vertex_pointer].position = vertices[BOT_LEFT].position;     // bot-left vertex
                p1 = vertices[BOT_RIGHT].position;
                p2 = vertices[TOP_RIGHT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

                final_vertices[vertex_pointer].position = vertices[BOT_RIGHT].position;   // bot-right vertex
                p1 = vertices[TOP_RIGHT].position;
                p2 = vertices[BOT_LEFT].position;
                final_vertices[vertex_pointer++].indicators = vec4m( p1.x, p1.y, p2.x, p2.y );

            }

        }
    }

    vertex_pointer = 0;

    GLuint vao;
    GLuint data_buffer;
	glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

	glGenBuffers(1, &data_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, data_buffer);

    glBufferData(GL_ARRAY_BUFFER, WATER_VERTEX_TOTAL_COUNT * sizeof(water_vertex_t), final_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(water_vertex_t), (void*) 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(water_vertex_t), (void*) (2 * sizeof(float)) );
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(terrain_vertex_t), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    char * wtype;
    if((int)water_type == WATER_LOW_POLY) {
        wtype = "LOW_POLY";
    } else {
        wtype = "LINEAR";
    }
    printf("WATER-LOG: Water initialized on tile (%d - %d) - TRIANGLES: %d - VERTEX_COUNT: %d - WATER_TYPE: %s\n", grid_x, grid_z,
                                                         (WATER_QUAD_COUNT * WATER_QUAD_COUNT) * 2,
                                                          WATER_VERTEX_TOTAL_COUNT, wtype);
    fflush(stdout);

    water_t water;
        water.vao_id = vao;
        water.vertex_count = WATER_VERTEX_TOTAL_COUNT;
        water.x = grid_x * WATER_SIZE;
        water.z = grid_z * WATER_SIZE;
        water.y = y_offset;

    return water;

}

mat4_t water_get_transformation_matrix( water_t water ) {

    mat4_t transf_mat = m4_identity();
    transf_mat = m4_mul( transf_mat, m4_translation( vec3m(water.x, water.y, water.z) ) );

    return transf_mat;
}
