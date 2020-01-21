#ifndef RAFGL_H_INCLUDED
#define RAFGL_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <rafgl_keys.h>

#ifdef RAFGL_IMPLEMENTATION
#define MATH_3D_IMPLEMENTATION
#endif // RAFGL_IMPLEMENTATION
#include <math_3d.h>

#define SYSTEM_SEPARATOR "/"


#define RAFGL_FONT_SMALL 0
#define RAFGL_FONT_MEDIUM 1
#define RAFGL_FONT_LARGE 2
#define RAFGL_FONT_COUNT 3

#define RAFGL_ERROR         0
#define RAFGL_WARNING       1
#define RAFGL_INFO          2
#define RAFGL_LOG_LEVELS    3


#define pixel_at_m(r, x, y) (*(r.data + (y) * r.width + (x)))
#define pixel_at_pm(r, x, y) (*(r->data + (y) * r->width + (x)))


#define rafgl_abs_m(x) ((x) >= 0 ? (x) : -(x))
#define rafgl_min_m(x, y) ((x) < (y) ? (x) : (y))
#define rafgl_max_m(x, y) ((x) > (y) ? (x) : (y))
#define rafgl_game_add_named_game_state(game_p, state_name) rafgl_game_add_game_state(game_p, state_name##_init, state_name##_update, state_name##_render, state_name##_cleanup)


#define rafgl_RGBA(r, g, b, a) (((r) << 0) | ((g) << 8) | ((b) << 16) | ((a) << 24))
#define rafgl_RGB(r, g, b) rafgl_RGBA(r, g, b, 0xff)

#define vec3m(x, y, z) ((vec3_t) {x, y, z})

#define RAFGL_RED vec3m(1.0f, 0.0f, 0.0f)
#define RAFGL_GREEN vec3m(0.0f, 1.0f, 0.0f)
#define RAFGL_BLUE vec3m(0.0f, 0.0f, 1.0f)
#define RAFGL_WHITE vec3m(1.0f, 1.0f, 1.0f)
#define RAFGL_BLACK vec3m(0.0f, 0.0f, 0.0f)
#define RAFGL_GRAY vec3m(0.5f, 0.5f, 0.5f)
#define RAFGL_GRAY_LIGHT vec3m(0.75f, 0.75f, 0.75f)
#define RAFGL_GRAY_DARK vec3m(0.25f, 0.25f, 0.25f)
#define RAFGL_GRAYX(x) vec3m(x, x, x)
#define RAFGL_CYAN vec3m(0.0f, 1.0f, 1.0f)
#define RAFGL_MAGENTA vec3m(1.0f, 0.0f, 1.0f)
#define RAFGL_YELOW vec3m(1.0f, 1.0f, 0.0f)


#define RAFGL_VEC3_ZERO vec3m(0.0f, 0.0f, 0.0f)

#define RAFGL_VEC3_X vec3m(1.0f, 0.0f, 0.0f)
#define RAFGL_VEC3_Y vec3m(0.0f, 1.0f, 0.0f)
#define RAFGL_VEC3_Z vec3m(0.0f, 0.0f, 1.0f)

#define RAFGL_VEC3_NEGX vec3m(-1.0f, 0.0f, 0.0f)
#define RAFGL_VEC3_NEGY vec3m(0.0f, -1.0f, 0.0f)
#define RAFGL_VEC3_NEGZ vec3m(0.0f, 0.0f, -1.0f)

#ifndef M_PIf
#define M_PIf 3.14159265359f
#endif // M_PIf

#define RAFGL_TRUE 1
#define RAFGL_FALSE 0

typedef struct { float x, y; } vec2_t;
typedef struct { float x, y, z, w; } vec4_t;

#define vec2m(x, y) ((vec2_t) {x, y})
#define vec4m(x, y, z, w) ((vec4_t) {x, y, z, w})

typedef union _rafgl_pixel_rgb_t
{

    struct
    {
        uint8_t r, g, b, a;
    };
    uint32_t rgba;
    uint8_t components[4];

} rafgl_pixel_rgb_t;

typedef struct _rafgl_raster
{
    int width, height;
    rafgl_pixel_rgb_t *data;
} rafgl_raster_t;

typedef struct _rafgl_spritesheet_t
{
    rafgl_raster_t sheet;
    int sheet_width, sheet_height;
    int frame_width, frame_height;

} rafgl_spritesheet_t;

typedef struct _rafgl_texture_t
{
    GLuint tex_id;
    int width, height, channels;
    GLuint tex_type;
} rafgl_texture_t;

typedef struct _rafgl_list_t
{
    void *head;
    void *tail;
    int element_size;
    int count;
} rafgl_list_t;


typedef struct _rafgl_game_t
{
    rafgl_list_t game_states;
    int current_game_state;
    int next_game_state;

    GLFWwindow *window;
} rafgl_game_t;

typedef struct _rafgl_game_data_t
{
    int raster_width, raster_height;
    double mouse_pos_x, mouse_pos_y;
    int is_lmb_down, is_rmb_down, is_mmb_down;

    uint8_t *keys_down, *keys_pressed;

} rafgl_game_data_t;

typedef struct _rafgl_game_state_t
{
    int id;
    void *args;
    void (*init)(GLFWwindow *window, void *args, int width, int height);
    void (*update)(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args);
    void (*render)(GLFWwindow *window, void *args);
    void (*cleanup)(GLFWwindow *window, void *args);
} rafgl_game_state_t;

typedef struct _rafgl_button_t
{
    int posx, posy, w, h;
    uint32_t colour;
}rafgl_button_t;

typedef struct _rafgl_vertexPUN_t
{
    vec3_t position;
    float u, v;
    vec3_t normal;
} rafgl_vertexPUN_t;

typedef struct _rafgl_meshPUN_t
{
    GLuint vao_id;
    unsigned int vertex_count;
    unsigned int triangle_count;
    int loaded;
    char name[64];
} rafgl_meshPUN_t;

typedef struct _rafgl_framebuffer_simple_t
{
    GLuint fbo_id, tex_id;
} rafgl_framebuffer_simple_t;

typedef struct  _rafgl_framebuffer_multitarget_t
{
    GLuint fbo_id;
    GLuint tex_ids[16];
    int num_textures;
    int width, height;
} rafgl_framebuffer_multitarget_t;



/* initializes the GLFW library, GLEW and the window. If full-screen mode is selected, width and hight are unused and the monitor resolution is used instead */
int rafgl_game_init(rafgl_game_t *game, const char *title, int window_width, int window_height, int fullscreen);
/* creates a new game state based on the appropriate function pointers */
void rafgl_game_add_game_state(rafgl_game_t *game, void (*init)(GLFWwindow *window, void *args), void (*update)(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args), void (*render)(GLFWwindow *window, void *args), void (*cleanup)(GLFWwindow *window, void *args));

void rafgl_window_set_title(const char *name);

/* allocates and NULLs the needed memory for the raster */
int rafgl_raster_init(rafgl_raster_t *raster, int width, int height);
/* copies the raster (resizes destination raster to fit the source raster) */
int rafgl_raster_copy(rafgl_raster_t *raster_to, rafgl_raster_t *raster_from);
/* reads an image from the disk and loads it into the raster (raster should NOT BE "inited" beforehand */
int rafgl_raster_load_from_image(rafgl_raster_t *raster, const char *image_path);
/* */
int rafgl_raster_save_to_png(rafgl_raster_t *raster, const char *image_path);
/* free */
int rafgl_raster_cleanup(rafgl_raster_t *raster);

void rafgl_spritesheet_init(rafgl_spritesheet_t *spritesheet, const char *sheet_path, int sheet_width, int sheet_height);
void rafgl_raster_draw_spritesheet(rafgl_raster_t *raster, rafgl_spritesheet_t *spritesheet, int sheet_x, int sheet_y, int x, int y);

void rafgl_log(int level, const char *format, ...);


/* helpers function declarations start */

/* allocates a texture slot on the GPU */
void rafgl_texture_init(rafgl_texture_t *tex);
/* loads a texture from the disk with basic settings */
int rafgl_texture_load_basic(const char *texture_path, rafgl_texture_t *res);
/* loads a texture from a raster in memory */
void rafgl_texture_load_from_raster(rafgl_texture_t *texture, rafgl_raster_t *raster);
/* shows the texture applied to a (-1, -1) (1, 1) NDC space quad */
void rafgl_texture_show(const rafgl_texture_t *texture, int flip);
/* free */
void rafgl_texture_cleanup(rafgl_texture_t *texture);

void rafgl_texture_load_cubemap_named(rafgl_texture_t *tex, const char *cubemap_name, const char *file_ext);
void rafgl_texture_load_cubemap(rafgl_texture_t *tex, const char *cubemap_paths[]);

/* allocates memory and reads the file content into it (requires free on the returned pointer later) */
char* rafgl_file_read_content(const char *filepath);
/* checks the file size */
int rafgl_file_size(const char *filepath);

/* creates a shader program from vertex and fragment files on the disk */
GLuint rafgl_program_create(const char *vertex_source_filepath, const char *fragment_source_filepath);
/* creates a shader program from vertex and fragment source in memory */
GLuint rafgl_program_create_from_source(const char *vertex_source, const char *fragment_source);
/* creates a shader program from vertex and fragment files with standardized names and locations */
GLuint rafgl_program_create_from_name(const char *program_name);

/* generic linked list */
int rafgl_list_init(rafgl_list_t *list, int element_size);
int rafgl_list_append(rafgl_list_t *list, void *data);
int rafgl_list_append_sized(rafgl_list_t *list, int size, void *data);
int rafgl_list_remove(rafgl_list_t *list, int index);
void* rafgl_list_get(rafgl_list_t *list, int index);
int rafgl_list_free(rafgl_list_t *list);
int rafgl_list_show(rafgl_list_t *list, void (*fun)(void *data, int last));
int rafgl_list_test(void);

/* random float in the range of [0, 1) */
float randf(void);
/* abs difference between two numbers */
float rafgl_distance1D(float x1, float x2);
/* euclidean distance between 2D points */
float rafgl_distance2D(float x1, float y1, float x2, float y2);
/* euclidean distance between 3D points */
float rafgl_distance3D(float x1, float y1, float z1, float x2, float y2, float z2);

/* clamps argument value between arguments lower and upper for integers */
int rafgl_clampi(int value, int lower, int upper);
/* clamps argument value between arguments lower and upper for floats */
float rafgl_clampf(float value, float lower, float upper);
/* clamps argument value between 0 and 255 for integers */
int rafgl_saturatei(int value);
/* clamps argument value between 0.0f and 1.0f for floats */
float rafgl_saturatef(float value);
/* linearly interpolate between float arguments from and to with the argument scale ( from + (to - from) * scale) */
float rafgl_lerpf(float from, float to, float scale);
/* linearly interpolate between integer arguments from and to with the argument scale ( from + (to - from) * scale) */
int rafgl_lerpi(int from, int to, float scale);
/* linearly interpolate between pixel arguments from and to with the argument scale ( from + (to - from) * scale). Pixels are treated as 4 component vectors in regards to interpolation */
rafgl_pixel_rgb_t rafgl_lerppix(rafgl_pixel_rgb_t from, rafgl_pixel_rgb_t to, float scale);
/* calculates the weighted average of the pixel colour components  */
int rafgl_calculate_pixel_brightness(rafgl_pixel_rgb_t pix);

/* point samples a pixel in the source raster on the normalised coordinates (u, v) u and v should be in range [0, 1] */
rafgl_pixel_rgb_t rafgl_point_sample(rafgl_raster_t *src, float u, float v);
/* bi-linearly samples a pixel in the source raster on the normalised coordinates (u, v) u and v should be in range [0, 1] */
rafgl_pixel_rgb_t rafgl_bilinear_sample(rafgl_raster_t *src, float u, float v);

/* creates a button */
void rafgl_button_innit(rafgl_button_t *btn, int posx, int posy, int width, int height, uint32_t colour);
/* applies the button to the raster */
void rafgl_button_show(rafgl_raster_t *target, rafgl_button_t *btn);
/* checks if the button is pressed (does not account for occlusion) */
int rafgl_button_check(rafgl_button_t *btn, rafgl_game_data_t *game_data);

void rafgl_raster_box_blur(rafgl_raster_t *result, rafgl_raster_t *tmp, rafgl_raster_t *from, int radius);

int rafgl_raster_draw_raster(rafgl_raster_t *to, rafgl_raster_t *from, int x, int y);

void rafgl_raster_draw_line(rafgl_raster_t *raster, int x0, int y0, int x1, int y1, uint32_t colour);
void rafgl_raster_draw_circle(rafgl_raster_t *raster, int cx, int cy, int r, uint32_t colour);
void rafgl_raster_draw_rectangle(rafgl_raster_t *raster, int x0, int y0, int w, int h, uint32_t colour);

void rafgl_raster_bilinear_upsample(rafgl_raster_t *to, rafgl_raster_t *from);

int rafgl_raster_draw_string(rafgl_raster_t *raster, const char *s, int x, int y, uint32_t colour, int font_size);

void rafgl_log_fps(int b);

void rafgl_meshPUN_init(rafgl_meshPUN_t *m);
void rafgl_meshPUN_load_from_OBJ(rafgl_meshPUN_t *m, const char *obj_path);
void rafgl_meshPUN_load_from_OBJ_offset(rafgl_meshPUN_t *m, const char *obj_path, vec3_t position_offset);
void rafgl_meshPUN_load_cube(rafgl_meshPUN_t *m, float coord);
void rafgl_meshPUN_load_terrain_from_heightmap(rafgl_meshPUN_t *m, float w, float h, const char *img_path, float height);

rafgl_framebuffer_simple_t rafgl_framebuffer_simple_create(int w, int h);
rafgl_framebuffer_multitarget_t rafgl_framebuffer_multitarget_create(int w, int h, int num_attachments);

void rafgl_meshPUN_load_plane(rafgl_meshPUN_t *m, float w, float h, int wtiles, int htiles);

void rafgl_meshPUN_load_plane_offset(rafgl_meshPUN_t *m, float w, float h, int wtiles, int htiles, vec3_t offset);


extern rafgl_pixel_rgb_t RAFGL_COLOUR_KEY;


/* helpers function declarations end*/


#ifdef RAFGL_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

/* rafgl core implementation */

rafgl_pixel_rgb_t RAFGL_COLOUR_KEY;

static GLFWwindow *__window;
static int __done = 0;
static int __window_width = 0, __window_height = 0;

static uint8_t __keys_down[400];
static uint8_t __keys_pressed[400];

static rafgl_spritesheet_t __mono_char_sheet[RAFGL_FONT_COUNT];
static int __countx = 16, __county = 8;

GLuint __flip;


static const char *__2D_raster_vertex_shader_source = "\
#version 410 core\n\
\n\
layout(location = 0) in vec2 pos;\n\
\n\
out vec2 uv;\n\
uniform float uni_flip;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(pos, 0.0, 1.0);\n\
    uv = (pos + vec2(1.0)) * 0.5;\n\
    if(uni_flip < 0.5)\n\
        uv.y = 1.0 - uv.y;\n\
}\
";

static const char *__2D_raster_fragment_shader_source = "\
#version 410 core\n\
\n\
in vec2 uv;\n\
out vec4 frag_colour;\n\
uniform sampler2D raster;\n\
\n\
void main()\n\
{\n\
    frag_colour = texture(raster, uv);\n\
    //frag_colour = vec4(uv.x);\n\
}\
";

static unsigned int __raster_program = 0;
static unsigned int __raster_vao = 0;

static float __raster_corners[] = {
     1.0f, 1.0f,
    -1.0f, 1.0f,
    -1.0f, -1.0f,

     1.0f, 1.0f,
    -1.0f, -1.0f,
     1.0f, -1.0f
};


void __key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    /* printf("%c %d\n", key, action); */
    if(__keys_down[key] == 0 && action != 0) __keys_pressed[key] = 1;
        else __keys_pressed[key] = 0;
    __keys_down[key] = action;

}

void __error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

char *__log_level_names[RAFGL_LOG_LEVELS] = {"error", "warning", "info"};
FILE *__log_files[RAFGL_LOG_LEVELS];

static float __rafgl_time_from_init = 0;
void rafgl_log(int level, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    FILE* fd = __log_files[level];
    if(level == RAFGL_ERROR)
    {
        fprintf(stderr, "%s: ", __log_level_names[level]);
        vfprintf(stderr, format, args);

    }
    else
    {
        printf("%s : ", __log_level_names[level]);
        vprintf(format, args);
    }

    vfprintf(fd, format, args);
    va_end(args);
}


int rafgl_game_init(rafgl_game_t *game, const char *title, int window_width, int window_height, int fullscreen)
{
    if(__done) return -1;
    __done = 1;


    int i;
    char fnames[255];
    for(i = 0; i < RAFGL_LOG_LEVELS; i++)
    {
        sprintf(fnames, "logs/%s.log", __log_level_names[i]);
        __log_files[i] = fopen(fnames, "w");
    }

    __window_width = window_width;
    __window_height = window_height;

    if(!glfwInit())
    {
        fprintf(stderr, "GLFWInit() failed\n");
    }

    glfwSetErrorCallback(__error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWmonitor *mnt = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(mnt);


    if(fullscreen)
    {
        __window_width = mode->width;
        __window_height = mode->height;
        __window = glfwCreateWindow(mode->width, mode->height, title, mnt, NULL);
    }
    else
    {
        __window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
    }


    if(__window == NULL)
    {
        rafgl_log(RAFGL_ERROR, "Failed to create GLFW window!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(__window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        rafgl_log(RAFGL_ERROR, "Failed to initiate GLAD!\n");
        glfwTerminate();
        return -1;
    }

    game -> window = __window;
    game -> current_game_state = -1;
    game -> next_game_state = -1;
    rafgl_list_init(&(game -> game_states), sizeof(rafgl_game_state_t));

    if(!__raster_vao)
    {
        glGenVertexArrays(1, &__raster_vao);
        GLuint raster_vbo;
        glGenBuffers(1, &raster_vbo);
        glBindVertexArray(__raster_vao);
        glBindBuffer(GL_ARRAY_BUFFER, raster_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(__raster_corners), __raster_corners, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    if(!__raster_program)
    {
        __raster_program = rafgl_program_create_from_source(__2D_raster_vertex_shader_source, __2D_raster_fragment_shader_source);
        glUniform1i(glGetUniformLocation(__raster_program, "raster"), 0);
        __flip = glGetUniformLocation(__raster_program, "uni_flip");
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwSetKeyCallback(__window, __key_callback);

    RAFGL_COLOUR_KEY.rgba = rafgl_RGB(255, 0, 254);
    rafgl_spritesheet_init(&__mono_char_sheet[0], "res/fonts/chars-small.png", __countx, __county);
    rafgl_spritesheet_init(&__mono_char_sheet[1], "res/fonts/chars.png", __countx, __county);
    rafgl_spritesheet_init(&__mono_char_sheet[2], "res/fonts/chars-large.png", __countx, __county);

    return 0;
}

void rafgl_window_set_title(const char *name)
{
    glfwSetWindowTitle(__window, name);
}


void __rafgl_raster_draw_spritesheet_text(rafgl_raster_t *raster, rafgl_spritesheet_t *spritesheet, int sheet_x, int sheet_y, int x, int y, uint32_t colour)
{
    int fl, fr, fu, fd;
    int flc, frc, fuc, fdc;
    int xi, yi;

    rafgl_pixel_rgb_t sampled;

    fl = x;
    fr = x + spritesheet->frame_width;
    fu = y;
    fd = y + spritesheet->frame_height;

    flc = rafgl_max_m(fl, 0);
    frc = rafgl_min_m(fr, raster->width);
    fuc = rafgl_max_m(fu, 0);
    fdc = rafgl_min_m(fd, raster->height);

    for(yi = fuc; yi < fdc; yi++)
    {
        for(xi = flc; xi < frc; xi++)
        {
            sampled = pixel_at_m(spritesheet->sheet, sheet_x * spritesheet->frame_width + xi - fl, sheet_y * spritesheet->frame_height + yi - fu);
            if(sampled.r || sampled.g || sampled.b)
            {
                pixel_at_pm(raster, xi, yi).rgba = colour;
            }
        }
    }

}


int rafgl_raster_draw_string(rafgl_raster_t *raster, const char *s, int x, int y, uint32_t colour, int font_size)
{

    char c, i = 0, index, xt, yt, ox = 0, oy = 0;
    while((c = s[i++]) != '\0')
    {
        if(c == '\n')
        {
            ox = -1;
            oy++;
        }
        if(c < 32 || c >= 128)
        {
            ox++;
            continue;
        }

        index = c - 32;
        yt = index / __countx;
        xt = index % __countx;

        __rafgl_raster_draw_spritesheet_text(raster, &__mono_char_sheet[font_size % 3], xt, yt, x + ox * __mono_char_sheet[font_size % 3].frame_width, y + oy * __mono_char_sheet[font_size % 3].frame_height, colour);
        ox++;




    }
}


int rafgl_raster_init(rafgl_raster_t *raster, int width, int height)
{
    raster->data = calloc(width * height, sizeof(rafgl_pixel_rgb_t));
    raster->width = width;
    raster->height = height;
    return 0;
}

int rafgl_raster_cleanup(rafgl_raster_t *raster)
{
    free(raster->data);
    raster->height = 0;
    raster->width = 0;
    return 0;
}


void rafgl_spritesheet_init(rafgl_spritesheet_t *spritesheet, const char *sheet_path, int sheet_width, int sheet_height)
{
    rafgl_raster_load_from_image(&(spritesheet->sheet), sheet_path);
    spritesheet->sheet_width = sheet_width;
    spritesheet->sheet_height = sheet_height;
    spritesheet->frame_width = spritesheet->sheet.width / sheet_width;
    spritesheet->frame_height = spritesheet->sheet.height / sheet_height;
}



void rafgl_raster_draw_spritesheet(rafgl_raster_t *raster, rafgl_spritesheet_t *spritesheet, int sheet_x, int sheet_y, int x, int y)
{
    int fl, fr, fu, fd;
    int flc, frc, fuc, fdc;
    int xi, yi;

    rafgl_pixel_rgb_t sampled;

    fl = x;
    fr = x + spritesheet->frame_width;
    fu = y;
    fd = y + spritesheet->frame_height;

    flc = rafgl_max_m(fl, 0);
    frc = rafgl_min_m(fr, raster->width);
    fuc = rafgl_max_m(fu, 0);
    fdc = rafgl_min_m(fd, raster->height);

    for(yi = fuc; yi < fdc; yi++)
    {
        for(xi = flc; xi < frc; xi++)
        {
            sampled = pixel_at_m(spritesheet->sheet, sheet_x * spritesheet->frame_width + xi - fl, sheet_y * spritesheet->frame_height + yi - fu);
            if(sampled.rgba != RAFGL_COLOUR_KEY.rgba)
            {
                pixel_at_pm(raster, xi, yi) = sampled;
            }
        }
    }

}


int rafgl_raster_copy(rafgl_raster_t *raster_to, rafgl_raster_t *raster_from)
{

    if(raster_to->data == NULL)
    {
        /* new raster */
        rafgl_raster_init(raster_to, raster_from->width, raster_from->height);
    }
    else if(raster_to -> width != raster_from -> width || raster_to -> height != raster_from -> height)
    {
        /* resize */
        rafgl_raster_cleanup(raster_to);
        rafgl_raster_init(raster_to, raster_from->width, raster_from->height);
    }

    /* just copy */
    memcpy(raster_to->data, raster_from->data, raster_from->width * raster_from->height * sizeof(rafgl_pixel_rgb_t));
    return 0;
}

int rafgl_raster_load_from_image(rafgl_raster_t *raster, const char *image_path)
{
    int width, height, channels;
    raster->data = (rafgl_pixel_rgb_t *) stbi_load(image_path, &width, &height, &channels, 4);
    raster->width = width;
    raster->height = height;
    return 0;
}

int rafgl_raster_save_to_png(rafgl_raster_t *raster, const char *image_path)
{
    return stbi_write_png(image_path, raster->width, raster->height, 4, raster->data, 0);
}

void rafgl_raster_box_blur(rafgl_raster_t *result, rafgl_raster_t *tmp, rafgl_raster_t *from, int radius)
{
    int x, y;
    float xn, yn, offset;
    int sample_count = 2 * radius + 1;

    rafgl_pixel_rgb_t sampled, resulting;

    int r, g, b;


    for(y = 0; y < tmp->height; y++)
    {
        for(x = 0; x < tmp->width; x++)
        {

            r = 0;
            g = 0;
            b = 0;
            for(offset = -radius; offset <= radius; offset++)
            {
                sampled = rafgl_point_sample(from, 1.0f * (x + offset) / (tmp->width), 1.0f * (y) / (tmp->height));
                r += sampled.r;
                g += sampled.g;
                b += sampled.b;
            }

            resulting.r = r / sample_count;
            resulting.g = g / sample_count;
            resulting.b = b / sample_count;

            pixel_at_pm(tmp, x, y) = resulting;
        }
    }

    for(y = 0; y < result->height; y++)
    {
        for(x = 0; x < result->width; x++)
        {
            r = g = b = 0;
            for(offset = -radius; offset <= radius; offset++)
            {
                sampled = rafgl_point_sample(tmp, 1.0f * (x) / result->width, 1.0f * (y + offset) / result->height);
                r += sampled.r;
                g += sampled.g;
                b += sampled.b;
            }

            resulting.r = r / sample_count;
            resulting.g = g / sample_count;
            resulting.b = b / sample_count;

            pixel_at_pm(result, x, y) = resulting;
        }
    }
}

int rafgl_raster_draw_raster(rafgl_raster_t *to, rafgl_raster_t *from, int x, int y)
{

    int fl, fr, fu, fd;
    int flc, frc, fuc, fdc;
    int xi, yi;

    rafgl_pixel_rgb_t sampled;

    fl = x;
    fr = x + from->width;
    fu = y;
    fd = y + from->height;

    flc = rafgl_max_m(fl, 0);
    frc = rafgl_min_m(fr, to->width);
    fuc = rafgl_max_m(fu, 0);
    fdc = rafgl_min_m(fd, to->height);

    for(yi = fuc; yi < fdc; yi++)
    {
        for(xi = flc; xi < frc; xi++)
        {
            sampled = pixel_at_pm(from, xi - fl, yi - fu);
            if(sampled.rgba != RAFGL_COLOUR_KEY.rgba)
            {
                pixel_at_pm(to, xi, yi) = sampled;
            }
        }
    }


}

/* Cohen-Sutherland line clipping algorithm constants */
static const int __cohsuth_INSIDE = 0;     /* 0000 */
static const int __cohsuth_LEFT   = 1;     /* 0001 */
static const int __cohsuth_RIGHT  = 2;     /* 0010 */
static const int __cohsuth_BOTTOM = 4;     /* 0100 */
static const int __cohsuth_TOP    = 8;     /* 1000 */

static int __compute_outcode(int x, int y, rafgl_raster_t *raster)
{
    int xmin = 0, ymin = 0, xmax = raster->width - 1, ymax = raster->height - 1;
    int code = __cohsuth_INSIDE;
    if(x < xmin)
    {
        code |= __cohsuth_LEFT;
    }
    else if(x > xmax)
    {
        code |= __cohsuth_RIGHT;
    }

    if(y < ymin)
    {
        code |= __cohsuth_BOTTOM;
    }
    else if(y > ymax)
    {
        code |= __cohsuth_TOP;
    }

    return code;
}

void rafgl_raster_draw_line(rafgl_raster_t *raster, int x0, int y0, int x1, int y1, uint32_t colour)
{

    int xmin = 0, ymin = 0, xmax = raster->width - 1, ymax = raster->height - 1;
    int outcode0 = __compute_outcode(x0, y0, raster);
    int outcode1 = __compute_outcode(x1, y1, raster);
    int accept = 0;
    int xnew, ynew;
    int outside_outcode;

    while(1)
    {

        if(!(outcode0 | outcode1))
        {
            /* trivijalno prihvatanje */
            accept = 1;
            break;
        }
        else if(outcode0 & outcode1)
        {
            /* trivijalno odbacivanje */
            break;
        }
        else
        {
            outside_outcode = outcode0 ? outcode0 : outcode1;
            if(outside_outcode & __cohsuth_TOP)
            {
                xnew = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                ynew = ymax;
            }
            else if(outside_outcode & __cohsuth_BOTTOM)
            {
                xnew = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				ynew = ymin;
            }
            else if (outside_outcode & __cohsuth_RIGHT)
            {
				ynew = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				xnew = xmax;
			}
			else if (outside_outcode & __cohsuth_LEFT)
            {
				ynew = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				xnew = xmin;
			}

			if(outside_outcode == outcode0)
            {
                x0 = xnew;
                y0 = ynew;
                outcode0 = __compute_outcode(x0, y0, raster);
            }
            else
            {
                x1 = xnew;
                y1 = ynew;
                outcode1 = __compute_outcode(x1, y1, raster);
            }
        }


    }


    if(!accept)
        return;

    x0 = rafgl_clampi(x0, 0, xmax);
    y0 = rafgl_clampi(y0, 0, ymax);
    x1 = rafgl_clampi(x1, 0, xmax);
    y1 = rafgl_clampi(y1, 0, ymax);


    /* printf("---\nx0: %d\ny0: %d\nx1: %d\ny1: %d\n", x0, y0, x1, y1); */

    int dx =  rafgl_abs_m((x1-x0)), sx = x0<x1 ? 1 : -1;
    int dy = -rafgl_abs_m((y1-y0)), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2; /* error value e_xy */

    while(1)
    {
        pixel_at_pm(raster, x0, y0).rgba = colour;
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }

}

/* DOES NOT DO CLIPPING! */
void rafgl_raster_draw_circle(rafgl_raster_t *raster, int cx, int cy, int r, uint32_t colour)
{
    int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */
    do {
        pixel_at_pm(raster, cx-x, cy+y).rgba = colour; /*   I. Quadrant */
        pixel_at_pm(raster, cx-y, cy-x).rgba = colour; /*  II. Quadrant */
        pixel_at_pm(raster, cx+x, cy-y).rgba = colour; /* III. Quadrant */
        pixel_at_pm(raster, cx+y, cy+x).rgba = colour; /*  IV. Quadrant */
        r = err;
        if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
        if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
    } while (x < 0);
}

void rafgl_raster_draw_rectangle(rafgl_raster_t *raster, int x0, int y0, int w, int h, uint32_t colour)
{
    rafgl_raster_draw_line(raster, x0, y0, x0 + w, y0, colour);
    rafgl_raster_draw_line(raster, x0, y0 + h, x0 + w, y0 + h, colour);
    rafgl_raster_draw_line(raster, x0, y0, x0, y0 + h, colour);
    rafgl_raster_draw_line(raster, x0 + w, y0, x0 + w, y0 + h, colour);
}

void rafgl_raster_bilinear_upsample(rafgl_raster_t *to, rafgl_raster_t *from)
{
    int x, y;
    int w = to->width, h = to->height;
    float xn, yn;

    for(y = 0; y < h; y++)
    {
        yn = ((float)y) / h;
        for(x = 0; x < w; x++)
        {
            xn = ((float)x) / w;
            pixel_at_pm(to, x, y) = rafgl_bilinear_sample(from, xn, yn);
        }
    }
}


void rafgl_game_add_game_state(rafgl_game_t *game, void (*init)(GLFWwindow *window, void *args), void (*update)(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args), void (*render)(GLFWwindow *window, void *args), void (*cleanup)(GLFWwindow *window, void *args))
{
    rafgl_game_state_t state;
    state.init = init;
    state.update = update;
    state.render = render;
    state.cleanup = cleanup;
    state.id = 0;

    rafgl_list_append(&game->game_states, &state);
}

static int __rafgl_log_fps = 0;
static int __game_state_change_request = -1;
static void *__game_state_change_request_args = NULL;

void rafgl_log_fps(int b)
{
    __rafgl_log_fps = b;
}

void rafgl_game_request_state_change(int state_index, void *args)
{
    __game_state_change_request = state_index;
    __game_state_change_request_args = args;
}

void rafgl_game_start(rafgl_game_t *game, void *_args)
{
    int frame_count = 0;
    void *args = _args;
    rafgl_game_state_t *current_state = rafgl_list_get(&game->game_states, 0);
    int current_game_state_index = 0, i;

    rafgl_game_data_t game_data;
    game_data.keys_down = __keys_down;
    game_data.keys_pressed = __keys_pressed;

    current_state->init(game->window, args, __window_width, __window_height);


    double current_frame, last_frame;
    float elapsed;

    double last_fps_frame;

    last_fps_frame = last_frame = glfwGetTime();

    int fbwidth, fbheight, fbwlast = 0, fbhlast = 0;

    while(!glfwWindowShouldClose(game->window))
    {
        for(i = 0; i < 400; i++)
        {
            __keys_pressed[i] = 0;
        }
        glfwPollEvents();

        current_frame = glfwGetTime();

        ++frame_count;
        if(current_frame - last_fps_frame >= 2.0f)
        {
            if(__rafgl_log_fps)
            {
                rafgl_log(RAFGL_INFO, "[FPS = %.2f]\n", frame_count / 2.0f);
            }
            frame_count = 0;
            last_fps_frame = current_frame;
        }

        elapsed = current_frame - last_frame;
        last_frame = current_frame;


        glfwGetFramebufferSize(game->window, &fbwidth, &fbheight);
        if(fbwlast != fbwidth || fbhlast != fbheight)
        {
            glViewport(0, 0, fbwidth, fbheight);
        }
        fbwlast = fbwidth;
        fbhlast = fbheight;

        game_data.raster_width = fbwidth;
        game_data.raster_height = fbheight;

        glfwGetCursorPos(game->window, &game_data.mouse_pos_x, &game_data.mouse_pos_y);

        game_data.is_lmb_down = glfwGetMouseButton(game->window, GLFW_MOUSE_BUTTON_LEFT);
        game_data.is_rmb_down = glfwGetMouseButton(game->window, GLFW_MOUSE_BUTTON_RIGHT);
        game_data.is_mmb_down = glfwGetMouseButton(game->window, GLFW_MOUSE_BUTTON_MIDDLE);

        current_state->update(game->window, elapsed, &game_data, args);


        current_state->render(game->window, args);

        glfwSwapBuffers(game->window);

        if(__game_state_change_request == current_game_state_index)
        {
            rafgl_log(RAFGL_WARNING, "Already in that state!\n");
            __game_state_change_request = -1;
        }

        if(__game_state_change_request >= 0)
        {
            rafgl_log(RAFGL_INFO, "Changigng state!\n");
            current_state->cleanup(game->window, args);

            args = __game_state_change_request_args;
            __game_state_change_request_args = NULL;

            current_state = rafgl_list_get(&game->game_states, __game_state_change_request);

            current_game_state_index = __game_state_change_request;
            __game_state_change_request = -1;

            current_state->init(game->window, args, __window_width, __window_height);
            last_frame = glfwGetTime();

        }

    }

    for(i = 0; i < RAFGL_LOG_LEVELS; i++)
    {
        fclose(__log_files[i]);
    }


}



/* Helpers implementation*/

void rafgl_button_innit(rafgl_button_t *btn, int posx, int posy, int width, int height, uint32_t colour)
{
    btn->colour = colour;
    btn->posx = posx;
    btn->posy = posy;
    btn->w = width;
    btn->h = height;
}

int rafgl_button_check(rafgl_button_t *btn, rafgl_game_data_t *game_data)
{
    return (rafgl_distance1D(btn->posx, game_data->mouse_pos_x) <= btn->w / 2) && (rafgl_distance1D(btn->posy, game_data->mouse_pos_y) <= btn->h / 2) && game_data->is_lmb_down;
}

void rafgl_button_show(rafgl_raster_t *target, rafgl_button_t *btn)
{
    int x, y, X, Y;

    for(Y = -btn->h/2; Y < btn->h/2; Y++)
    {
        for(X = -btn->w/2; X < btn->w/2; X++)
        {
            x = rafgl_clampi(btn->posx + X, 0, target->width - 1);
            y = rafgl_clampi(btn->posy + Y, 0, target->height - 1);

            pixel_at_pm(target, x, y).rgba = btn->colour;

        }

    }
}


inline float randf(void)
{
    return 1.0f * rand() / (RAND_MAX + 1);
}

inline float rafgl_distance1D(float x1, float x2)
{
    if(x1 > x2)
        return x1 - x2;
    else
        return x2 - x1;
}

inline float rafgl_distance2D(float x1, float y1, float x2, float y2)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;

    return sqrtf(delta_x * delta_x + delta_y * delta_y);
}

inline float rafgl_distance3D(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float delta_z = z2 - z1;

    return sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

inline int rafgl_clampi(int value, int lower, int upper)
{
    if(value < lower)
        return lower;
    else if(value > upper)
        return upper;
    else return value;
}

inline float rafgl_clampf(float value, float lower, float upper)
{
    if(value < lower)
        return lower;
    else if(value > upper)
        return upper;
    else return value;
}

inline int rafgl_saturatei(int value)
{
    return rafgl_clampi(value, 0, 255);
}

inline float rafgl_saturatef(float value)
{
    return rafgl_clampf(value, 0.0f, 1.0f);
}


inline float rafgl_lerpf(float from, float to, float scale)
{
    return from + (to - from) * scale;
}

inline int rafgl_lerpi(int from, int to, float scale)
{
    return from + (to - from) * scale;
}

inline int rafgl_calculate_pixel_brightness(rafgl_pixel_rgb_t pix)
{
    return 0.3f * pix.r + 0.59f * pix.g + 0.11f * pix.b;
}

inline rafgl_pixel_rgb_t rafgl_lerppix(rafgl_pixel_rgb_t from, rafgl_pixel_rgb_t to, float scale)
{
    from.r = rafgl_lerpi(from.r, to.r, scale);
    from.g = rafgl_lerpi(from.g, to.g, scale);
    from.b = rafgl_lerpi(from.b, to.b, scale);
    from.a = rafgl_lerpi(from.a, to.a, scale);
    return from;
}

rafgl_pixel_rgb_t rafgl_point_sample(rafgl_raster_t *src, float u, float v)
{
    int x = rafgl_clampi(u * src -> width, 0, src -> width - 1);
    int y = rafgl_clampi(v * src -> height, 0, src -> height - 1);
    return pixel_at_pm(src, x, y);
}

rafgl_pixel_rgb_t rafgl_bilinear_sample(rafgl_raster_t *src, float u, float v)
{
    rafgl_pixel_rgb_t UL, UR, LL, LR, UM, LM;

    int width = src->width, height = src->height;

    u = rafgl_clampf((u * src -> width) - 0.5f, 0, src->width - 1.0f);
    v = rafgl_clampf((v * src -> height)- 0.5f, 0, src->height - 1.0f);

    int x0, y0, x1, y1;

    x0 = u;
    y0 = v;
    x1 = x0 + 1;
    y1 = y0 + 1;

    if(x1 > width - 1) x1 = width - 1;
    if(y1 > height - 1) y1 = height - 1;


    float xscale = u - x0, yscale = v - y0;

    UL = pixel_at_pm(src, x0, y0);
    UR = pixel_at_pm(src, x1, y0);
    LL = pixel_at_pm(src, x0, y1);
    LR = pixel_at_pm(src, x1, y1);

    UM = rafgl_lerppix(UL, UR, xscale);
    LM = rafgl_lerppix(LL, LR, xscale);

    return rafgl_lerppix(UM, LM, yscale);
}



void rafgl_texture_init(rafgl_texture_t *tex)
{
    GLuint tx;
    glGenTextures(1, &tx);
    tex->channels = 0;
    tex->width = 0;
    tex->height = 0;
    tex->tex_id = tx;
    tex->tex_type = 0;
}

int rafgl_texture_load_basic(const char *texture_path, rafgl_texture_t *res)
{
    return -1;
}



void rafgl_texture_load_from_raster(rafgl_texture_t *texture, rafgl_raster_t *raster)
{
    GLuint tex_slot = texture->tex_id;
    glBindTexture(GL_TEXTURE_2D, tex_slot);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, raster->width, raster->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster->data);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture->tex_id = tex_slot;
    texture->width = raster->width;
    texture->height = raster->height;
    texture->channels = 3;
    texture->tex_type = GL_TEXTURE_2D;
}


void rafgl_texture_show(const rafgl_texture_t *texture, int flip)
{

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->tex_id);

    glBindVertexArray(__raster_vao);
    glUseProgram(__raster_program);

    glUniform1f(__flip, flip);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void rafgl_texture_cleanup(rafgl_texture_t *texture)
{
    glDeleteTextures(1, &(texture->tex_id));
    texture->channels = 0;
    texture->height = 0;
    texture->width = 0;
    texture->tex_id = 0;
    texture->tex_type = 0;
    return;
}

void rafgl_texture_load_cubemap_named(rafgl_texture_t *tex, const char *cubemap_name, const char *file_ext)
{
    char cubemap_paths[6][128];
    char *pcubemap_paths[6] = {&cubemap_paths[0][0], &cubemap_paths[1][0], &cubemap_paths[2][0], &cubemap_paths[3][0], &cubemap_paths[4][0], &cubemap_paths[5][0]};
    char names[6][3] = {"/E", "/W", "/U", "/D", "/N", "/S"};
    int i;
    for(i = 0; i < 6; i++)
    {
        strcpy(cubemap_paths[i], "res/cubemaps/");
        strcat(cubemap_paths[i], cubemap_name);
        strcat(cubemap_paths[i], names[i]);
        strcat(cubemap_paths[i], ".");
        strcat(cubemap_paths[i], file_ext);
    }

    rafgl_texture_load_cubemap(tex, pcubemap_paths);
}

void rafgl_texture_load_cubemap(rafgl_texture_t *tex, const char *cubemap_paths[])
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex->tex_id);

    int width, height, channels;
    unsigned char *data;
    GLuint i;
    for(i = 0; i < 6; i++)
    {
        data = stbi_load(cubemap_paths[i], &width, &height, &channels, 4);
        if (!data)
        {
            rafgl_log(RAFGL_ERROR, "Failed to load texture at path [%s] intended for a cubemap!\n", cubemap_paths[i]);
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    tex->tex_type = GL_TEXTURE_CUBE_MAP;



}


rafgl_framebuffer_multitarget_t rafgl_framebuffer_multitarget_create(int w, int h, int num_attachments)
{
    if(num_attachments > 16)
    {
        rafgl_log(RAFGL_WARNING, "Cant make %d attachments to a fbo, using 16 instead!\n", num_attachments);
        num_attachments = 16;
    }
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    rafgl_framebuffer_multitarget_t fb_mt;

    fb_mt.width = w;
    fb_mt.height = h;

    fb_mt.fbo_id = framebuffer;
    fb_mt.num_textures = num_attachments;

    GLuint texture_colour_buffer;
    int i;

    for(i = 0; i < num_attachments; i++)
    {
        glGenTextures(1, &texture_colour_buffer);
        glBindTexture(GL_TEXTURE_2D, texture_colour_buffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        // attach it to currently bound framebuffer object
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture_colour_buffer, 0);
        fb_mt.tex_ids[i] = texture_colour_buffer;
    }



    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
	    rafgl_log(RAFGL_ERROR, "Failed to create framebuffer!\n");
	}
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fb_mt;


}

rafgl_framebuffer_simple_t rafgl_framebuffer_simple_create(int w, int h)
{

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


    GLuint texture_colour_buffer;
    glGenTextures(1, &texture_colour_buffer);
    glBindTexture(GL_TEXTURE_2D, texture_colour_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_colour_buffer, 0);

    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
	    rafgl_log(RAFGL_ERROR, "Failed to create framebuffer!\n");
	}
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    rafgl_framebuffer_simple_t fb;
    fb.fbo_id = framebuffer;
    fb.tex_id = texture_colour_buffer;

    return fb;
}

void rafgl_meshPUN_init(rafgl_meshPUN_t *m)
{
    m->loaded = 0;
    m->triangle_count = 0;
    m->vertex_count = 0;
    m->vao_id = 0;
    memset(m->name, 0, sizeof(m->name));
}

void rafgl_meshPUN_load_plane(rafgl_meshPUN_t *m, float w, float h, int wtiles, int htiles)
{
    rafgl_meshPUN_load_plane_offset(m, w, h, wtiles, htiles, vec3(0.0f, 0.0f, 0.0f));
}

void rafgl_meshPUN_load_plane_offset(rafgl_meshPUN_t *m, float w, float h, int wtiles, int htiles, vec3_t offset)
{
    int num_vertices = wtiles * htiles * 6;
    float tilew = w / wtiles;
    float tileh = h / htiles;

    rafgl_vertexPUN_t *data = malloc(num_vertices * sizeof(rafgl_vertexPUN_t));

    int vertex = 0, x, z;

    for(z = 0; z < htiles; z++)
    {
        for(x = 0; x < wtiles; x++, vertex += 6)
        {
            data[vertex + 0].position = v3_add(vec3((x + 1) * tilew - w / 2, 0.0f, z * tileh - h / 2), offset);
            data[vertex + 0].normal = vec3(0.0f, 1.0f, 0.0f);
            data[vertex + 0].u = 1.0f / wtiles * (x + 1);
            data[vertex + 0].v = 1.0f / htiles * z;

            data[vertex + 1].position = v3_add(vec3(x  * tilew - w / 2, 0.0f, z * tileh - h / 2), offset);
            data[vertex + 1].normal = vec3(0.0f, 1.0f, 0.0f);
            data[vertex + 1].u = 1.0f / wtiles * x;
            data[vertex + 1].v = 1.0f / htiles * z;

            data[vertex + 2].position = v3_add(vec3(x  * tilew - w / 2, 0.0f, (z + 1) * tileh - h / 2), offset);
            data[vertex + 2].normal = vec3(0.0f, 1.0f, 0.0f);
            data[vertex + 2].u = 1.0f / wtiles * x;
            data[vertex + 2].v = 1.0f / htiles * (z + 1);



            data[vertex + 3].position = v3_add(vec3((x + 1) * tilew - w / 2, 0.0f, z * tileh - h / 2), offset);
            data[vertex + 3].normal = vec3(0.0f, 1.0f, 0.0f);
            data[vertex + 3].u = 1.0f / wtiles * (x + 1);
            data[vertex + 3].v = 1.0f / htiles * z;

            data[vertex + 4].position = v3_add(vec3(x  * tilew - w / 2, 0.0f, (z + 1) * tileh - h / 2), offset);
            data[vertex + 4].normal = vec3(0.0f, 1.0f, 0.0f);
            data[vertex + 4].u = 1.0f / wtiles * x;
            data[vertex + 4].v = 1.0f / htiles * (z + 1);

            data[vertex + 5].position = v3_add(vec3((x + 1)  * tilew - w / 2, 0.0f, (z + 1) * tileh - h / 2), offset);
            data[vertex + 5].normal = vec3(0.0f, 1.0f, 0.0f);
            data[vertex + 5].u = 1.0f / wtiles * (x + 1);
            data[vertex + 5].v = 1.0f / htiles * (z + 1);
        }
    }

    glGenVertexArrays(1, &m->vao_id);
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindVertexArray(m->vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER,num_vertices * sizeof(rafgl_vertexPUN_t), data, GL_STATIC_DRAW);

    free(data);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)(5 * sizeof(float)));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);

    m->loaded = 1;
    sprintf(m->name, "%d x %d plane", wtiles, htiles);
    m->triangle_count = wtiles * htiles * 2;
    m->vertex_count =  wtiles * htiles * 6;

}

static vec3_t calculate_normal(rafgl_raster_t *heightmap, int x, int z, float tilew, float tileh, float height)
{
    if(x == 0 || x == heightmap->width - 1 || z == 0 || z == heightmap->height - 1)
    {
        return vec3(0.0f, 1.0f, 0.0f);
    }
    vec3_t u = vec3(tilew, pixel_at_pm(heightmap, x + 1, z).r / 256.0f * height - pixel_at_pm(heightmap, x - 1, z).r / 256.0f * height, 0);
    vec3_t v = vec3(0, pixel_at_pm(heightmap, x, z + 1).r / 256.0f * height - pixel_at_pm(heightmap, x, z - 1).r / 256.0f * height, -tileh);
    return v3_cross(u, v);

}

void rafgl_meshPUN_load_terrain_from_heightmap(rafgl_meshPUN_t *m, float w, float h, const char *img_path, float height)
{

    rafgl_raster_t map_raster;
    rafgl_raster_load_from_image(&map_raster, img_path);

    int wtiles = map_raster.width - 1;
    int htiles = map_raster.height - 1;

    int num_vertices = wtiles * htiles * 6;
    float tilew = w / wtiles;
    float tileh = h / htiles;

    rafgl_vertexPUN_t *data = malloc(num_vertices * sizeof(rafgl_vertexPUN_t));

    int vertex = 0, x, z;
    vec3_t direction, normal;

    for(z = 0; z < htiles; z++)
    {
        for(x = 0; x < wtiles; x++, vertex += 6)
        {
            data[vertex + 0].position = vec3((x + 1) * tilew - w / 2, pixel_at_m(map_raster, x + 1, z).r / 256.0f * height, z * tileh - h / 2);
            data[vertex + 0].u = 1.0f / wtiles * (x + 1);
            data[vertex + 0].v = 1.0f / htiles * z;
            data[vertex + 0].normal = calculate_normal(&map_raster, x + 1, z, tilew, tileh, height);

            data[vertex + 1].position = vec3(x  * tilew - w / 2, pixel_at_m(map_raster, x, z).r / 256.0f * height, z * tileh - h / 2);
            data[vertex + 1].u = 1.0f / wtiles * x;
            data[vertex + 1].v = 1.0f / htiles * z;
            data[vertex + 1].normal = calculate_normal(&map_raster, x, z, tilew, tileh, height);

            data[vertex + 2].position = vec3(x  * tilew - w / 2, pixel_at_m(map_raster, x, z + 1).r / 256.0f * height, (z + 1) * tileh - h / 2);
            data[vertex + 2].u = 1.0f / wtiles * x;
            data[vertex + 2].v = 1.0f / htiles * (z + 1);
            data[vertex + 2].normal = calculate_normal(&map_raster, x, z + 1, tilew, tileh, height);






            data[vertex + 3].position = vec3((x + 1) * tilew - w / 2, pixel_at_m(map_raster, x + 1, z).r / 256.0f * height, z * tileh - h / 2);
            data[vertex + 3].u = 1.0f / wtiles * (x + 1);
            data[vertex + 3].v = 1.0f / htiles * z;
            data[vertex + 3].normal = calculate_normal(&map_raster, x + 1, z, tilew, tileh, height);

            data[vertex + 4].position = vec3(x  * tilew - w / 2, pixel_at_m(map_raster, x, z + 1).r / 256.0f * height, (z + 1) * tileh - h / 2);
            data[vertex + 4].u = 1.0f / wtiles * x;
            data[vertex + 4].v = 1.0f / htiles * (z + 1);
            data[vertex + 4].normal = calculate_normal(&map_raster, x, z + 1, tilew, tileh, height);

            data[vertex + 5].position = vec3((x + 1)  * tilew - w / 2, pixel_at_m(map_raster, x + 1, z + 1).r / 256.0f * height, (z + 1) * tileh - h / 2);
            data[vertex + 5].u = 1.0f / wtiles * (x + 1);
            data[vertex + 5].v = 1.0f / htiles * (z + 1);
            data[vertex + 5].normal = calculate_normal(&map_raster, x + 1, z + 1, tilew, tileh, height);


        }
    }

    glGenVertexArrays(1, &m->vao_id);
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindVertexArray(m->vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER,num_vertices * sizeof(rafgl_vertexPUN_t), data, GL_STATIC_DRAW);

    free(data);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)(5 * sizeof(float)));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);

    m->loaded = 1;
    sprintf(m->name, "%d x %d plane", wtiles, htiles);
    m->triangle_count = wtiles * htiles * 2;
    m->vertex_count =  wtiles * htiles * 6;

}

void rafgl_meshPUN_load_cube(rafgl_meshPUN_t *m, float coord)
{
    float coord_sign = coord > 0 ? 1.0f : -1.0f;
    GLfloat cube_vertices[] = {
        /* positions                   UV                              normals */
         coord,  coord, -coord,         0.0f, 0.0f,                    0.0f,  coord_sign *  1.0f, 0.0f,
        -coord,  coord, -coord,         0.0f, 0.0f,                    0.0f,  coord_sign *  1.0f, 0.0f,
        -coord,  coord,  coord,         0.0f, 0.0f,                    0.0f,  coord_sign *  1.0f, 0.0f,
//y+
         coord,  coord, -coord,         0.0f, 0.0f,                    0.0f,  coord_sign *  1.0f, 0.0f,
        -coord,  coord,  coord,         0.0f, 0.0f,                    0.0f,  coord_sign *  1.0f, 0.0f,
         coord,  coord,  coord,         0.0f, 0.0f,                    0.0f,  coord_sign *  1.0f, 0.0f,


         coord, -coord,  coord,         0.0f, 0.0f,                    0.0f,  coord_sign * -1.0f, 0.0f,
        -coord, -coord,  coord,         0.0f, 0.0f,                    0.0f,  coord_sign * -1.0f, 0.0f,
        -coord, -coord, -coord,         0.0f, 0.0f,                    0.0f,  coord_sign * -1.0f, 0.0f,
//y-
         coord, -coord,  coord,         0.0f, 0.0f,                    0.0f,  coord_sign * -1.0f, 0.0f,
        -coord, -coord, -coord,         0.0f, 0.0f,                    0.0f,  coord_sign * -1.0f, 0.0f,
         coord, -coord, -coord,         0.0f, 0.0f,                    0.0f,  coord_sign * -1.0f, 0.0f,





         coord,  coord, -coord,         0.0f, 0.0f,                    coord_sign *  1.0f,  0.0f,  0.0f,
         coord,  coord,  coord,         0.0f, 0.0f,                    coord_sign *  1.0f,  0.0f,  0.0f,
         coord, -coord,  coord,         0.0f, 0.0f,                    coord_sign *  1.0f,  0.0f,  0.0f,
//x+
         coord,  coord, -coord,         0.0f, 0.0f,                    coord_sign *  1.0f,  0.0f,  0.0f,
         coord, -coord,  coord,         0.0f, 0.0f,                    coord_sign *  1.0f,  0.0f,  0.0f,
         coord, -coord, -coord,         0.0f, 0.0f,                    coord_sign *  1.0f,  0.0f,  0.0f,




        -coord,  coord,  coord,         0.0f, 0.0f,                    coord_sign * -1.0f,  0.0f,  0.0f,
        -coord,  coord, -coord,         0.0f, 0.0f,                    coord_sign * -1.0f,  0.0f,  0.0f,
        -coord, -coord, -coord,         0.0f, 0.0f,                    coord_sign * -1.0f,  0.0f,  0.0f,
//x-
        -coord,  coord,  coord,         0.0f, 0.0f,                    coord_sign * -1.0f,  0.0f,  0.0f,
        -coord, -coord, -coord,         0.0f, 0.0f,                    coord_sign * -1.0f,  0.0f,  0.0f,
        -coord, -coord,  coord,         0.0f, 0.0f,                    coord_sign * -1.0f,  0.0f,  0.0f,





         coord,  coord,  coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign *  1.0f,
        -coord,  coord,  coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign *  1.0f,
        -coord, -coord,  coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign *  1.0f,
//z+
         coord,  coord,  coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign *  1.0f,
        -coord, -coord,  coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign *  1.0f,
         coord, -coord,  coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign *  1.0f,




        -coord,  coord, -coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign * -1.0f,
         coord,  coord, -coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign * -1.0f,
         coord, -coord, -coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign * -1.0f,
//z-
        -coord,  coord, -coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign * -1.0f,
         coord, -coord, -coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign * -1.0f,
        -coord, -coord, -coord,         0.0f, 0.0f,                    0.0f, 0.0f,  coord_sign * -1.0f,
    };

    glGenVertexArrays(1, &m->vao_id);
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindVertexArray(m->vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * 3 * (3 + 2 + 3) * sizeof(GLfloat), cube_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 3) *sizeof(GLfloat), (void*)(5 * sizeof(float)));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);

    m->loaded = 1;
    strcpy(m->name, "cube");
    m->triangle_count = 6 * 2;
    m->vertex_count = 6 * 2 * 3;


}

void rafgl_meshPUN_load_from_OBJ(rafgl_meshPUN_t *m, const char *obj_path)
{
    rafgl_meshPUN_load_from_OBJ_offset(m, obj_path, vec3(0.0f, 0.0f, 0.0f));
}

/* TODO: create cache system */
void rafgl_meshPUN_load_from_OBJ_offset(rafgl_meshPUN_t *m, const char *obj_path, vec3_t position_offset)
{
    if(m->loaded)
    {
        rafgl_log(RAFGL_WARNING, "Trying to load to already loaded mesh! Loading from [%s] to mesh taken by [%s]", obj_path, m->name);
        return;
    }
    rafgl_list_t vertices, uv_coordinates, normals;
    rafgl_list_init(&vertices, sizeof(vec3_t));
    rafgl_list_init(&uv_coordinates, sizeof(vec3_t));
    rafgl_list_init(&normals, sizeof(vec3_t));
    vec3_t vectmp;

    FILE *f = fopen(obj_path, "rt");
    char line[256];


    while(!feof(f))
    {
        fgets(line, 256, f);


        if(line[0] == 'o' && line[1] == ' ')
		{
			strcpy(m->name, line + 2);
			m->name[strlen(m->name) - 1] = '\0';
		}

		if(line[0] == 'v' && line[1] == ' ')
		{
			sscanf(line + 2, "%f%f%f", &(vectmp.x), &(vectmp.y), &(vectmp.z));
			vectmp = v3_add(vectmp, position_offset);
			rafgl_list_append(&vertices, &vectmp);
		}
		else if (line[0] == 'v' && line[1] == 't')
		{
			sscanf(line + 3, "%f%f", &(vectmp.x), &(vectmp.y));
			vectmp.z = 0;
			rafgl_list_append(&uv_coordinates, &vectmp);
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			sscanf(line + 3, "%f%f%f", &(vectmp.x), &(vectmp.y), &(vectmp.z));
			rafgl_list_append(&normals, &vectmp);
		}
		else if (line[0] == 'f')
		{
			break;
		}

    }

    vec3_t *vertices_buffer, *uv_buffer, *normals_buffer;

    vertices_buffer = malloc(vertices.count * sizeof(vec3_t));
    uv_buffer = malloc(uv_coordinates.count * sizeof(vec3_t));
    normals_buffer = malloc(normals.count * sizeof(vec3_t));

    vec3_t *vb1, *vb2, *vb3;
    int o1 = 0, o2 = 0, o3 = 0;
    while((vb1 = rafgl_list_get(&vertices, 0)) != NULL && (vb2 = rafgl_list_get(&uv_coordinates, 0)) != NULL && (vb3 = rafgl_list_get(&normals, 0)) != NULL)
    {
        vertices_buffer[o1++] = *vb1;
        uv_buffer[o2++] = *vb2;
        normals_buffer[o3++] = *vb3;
        rafgl_list_remove(&vertices, 0);
        rafgl_list_remove(&uv_coordinates, 0);
        rafgl_list_remove(&normals, 0);
    }

    while((vb1 = rafgl_list_get(&vertices, 0)) != NULL)
    {
        vertices_buffer[o1++] = *vb1;
        rafgl_list_remove(&vertices, 0);
    }

    while((vb1 = rafgl_list_get(&uv_coordinates, 0)) != NULL)
    {
        uv_buffer[o2++] = *vb1;
        rafgl_list_remove(&uv_coordinates, 0);
    }

    while((vb1 = rafgl_list_get(&normals, 0)) != NULL)
    {
        normals_buffer[o3++] = *vb1;
        rafgl_list_remove(&normals, 0);
    }

	int fake_uvs = 0;
	rafgl_list_t vertex_indices, uv_indices, normal_indices;
    rafgl_list_init(&vertex_indices, sizeof(int));
    rafgl_list_init(&uv_indices, sizeof(int));
    rafgl_list_init(&normal_indices, sizeof(int));

    int v1, v2, v3;
    int n1, n2, n3;
    int t1, t2, t3;

    while(!feof(f))
	{
		while(line[0] != 'f' && !feof(f))
		{
			fgets(line, 256, f);
		}



		int matches = sscanf(line + 2, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
		if(matches != 9)
		{
			matches = sscanf(line + 2, "%d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
			if(matches != 6)
			{
				rafgl_log(RAFGL_WARNING, "File can't be read, try exporting with other options [matches = %d]", matches);
				rafgl_log(RAFGL_WARNING, "error on: %s\n", line);
				return;
			}
			else
			{
				t1 = t2 = t3 = 1;
				if(!fake_uvs)
				{
				    fake_uvs = 1;
                    rafgl_log(RAFGL_WARNING, "Using fake uvs for model on path [%s]\n", obj_path);
				}
			}


		}

		rafgl_list_append(&vertex_indices, &v1);
		rafgl_list_append(&vertex_indices, &v2);
		rafgl_list_append(&vertex_indices, &v3);

		rafgl_list_append(&uv_indices, &t1);
		rafgl_list_append(&uv_indices, &t2);
		rafgl_list_append(&uv_indices, &t3);

		rafgl_list_append(&normal_indices, &n1);
		rafgl_list_append(&normal_indices, &n2);
		rafgl_list_append(&normal_indices, &n3);
		fgets(line, 256, f);



	}

	if(fake_uvs)
    {
        vectmp = vec3(0.0f, 0.0f, 0.0f);
        rafgl_list_append(&uv_coordinates, &vectmp);
    }

    rafgl_vertexPUN_t *vertex_buffer = malloc(vertex_indices.count * sizeof(rafgl_vertexPUN_t));
    int i;
    int vert_ind;
    int uv_ind;
    int norm_ind;

    vec3_t vertex_data, uv_data, normal_data;

    int vcount = vertex_indices.count;
    for(i = 0; i < vcount; i++)
    {
        vert_ind = *((int*)rafgl_list_get(&vertex_indices, 0));
		uv_ind = *((int*)rafgl_list_get(&uv_indices, 0));
		norm_ind = *((int*)rafgl_list_get(&normal_indices, 0));

		rafgl_list_remove(&vertex_indices, 0);
		rafgl_list_remove(&uv_indices, 0);
		rafgl_list_remove(&normal_indices, 0);

		vertex_data = vertices_buffer[vert_ind - 1];
		uv_data = uv_buffer[uv_ind - 1];
		normal_data = normals_buffer[norm_ind - 1];

		vertex_buffer[i].position = vertex_data;
        vertex_buffer[i].normal = normal_data;
        vertex_buffer[i].u = uv_data.x;
        vertex_buffer[i].v = 1.0f - uv_data.y;



    }

    /* GL BUFFER DATA */

	int vao;
	glGenVertexArrays(1, &vao);

	m -> vao_id = vao;
	m -> vertex_count = vcount;
	m -> triangle_count = vcount / 3;

	glBindVertexArray(vao);

	int data_buffer;
	glGenBuffers(1, &data_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, data_buffer);
	glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(rafgl_vertexPUN_t), vertex_buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rafgl_vertexPUN_t), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(rafgl_vertexPUN_t), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(rafgl_vertexPUN_t), (void*)(5 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /* free RAM */
	free(vertex_buffer);

	rafgl_list_free(&vertices);
	rafgl_list_free(&uv_coordinates);
	rafgl_list_free(&normals);

	rafgl_list_free(&vertex_indices);
	rafgl_list_free(&uv_indices);
	rafgl_list_free(&normal_indices);
	m->loaded = 1;

	free(vertices_buffer);
	free(uv_buffer);
	free(normals_buffer);

    fclose(f);

}


int rafgl_list_init(rafgl_list_t *list, int element_size)
{
    list -> count = 0;
    list -> element_size = element_size;
    list -> head = NULL;
    list -> tail = NULL;
    return 0;
}

int rafgl_list_append(rafgl_list_t *list, void *data)
{
    return rafgl_list_append_sized(list, list -> element_size, data);
}

int rafgl_list_append_sized(rafgl_list_t *list, int size, void *data)
{
    if(list -> head == NULL && list -> tail == NULL)
    {
        list -> head = list -> tail = malloc(sizeof(void*) + size);
        memcpy(list -> tail + sizeof(void*), data, size);
        *((void**)list -> tail) = NULL;
        list -> count++;
    }
    else
    {
        *((void**)list -> tail) = malloc(sizeof(void*) + size);
        list -> tail = *((void**)list -> tail);
        memcpy(list -> tail + sizeof(void*), data, size);
        *((void**)list -> tail) = NULL;
        list -> count++;
    }
    return 0;
}

int rafgl_list_remove(rafgl_list_t *list, int index)
{
    void *target, *i = list -> head;
    if(index >= list -> count) return -1;
    if(index < 0) index = list -> count + index;
    if(index < 0) return -1;

    if(index == 0)
    {
        target = list -> head;
        list -> head = *((void**) list -> head);
    }
    else
    {
        index--;
        while(index--)
        {
            i = *((void**)i);
        }
        target = *((void**)i);
        *((void**)i) = *((void**)(*((void**)i)));

    }
    list -> count--;
    free(target);
    return 0;
}

void* rafgl_list_get(rafgl_list_t *list, int index)
{
    void *i = list -> head;

    if(index >= list -> count) return NULL;
    if(index < 0) index = list -> count + index;
    if(index < 0) return NULL;

    while(index--)
    {
        i = *((void**)i);
    }

    return i + sizeof(void*);
}

int rafgl_list_free(rafgl_list_t *list)
{
    void **i = list -> head;
    void *curr;
    while(i)
    {
        curr = i;
        i = *i;
        free(curr);
    }
    return 0;
}

int rafgl_list_show(rafgl_list_t *list, void (*fun)(void*, int))
{
    void **i = list -> head;
    void *curr_data;
    while(i)
    {
        curr_data = i + 1;
        i = *i;
        fun(curr_data, i == NULL);
    }
    return 0;
}

int rafgl_file_size(const char *filepath)
{
    int size = 0;
    FILE *f = fopen(filepath, "rt");

    fseek(f, 0L, SEEK_END);

    size = ftell(f);

    fclose(f);

    return size;
}

char* rafgl_file_read_content(const char *filepath)
{
    int fsize = rafgl_file_size(filepath);
    FILE *f = fopen(filepath, "rt");

    fseek(f, 0, SEEK_SET);

    char *content = calloc(sizeof(char), fsize + 10);          /* This must later be freed */

    fread(content, 1, fsize, f);

    fclose(f);

    *(content + fsize) = 0;
    return content;
}

GLuint rafgl_program_create_from_source(const char *vertex_source, const char *fragment_source)
{
    GLuint vert, frag, program;
    int success;
    char info_log[512];

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertex_source, NULL);
    glCompileShader(vert);

    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vert, 512, NULL, info_log);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILE_FAILED\n%s\n", info_log);
    }

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragment_source, NULL);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(frag, 512, NULL, info_log);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n%s\n", info_log);
    }


    program = glCreateProgram();

    glAttachShader(program, vert);
    glAttachShader(program, frag);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
    }


    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}

GLuint rafgl_program_create(const char *vertex_source_filepath, const char *fragment_source_filepath)
{
    GLuint program;

    char *vert_source = rafgl_file_read_content(vertex_source_filepath);
    char *frag_source = rafgl_file_read_content(fragment_source_filepath);


    program = rafgl_program_create_from_source(vert_source, frag_source);

    free(vert_source);
    free(frag_source);

    return program;
}

GLuint rafgl_program_create_from_name(const char *program_name)
{
    char v[255], f[255];
    v[0] = 0;
    f[0] = 0;

    strcat(v, "res" SYSTEM_SEPARATOR "shaders" SYSTEM_SEPARATOR);
    strcat(v, program_name);
    strcat(v, SYSTEM_SEPARATOR "vert.glsl");

    strcat(f, "res" SYSTEM_SEPARATOR "shaders" SYSTEM_SEPARATOR);
    strcat(f, program_name);
    strcat(f, SYSTEM_SEPARATOR "frag.glsl");

    return rafgl_program_create(v, f);
}

/*
void test_show(void *element, int last)
{
    vec3f data = *((vec3f*)element);
    vec3f_show(data);
    if(!last) printf(" -> ");
}

int rafgl_list_test(void)
{
    rafgl_list_t list;
    rafgl_list_init(&list, sizeof(vec3f));
    vec3f tmp = vec3f_create(0.0f, 0.0f, 0.0f);

    int i;
    for(i = 0; i < 10; i++)
    {
        tmp.x = i;
        tmp.z = 2.0f * i;
        rafgl_list_append(&list, &tmp);
    }

    rafgl_list_show(&list, test_show);
    rafgl_list_remove(&list, 0);
    rafgl_list_remove(&list, 1);
    rafgl_list_remove(&list, -1);
    rafgl_list_show(&list, test_show);

    rafgl_list_free(&list);

}
*/

#endif // RAFGL_IMPLEMENTATION
#endif // RAFGL_H_INCLUDED
